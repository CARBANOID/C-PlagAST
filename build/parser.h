/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BUILD_PARSER_HPP_INCLUDED
# define YY_YY_BUILD_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PREPROCESSOR = 258,            /* PREPROCESSOR  */
    IDENTIFIER = 259,              /* IDENTIFIER  */
    NUMBER = 260,                  /* NUMBER  */
    CHAR_LITERAL = 261,            /* CHAR_LITERAL  */
    STRING_LITERAL = 262,          /* STRING_LITERAL  */
    TYPEDEF_NAME = 263,            /* TYPEDEF_NAME  */
    TYPEDEF = 264,                 /* TYPEDEF  */
    EXTERN = 265,                  /* EXTERN  */
    STATIC = 266,                  /* STATIC  */
    AUTO = 267,                    /* AUTO  */
    REGISTER = 268,                /* REGISTER  */
    VOID = 269,                    /* VOID  */
    CHAR = 270,                    /* CHAR  */
    SHORT = 271,                   /* SHORT  */
    INT = 272,                     /* INT  */
    LONG = 273,                    /* LONG  */
    FLOAT = 274,                   /* FLOAT  */
    DOUBLE = 275,                  /* DOUBLE  */
    SIGNED = 276,                  /* SIGNED  */
    UNSIGNED = 277,                /* UNSIGNED  */
    BOOL = 278,                    /* BOOL  */
    STRUCT = 279,                  /* STRUCT  */
    UNION = 280,                   /* UNION  */
    ENUM = 281,                    /* ENUM  */
    CONST = 282,                   /* CONST  */
    RESTRICT = 283,                /* RESTRICT  */
    VOLATILE = 284,                /* VOLATILE  */
    INLINE = 285,                  /* INLINE  */
    NORETURN = 286,                /* NORETURN  */
    ALIGNAS = 287,                 /* ALIGNAS  */
    SIZEOF = 288,                  /* SIZEOF  */
    ELLIPSIS = 289,                /* ELLIPSIS  */
    LPAREN = 290,                  /* LPAREN  */
    RPAREN = 291,                  /* RPAREN  */
    LSQBRACKET = 292,              /* LSQBRACKET  */
    RSQBRACKET = 293,              /* RSQBRACKET  */
    LBRACE = 294,                  /* LBRACE  */
    RBRACE = 295,                  /* RBRACE  */
    SEMICOLON = 296,               /* SEMICOLON  */
    COMMA = 297,                   /* COMMA  */
    COLON = 298,                   /* COLON  */
    DOT = 299,                     /* DOT  */
    ARROW = 300,                   /* ARROW  */
    QUESTION = 301,                /* QUESTION  */
    ASSIGN = 302,                  /* ASSIGN  */
    PLUS_ASSIGN = 303,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 304,            /* MINUS_ASSIGN  */
    MUL_ASSIGN = 305,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 306,              /* DIV_ASSIGN  */
    MOD_ASSIGN = 307,              /* MOD_ASSIGN  */
    SHIFT_LEFT_ASSIGN = 308,       /* SHIFT_LEFT_ASSIGN  */
    SHIFT_RIGHT_ASSIGN = 309,      /* SHIFT_RIGHT_ASSIGN  */
    BIT_AND_ASSIGN = 310,          /* BIT_AND_ASSIGN  */
    BIT_XOR_ASSIGN = 311,          /* BIT_XOR_ASSIGN  */
    BIT_OR_ASSIGN = 312,           /* BIT_OR_ASSIGN  */
    OR = 313,                      /* OR  */
    AND = 314,                     /* AND  */
    BIT_OR = 315,                  /* BIT_OR  */
    BIT_AND = 316,                 /* BIT_AND  */
    BIT_XOR = 317,                 /* BIT_XOR  */
    XOR = 318,                     /* XOR  */
    NOT = 319,                     /* NOT  */
    BIT_NOT = 320,                 /* BIT_NOT  */
    EQUAL = 321,                   /* EQUAL  */
    NOT_EQUAL = 322,               /* NOT_EQUAL  */
    LESS = 323,                    /* LESS  */
    GREATER = 324,                 /* GREATER  */
    LESS_EQUAL = 325,              /* LESS_EQUAL  */
    GREATER_EQUAL = 326,           /* GREATER_EQUAL  */
    SHIFT_LEFT = 327,              /* SHIFT_LEFT  */
    SHIFT_RIGHT = 328,             /* SHIFT_RIGHT  */
    PLUS = 329,                    /* PLUS  */
    MINUS = 330,                   /* MINUS  */
    MULTIPLY = 331,                /* MULTIPLY  */
    DIVIDE = 332,                  /* DIVIDE  */
    MODULO = 333,                  /* MODULO  */
    IF = 334,                      /* IF  */
    ELSE = 335,                    /* ELSE  */
    WHILE = 336,                   /* WHILE  */
    GOTO = 337,                    /* GOTO  */
    BREAK = 338,                   /* BREAK  */
    CONTINUE = 339,                /* CONTINUE  */
    FOR = 340,                     /* FOR  */
    SWITCH = 341,                  /* SWITCH  */
    CASE = 342,                    /* CASE  */
    DEFAULT = 343,                 /* DEFAULT  */
    DO = 344,                      /* DO  */
    INCREMENT = 345,               /* INCREMENT  */
    DECREMENT = 346,               /* DECREMENT  */
    RETURN = 347,                  /* RETURN  */
    LOWER_THAN_ELSE = 348          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BUILD_PARSER_HPP_INCLUDED  */
