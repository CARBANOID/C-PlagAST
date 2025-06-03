#pragma once
#ifndef TOKEN_TYPES_H
#define TOKEN_TYPES_H

// This file defines token types that are shared between the lexer and parser for integration
// Put all token type definitions in a namespace to avoid conflicts with Bison

namespace TokenTypes {
    // Token type enumeration (matches Bison %token definitions)
    enum TokenType {
        // Special tokens
        TOKEN_EOF = 0,
        
        // Preprocessor directives
        PREPROCESSOR = 258,

        // Identifiers and literals
        IDENTIFIER,
        NUMBER,
        CHAR_LITERAL,
        STRING_LITERAL,
        TYPEDEF_NAME,

        // Storage class specifiers
        TYPEDEF,
        EXTERN,
        STATIC,
        AUTO,
        REGISTER,

        // Type specifiers
        VOID,
        CHAR,
        SHORT,
        INT,
        LONG,
        FLOAT,
        DOUBLE,
        SIGNED,
        UNSIGNED,
        BOOL,
        STRUCT,
        UNION,
        ENUM,

        // Type qualifiers
        CONST,
        RESTRICT,
        VOLATILE,

        // Function specifiers and other keywords
        INLINE,
        NORETURN,
        ALIGNAS,
        SIZEOF,
        ELLIPSIS,

        // Parentheses, brackets, and braces
        LPAREN,
        RPAREN,
        LSQBRACKET,
        RSQBRACKET,
        LBRACE,
        RBRACE,

        // Punctuation and separators
        SEMICOLON,
        COMMA,
        COLON,
        DOT,
        ARROW,
        QUESTION,

        // Assignment operators
        ASSIGN,
        PLUS_ASSIGN,
        MINUS_ASSIGN,
        MUL_ASSIGN,
        DIV_ASSIGN,
        MOD_ASSIGN,
        SHIFT_LEFT_ASSIGN,
        SHIFT_RIGHT_ASSIGN,
        BIT_AND_ASSIGN,
        BIT_XOR_ASSIGN,
        BIT_OR_ASSIGN,

        // Logical and bitwise operators
        OR,
        AND,
        BIT_OR,
        BIT_AND,
        BIT_XOR,
        XOR,
        NOT,
        BIT_NOT,

        // Relational operators
        EQUAL,
        NOT_EQUAL,
        LESS,
        GREATER,
        LESS_EQUAL,
        GREATER_EQUAL,

        // Shift operators
        SHIFT_LEFT,
        SHIFT_RIGHT,

        // Arithmetic operators
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        MODULO,

        // Control flow
        IF,
        ELSE,
        WHILE,
        GOTO,
        BREAK,
        CONTINUE,
        FOR,
        SWITCH,
        CASE,
        DEFAULT,
        DO,

        // Increment/decrement
        INCREMENT,
        DECREMENT,

        // Return
        RETURN
    };
}

// Forward declaration of the ASTNode 
class ASTNode;

// Yylval union for storing semantic values
typedef union {
    ASTNode *node;
    int val;
    char *sval;
} YYSTYPE;

// External declaration of yylval is handled by parser.h
// We don't declare it here to avoid conflicts

#endif // TOKEN_TYPES_H 