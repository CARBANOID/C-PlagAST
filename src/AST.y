%{
#define YYDEBUG 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unordered_set>
#include <string>
#define BISON_PARSER
#include "token_types.h"
#include "c_parser.h"

#define makelist(x) create_ast_node(AST_LIST, 1, x)
#define makelist_leaf(x) create_leaf_node(AST_LIST, x)
#define append_list(x1, x2) ((x1 && x2) ? create_ast_node(AST_LIST, 2, x1, x2) : (x1) ? x1 : (class ASTNode *)NULL)

// Global tracking for dead functions - grammar-level optimization
static std::unordered_set<std::string> dead_function_names;

// Helper function to add dead function name
inline void add_dead_function(const char* name) {
    if (name && strlen(name) > 0) {
        dead_function_names.insert(std::string(name));
    }
}

// Helper function to check if function call is dead
inline bool is_dead_function_call(const char* name) {
    if (!name) return false;
    return dead_function_names.find(std::string(name)) != dead_function_names.end();
}

// Helper function to check if a condition is always false (literal 0)
inline bool is_always_false_condition(ASTNode* condition) {
    if (!condition) return false;
    if (condition->type == AST_NUMBER) {
        return (strcmp(condition->value.c_str(), "0") == 0);
    }
    return false;
}

// Helper function to check if a statement is empty (NULL or empty block)
inline bool is_empty_statement(ASTNode* statement) {
    if (!statement) return true;
    if (statement->type == AST_COMPOUND_STMT || statement->type == AST_BLOCK) {
        return (statement->child_count == 0);
    }
    if (statement->type == AST_LIST && statement->child_count == 0) {
        return true;
    }
    return false;
}

// Enhanced helper to check if expression is always true (literal 1)
inline bool is_always_true_condition(ASTNode* condition) {
    if (!condition) return false;
    if (condition->type == AST_NUMBER) {
        return (strcmp(condition->value.c_str(), "1") == 0 || 
                strcmp(condition->value.c_str(), "true") == 0);
    }
    return false;
}

void clear_dead_function_tracking() {
    dead_function_names.clear();
}

extern ASTNode *root;
extern ASTNode* extract_ast_element(ASTNode* node, ASTNodeType target_type, int child_index);
extern bool is_function_prototype(ASTNode *node);

extern int yylex(void);
extern void yyerror(const char *s);
%}

/* Use YYSTYPE from token_types.h */

/* Token declarations */

%token PREPROCESSOR
%token IDENTIFIER NUMBER CHAR_LITERAL STRING_LITERAL TYPEDEF_NAME
%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token VOID CHAR SHORT INT LONG FLOAT DOUBLE SIGNED UNSIGNED BOOL
%token STRUCT UNION ENUM
%token CONST RESTRICT VOLATILE
%token INLINE NORETURN ALIGNAS SIZEOF ELLIPSIS
%token LPAREN RPAREN LSQBRACKET RSQBRACKET LBRACE RBRACE
%token SEMICOLON COMMA COLON DOT ARROW QUESTION
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token SHIFT_LEFT_ASSIGN SHIFT_RIGHT_ASSIGN BIT_AND_ASSIGN BIT_XOR_ASSIGN BIT_OR_ASSIGN
%token OR AND BIT_OR BIT_AND BIT_XOR XOR NOT BIT_NOT
%token EQUAL NOT_EQUAL LESS GREATER LESS_EQUAL GREATER_EQUAL
%token SHIFT_LEFT SHIFT_RIGHT PLUS MINUS MULTIPLY DIVIDE MODULO
%token IF ELSE WHILE GOTO BREAK CONTINUE FOR SWITCH CASE DEFAULT DO
%token INCREMENT DECREMENT
%token RETURN
%define parse.error verbose
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%type <node> translation_unit external_declaration function_definition declaration declaration_list statement block_item type_qualifier_list compound_statement non_empty_block_item_list declaration_specifiers declarator init_declarator_list init_declarator initializer alignment_specifier pointer type_name direct_declarator storage_class_specifier type_specifier  type_qualifier function_specifier struct_or_union_specifier enum_specifier specifier_qualifier_list struct_declaration_list struct_declaration struct_declarator_list struct_declarator parameter_type_list parameter_list parameter_declaration abstract_declarator direct_abstract_declarator initializer_list expression_statement iteration_statement conditional_statement selection_statement jump_statement switch_statement labeled_statement expression assignment_expression constant_expression primary_expression postfix_expression argument_expression_list unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression conditional_expression enumeration_constant enumerator_list unary_operator expression_opt

%type <sval> PREPROCESSOR CONST RESTRICT VOLATILE TYPEDEF EXTERN STATIC AUTO REGISTER VOID CHAR SHORT INT LONG FLOAT DOUBLE SIGNED UNSIGNED BOOL INLINE NORETURN TYPEDEF_NAME IDENTIFIER NUMBER CHAR_LITERAL STRING_LITERAL

%start translation_unit

%%


translation_unit
    : external_declaration { root = $1; $$ = $1; }
    | translation_unit external_declaration { 
            $$ = create_ast_node(AST_TRANSLATION_UNIT, 2, $1, $2);
            root = $$; 
        }
    ;

external_declaration
    : function_definition { $$ = $1; }
    | declaration { $$ = $1; }
    | PREPROCESSOR {
         $$ = NULL ;  /* For Preprocessor normalization*/
        /* $$ = create_leaf_node(AST_PREPROCESSOR, $1); */
    }
    ;

/* Helper lists */
declaration_list
    : declaration { $$ = makelist($1); }
    | declaration_list declaration { $$ = append_list($1, $2); }
    ;

block_item
    : declaration { $$ = $1; }
    | statement { $$ = $1; }
    | function_definition { $$ = $1; }
    ;

/* Type qualifiers */
type_qualifier_list
    : type_qualifier { $$ = makelist($1); }
    | type_qualifier_list type_qualifier { $$ = append_list($1, $2); }
    ;

/* Compound blocks - Grammar-level empty structure normalization */
compound_statement
    : LBRACE RBRACE { $$ = NULL; /* Empty blocks normalized to NULL at grammar level */ }
    | LBRACE non_empty_block_item_list RBRACE { $$ = create_ast_node(AST_COMPOUND_STMT, 1, $2); }
    ;

non_empty_block_item_list
    : block_item { $$ = makelist($1); }
    | non_empty_block_item_list block_item { $$ = append_list($1, $2); } 
    ;

/* Declarations & definitions */
function_definition
    : declaration_specifiers declarator declaration_list compound_statement 
        { 
            // Grammar-level dead function elimination
            if ($4 == NULL) {
                // Empty function body - track as dead and return NULL
                ASTNode *function_name = extract_ast_element($2, AST_IDENTIFIER, 0);
                if (function_name && function_name->value.c_str()) {
                    add_dead_function(function_name->value.c_str());
                }
                $$ = NULL; /* Dead function eliminated at grammar level */
            } else {
                // Extract the function name from the declarator
                ASTNode *function_name = extract_ast_element($2, AST_IDENTIFIER, 0);
                // Extract the parameter list from the declarator
                ASTNode *param_list = extract_ast_element($2, AST_PARAM_LIST, 0);
                $$ = create_ast_node(AST_FUNCTION_DEF, 5, $1, function_name, param_list, $3, $4);
            }
        }
    | declaration_specifiers declarator compound_statement
        { 
            // Grammar-level dead function elimination
            if ($3 == NULL) {
                // Empty function body - track as dead and return NULL
                ASTNode *function_name = extract_ast_element($2, AST_IDENTIFIER, 0);
                if (function_name && function_name->value.c_str()) {
                    add_dead_function(function_name->value.c_str());
                }
                $$ = NULL; /* Dead function eliminated at grammar level */
            } else {
                // Extract the function name from the declarator
                ASTNode *function_name = extract_ast_element($2, AST_IDENTIFIER, 0);
                // Extract the parameter list from the declarator
                ASTNode *param_list = extract_ast_element($2, AST_PARAM_LIST, 0);
                $$ = create_ast_node(AST_FUNCTION_DEF, 4, $1, function_name, param_list, $3);
            }
        }
    ;

declaration
    : declaration_specifiers SEMICOLON { $$ = create_ast_node(AST_DECLARATION, 1, $1); }
    | declaration_specifiers init_declarator_list SEMICOLON { 
        if (is_function_prototype($2)){
            $$ = NULL ;  /* for AST Normalization */
            /*  $$ = create_ast_node(AST_FUNCTION_PROTOTYPE, 2, $1, $2); */
        }
         else $$ = create_ast_node(AST_DECLARATION, 2, $1, $2);
    }
    ;

init_declarator_list
    : init_declarator { $$ = makelist($1); }
    | init_declarator_list COMMA init_declarator { $$ = append_list($1, $3); }
    ;

init_declarator 
    : declarator ASSIGN initializer { $$ = create_ast_node(AST_INIT_DECLARATOR, 2, $1, $3); }
    | declarator { $$ = $1; }
    ;

declaration_specifiers
    : storage_class_specifier { $$ = makelist($1); }
    | type_specifier { $$ = makelist($1); }
    | type_qualifier { $$ = makelist($1); }
    | function_specifier { $$ = makelist($1); }
    | alignment_specifier { $$ = makelist($1); }
    | declaration_specifiers storage_class_specifier { $$ = append_list($1, $2); }
    | declaration_specifiers type_specifier { $$ = append_list($1, $2); }
    | declaration_specifiers type_qualifier { $$ = append_list($1, $2); }
    | declaration_specifiers function_specifier { $$ = append_list($1, $2); }
    | declaration_specifiers alignment_specifier { $$ = append_list($1, $2); }
    ;

storage_class_specifier
    : TYPEDEF { $$ = create_leaf_node(AST_STORAGE_CLASS_SPECIFIER, "typedef"); }
    | EXTERN { $$ = create_leaf_node(AST_STORAGE_CLASS_SPECIFIER, "extern"); }
    | STATIC { $$ = create_leaf_node(AST_STORAGE_CLASS_SPECIFIER, "static"); }
    | AUTO { $$ = create_leaf_node(AST_STORAGE_CLASS_SPECIFIER, "auto"); }
    | REGISTER { $$ = create_leaf_node(AST_STORAGE_CLASS_SPECIFIER, "register"); }
    ;

type_specifier
    : VOID { $$ = create_leaf_node(AST_TYPE_SPECIFIER, "void"); }
    | CHAR { $$ = create_leaf_node(AST_TYPE_SPECIFIER, "char"); }
    | SHORT { $$ = create_leaf_node(AST_TYPE_SPECIFIER, "short"); }
    | INT { $$ = create_leaf_node(AST_TYPE_SPECIFIER, "int"); }
    | LONG { $$ = create_leaf_node(AST_TYPE_SPECIFIER, "long"); }
    | FLOAT { $$ = create_leaf_node(AST_TYPE_SPECIFIER, "float"); }
    | DOUBLE { $$ = create_leaf_node(AST_TYPE_SPECIFIER, "double"); }
    | SIGNED { $$ = create_leaf_node(AST_TYPE_SPECIFIER, "signed"); }
    | UNSIGNED { $$ = create_leaf_node(AST_TYPE_SPECIFIER, "unsigned"); }
    | BOOL { $$ = create_leaf_node(AST_TYPE_SPECIFIER, "bool"); }
    | struct_or_union_specifier { $$ = $1; }
    | enum_specifier { $$ = $1; }
    | TYPEDEF_NAME { $$ = create_leaf_node(AST_TYPE_SPECIFIER, $1); }
    ;

type_qualifier
    : CONST { $$ = create_leaf_node(AST_TYPE_QUALIFIER, "const"); }
    | RESTRICT { $$ = create_leaf_node(AST_TYPE_QUALIFIER, "restrict"); }
    | VOLATILE { $$ = create_leaf_node(AST_TYPE_QUALIFIER, "volatile"); }
    ;

function_specifier
    : INLINE { $$ = create_leaf_node(AST_FUNCTION_SPECIFIER, "inline"); }
    | NORETURN { $$ = create_leaf_node(AST_FUNCTION_SPECIFIER, "noreturn"); }
    ;

alignment_specifier
    : ALIGNAS LPAREN type_name RPAREN { $$ = create_ast_node(AST_ALIGNMENT_SPECIFIER, 1, $3); }
    | ALIGNAS LPAREN constant_expression RPAREN { 
           $$ = create_ast_node(AST_ALIGNMENT_SPECIFIER, 1, $3); 
        }
    ;

/* Declarator rules */
declarator
    : pointer direct_declarator { $$ = create_ast_node(AST_DECLARATOR, 2, $1, $2); }
    | direct_declarator { $$ = create_ast_node(AST_DECLARATOR, 1, $1); }
    ;

pointer
    : MULTIPLY { $$ = create_ast_node(AST_POINTER, 1, NULL);}
    | MULTIPLY type_qualifier_list { $$ = create_ast_node(AST_POINTER, 1, $2);}
    | MULTIPLY pointer { $$ = create_ast_node(AST_POINTER, 1, $2); }
    | MULTIPLY type_qualifier_list pointer { $$ = create_ast_node(AST_POINTER, 2, $2, $3); }
    ;

direct_declarator
    : IDENTIFIER { $$ = create_leaf_node(AST_IDENTIFIER, $1); }
    | LPAREN declarator RPAREN { $$ = $2; }
    | direct_declarator LSQBRACKET RSQBRACKET { $$ = create_ast_node(AST_ARRAY_ACCESS, 1, $1); }
    | direct_declarator LSQBRACKET assignment_expression RSQBRACKET { $$ = create_ast_node(AST_ARRAY_ACCESS, 2, $1, $3); }
    | direct_declarator LPAREN RPAREN { $$ = create_ast_node(AST_FUNCTION_DECLARATOR, 1, $1); }
    | direct_declarator LPAREN argument_expression_list RPAREN  { $$ = create_ast_node(AST_FUNCTION_CALL, 2, $1, $3); }
    | direct_declarator LPAREN parameter_type_list RPAREN  { $$ = create_ast_node(AST_FUNCTION_DECLARATOR, 2, $1, $3); }
    ;

struct_or_union_specifier
    : STRUCT LBRACE RBRACE { $$ = NULL; /* Empty struct normalized to NULL at grammar level */ }
    | STRUCT LBRACE struct_declaration_list RBRACE { $$ = create_ast_node(AST_STRUCT_DECL, 1, $3); }
    | STRUCT IDENTIFIER LBRACE RBRACE { $$ = NULL; /* Empty named struct normalized to NULL at grammar level */ }
    | STRUCT IDENTIFIER LBRACE struct_declaration_list RBRACE { $$ = create_ast_node(AST_STRUCT_DECL, 2, create_leaf_node(AST_IDENTIFIER, $2), $4); }
    | STRUCT IDENTIFIER { $$ = create_ast_node(AST_STRUCT_DECL, 1, create_leaf_node(AST_IDENTIFIER, $2)); }
    | UNION LBRACE RBRACE { $$ = NULL; /* Empty union normalized to NULL at grammar level */ }
    | UNION LBRACE struct_declaration_list RBRACE { $$ = create_ast_node(AST_STRUCT_DECL, 1, $3); }
    | UNION IDENTIFIER LBRACE RBRACE { $$ = NULL; /* Empty named union normalized to NULL at grammar level */ }
    | UNION IDENTIFIER LBRACE struct_declaration_list RBRACE { $$ = create_ast_node(AST_STRUCT_DECL, 2, create_leaf_node(AST_IDENTIFIER, $2), $4); }
    | UNION IDENTIFIER { $$ = create_ast_node(AST_STRUCT_DECL, 1, create_leaf_node(AST_IDENTIFIER, $2)); }
    ;

struct_declaration_list
    : struct_declaration { $$ = makelist($1); }
    | struct_declaration_list struct_declaration { $$ = append_list($1, $2); }
    ;

struct_declaration
    : specifier_qualifier_list SEMICOLON { $$ = $1; }
    | specifier_qualifier_list struct_declarator_list SEMICOLON { $$ = create_ast_node(AST_DECLARATION, 2, $1, $2); }
    ;

specifier_qualifier_list
    : type_specifier { $$ = $1; }
    | type_specifier specifier_qualifier_list { $$ = append_list($1, $2); }
    | type_qualifier { $$ = $1; }
    | type_qualifier specifier_qualifier_list { $$ = append_list($1, $2); }
    | alignment_specifier { $$ = $1; }
    | alignment_specifier specifier_qualifier_list { $$ = append_list($1, $2); }
    ;

struct_declarator_list
    : struct_declarator { $$ = makelist($1); }
    | struct_declarator_list COMMA struct_declarator { $$ = append_list($1, $3); }
    ;

struct_declarator
    : declarator { $$ = $1; }
    | declarator COLON constant_expression { $$ = create_ast_node(AST_DECLARATOR, 2, $1, $3); }
    | COLON constant_expression { $$ = create_ast_node(AST_DECLARATOR, 1, $2); }
    ;

enum_specifier
    : ENUM LBRACE RBRACE { $$ = NULL; /* Empty enum normalized to NULL at grammar level */ }
    | ENUM LBRACE enumerator_list RBRACE { $$ = create_ast_node(AST_ENUM, 1, $3); }
    | ENUM IDENTIFIER LBRACE RBRACE { $$ = NULL; /* Empty named enum normalized to NULL at grammar level */ }
    | ENUM IDENTIFIER LBRACE enumerator_list RBRACE { $$ = create_ast_node(AST_ENUM, 2, create_leaf_node(AST_IDENTIFIER, $2), $4); }
    | ENUM IDENTIFIER { $$ = create_ast_node(AST_ENUM, 1, create_leaf_node(AST_IDENTIFIER, $2)); }
    ;

enumerator_list
    : enumeration_constant { $$ = makelist($1); }
    | enumerator_list COMMA enumeration_constant { $$ = append_list($1, $3); }
    ;

enumeration_constant
    : IDENTIFIER { $$ = create_leaf_node(AST_IDENTIFIER, $1); }
    ;

type_name
    : specifier_qualifier_list { $$ = $1; }
    | specifier_qualifier_list abstract_declarator { $$ = create_ast_node(AST_TYPE_NAME, 2, $1, $2); }
    ;

abstract_declarator
    : pointer { $$ = $1; }
    | pointer direct_abstract_declarator { $$ = create_ast_node(AST_DECLARATOR, 2, $1, $2); }
    | direct_abstract_declarator { $$ = $1; }
    ;

direct_abstract_declarator
    : LPAREN abstract_declarator RPAREN { $$ = $2; }
    | LSQBRACKET RSQBRACKET { $$ = create_ast_node(AST_ARRAY_ACCESS, 0); }
    | LSQBRACKET type_qualifier_list assignment_expression RSQBRACKET { $$ = create_ast_node(AST_ARRAY_ACCESS, 2, $2, $3); }
    | direct_abstract_declarator LSQBRACKET assignment_expression RSQBRACKET { $$ = create_ast_node(AST_ARRAY_ACCESS, 2, $1, $3); }
    | LPAREN parameter_type_list RPAREN { $$ = create_ast_node(AST_FUNCTION_DECLARATOR, 1, $2); }
    | direct_abstract_declarator LPAREN parameter_type_list RPAREN { $$ = create_ast_node(AST_FUNCTION_DECLARATOR, 2, $1, $3); }
    ;

parameter_type_list
    : parameter_list { $$ = create_ast_node(AST_PARAM_LIST, 1, $1); }
    | parameter_list COMMA ELLIPSIS { $$ = create_ast_node(AST_PARAM_LIST, 2, $1, create_leaf_node(AST_IDENTIFIER, "...")); }
    ;

parameter_list
    : parameter_declaration { $$ = makelist($1); }
    | parameter_list COMMA parameter_declaration { $$ = append_list($1, $3); }
    ;

parameter_declaration
    : declaration_specifiers declarator { $$ = create_ast_node(AST_PARAM, 2, $1, $2); }
    | declaration_specifiers abstract_declarator { $$ = create_ast_node(AST_PARAM, 2, $1, $2); }
    | declaration_specifiers { $$ = $1; }
    ;

initializer
    : assignment_expression { $$ = $1; }
    | LBRACE initializer_list RBRACE { $$ = create_ast_node(AST_INIT_LIST, 1, $2); }
    | LBRACE initializer_list COMMA RBRACE { $$ = create_ast_node(AST_INIT_LIST, 1, $2); }
    ;

initializer_list
    : initializer { $$ = makelist($1); }
    | initializer_list COMMA initializer { $$ = append_list($1, $3); }
    ;

/* Enhanced statement handling with comprehensive selection and jump statement support */
statement
    : expression_statement { $$ = $1; }
    | selection_statement { $$ = $1; }
    | iteration_statement { $$ = $1; }
    | jump_statement { $$ = $1; }
    | compound_statement { $$ = $1; }
    | labeled_statement { $$ = $1; }
    ;

/* Comprehensive selection statement covering all conditional constructs */
selection_statement
    : conditional_statement { $$ = $1; }
    | switch_statement { $$ = $1; }
    ;

/* Enhanced jump statement handling with grammar-level optimizations */
jump_statement
    : RETURN expression SEMICOLON { $$ = create_ast_node(AST_RETURN, 1, $2); }
    | RETURN SEMICOLON { $$ = create_ast_node(AST_RETURN, 0); }
    | BREAK SEMICOLON { $$ = create_ast_node(AST_BREAK, 0); }
    | CONTINUE SEMICOLON { $$ = create_ast_node(AST_CONTINUE, 0); }    
    | GOTO IDENTIFIER SEMICOLON { 
        $$ = create_ast_node(AST_GOTO_STMT, 1, create_leaf_node(AST_IDENTIFIER, $2)); 
    }
    ;

iteration_statement
    : DO statement WHILE LPAREN expression RPAREN SEMICOLON { 
        // Grammar-level dead loop elimination: empty body or always-false condition
        if (is_empty_statement($2) || is_always_false_condition($5)) {
            $$ = NULL; /* Dead do-while loop eliminated at grammar level */
        } else {
            $$ = create_ast_node(AST_ITERATION_STMT, 2, $2, $5);
        }
    }
    | WHILE LPAREN expression RPAREN statement { 
        // Grammar-level dead loop elimination: always-false condition or empty body
        if (is_always_false_condition($3) || is_empty_statement($5)) {
            $$ = NULL; /* Dead while loop eliminated at grammar level */
        } else {
            $$ = create_ast_node(AST_ITERATION_STMT, 2, $3, $5);
        }
    }
    | FOR LPAREN type_specifier expression_statement expression_statement expression_opt RPAREN statement { 
        // Grammar-level dead loop elimination: always-false condition or empty body
        if (is_always_false_condition($5) || is_empty_statement($8)) {
            $$ = NULL; /* Dead for loop eliminated at grammar level */
        } else {
            $$ = create_ast_node(AST_ITERATION_STMT, 4, $4, $5, $6, $8);
        }
    }
    ;

/* Enhanced conditional statement with grammar-level optimizations */
conditional_statement
    : IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE { 
        /* Grammar-level condition optimization */
        if (is_always_false_condition($3)) {
            $$ = NULL; /* Always-false if eliminated */
        } else if (is_empty_statement($5)) {
            $$ = NULL; /* If with empty body eliminated */
        } else {
            $$ = create_ast_node(AST_IF, 2, $3, $5); 
        }
    }
    | IF LPAREN expression RPAREN statement ELSE statement { 
        /* Grammar-level condition optimization with else */
        if (is_always_false_condition($3)) {
            /* Always false - replace with else branch */
            if (is_empty_statement($7)) {
                $$ = NULL; /* Both branches empty */
            } else {
                $$ = $7; /* Use else branch directly */
            }
        } else if (is_empty_statement($5) && is_empty_statement($7)) {
            $$ = NULL; /* Both branches empty */
        } 
        else if (is_empty_statement($7)) {
            // Else branch empty, keep only if branch
            $$ = create_ast_node(AST_IF, 2, $3, $5); 
        }
        else {
            ASTNode* else_node = create_ast_node(AST_ELSE, 1, $7);
            $$ = create_ast_node(AST_IF, 3, $3, $5, else_node); 
        }
    }
    ;

switch_statement
    : SWITCH LPAREN expression RPAREN statement {
        $$ = create_ast_node(AST_SWITCH, 2, $3, $5);
    }
    ;

labeled_statement
    : IDENTIFIER COLON statement { 
        $$ = create_ast_node(AST_LABELED_STMT, 2, create_leaf_node(AST_IDENTIFIER, $1), $3); 
    }
    | CASE constant_expression COLON statement {
        $$ = create_ast_node(AST_CASE, 2, $2, $4);
    }
    | DEFAULT COLON statement {
        $$ = create_ast_node(AST_DEFAULT, 1, $3);
    }
    ;

expression_opt : expression { $$ = $1; } ;

expression_statement
    : SEMICOLON { $$ = NULL; }
    | expression SEMICOLON { $$ = $1; }
    ;

primary_expression
    : IDENTIFIER { $$ = create_leaf_node(AST_IDENTIFIER, $1); }
    | NUMBER { $$ = create_leaf_node(AST_NUMBER, $1); }
    | CHAR_LITERAL { $$ = create_leaf_node(AST_LITERAL, $1); }
    | STRING_LITERAL { $$ = create_leaf_node(AST_LITERAL, $1); }
    | LPAREN expression RPAREN { $$ = $2; }
    ;

postfix_expression
    : primary_expression
        { $$ = $1; }
    | postfix_expression LSQBRACKET expression RSQBRACKET
        { $$ = create_ast_node(AST_ARRAY_ACCESS, 2, $1, $3); }
    | postfix_expression DOT IDENTIFIER
        { $$ = create_ast_node(AST_MEMBER_ACCESS, 2, $1, create_leaf_node(AST_IDENTIFIER, $3)); }
    | postfix_expression ARROW IDENTIFIER
        { $$ = create_ast_node(AST_PTR_MEMBER_ACCESS, 2, $1, create_leaf_node(AST_IDENTIFIER, $3)); }    
    | postfix_expression LPAREN argument_expression_list RPAREN
        { 
            // Grammar-level dead function call elimination
            if ($1 && $1->type == AST_IDENTIFIER && is_dead_function_call($1->value.c_str())) {
                $$ = NULL; /* Dead function call eliminated at grammar level */
            } else {
                $$ = create_ast_node(AST_FUNCTION_CALL, 2, $1, $3);
            }
        }
    | postfix_expression LPAREN RPAREN
        { 
            // Grammar-level dead function call elimination
            if ($1 && $1->type == AST_IDENTIFIER && is_dead_function_call($1->value.c_str())) {
                $$ = NULL; /* Dead function call eliminated at grammar level */
            } else {
                $$ = create_ast_node(AST_FUNCTION_CALL, 1, $1);
            }
        }
    | postfix_expression INCREMENT
        { 
            // x++ becomes x = x + 1
            ASTNode* one = create_leaf_node(AST_NUMBER, "1");
            ASTNode* binary_op = create_ast_node(AST_PLUS, 2, $1, one);
            $$ = create_ast_node(AST_ASSIGNMENT, 2, $1, binary_op); 
        }
    | postfix_expression DECREMENT
        { 
            // x-- becomes x = x - 1
            ASTNode* one = create_leaf_node(AST_NUMBER, "1");
            ASTNode* binary_op = create_ast_node(AST_MINUS, 2, $1, one);
            $$ = create_ast_node(AST_ASSIGNMENT, 2, $1, binary_op); 
        }
    ;


argument_expression_list
    : assignment_expression { $$ = makelist($1); }
    | argument_expression_list COMMA assignment_expression { $$ = append_list($1, $3); }
    ;

unary_expression
    : postfix_expression { $$ = $1; }
    | INCREMENT unary_expression { 
        // ++x becomes x = x + 1
        ASTNode* one = create_leaf_node(AST_NUMBER, "1");
        ASTNode* binary_op = create_ast_node(AST_PLUS, 2, $2, one);
        $$ = create_ast_node(AST_ASSIGNMENT, 2, $2, binary_op); 
    }
    | DECREMENT unary_expression { 
        // --x becomes x = x - 1
        ASTNode* one = create_leaf_node(AST_NUMBER, "1");
        ASTNode* binary_op = create_ast_node(AST_MINUS, 2, $2, one);
        $$ = create_ast_node(AST_ASSIGNMENT, 2, $2, binary_op); 
    }    | unary_operator cast_expression { 
        // Handle unary operators with appropriate node types
        if ($1->type == AST_UNARY_MINUS) {
            $$ = create_ast_node(AST_UNARY_MINUS, 1, $2);
        } else if ($1->type == AST_UNARY_PLUS) {
            $$ = create_ast_node(AST_UNARY_PLUS, 1, $2);
        } else if ($1->type == AST_BIT_NOT) {
            $$ = create_ast_node(AST_BIT_NOT, 1, $2);
        } else if ($1->type == AST_LOGICAL_NOT) {
            $$ = create_ast_node(AST_LOGICAL_NOT, 1, $2);
        } else if ($1->type == AST_ADDRESS_OF) {
            $$ = create_ast_node(AST_ADDRESS_OF, 1, $2);
        } else if ($1->type == AST_POINTER_DEREF) {
            $$ = create_ast_node(AST_POINTER_DEREF, 1, $2);
        } else {
            $$ = create_ast_node(AST_TRANS, 2, $1, $2);
        }
    }
    | SIZEOF unary_expression { $$ = create_ast_node(AST_SIZEOF, 1, $2); }
    | SIZEOF LPAREN type_name RPAREN { $$ = create_ast_node(AST_SIZEOF, 1, $3); }
    ;

unary_operator
    : BIT_AND { $$ = create_leaf_node(AST_ADDRESS_OF, "&"); }
    | MULTIPLY { $$ = create_leaf_node(AST_POINTER_DEREF, "*"); }
    | PLUS { $$ = create_leaf_node(AST_UNARY_PLUS, "+"); }
    | MINUS { $$ = create_leaf_node(AST_UNARY_MINUS, "-"); }
    | BIT_NOT { $$ = create_leaf_node(AST_BIT_NOT, "~"); }
    | NOT { $$ = create_leaf_node(AST_LOGICAL_NOT, "!"); }
    ;

cast_expression
    : unary_expression { $$ = $1; }
    | LPAREN type_name RPAREN cast_expression { 
        /* Grammar-level type cast elimination for plagiarism detection 
        Converts: (float)(x + y) -> (x + y) */
        $$ = $4; 
        }
    ;

multiplicative_expression
    : cast_expression { $$ = $1; }
    | multiplicative_expression MULTIPLY cast_expression { $$ = create_ast_node(AST_MUL, 2, $1, $3); }
    | multiplicative_expression DIVIDE cast_expression { $$ = create_ast_node(AST_DIV, 2, $1, $3); }
    | multiplicative_expression MODULO cast_expression { $$ = create_ast_node(AST_MOD, 2, $1, $3); }
    ;

additive_expression
    : multiplicative_expression { $$ = $1; }
    | additive_expression PLUS multiplicative_expression { $$ = create_ast_node(AST_PLUS, 2, $1, $3); }
    | additive_expression MINUS multiplicative_expression { $$ = create_ast_node(AST_MINUS, 2, $1, $3); }
    ;

shift_expression
    : additive_expression { $$ = $1; }
    | shift_expression SHIFT_LEFT additive_expression { $$ = create_ast_node(AST_SHIFT_LEFT, 2, $1, $3); }
    | shift_expression SHIFT_RIGHT additive_expression { $$ = create_ast_node(AST_SHIFT_RIGHT, 2, $1, $3); }
    ;

relational_expression
    : shift_expression { $$ = $1; }
    | relational_expression LESS shift_expression { $$ = create_ast_node(AST_LT, 2, $1, $3); }
    | relational_expression GREATER shift_expression { $$ = create_ast_node(AST_GT, 2, $1, $3); }
    | relational_expression LESS_EQUAL shift_expression { $$ = create_ast_node(AST_LE, 2, $1, $3); }
    | relational_expression GREATER_EQUAL shift_expression { $$ = create_ast_node(AST_GE, 2, $1, $3); }
    ;

equality_expression
    : relational_expression { $$ = $1; }
    | equality_expression EQUAL relational_expression { $$ = create_ast_node(AST_EQUALS, 2, $1, $3); }
    | equality_expression NOT_EQUAL relational_expression { $$ = create_ast_node(AST_NOT_EQUALS, 2, $1, $3); }
    ;

and_expression
    : equality_expression { $$ = $1; }
    | and_expression BIT_AND equality_expression { $$ = create_ast_node(AST_BIT_AND, 2, $1, $3); }
    ;

exclusive_or_expression
    : and_expression { $$ = $1; }
    | exclusive_or_expression BIT_XOR and_expression { $$ = create_ast_node(AST_BIT_XOR, 2, $1, $3); }
    ;

inclusive_or_expression
    : exclusive_or_expression { $$ = $1; }
    | inclusive_or_expression BIT_OR exclusive_or_expression { $$ = create_ast_node(AST_BIT_OR, 2, $1, $3); }
    ;

logical_and_expression
    : inclusive_or_expression { $$ = $1; }
    | logical_and_expression AND inclusive_or_expression { $$ = create_ast_node(AST_LOGICAL_AND, 2, $1, $3); }
    ;

logical_or_expression
    : logical_and_expression { $$ = $1; }
    | logical_or_expression OR logical_and_expression { $$ = create_ast_node(AST_LOGICAL_OR, 2, $1, $3); }
    ;

conditional_expression
    : logical_or_expression { $$ = $1; }
    | logical_or_expression QUESTION expression COLON conditional_expression { $$ = create_ast_node(AST_CONDITIONAL, 3, $1, $3, $5); }
    ;

assignment_expression
    : conditional_expression { $$ = $1; }
    | unary_expression ASSIGN assignment_expression { $$ = create_ast_node(AST_ASSIGNMENT, 2, $1, $3); }
    | unary_expression PLUS_ASSIGN assignment_expression { 
        // x += y becomes x = x + y
        ASTNode* binary_op = create_ast_node(AST_PLUS, 2, $1, $3);
        $$ = create_ast_node(AST_ASSIGNMENT, 2, $1, binary_op); 
    }
    | unary_expression MINUS_ASSIGN assignment_expression { 
        // x -= y becomes x = x - y
        ASTNode* binary_op = create_ast_node(AST_MINUS, 2, $1, $3);
        $$ = create_ast_node(AST_ASSIGNMENT, 2, $1, binary_op); 
    }
    | unary_expression MUL_ASSIGN assignment_expression { 
        // x *= y becomes x = x * y
        ASTNode* binary_op = create_ast_node(AST_MUL, 2, $1, $3);
        $$ = create_ast_node(AST_ASSIGNMENT, 2, $1, binary_op); 
    }
    | unary_expression DIV_ASSIGN assignment_expression { 
        // x /= y becomes x = x / y
        ASTNode* binary_op = create_ast_node(AST_DIV, 2, $1, $3);
        $$ = create_ast_node(AST_ASSIGNMENT, 2, $1, binary_op); 
    }
    | unary_expression MOD_ASSIGN assignment_expression { 
        // x %= y becomes x = x % y
        ASTNode* binary_op = create_ast_node(AST_MOD, 2, $1, $3);
        $$ = create_ast_node(AST_ASSIGNMENT, 2, $1, binary_op); 
    }    | unary_expression SHIFT_LEFT_ASSIGN assignment_expression { 
        // x <<= y becomes x = x << y
        ASTNode* binary_op = create_ast_node(AST_SHIFT_LEFT, 2, $1, $3);
        $$ = create_ast_node(AST_ASSIGNMENT, 2, $1, binary_op); 
    }
    | unary_expression SHIFT_RIGHT_ASSIGN assignment_expression { 
        // x >>= y becomes x = x >> y
        ASTNode* binary_op = create_ast_node(AST_SHIFT_RIGHT, 2, $1, $3);
        $$ = create_ast_node(AST_ASSIGNMENT, 2, $1, binary_op); 
    }
    | unary_expression BIT_AND_ASSIGN assignment_expression { 
        // x &= y becomes x = x & y
        ASTNode* binary_op = create_ast_node(AST_BIT_AND, 2, $1, $3);
        $$ = create_ast_node(AST_ASSIGNMENT, 2, $1, binary_op); 
    }
    | unary_expression BIT_XOR_ASSIGN assignment_expression { 
        // x ^= y becomes x = x ^ y
        ASTNode* binary_op = create_ast_node(AST_BIT_XOR, 2, $1, $3);
        $$ = create_ast_node(AST_ASSIGNMENT, 2, $1, binary_op); 
    }
    | unary_expression BIT_OR_ASSIGN assignment_expression { 
        // x |= y becomes x = x | y
        ASTNode* binary_op = create_ast_node(AST_BIT_OR, 2, $1, $3);
        $$ = create_ast_node(AST_ASSIGNMENT, 2, $1, binary_op); 
    }
    ;
    
expression
    : assignment_expression { $$ = $1; }
    | expression COMMA assignment_expression { $$ = create_ast_node(AST_COMMA, 2, $1, $3); }
    ;

constant_expression
    : conditional_expression { $$ = $1; }
    ;

%%