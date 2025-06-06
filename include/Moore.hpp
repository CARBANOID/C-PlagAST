#pragma once
#ifndef MOORE_HPP
#define MOORE_HPP
#include <array>
#include <chrono>
#include <string>
#include "C_TOKENS.hpp"
#include <unordered_set>
#include <deque>


extern int yylineno;

class token {
	public:
	std::string token_name;
	std::string token_type;
	TokenTypes::TokenType token_no; // Bison token number
	
	token() : token_name(""), token_type(""), token_no(TokenTypes::TOKEN_EOF) {}
	
	token(std::string token_name, std::string token_type, TokenTypes::TokenType token_no) {
		this->token_name = token_name;
		this->token_type = token_type;
		this->token_no = token_no;	
	}
};

constexpr size_t CHILD_ARRAY_SIZE = 128;

class State {
public :
    char data;
    token token_info ;
    std::array<State*, CHILD_ARRAY_SIZE> childs{};

    explicit State(char data) : data(data) {
        childs.fill(nullptr);
    }

    inline void setTokenInfo(token token_info) {
        this->token_info = token_info;
    }

    inline token getTokenInfo() {
        return token_info;
    }
};

static State* Moore;	
token search(std::ifstream& fin);

// For Handing Dead Code after Return
//------------------------------------
bool return_found = false ; 
bool IsDeadCode = false ;
bool semi = false ; // for single line statements with for,if,while,else,for
std::string conditional = "" ;
//------------------------------------

// For typedef
//------------
int typedefs = 0 ; 
std::unordered_set<std::string> user_defined_types;
static const std::unordered_set<std::string> standard_typedefs = {
    "size_t", "wchar_t", "ptrdiff_t", "max_align_t", "nullptr_t",
    "FILE", "fpos_t", "time_t", "clock_t", "va_list"
};

inline bool IsTypedef(const std::string &type_name) {
    return (user_defined_types.count(type_name) > 0) || (standard_typedefs.count(type_name) > 0);
}

bool Lock = false ;
std::deque<token>LookAheadTokens ; 

void singleLineTypedef(std::ifstream &fin) {
    token tok = search(fin);
    int LastID = -1 ; 

    while(tok.token_no != TokenTypes::SEMICOLON) {
        LookAheadTokens.push_back(tok) ;
        if(tok.token_no == TokenTypes::IDENTIFIER) LastID = LookAheadTokens.size()-1 ; 
        tok = search(fin) ;
    }
    LookAheadTokens.push_back(tok) ;
    user_defined_types.insert(LookAheadTokens[LastID].token_name) ;
}

int op_cl = 0; // brace counter

//-------------


//----Moore seter-----------
void setMoore(){
Lock = semi = return_found = IsDeadCode = false;
op_cl = typedefs = 0 ;
conditional = "" ; 
user_defined_types.clear() ;  
}
// ----------------------------



inline bool skip_preprocessor_directive(std::ifstream &fin, std::string &directive) {
    directive = "#";
    fin.get();
    char ch;
    while(fin.good() && (ch = fin.peek()) != EOF && ch != '\n') {
        if(!isspace(ch)) directive += ch;
        fin.get();
    } 
    return true;
} 


inline bool isEscapeSequence(char ch) {
	int val = ch ;
    return ((val >= 7 && val <= 13) || val == 0 || val == 92) ? true : false ;
}

inline token string_literal(std::ifstream &fin) {
	std::string str = "";
	str.push_back('"');
	fin.get(); // consume the opening quote
	
	char ch;
	while ((ch = fin.get()) != EOF) {
		if (ch == '"') {
			break; // Found the closing quote
		} else if (ch == '\\') {
			char next = fin.get();
			if (next != EOF) {
				str.push_back('\\');
				str.push_back(next);
			}
		} else {
			str.push_back(ch);
		}
	}
	str.push_back('"');
	return token(str, "STRING_LITERAL", TokenTypes::STRING_LITERAL);
}

inline token numeric_literal(std::ifstream &fin) {
    std::string num = "";
    std::string token_type ;
    
    char ch = fin.get();
    bool isOctal = false ;
    if(ch == '0') isOctal = true ;

    num += ch;
    ch = fin.peek();
    
    if (ch == 'x' || ch == 'X') {
        token_type = "HEX_LITERAL";
        isOctal = false ;
        num += ch;
        fin.get();
    } 
    else if (ch == 'b' || ch == 'B') {
        token_type = "BINARY_LITERAL";
        isOctal = false ;
        num += ch;
        fin.get();
    }  

    while (true) {
        ch = fin.peek();
        if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f') || ch == '.') {
            if(isOctal && !(ch >= '0' && ch <='7')) isOctal = false ;      
            num += ch;
            fin.get();
            if(ch == '.') token_type = "FLOAT_LITERAL";
            else if(ch == 'E' || ch == 'e'){
                ch = fin.peek();
                if(ch == '+' || ch == '-') { num += ch; fin.get(); }
            }
        } 
        else break;
    }

   while (true) {
        ch = fin.peek();
        if (ch == 'U' || ch == 'u' || ch == 'L' || ch == 'l' || ch == 'F' || ch == 'f') {
            fin.get(); // ignore the suffix character
        } else break;
    }

    // ignore 0x,0X,0b,0B prefixes
    if(token_type[0] == 'H') num = std::to_string(std::stol(num.substr(2), nullptr, 16));
    else if(token_type[0] == 'B') num = std::to_string(std::stol(num.substr(2), nullptr, 2));
    else if(isOctal) num = std::to_string(std::stol(num, nullptr, 8));

    token_type = "DECIMAL";
    return token(num,token_type,TokenTypes::NUMBER);
}

inline token search(std::ifstream& fin) ;

void skip_dead_code_after_return(std::ifstream &fin,int &op){
    while(fin.good() && !fin.eof()) {
        token tok = search(fin) ;
        if(tok.token_no == TokenTypes::RBRACE && op == 0) break ;
        if(tok.token_no == TokenTypes::LBRACE) op++ ;
        else if(tok.token_no == TokenTypes::RBRACE) op-- ;
    }
}   

inline token search(std::ifstream& fin) {

    if(!Lock && !LookAheadTokens.empty()){
        token& tok = LookAheadTokens.front();
        LookAheadTokens.pop_front();
        return tok;
    }

    if(fin.eof()) return token("", "", TokenTypes::TOKEN_EOF) ;

    char ch;
    while (fin.good()) {
        ch = fin.peek();  
        if (ch == '\n' || ch == ' ' || isEscapeSequence(ch)) {
            if(ch == '\n') yylineno++;
            fin.get();
        } else break;
    }

    ch = fin.peek();
    std::string str;
    	
    if (ch == '#') {
        std::string directive;
        skip_preprocessor_directive(fin, directive);
        if (fin.peek() == '\n') {
            fin.get();
            yylineno++;
        }
        return token(directive, "PREPROCESSOR", TokenTypes::PREPROCESSOR);
    }
    
    if (ch >= '0' && ch <= '9') return numeric_literal(fin);
    else if(ch == '"') return string_literal(fin) ;
    else if(ch == char(39)){ // character literal
        fin.get(); 
        str.push_back(char(39)); 
        ch = fin.peek(); 
        while(ch != char(39) && ch != EOF) {
            str.push_back(fin.get()); 
            ch = fin.peek();
        }
        if(ch == char(39)) {
            str.push_back(char(39)); 
            fin.get(); 
        }
        return token(str, "CHAR_LITERAL", TokenTypes::CHAR_LITERAL);
    }

    State* curr = Moore;
    while (ch != EOF && curr->childs[ch]) {
        str.push_back(ch);
        curr = curr->childs[ch];
        fin.get();
        ch = fin.peek();
    }

    if (curr->token_info.token_type.empty() || curr->token_info.token_type == "KEYWORD") {
	    if (ch == ' ' || ch == EOF || isEscapeSequence(ch) || !(isalnum(ch) || ch == '_')) {
	    	if(curr->token_info.token_type == "KEYWORD") {
                if(!IsDeadCode){
                    if(str == "typedef") {  // Handle typedefs and type definitions
                        Lock = true ;
                        token tok = search(fin) ; LookAheadTokens.push_back(tok) ;
                        if(tok.token_no == TokenTypes::STRUCT || tok.token_no == TokenTypes::UNION || tok.token_no == TokenTypes::ENUM){
                            tok = search(fin) ; LookAheadTokens.push_back(tok) ;
                            if(tok.token_no == TokenTypes::LBRACE){ op_cl++ , typedefs++ ; }
                            else{
                            tok = search(fin) ; LookAheadTokens.push_back(tok) ;
                            if(tok.token_no == TokenTypes::LBRACE) { op_cl++ , typedefs++ ; }
                            else if(tok.token_no == TokenTypes::IDENTIFIER){
                                user_defined_types.insert(tok.token_name) ;
                            }
                            else singleLineTypedef(fin) ;
                            }
                        }
                        else singleLineTypedef(fin) ;   
                        Lock = false ;
                    }
                    else if(str == "return" || str == "break") return_found = true ;
                    else if(str == "for" || str == "if" || str == "while" || str == "else" || str == "do" || str == "case"){
                        conditional = str ; 
                        semi = true ;
                    }
                    else conditional = "" ;
                }
	    		return curr->getTokenInfo();
	    	}
		}

	    while ((ch = fin.peek()) != EOF) {
		 	if(((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch =='_') || (ch >= '0' && ch <= '9'))){
	            str.push_back(ch);
	        	fin.get();
	        } else break;
	    }

        if (IsTypedef(str)) return token(str, "TYPEDEF_NAME", TokenTypes::TYPEDEF_NAME);
 	    return token(str,"ID",TokenTypes::IDENTIFIER);
	}	

    if(curr->token_info.token_type == "COMMENT"){
        if(str[1] == '/'){
            while(ch != EOF && ch != '\n') {
                ch = fin.get();
            }
            if(ch == '\n') yylineno++;
        }
        else { 
            while(true){ 
                ch = fin.get(); 
                if(ch == '*'){
                    ch = fin.get(); 
                    if(ch == '/') break;    
                }
                else if(ch == '\n') yylineno++; 
            }
        }
        return token("", "", TokenTypes::TOKEN_EOF);
    }    

    if(str == "{") semi = false ;  // for dead code after retun


    if(typedefs && str == "}"){ // for struct/enum/union typedefs
        if(op_cl == typedefs){
            Lock = true ;
            while(true){
                token tok = search(fin) ;
                LookAheadTokens.push_back(tok) ; 
                if(tok.token_no == TokenTypes::IDENTIFIER){ 
                    user_defined_types.insert(tok.token_name) ;
                }
                else if(tok.token_no == TokenTypes::SEMICOLON) break  ;       
            }
            op_cl-- ; typedefs-- ;  
            Lock = false ;
        }
        else op_cl-- ;
    }
    else if(!IsDeadCode && (return_found && str == ";")){ // for dead code after return/break normalization 
        if(conditional!= "case" && (!semi || conditional == "")){
            int op = 0 ;    
            if(conditional == "else") op = 1 ;
        
            IsDeadCode = true ; 
            return_found = false ;
            skip_dead_code_after_return(fin,op) ; 

            if(conditional == "else") LookAheadTokens.push_back(token("RCURLY", "RBRACE", TokenTypes::RBRACE));
            IsDeadCode = false ;
            fin.seekg(-1, std::ios::cur) ; 
        }
        else return_found = false ;
    }
    return curr->token_info;
}

inline void insertTokensInMoore() {
    for(auto &tok : TOKENS){
        std::string token_type = tok.first ; 
        for(auto &data : *tok.second){
            std::string lexeme_name = data.lexeme_name ; 
            State* curr = Moore;
            for (char ch : lexeme_name) {
                if (!curr->childs[ch]) {
                    curr->childs[ch] = new State(ch);
                }
                curr = curr->childs[ch];
            }
            curr->setTokenInfo(token(data.token_name,token_type,data.token_no));
        }
    }
}

struct MooreInitializer {
    MooreInitializer() {
	    auto start = std::chrono::high_resolution_clock::now();
	    Moore = new State('\0');
        define_tokens() ;
	    insertTokensInMoore();
	    auto end = std::chrono::high_resolution_clock::now();
	    std::chrono::duration<double> elapsed = end - start;
	    std::cout << "Moore Machine Creation Time: " << elapsed.count() << " seconds" << std::endl;
    }
};

static MooreInitializer  mooreInitializer ;
#endif
