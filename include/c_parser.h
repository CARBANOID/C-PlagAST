#pragma once
#ifndef C_PARSER_H
#define C_PARSER_H
#include <vector>
#include <string>
#include <memory>
#include "token_types.h"

// AST node type enumeration
typedef enum {
    AST_FUNCTION_DEF = 2,
    AST_PARAM_LIST = 3,
    AST_PARAM = 5,
    AST_DECLARATION = 7,
    AST_INIT_DECLARATOR = 11,
    AST_ASSIGNMENT = 13,
    AST_FUNCTION_PROTOTYPE = 16,
    AST_PREPROCESSOR = 17,
    AST_PLUS = 19,
    AST_MINUS = 23,
    AST_MUL = 29,
    AST_DIV = 31,
    AST_MOD = 37,
    AST_LT = 41,
    AST_GT = 43,
    AST_LE = 47,
    AST_GE = 53,
    AST_EQUALS = 379,
    AST_NOT_EQUALS = 383,
    AST_UNARY_PLUS = 389,
    AST_UNARY_MINUS = 397,
    AST_FUNCTION_CALL = 59,
    AST_FUNCTION_DECLARATOR = 61,
    AST_IDENTIFIER = 67,
    AST_LITERAL = 71,
    AST_NUMBER = 73,
    AST_RETURN = 79,
    AST_IF = 83,
    AST_ITERATION_STMT = 89,
    AST_COMPOUND_STMT = 149,
    AST_ARRAY_ACCESS = 151,
    AST_STRUCT_DECL = 157,
    AST_TYPEDEF = 163,
    AST_INIT_LIST = 167,
    AST_POINTER_DEREF = 173,
    AST_ADDRESS_OF = 179,
    AST_BREAK = 181,
    AST_CONTNUE = 191,
    AST_SIZEOF = 193,
    AST_POINTER = 197,
    AST_TYPE_QUALIFIER = 199,
    AST_TYPE_SPECIFIER = 211,
    AST_FUNCTION_SPECIFIER = 223,
    AST_TRANS = 227,
    AST_LIST = 229,
    AST_BLOCK = 233,
    AST_ALIGNMENT_SPECIFIER = 239,
    AST_STORAGE_CLASS_SPECIFIER = 241,
    AST_DECLARATOR = 251,
    AST_ARRAY_DECLARATOR = 253,
    AST_ENUM = 257,
    AST_TYPE_NAME = 263,
    AST_CONTINUE = 269,
    AST_MEMBER_ACCESS = 271,
    AST_PTR_MEMBER_ACCESS = 277,
    AST_POST_INCREMENT = 281,
    AST_POST_DECREMENT = 282,
    AST_NULL = 283,
    AST_PLUS_ASSIGN = 293,
    AST_MINUS_ASSIGN = 307,
    AST_MUL_ASSIGN = 311,
    AST_DIV_ASSIGN = 313,
    AST_MOD_ASSIGN = 317,
    AST_BIT_AND_ASSIGN = 331,
    AST_BIT_OR_ASSIGN = 337,
    AST_BIT_XOR_ASSIGN = 347,
    AST_SHIFT_LEFT_ASSIGN = 349,
    AST_SHIFT_RIGHT_ASSIGN = 353,
    AST_SWITCH = 359,
    AST_CASE = 367,
    AST_DEFAULT = 373,
    AST_TRANSLATION_UNIT = 401,   
    AST_GOTO_STMT = 409,           
    AST_LABELED_STMT = 419,       
    AST_BIT_NOT = 421,            
    AST_LOGICAL_NOT = 431,         
    AST_SHIFT_LEFT = 433,        
    AST_SHIFT_RIGHT = 439,         
    AST_BIT_AND = 443,            
    AST_BIT_XOR = 449,            
    AST_BIT_OR = 457,              
    AST_LOGICAL_AND = 461,         
    AST_LOGICAL_OR = 463,         
    AST_CONDITIONAL = 467,         
    AST_COMMA = 479,               
    AST_ELSE = 487,              
} ASTNodeType;


class ASTNode {
    public : 
    ASTNodeType type;
    int val;
    std::string value;
    int child_count;
    std::vector<ASTNode*> children;

    ASTNode(ASTNodeType type, int val, const std::string& value, int child_count, const std::vector<ASTNode*>& children){
        this->type = type;
        this->val = val;
        this->value = value;
        this->child_count = child_count;
        this->children = children;
   }
    ~ASTNode(){
        for(ASTNode* child : children) delete child;
    }  
} ;

extern ASTNode *root;

ASTNode *create_ast_node(ASTNodeType type, int n, ...);
ASTNode *create_leaf_node(ASTNodeType type, const char *val);
void print_ast(ASTNode *node, int depth);
void print_ast_side_by_side(ASTNode *originalNode, ASTNode *suspectedNode);
ASTNode* extract_ast_element(ASTNode* node, ASTNodeType target_type, int child_index = -1);
std::string ast_node_type_to_string(ASTNodeType type);
void normalize_ast(ASTNode *node);

void cleanup_redundant_nodes();
void clear_dead_function_tracking();

// Parser functions
void parse_file(const char* filename);
int yyparse(void);

// Lexer functions
void init_lexer(const char* filename);
void close_lexer(void);
void setMoore() ;
int yylex(void);

#endif // C_PARSER_H
