#pragma once
#ifndef C_TOKENS_HPP
#define C_TOKENS_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "token_types.h"

class lexeme {
	public:
    std::string lexeme_name;
	std::string token_name;
	TokenTypes::TokenType token_no; // Bison token number
		
	lexeme(std::string lexeme_name, std::string token_name, TokenTypes::TokenType token_no) {
		this->lexeme_name = lexeme_name;
		this->token_name = token_name;
		this->token_no = token_no;	
	}
};


std::unordered_map<std::string, std::vector<lexeme>*> TOKENS;

std::vector<lexeme> keywords = {
	lexeme("auto", "AUTO", TokenTypes::AUTO),
	lexeme("break", "BREAK", TokenTypes::BREAK),
	lexeme("case", "CASE", TokenTypes::CASE),
	lexeme("char", "CHAR", TokenTypes::CHAR),
	lexeme("const", "CONST", TokenTypes::CONST),
	lexeme("continue", "CONTINUE", TokenTypes::CONTINUE),
	lexeme("default", "DEFAULT", TokenTypes::DEFAULT),
	lexeme("do", "DO", TokenTypes::DO),
	lexeme("double", "DOUBLE", TokenTypes::DOUBLE),
	lexeme("else", "ELSE", TokenTypes::ELSE),
	lexeme("enum", "ENUM", TokenTypes::ENUM),
	lexeme("extern", "EXTERN", TokenTypes::EXTERN),
	lexeme("float", "FLOAT", TokenTypes::FLOAT),
	lexeme("for", "FOR", TokenTypes::FOR),
	lexeme("_Alignof", "ALIGNOF", TokenTypes::ALIGNAS), // Using ALIGNAS as closest match
	lexeme("_Atomic", "ATOMIC", TokenTypes::TOKEN_EOF), // No direct match, using 0
	lexeme("goto", "GOTO", TokenTypes::GOTO),
	lexeme("if", "IF", TokenTypes::IF),
	lexeme("inline", "INLINE", TokenTypes::INLINE),
	lexeme("int", "INT", TokenTypes::INT),
	lexeme("long", "LONG", TokenTypes::LONG),
	lexeme("register", "REGISTER", TokenTypes::REGISTER),
	lexeme("restrict", "RESTRICT", TokenTypes::RESTRICT),
	lexeme("return", "RETURN", TokenTypes::RETURN),
	lexeme("short", "SHORT", TokenTypes::SHORT),
	lexeme("signed", "SIGNED", TokenTypes::SIGNED),
	lexeme("sizeof", "SIZEOF", TokenTypes::SIZEOF),
	lexeme("static", "STATIC", TokenTypes::STATIC),
	lexeme("struct", "STRUCT", TokenTypes::STRUCT),
	lexeme("switch", "SWITCH", TokenTypes::SWITCH),
	lexeme("while", "WHILE", TokenTypes::WHILE),
	lexeme("_Alignas", "ALIGNAS", TokenTypes::ALIGNAS),
	lexeme("typedef", "TYPEDEF", TokenTypes::TYPEDEF),
	lexeme("union", "UNION", TokenTypes::UNION),
	lexeme("unsigned", "UNSIGNED", TokenTypes::UNSIGNED),
	lexeme("void", "VOID", TokenTypes::VOID),
	lexeme("volatile", "VOLATILE", TokenTypes::VOLATILE),
	lexeme("_Bool", "BOOL", TokenTypes::BOOL),
	lexeme("_Complex", "COMPLEX", TokenTypes::TOKEN_EOF), // No direct match, using 0
	lexeme("_Generic", "GENERIC", TokenTypes::TOKEN_EOF), // No direct match, using 0
	lexeme("_Imaginary", "IMAGINARY", TokenTypes::TOKEN_EOF), // No direct match, using 0
	lexeme("_Noreturn", "NORETURN", TokenTypes::NORETURN),
	lexeme("_Static_assert", "STATIC_ASSERT", TokenTypes::TOKEN_EOF), // No direct match, using 0
	lexeme("_Thread_local", "THREAD_LOCAL", TokenTypes::TOKEN_EOF) // No direct match, using 0
};

std::vector<lexeme> operators = {
	lexeme("+", "ADD", TokenTypes::PLUS),
	lexeme("-", "SUB", TokenTypes::MINUS),
	lexeme("*", "MUL", TokenTypes::MULTIPLY),
	lexeme("/", "DIV", TokenTypes::DIVIDE),
	lexeme("%", "MOD", TokenTypes::MODULO),
	lexeme("++", "INR", TokenTypes::INCREMENT),
	lexeme("--", "DCR", TokenTypes::DECREMENT),
	lexeme("==", "EQUAL", TokenTypes::EQUAL),
	lexeme("!=", "NOT_EQUAL", TokenTypes::NOT_EQUAL),
	lexeme(">", "GREATER", TokenTypes::GREATER),
	lexeme("<", "LESS", TokenTypes::LESS),
	lexeme(">=", "GREATER_EQUAL", TokenTypes::GREATER_EQUAL),
	lexeme("<=", "LESS_EQUAL", TokenTypes::LESS_EQUAL),
	lexeme("&&", "LOGICAL_AND", TokenTypes::AND),
	lexeme("||", "LOGICAL_OR", TokenTypes::OR),
	lexeme("!", "LOGICAL_NOT", TokenTypes::NOT),
	lexeme("&", "BIT_AND", TokenTypes::BIT_AND),
	lexeme("|", "BIT_OR", TokenTypes::BIT_OR),
	lexeme("^", "BIT_XOR", TokenTypes::BIT_XOR),
	lexeme("~", "BIT_NOT", TokenTypes::BIT_NOT),
	lexeme("<<", "BIT_LEFT_SHIFT", TokenTypes::SHIFT_LEFT),
	lexeme(">>", "BIT_RIGHT_SHIFT", TokenTypes::SHIFT_RIGHT),
	lexeme("+=", "ADD_ASSIGN", TokenTypes::PLUS_ASSIGN),
	lexeme("-=", "SUB_ASSIGN", TokenTypes::MINUS_ASSIGN),
	lexeme("*=", "MUL_ASSIGN", TokenTypes::MUL_ASSIGN),
	lexeme("/=", "DIV_ASSIGN", TokenTypes::DIV_ASSIGN),
	lexeme("%=", "MOD_ASSIGN", TokenTypes::MOD_ASSIGN),
	lexeme("&=", "BIT_AND_ASSIGN", TokenTypes::BIT_AND_ASSIGN),
	lexeme("|=", "BIT_OR_ASSIGN", TokenTypes::BIT_OR_ASSIGN),
	lexeme("^=", "BIT_XOR_ASSIGN", TokenTypes::BIT_XOR_ASSIGN),
	lexeme("<<=", "LEFT_SHIFT_ASSIGN", TokenTypes::SHIFT_LEFT_ASSIGN),
	lexeme(">>=", "RIGHT_SHIFT_ASSIGN", TokenTypes::SHIFT_RIGHT_ASSIGN),
	lexeme("=", "ASSIGN", TokenTypes::ASSIGN),
	lexeme("?", "TERNARY_CONDITIONAL", TokenTypes::QUESTION),
	lexeme(":", "TERNARY_SEPARATOR", TokenTypes::COLON),
	lexeme("->", "REF", TokenTypes::ARROW)
};

/*
// preprocessors (except #define) does not hold any Algorithmic Value
std::vector<lexeme> preprocessors = {
	lexeme("#include", "INCLUDE_HEADER", TokenTypes::PREPROCESSOR),
	lexeme("#define", "DEFINE_MACRO", TokenTypes::PREPROCESSOR),
	lexeme("#undef", "UNDEFINE_MACRO", TokenTypes::PREPROCESSOR),
	lexeme("#if", "IF_CONDITIONAL", TokenTypes::PREPROCESSOR),
	lexeme("#ifdef", "IF_DEFINED", TokenTypes::PREPROCESSOR),
	lexeme("#ifndef", "IF_NOT_DEFINED", TokenTypes::PREPROCESSOR),
	lexeme("#elif", "ELIF_CONDITIONAL", TokenTypes::PREPROCESSOR),
	lexeme("#elifdef", "ELIFDEF_CONDITIONAL", TokenTypes::PREPROCESSOR),
	lexeme("#elifndef", "ELIFNDEF_CONDITIONAL", TokenTypes::PREPROCESSOR),
	lexeme("#else", "ELSE_CONDITIONAL", TokenTypes::PREPROCESSOR),
	lexeme("#endif", "END_IF_CONDITIONAL", TokenTypes::PREPROCESSOR),
	lexeme("#error", "ERROR_DIRECTIVE", TokenTypes::PREPROCESSOR),
	lexeme("#warning", "WARNING_DIRECTIVE", TokenTypes::PREPROCESSOR),
	lexeme("#pragma", "PRAGMA_DIRECTIVE", TokenTypes::PREPROCESSOR),
	lexeme("#line", "LINE_DIRECTIVE", TokenTypes::PREPROCESSOR),
	lexeme("#embed", "EMBED_DIRECTIVE", TokenTypes::PREPROCESSOR)
};
*/

std::vector<lexeme> delimiters = {
	lexeme("{", "LCURLY", TokenTypes::LBRACE),
	lexeme("}", "RCURLY", TokenTypes::RBRACE),
	lexeme("(", "LPAREN", TokenTypes::LPAREN),
	lexeme(")", "RPAREN", TokenTypes::RPAREN),
	lexeme("[", "LSQUARE", TokenTypes::LSQBRACKET),
	lexeme("]", "RSQUARE", TokenTypes::RSQBRACKET),
	lexeme(";", "SEMI", TokenTypes::SEMICOLON),
	lexeme(",", "COMMA", TokenTypes::COMMA),
	lexeme(":", "COLON", TokenTypes::COLON),
	lexeme(".", "DOT", TokenTypes::DOT),
	lexeme("...", "ELLIPSIS", TokenTypes::ELLIPSIS),
	lexeme("#", "HASH", TokenTypes::TOKEN_EOF), // No direct match, using 0
	lexeme("##", "HASHHASH", TokenTypes::TOKEN_EOF), // No direct match, using 0
	lexeme("@", "AT", TokenTypes::TOKEN_EOF) // No direct match, using 0
};

std::vector<lexeme> comments = {
	lexeme("//", "SINGLE_LINE_COMMENT", TokenTypes::TOKEN_EOF), // Comments don't have lexemes in Bison
	lexeme("/*", "MULTI_LINE_COMMENT", TokenTypes::TOKEN_EOF)
};

std::vector<lexeme> predifined_typedefs = {
	lexeme("size_t", "SIZE_T", TokenTypes::TYPEDEF),
	lexeme("wchar_t", "WCHAR_T", TokenTypes::TYPEDEF),
	lexeme("ptrdiff_t", "PTRDIFF_T", TokenTypes::TYPEDEF),
	lexeme("max_align_t", "MAX_ALIGN_T", TokenTypes::TYPEDEF),
	lexeme("nullptr_t", "NULLPTR_T", TokenTypes::TYPEDEF),
	lexeme("FILE", "FILE", TokenTypes::TYPEDEF),
	lexeme("fpos_t", "FPOS_T", TokenTypes::TYPEDEF),
	lexeme("time_t", "TIME_T", TokenTypes::TYPEDEF),
	lexeme("clock_t", "CLOCK_T", TokenTypes::TYPEDEF),
	lexeme("va_list", "VA_LIST", TokenTypes::TYPEDEF)
};

inline void define_tokens() {
	TOKENS["KEYWORD"] = &keywords;
	TOKENS["OPERATOR"] = &operators;
	// TOKENS["PREPROCESSORS"] = &preprocessors;
	TOKENS["DELIMITER"] = &delimiters;
	TOKENS["COMMENT"] = &comments;
}

#endif
