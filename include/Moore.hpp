#pragma once
#ifndef MOORE_HPP
#define MOORE_HPP
#include <array>
#include <chrono>
#include <string>
#include "C_TOKENS.hpp"
#include <unordered_set>
#include <stack>


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

struct TypedefInfo {
    std::string name;
    std::string baseType;
    bool is_seu ; // struct/enum/union
    bool isPointer;
};

// For Handing Dead Code after Return
//------------------------------------
bool return_found = false ; 
bool IsDeadCode = false ;
bool semi = false ; // for single line statements with for,if,while,else,for
bool rbrace = false ;
std::string conditional = "" ;
//------------------------------------

// For typedef
//------------
std::unordered_set<std::string> user_defined_types;
std::stack<std::string> current_type_stack;
bool IsUserDefinedType = false;
bool InTypedefDeclaration = false;
int seu = 0; // struct/enum/union counter
int op_cl = 0; // brace counter
//-------------


//----Moore seter-----------
void setMoore(){
semi = return_found = rbrace = IsDeadCode = IsUserDefinedType = InTypedefDeclaration = false;
seu = op_cl = 0 ;
conditional = "" ; 
user_defined_types.clear() ;  
while(!current_type_stack.empty()) current_type_stack.pop() ;
}
// ----------------------------

static const std::unordered_set<std::string> standard_typedefs = {
    "size_t", "wchar_t", "ptrdiff_t", "max_align_t", "nullptr_t",
    "FILE", "fpos_t", "time_t", "clock_t", "va_list"
};

inline bool IsTypedef(const std::string &type_name) {
    return (user_defined_types.count(type_name) > 0) || (standard_typedefs.count(type_name) > 0);
}

inline void process_typedef_declaration(std::ifstream &fin, const std::string &identifier) {
    int pos = fin.tellg();
    std::string temp;
    TypedefInfo info;
    info.name = identifier;
    
    if (!current_type_stack.empty()) {
        info.baseType = current_type_stack.top();
        current_type_stack.pop();
    } else info.baseType = "unknown";
    
    info.is_seu = (seu > 0);
    fin >> temp;
    info.isPointer = (temp.find('*') != std::string::npos);
    user_defined_types.insert(identifier);    
    fin.seekg(pos);
}


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
    if(rbrace){
        rbrace = false;
        return token("}", "RBRACE", TokenTypes::RBRACE);
    }

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
                // Handle typedefs and type definitions
                if(!IsDeadCode){
                    if(str == "typedef") {
                        InTypedefDeclaration = true;
                        IsUserDefinedType = true;
                    } 
                    else if(IsUserDefinedType) {
                        if(str == "struct" || str == "union" || str == "enum") {
                            seu++;
                            current_type_stack.push(str);
                        } 
                        else if (str == "int" || str == "char" || str == "float" || 
                                str == "double" || str == "void" || str == "short" || 
                                str == "long" || str == "signed" || str == "unsigned") {
                            current_type_stack.push(str);
                        }
                    }
                    else if(str == "return" || str == "break") return_found = true ;
                    else if(str == "for" || str == "if" || str == "while" || str == "else" || str == "do" || str == "case"){
                        conditional = str ; 
                        semi = true ;
                    }else conditional = "" ;
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

        if(InTypedefDeclaration && op_cl == 0) {
            int pos = fin.tellg();
            std::string temp = "";
            
            if(seu == 0) {   // Regular typedef (not struct/enum/union)
                while(true) {
                    fin >> temp;
                    if(temp == ";") {
                        InTypedefDeclaration = false;
                        IsUserDefinedType = false;
                        break;
                    } 
                    else if(temp == ",") continue;
                    else process_typedef_declaration(fin, temp); 
                }
            } else if(seu == 1) { // Typedef for struct/enum/union
                fin >> temp;
                if(temp == ";") {
                    process_typedef_declaration(fin, str);
                    InTypedefDeclaration = false;
                    IsUserDefinedType = false;
                }
            }
            fin.seekg(pos);
        }
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

    if(seu){        //  for typedefs hanlding 
        if(str == "{") op_cl++;
        else if(str == "}") { 
            op_cl--; 
            seu--;
        }
    }
    else if(!IsDeadCode && (return_found && str == ";")){ // for dead code after return normalization 
        if(conditional!= "case" && (!semi || conditional == "")){
            int op = 0 ;    
            if(conditional == "else") op = 1 ;
        
            IsDeadCode = true ; 
            return_found = false ;
            skip_dead_code_after_return(fin,op) ; 

            if(conditional == "else") rbrace = true ;
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