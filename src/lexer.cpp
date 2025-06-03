#include "Moore.hpp"
#include "parser.h"
#include "c_parser.h"
#include "Visualize.hpp"
#include <string.h>
#include <unordered_set>

std::ofstream fout ; // for lexical analysis
std::ifstream *fin = nullptr;

extern YYSTYPE yylval;
extern class ASTNode *root;

int yylineno = 1;
bool printAST = false;
extern "C" int Run_AST_CC(int argc, char **argv);


char* my_strdup(const char* str) {
    if (!str) return nullptr;
    size_t len = strlen(str) + 1;
    char* new_str = new char[len];
    memcpy(new_str, str, len);
    return new_str;
}

void init_lexer(const char* filename) { 
    close_lexer();
    fin = new std::ifstream(filename); 
    if (!fin->is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        exit(1);
    }
    yylineno = 1; 
}

void close_lexer() { 
    if (fin) {
        if (fin->is_open())fin->close();
        delete fin;
        fin = nullptr;
    }
}

void parse_file(const char* filename) {
    std::cout << "Parsing file: " << filename << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    
    init_lexer(filename);  
    int parse_result = yyparse(); 
    close_lexer();  
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Parse time: " << diff.count() << " seconds" << std::endl;
    
    if (parse_result == 0) {
        std::cout << "Parse successful. AST:" << std::endl;
        if (root) {
            std::cout << "Root is not null, printing AST..." << std::endl;
            normalize_ast(root);
            cleanup_redundant_nodes();
 
            if(printAST){
                std::cout << "\n=== AFTER NORMALIZATION ===\n";
                print_ast(root,0);

            std::string dot_file = filename + std::string("_ast.dot");
            
            std::cout << "\n=== Generating AST Visualizations ===\n";
            generate_dot_file(root, dot_file.c_str());
            // export_ast_to_json(root, "ast_tree.json");
            std::cout << "=====================================\n";
            }
        }
        else std::cerr << "Error: AST root is null" << std::endl;
    } 
    else std::cerr << "Parse failed with error code: " << parse_result << std::endl;
}



// yylex for Bison
int yylex() {
    if (fin == nullptr || !fin->is_open()) {
        std::cerr << "Lexer error: No input file open" << std::endl;
        return 0; 
    }
    if(fin->eof()) return 0; // EOF
    token result = search(*fin); 

    // for lexical Analyis
    fout << "Token: " << result.token_name << ", Type: " << result.token_type << ", Code: " << result.token_no << std::endl;

     if (result.token_name.empty()) return yylex(); 
    yylval.sval = my_strdup(result.token_name.c_str());
    
    return result.token_no; 
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " source.c [--debug] [--ast-cc-test [file2.c]]" << std::endl;
        return 1;
    }
    bool ast_cc_test = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--ast-cc-test") == 0) {
            ast_cc_test = true;
            break;
        }
    }
    if (ast_cc_test) {
        Run_AST_CC(argc, argv);
        return 0;
    }
    printAST = (argc > 2 && strcmp(argv[1], "--printAST") == 0); 
    if(printAST) {
        for(int i = 2; i < argc; i++) {
            fout.open(std::string(argv[i]) + "_tokens.txt");
            parse_file(argv[i]);
            fout.close();
        }
    }
    return 0;
} 