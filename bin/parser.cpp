/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "AST.y"

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

#line 146 "../build/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PREPROCESSOR = 3,               /* PREPROCESSOR  */
  YYSYMBOL_IDENTIFIER = 4,                 /* IDENTIFIER  */
  YYSYMBOL_NUMBER = 5,                     /* NUMBER  */
  YYSYMBOL_CHAR_LITERAL = 6,               /* CHAR_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 7,             /* STRING_LITERAL  */
  YYSYMBOL_TYPEDEF_NAME = 8,               /* TYPEDEF_NAME  */
  YYSYMBOL_TYPEDEF = 9,                    /* TYPEDEF  */
  YYSYMBOL_EXTERN = 10,                    /* EXTERN  */
  YYSYMBOL_STATIC = 11,                    /* STATIC  */
  YYSYMBOL_AUTO = 12,                      /* AUTO  */
  YYSYMBOL_REGISTER = 13,                  /* REGISTER  */
  YYSYMBOL_VOID = 14,                      /* VOID  */
  YYSYMBOL_CHAR = 15,                      /* CHAR  */
  YYSYMBOL_SHORT = 16,                     /* SHORT  */
  YYSYMBOL_INT = 17,                       /* INT  */
  YYSYMBOL_LONG = 18,                      /* LONG  */
  YYSYMBOL_FLOAT = 19,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 20,                    /* DOUBLE  */
  YYSYMBOL_SIGNED = 21,                    /* SIGNED  */
  YYSYMBOL_UNSIGNED = 22,                  /* UNSIGNED  */
  YYSYMBOL_BOOL = 23,                      /* BOOL  */
  YYSYMBOL_STRUCT = 24,                    /* STRUCT  */
  YYSYMBOL_UNION = 25,                     /* UNION  */
  YYSYMBOL_ENUM = 26,                      /* ENUM  */
  YYSYMBOL_CONST = 27,                     /* CONST  */
  YYSYMBOL_RESTRICT = 28,                  /* RESTRICT  */
  YYSYMBOL_VOLATILE = 29,                  /* VOLATILE  */
  YYSYMBOL_INLINE = 30,                    /* INLINE  */
  YYSYMBOL_NORETURN = 31,                  /* NORETURN  */
  YYSYMBOL_ALIGNAS = 32,                   /* ALIGNAS  */
  YYSYMBOL_SIZEOF = 33,                    /* SIZEOF  */
  YYSYMBOL_ELLIPSIS = 34,                  /* ELLIPSIS  */
  YYSYMBOL_LPAREN = 35,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 36,                    /* RPAREN  */
  YYSYMBOL_LSQBRACKET = 37,                /* LSQBRACKET  */
  YYSYMBOL_RSQBRACKET = 38,                /* RSQBRACKET  */
  YYSYMBOL_LBRACE = 39,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 40,                    /* RBRACE  */
  YYSYMBOL_SEMICOLON = 41,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 42,                     /* COMMA  */
  YYSYMBOL_COLON = 43,                     /* COLON  */
  YYSYMBOL_DOT = 44,                       /* DOT  */
  YYSYMBOL_ARROW = 45,                     /* ARROW  */
  YYSYMBOL_QUESTION = 46,                  /* QUESTION  */
  YYSYMBOL_ASSIGN = 47,                    /* ASSIGN  */
  YYSYMBOL_PLUS_ASSIGN = 48,               /* PLUS_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 49,              /* MINUS_ASSIGN  */
  YYSYMBOL_MUL_ASSIGN = 50,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 51,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 52,                /* MOD_ASSIGN  */
  YYSYMBOL_SHIFT_LEFT_ASSIGN = 53,         /* SHIFT_LEFT_ASSIGN  */
  YYSYMBOL_SHIFT_RIGHT_ASSIGN = 54,        /* SHIFT_RIGHT_ASSIGN  */
  YYSYMBOL_BIT_AND_ASSIGN = 55,            /* BIT_AND_ASSIGN  */
  YYSYMBOL_BIT_XOR_ASSIGN = 56,            /* BIT_XOR_ASSIGN  */
  YYSYMBOL_BIT_OR_ASSIGN = 57,             /* BIT_OR_ASSIGN  */
  YYSYMBOL_OR = 58,                        /* OR  */
  YYSYMBOL_AND = 59,                       /* AND  */
  YYSYMBOL_BIT_OR = 60,                    /* BIT_OR  */
  YYSYMBOL_BIT_AND = 61,                   /* BIT_AND  */
  YYSYMBOL_BIT_XOR = 62,                   /* BIT_XOR  */
  YYSYMBOL_XOR = 63,                       /* XOR  */
  YYSYMBOL_NOT = 64,                       /* NOT  */
  YYSYMBOL_BIT_NOT = 65,                   /* BIT_NOT  */
  YYSYMBOL_EQUAL = 66,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 67,                 /* NOT_EQUAL  */
  YYSYMBOL_LESS = 68,                      /* LESS  */
  YYSYMBOL_GREATER = 69,                   /* GREATER  */
  YYSYMBOL_LESS_EQUAL = 70,                /* LESS_EQUAL  */
  YYSYMBOL_GREATER_EQUAL = 71,             /* GREATER_EQUAL  */
  YYSYMBOL_SHIFT_LEFT = 72,                /* SHIFT_LEFT  */
  YYSYMBOL_SHIFT_RIGHT = 73,               /* SHIFT_RIGHT  */
  YYSYMBOL_PLUS = 74,                      /* PLUS  */
  YYSYMBOL_MINUS = 75,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 76,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 77,                    /* DIVIDE  */
  YYSYMBOL_MODULO = 78,                    /* MODULO  */
  YYSYMBOL_IF = 79,                        /* IF  */
  YYSYMBOL_ELSE = 80,                      /* ELSE  */
  YYSYMBOL_WHILE = 81,                     /* WHILE  */
  YYSYMBOL_GOTO = 82,                      /* GOTO  */
  YYSYMBOL_BREAK = 83,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 84,                  /* CONTINUE  */
  YYSYMBOL_FOR = 85,                       /* FOR  */
  YYSYMBOL_SWITCH = 86,                    /* SWITCH  */
  YYSYMBOL_CASE = 87,                      /* CASE  */
  YYSYMBOL_DEFAULT = 88,                   /* DEFAULT  */
  YYSYMBOL_DO = 89,                        /* DO  */
  YYSYMBOL_INCREMENT = 90,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 91,                 /* DECREMENT  */
  YYSYMBOL_RETURN = 92,                    /* RETURN  */
  YYSYMBOL_LOWER_THAN_ELSE = 93,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 94,                  /* $accept  */
  YYSYMBOL_translation_unit = 95,          /* translation_unit  */
  YYSYMBOL_external_declaration = 96,      /* external_declaration  */
  YYSYMBOL_declaration_list = 97,          /* declaration_list  */
  YYSYMBOL_block_item = 98,                /* block_item  */
  YYSYMBOL_type_qualifier_list = 99,       /* type_qualifier_list  */
  YYSYMBOL_compound_statement = 100,       /* compound_statement  */
  YYSYMBOL_non_empty_block_item_list = 101, /* non_empty_block_item_list  */
  YYSYMBOL_function_definition = 102,      /* function_definition  */
  YYSYMBOL_declaration = 103,              /* declaration  */
  YYSYMBOL_init_declarator_list = 104,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 105,          /* init_declarator  */
  YYSYMBOL_declaration_specifiers = 106,   /* declaration_specifiers  */
  YYSYMBOL_storage_class_specifier = 107,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 108,           /* type_specifier  */
  YYSYMBOL_type_qualifier = 109,           /* type_qualifier  */
  YYSYMBOL_function_specifier = 110,       /* function_specifier  */
  YYSYMBOL_alignment_specifier = 111,      /* alignment_specifier  */
  YYSYMBOL_declarator = 112,               /* declarator  */
  YYSYMBOL_pointer = 113,                  /* pointer  */
  YYSYMBOL_direct_declarator = 114,        /* direct_declarator  */
  YYSYMBOL_struct_or_union_specifier = 115, /* struct_or_union_specifier  */
  YYSYMBOL_struct_declaration_list = 116,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 117,       /* struct_declaration  */
  YYSYMBOL_specifier_qualifier_list = 118, /* specifier_qualifier_list  */
  YYSYMBOL_struct_declarator_list = 119,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 120,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 121,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 122,          /* enumerator_list  */
  YYSYMBOL_enumeration_constant = 123,     /* enumeration_constant  */
  YYSYMBOL_type_name = 124,                /* type_name  */
  YYSYMBOL_abstract_declarator = 125,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 126, /* direct_abstract_declarator  */
  YYSYMBOL_parameter_type_list = 127,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 128,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 129,    /* parameter_declaration  */
  YYSYMBOL_initializer = 130,              /* initializer  */
  YYSYMBOL_initializer_list = 131,         /* initializer_list  */
  YYSYMBOL_statement = 132,                /* statement  */
  YYSYMBOL_selection_statement = 133,      /* selection_statement  */
  YYSYMBOL_jump_statement = 134,           /* jump_statement  */
  YYSYMBOL_iteration_statement = 135,      /* iteration_statement  */
  YYSYMBOL_conditional_statement = 136,    /* conditional_statement  */
  YYSYMBOL_switch_statement = 137,         /* switch_statement  */
  YYSYMBOL_labeled_statement = 138,        /* labeled_statement  */
  YYSYMBOL_expression_opt = 139,           /* expression_opt  */
  YYSYMBOL_expression_statement = 140,     /* expression_statement  */
  YYSYMBOL_primary_expression = 141,       /* primary_expression  */
  YYSYMBOL_postfix_expression = 142,       /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 143, /* argument_expression_list  */
  YYSYMBOL_unary_expression = 144,         /* unary_expression  */
  YYSYMBOL_unary_operator = 145,           /* unary_operator  */
  YYSYMBOL_cast_expression = 146,          /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 147, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 148,      /* additive_expression  */
  YYSYMBOL_shift_expression = 149,         /* shift_expression  */
  YYSYMBOL_relational_expression = 150,    /* relational_expression  */
  YYSYMBOL_equality_expression = 151,      /* equality_expression  */
  YYSYMBOL_and_expression = 152,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 153,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 154,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 155,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 156,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 157,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 158,    /* assignment_expression  */
  YYSYMBOL_expression = 159,               /* expression  */
  YYSYMBOL_constant_expression = 160       /* constant_expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  46
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1453

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  228
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  380

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   348


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   111,   111,   112,   119,   120,   121,   129,   130,   134,
     135,   136,   141,   142,   147,   148,   152,   153,   158,   176,
     197,   198,   208,   209,   213,   214,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   231,   232,   233,   234,
     235,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   255,   256,   257,   261,   262,   266,
     267,   274,   275,   279,   280,   281,   282,   286,   287,   288,
     289,   290,   291,   292,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   309,   310,   314,   315,   319,   320,
     321,   322,   323,   324,   328,   329,   333,   334,   335,   339,
     340,   341,   342,   343,   347,   348,   352,   356,   357,   361,
     362,   363,   367,   368,   369,   370,   371,   372,   376,   377,
     381,   382,   386,   387,   388,   392,   393,   394,   398,   399,
     404,   405,   406,   407,   408,   409,   414,   415,   420,   421,
     422,   423,   424,   430,   438,   446,   458,   468,   492,   498,
     501,   504,   509,   512,   513,   517,   518,   519,   520,   521,
     525,   527,   529,   531,   533,   542,   551,   558,   569,   570,
     574,   575,   581,   586,   604,   605,   609,   610,   611,   612,
     613,   614,   618,   619,   627,   628,   629,   630,   634,   635,
     636,   640,   641,   642,   646,   647,   648,   649,   650,   654,
     655,   656,   660,   661,   665,   666,   670,   671,   675,   676,
     680,   681,   685,   686,   690,   691,   692,   697,   702,   707,
     712,   716,   721,   726,   731,   736,   744,   745,   749
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PREPROCESSOR",
  "IDENTIFIER", "NUMBER", "CHAR_LITERAL", "STRING_LITERAL", "TYPEDEF_NAME",
  "TYPEDEF", "EXTERN", "STATIC", "AUTO", "REGISTER", "VOID", "CHAR",
  "SHORT", "INT", "LONG", "FLOAT", "DOUBLE", "SIGNED", "UNSIGNED", "BOOL",
  "STRUCT", "UNION", "ENUM", "CONST", "RESTRICT", "VOLATILE", "INLINE",
  "NORETURN", "ALIGNAS", "SIZEOF", "ELLIPSIS", "LPAREN", "RPAREN",
  "LSQBRACKET", "RSQBRACKET", "LBRACE", "RBRACE", "SEMICOLON", "COMMA",
  "COLON", "DOT", "ARROW", "QUESTION", "ASSIGN", "PLUS_ASSIGN",
  "MINUS_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN",
  "SHIFT_LEFT_ASSIGN", "SHIFT_RIGHT_ASSIGN", "BIT_AND_ASSIGN",
  "BIT_XOR_ASSIGN", "BIT_OR_ASSIGN", "OR", "AND", "BIT_OR", "BIT_AND",
  "BIT_XOR", "XOR", "NOT", "BIT_NOT", "EQUAL", "NOT_EQUAL", "LESS",
  "GREATER", "LESS_EQUAL", "GREATER_EQUAL", "SHIFT_LEFT", "SHIFT_RIGHT",
  "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MODULO", "IF", "ELSE", "WHILE",
  "GOTO", "BREAK", "CONTINUE", "FOR", "SWITCH", "CASE", "DEFAULT", "DO",
  "INCREMENT", "DECREMENT", "RETURN", "LOWER_THAN_ELSE", "$accept",
  "translation_unit", "external_declaration", "declaration_list",
  "block_item", "type_qualifier_list", "compound_statement",
  "non_empty_block_item_list", "function_definition", "declaration",
  "init_declarator_list", "init_declarator", "declaration_specifiers",
  "storage_class_specifier", "type_specifier", "type_qualifier",
  "function_specifier", "alignment_specifier", "declarator", "pointer",
  "direct_declarator", "struct_or_union_specifier",
  "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list",
  "enumeration_constant", "type_name", "abstract_declarator",
  "direct_abstract_declarator", "parameter_type_list", "parameter_list",
  "parameter_declaration", "initializer", "initializer_list", "statement",
  "selection_statement", "jump_statement", "iteration_statement",
  "conditional_statement", "switch_statement", "labeled_statement",
  "expression_opt", "expression_statement", "primary_expression",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "unary_operator", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "expression", "constant_expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-321)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1344,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,    11,    18,
      93,  -321,  -321,  -321,  -321,  -321,   -17,  1173,  -321,  -321,
    -321,  1030,  -321,  -321,  -321,  -321,  -321,  -321,  -321,    -9,
     380,    -5,   471,    50,    22,   670,  -321,  -321,  -321,    32,
    -321,    27,     3,  -321,  -321,  -321,  -321,  -321,  -321,  1133,
      98,   176,   531,  -321,  1421,  1421,  1421,   618,  -321,    31,
    1198,  -321,  1225,    48,  -321,  -321,   174,  -321,  -321,  -321,
    -321,  -321,   902,   670,  -321,  -321,  -321,  -321,  -321,  -321,
     924,   924,    23,    57,  -321,   153,  -321,   946,  -321,   188,
      70,   146,   166,    99,    52,    54,    66,    89,   -18,  -321,
     122,   156,    27,  -321,  -321,  -321,    32,   352,   763,  1312,
    -321,  -321,  1030,   176,   592,   807,  -321,  1252,  -321,  -321,
    -321,  -321,  -321,  -321,   946,   152,   200,  -321,  -321,  1279,
    -321,  -321,   186,  -321,   185,   670,  -321,   167,   294,  -321,
    -321,    -4,   946,  -321,  -321,  1099,   221,   233,  -321,   236,
    -321,   813,   946,   218,   227,  -321,  -321,  -321,   946,   946,
     946,   946,   946,   946,   946,   946,   946,   946,   946,   946,
     946,   946,   946,   946,   946,   946,   946,  -321,  -321,  -321,
    -321,  -321,   220,   204,  -321,  -321,   243,   269,   258,   264,
     265,   275,   276,   946,   271,   503,   851,  -321,  -321,   441,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,
     215,   763,  -321,  -321,  -321,  -321,  -321,  1064,   279,   274,
    -321,    68,  -321,  -321,   283,  -321,  -321,   946,  -321,    38,
    -321,  -321,  -321,   281,   946,   946,   946,   946,   946,   946,
     946,   946,   946,   946,   946,   946,  -321,   946,   286,   287,
    -321,   714,   236,  1396,   946,  -321,    69,   -13,  -321,  -321,
    -321,  -321,  -321,   188,   188,    70,    70,   146,   146,   146,
     146,   166,   166,    99,    52,    54,    66,   234,    89,   503,
     946,   946,   284,  -321,  -321,   312,   946,   296,   503,   273,
    -321,   239,  -321,  -321,  -321,  -321,   232,  1064,  -321,   117,
    -321,  -321,  1369,  -321,   946,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,   314,   319,   348,  -321,  -321,   946,
    -321,    73,   105,  -321,   858,   126,   503,  -321,   354,  -321,
    -321,   719,  -321,  -321,  -321,  -321,  -321,  -321,  -321,   503,
     503,   858,   503,  -321,   946,  -321,  -321,   330,  -321,   946,
    -321,   160,   503,   375,   372,   374,  -321,   503,  -321,  -321
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     6,    53,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,     0,     0,
       0,    54,    55,    56,    57,    58,     0,     0,     2,     4,
       5,     0,    26,    27,    28,    29,    30,    51,    52,    78,
       0,    83,     0,   103,     0,     0,     1,     3,    67,     0,
      20,    63,     0,    22,    31,    32,    33,    34,    35,    25,
       0,    62,     0,    74,    88,    90,    92,     0,    84,     0,
       0,    79,     0,     0,   106,    99,     0,   104,   155,   156,
     157,   158,     0,     0,   176,   181,   180,   178,   179,   177,
       0,     0,   107,     0,   160,   170,   182,     0,   184,   188,
     191,   194,   199,   202,   204,   206,   208,   210,   212,   228,
       0,     0,    64,    12,    65,    21,     0,     0,     0,     0,
      19,     7,     0,    61,     0,     0,    76,     0,    89,    91,
      93,    75,    85,    86,     0,    96,     0,    94,    81,     0,
      80,   101,     0,   100,     0,     0,   174,     0,   182,   214,
     226,     0,     0,   171,   172,     0,     0,   109,   108,   111,
      59,     0,     0,     0,     0,   166,   167,   173,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    60,    68,    13,
      66,    23,    25,   155,    14,   153,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    16,   134,     0,
      11,     9,    10,   131,   133,   132,   136,   137,   135,   130,
       0,     0,    24,   125,    18,     8,    71,   124,     0,   118,
     120,     0,   168,    69,     0,    77,    98,     0,    87,     0,
      82,   102,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   159,     0,     0,     0,
     113,     0,   110,     0,     0,   165,     0,     0,   162,   163,
     185,   186,   187,   189,   190,   192,   193,   195,   196,   197,
     198,   200,   201,   203,   205,   207,   209,     0,   211,     0,
       0,     0,     0,   140,   141,     0,     0,     0,     0,     0,
     139,     0,    15,    17,   154,   128,     0,     0,   122,   109,
     123,    73,     0,    72,     0,    70,    97,    95,   175,   183,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   227,   112,   116,     0,     0,     0,   164,   161,     0,
     149,     0,     0,   142,     0,     0,     0,   151,     0,   138,
     126,     0,   119,   121,   169,   114,   117,   115,   213,     0,
       0,     0,     0,   150,     0,   127,   129,   146,   144,     0,
     148,     0,     0,     0,   152,     0,   147,     0,   143,   145
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -321,  -321,   391,  -321,   210,   266,   -40,  -321,  -103,   -56,
    -321,   305,    21,   -26,     6,     0,   -21,    12,   -22,   -28,
     -58,  -321,   170,   119,     4,  -321,   184,  -321,   351,   285,
     -63,   -85,  -149,  -113,  -321,   113,  -208,  -321,  -152,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -320,  -321,  -321,   316,
       1,  -321,   -93,   111,   125,    77,   129,   249,   250,   292,
     299,   298,  -321,   -44,    39,   -67,  -117
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    27,    28,   119,   207,   112,   208,   209,    29,    30,
      52,    53,   227,    32,    64,    65,    35,    66,   111,    60,
      61,    37,    67,    68,    69,   136,   137,    38,    76,    77,
      93,   258,   159,   259,   229,   230,   222,   306,   212,   213,
     214,   215,   216,   217,   218,   373,   219,    94,    95,   231,
     148,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   149,   150,   220,   110
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      34,   109,   123,   121,   167,    54,    33,   158,   262,    59,
      57,   228,    36,   305,   210,    39,   151,   236,    45,   120,
     147,    31,    41,   114,   361,   338,    74,    34,   185,   257,
      62,    56,   256,    33,    70,    48,    48,    55,   257,    36,
     186,   369,    48,    58,   115,   116,    96,   135,    31,    92,
      40,   113,    74,   299,    21,    22,    23,    42,   155,    34,
     156,   211,    75,   225,   157,    33,    49,    49,   128,   129,
     130,    36,   133,    49,   134,   270,   271,   272,   151,   224,
     122,   134,   243,   146,   190,   151,   297,    92,   141,    73,
     109,   153,   154,   160,   192,   267,    54,    43,    96,    51,
     192,    57,    48,    51,   313,   337,   210,    51,    51,   359,
     314,   314,   189,   181,    51,   257,   182,    34,   287,    34,
     316,    48,    56,    33,    34,    33,   183,   157,    55,    36,
      33,    36,    44,    49,    58,    96,    36,   340,    31,   301,
     122,   360,   310,   366,   171,   172,   347,   257,   184,    92,
     335,   319,   307,   211,   156,    34,   113,   223,   187,   109,
     262,    33,   362,   232,   234,   179,   180,    36,   257,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,   132,    96,   161,    74,
     162,   132,   188,   109,   363,   237,   375,   163,   164,   309,
     232,    54,   257,   244,    96,   308,    57,   367,   368,    34,
     370,   124,    72,   125,   143,    33,   144,   135,   173,   174,
     376,    36,   268,   341,   342,   379,   241,    56,   144,   345,
      31,   269,   127,    55,   175,   176,   177,   178,    96,    58,
     139,   238,   239,   165,   166,    96,   132,   289,    21,    22,
      23,   123,   277,   278,   279,   280,   304,   257,   132,   260,
     223,   189,   292,    34,   168,   169,   170,   118,   155,    33,
     156,   263,   350,   264,   351,    36,   257,   339,   290,   309,
     349,   257,   273,   274,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   358,   331,   371,   275,   276,
     334,   344,   374,   336,   291,   293,   294,    34,   281,   282,
     295,   296,    34,    33,   298,   311,   312,   318,    33,    36,
       2,   315,   332,   333,    36,   343,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,   346,
      96,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   355,   354,   348,   356,   193,    79,    80,    81,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    82,   357,    83,     2,   364,
     223,   117,   194,   195,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
     372,   377,    26,    84,   257,   378,    85,    86,    47,   303,
      63,   191,   261,   317,   142,   353,    87,    88,    89,   242,
     283,   196,   284,   197,   198,   199,   200,   201,   202,   203,
     204,   205,    90,    91,   206,   193,    79,    80,    81,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    82,   285,    83,   266,     0,     2,
     117,   302,   195,   286,   288,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,     0,    84,    26,     0,    85,    86,   193,    79,    80,
      81,    71,     0,     0,     0,    87,    88,    89,     0,     0,
     196,     0,   197,   198,   199,   200,   201,   202,   203,   204,
     205,    90,    91,   206,     0,     0,    82,     0,    83,     2,
       0,     0,   117,     0,   195,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,     0,     0,    26,    84,     0,     0,    85,    86,     0,
       0,   126,     0,     0,     0,     0,     0,    87,    88,    89,
       0,     0,   196,     0,   197,   198,   199,   200,   201,   202,
     203,   204,   205,    90,    91,   206,    78,    79,    80,    81,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    82,     2,    83,   226,     0,
       0,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,     0,     0,
      26,     0,     0,    84,     0,     0,    85,    86,   131,     0,
       0,     0,     0,     0,     0,     0,    87,    88,    89,     0,
       0,     0,     0,     0,    78,    79,    80,    81,     2,     0,
       0,     0,    90,    91,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       0,     0,    26,    82,     0,    83,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    78,    79,
      80,    81,     0,    78,    79,    80,    81,     0,     0,     0,
       0,    84,     0,     0,    85,    86,     0,     0,     0,     0,
       0,    21,    22,    23,    87,    88,    89,    82,     0,    83,
       0,     0,    82,     0,    83,     0,     0,     0,   221,   365,
      90,    91,     0,     0,     0,     0,     0,    78,    79,    80,
      81,     0,     0,     0,     0,    84,     0,     0,    85,    86,
      84,     0,     0,    85,    86,     0,     0,     0,    87,    88,
      89,     0,     0,    87,    88,    89,    82,     0,    83,     0,
       0,     0,   221,     0,    90,    91,     0,     0,     0,    90,
      91,    78,    79,    80,    81,     0,     0,    78,    79,    80,
      81,     0,     0,     0,    84,     0,     0,    85,    86,     0,
       0,     0,     0,     0,     0,     0,     0,    87,    88,    89,
      82,     0,    83,     0,     0,   233,    82,     0,    83,   265,
       0,     0,     0,    90,    91,    78,    79,    80,    81,     0,
       0,     0,    78,    79,    80,    81,     0,     0,    84,     0,
       0,    85,    86,     0,    84,     0,     0,    85,    86,     0,
       0,    87,    88,    89,    82,     0,    83,    87,    88,    89,
       0,    82,   300,    83,     0,     0,     0,    90,    91,   195,
       0,     0,     0,    90,    91,     0,    78,    79,    80,    81,
       0,     0,    84,     0,     0,    85,    86,     0,     0,    84,
       0,     0,    85,    86,     0,    87,    88,    89,    78,    79,
      80,    81,    87,    88,    89,    82,     0,   145,     0,     0,
       0,    90,    91,     0,     0,     0,     0,     0,    90,    91,
      78,    79,    80,    81,     0,     0,     0,    82,     0,   152,
       0,     0,     0,    84,     0,     0,    85,    86,     0,     0,
       0,     0,     0,     0,     0,     0,    87,    88,    89,    82,
       0,    83,     0,     0,     0,    84,     0,     0,    85,    86,
       0,     0,    90,    91,     0,     0,     0,     0,    87,    88,
      89,     0,     0,     0,     0,     0,     0,    84,     0,     0,
      85,    86,     0,     0,    90,    91,     0,     0,     0,     0,
      87,    88,    89,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    48,     0,    90,    91,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,     0,     0,    49,     0,     0,    48,     0,
       0,    50,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,     0,     0,   307,
       0,   156,     0,     0,     0,     0,    51,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,     0,     0,   155,     0,   156,     0,     0,     0,
      51,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,     0,     0,     0,     0,
       0,     0,   117,    46,     0,    51,     1,     0,     0,     0,
     118,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,     2,     0,     0,     0,
       0,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,     0,     0,
      26,     0,     0,     2,     0,     0,     0,     0,   138,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     0,     0,    26,     0,     0,
       2,     0,     0,     0,     0,   140,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,     0,     0,    26,     0,     0,     2,     0,     0,
       0,     0,   235,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,     0,
       0,    26,     0,     0,     0,     0,     0,     0,     0,   240,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,     0,     0,     1,     0,     0,
       0,   117,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,     0,   352,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,     2,
       0,     0,     0,     0,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,     0,     0,    26
};

static const yytype_int16 yycheck[] =
{
       0,    45,    60,    59,    97,    31,     0,    92,   157,    31,
      31,   124,     0,   221,   117,     4,    83,   134,    35,    59,
      83,     0,     4,    51,   344,    38,     4,    27,    46,    42,
      39,    31,    36,    27,    39,     4,     4,    31,    42,    27,
      58,   361,     4,    31,    41,    42,    45,    69,    27,    45,
      39,    51,     4,   205,    27,    28,    29,    39,    35,    59,
      37,   117,    40,   119,    92,    59,    35,    35,    64,    65,
      66,    59,    41,    35,    43,   168,   169,   170,   145,   119,
      59,    43,   145,    82,   112,   152,   203,    83,    40,    39,
     134,    90,    91,    36,   116,   162,   122,     4,    97,    76,
     122,   122,     4,    76,    36,    36,   209,    76,    76,    36,
      42,    42,   112,    61,    76,    42,    62,   117,   185,   119,
     237,     4,   122,   117,   124,   119,    60,   155,   122,   117,
     124,   119,    39,    35,   122,   134,   124,   289,   117,   206,
     119,    36,   227,   351,    74,    75,   298,    42,    59,   145,
     263,   244,    35,   209,    37,   155,   156,   118,    36,   203,
     309,   155,    36,   124,   125,    66,    67,   155,    42,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,    67,   186,    35,     4,
      37,    72,    36,   237,   346,    43,    36,    44,    45,   227,
     161,   227,    42,    36,   203,   227,   227,   359,   360,   209,
     362,    35,    42,    37,    40,   209,    42,   239,    72,    73,
     372,   209,     4,   290,   291,   377,    40,   227,    42,   296,
     209,     4,    62,   227,    68,    69,    70,    71,   237,   227,
      70,    41,    42,    90,    91,   244,   127,    43,    27,    28,
      29,   309,   175,   176,   177,   178,    41,    42,   139,    38,
     221,   261,     4,   263,    76,    77,    78,    47,    35,   263,
      37,    35,    40,    37,    42,   263,    42,    43,    35,   307,
      41,    42,   171,   172,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   339,   257,   364,   173,   174,
     261,   295,   369,   264,    35,    41,    41,   307,   179,   180,
      35,    35,   312,   307,    43,    36,    42,    36,   312,   307,
       8,    38,    36,    36,   312,    41,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    43,
     339,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    38,   314,    81,    36,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    38,    35,     8,    35,
     351,    39,    40,    41,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      80,    36,    32,    61,    42,    41,    64,    65,    27,   209,
      40,   116,   156,   239,    73,   312,    74,    75,    76,   144,
     181,    79,   182,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,   183,    35,   161,    -1,     8,
      39,    40,    41,   184,   186,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    -1,    61,    32,    -1,    64,    65,     4,     5,     6,
       7,    40,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,
      79,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    -1,    -1,    33,    -1,    35,     8,
      -1,    -1,    39,    -1,    41,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    32,    61,    -1,    -1,    64,    65,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    79,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,     8,    35,    36,    -1,
      -1,    -1,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    -1,    -1,    61,    -1,    -1,    64,    65,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    -1,
      -1,    -1,    -1,    -1,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    90,    91,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    32,    33,    -1,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,     5,
       6,     7,    -1,     4,     5,     6,     7,    -1,    -1,    -1,
      -1,    61,    -1,    -1,    64,    65,    -1,    -1,    -1,    -1,
      -1,    27,    28,    29,    74,    75,    76,    33,    -1,    35,
      -1,    -1,    33,    -1,    35,    -1,    -1,    -1,    39,    40,
      90,    91,    -1,    -1,    -1,    -1,    -1,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    61,    -1,    -1,    64,    65,
      61,    -1,    -1,    64,    65,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    74,    75,    76,    33,    -1,    35,    -1,
      -1,    -1,    39,    -1,    90,    91,    -1,    -1,    -1,    90,
      91,     4,     5,     6,     7,    -1,    -1,     4,     5,     6,
       7,    -1,    -1,    -1,    61,    -1,    -1,    64,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,
      33,    -1,    35,    -1,    -1,    38,    33,    -1,    35,    36,
      -1,    -1,    -1,    90,    91,     4,     5,     6,     7,    -1,
      -1,    -1,     4,     5,     6,     7,    -1,    -1,    61,    -1,
      -1,    64,    65,    -1,    61,    -1,    -1,    64,    65,    -1,
      -1,    74,    75,    76,    33,    -1,    35,    74,    75,    76,
      -1,    33,    41,    35,    -1,    -1,    -1,    90,    91,    41,
      -1,    -1,    -1,    90,    91,    -1,     4,     5,     6,     7,
      -1,    -1,    61,    -1,    -1,    64,    65,    -1,    -1,    61,
      -1,    -1,    64,    65,    -1,    74,    75,    76,     4,     5,
       6,     7,    74,    75,    76,    33,    -1,    35,    -1,    -1,
      -1,    90,    91,    -1,    -1,    -1,    -1,    -1,    90,    91,
       4,     5,     6,     7,    -1,    -1,    -1,    33,    -1,    35,
      -1,    -1,    -1,    61,    -1,    -1,    64,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    33,
      -1,    35,    -1,    -1,    -1,    61,    -1,    -1,    64,    65,
      -1,    -1,    90,    91,    -1,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,
      64,    65,    -1,    -1,    90,    91,    -1,    -1,    -1,    -1,
      74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     4,    -1,    90,    91,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    35,    -1,    -1,     4,    -1,
      -1,    41,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    -1,    35,
      -1,    37,    -1,    -1,    -1,    -1,    76,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    -1,    35,    -1,    37,    -1,    -1,    -1,
      76,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    39,     0,    -1,    76,     3,    -1,    -1,    -1,
      47,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     8,    -1,    -1,    -1,
      -1,    -1,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    -1,    -1,     8,    -1,    -1,    -1,    -1,    40,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    32,    -1,    -1,
       8,    -1,    -1,    -1,    -1,    40,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    32,    -1,    -1,     8,    -1,    -1,
      -1,    -1,    40,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,     3,    -1,    -1,
      -1,    39,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,     8,
      -1,    -1,    -1,    -1,    -1,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    32
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    95,    96,   102,
     103,   106,   107,   108,   109,   110,   111,   115,   121,     4,
      39,     4,    39,     4,    39,    35,     0,    96,     4,    35,
      41,    76,   104,   105,   107,   108,   109,   110,   111,   112,
     113,   114,    39,    40,   108,   109,   111,   116,   117,   118,
      39,    40,   116,    39,     4,    40,   122,   123,     4,     5,
       6,     7,    33,    35,    61,    64,    65,    74,    75,    76,
      90,    91,   118,   124,   141,   142,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     160,   112,    99,   109,   113,    41,    42,    39,    47,    97,
     100,   103,   106,   114,    35,    37,    40,   116,   118,   118,
     118,    40,   117,    41,    43,   112,   119,   120,    40,   116,
      40,    40,   122,    40,    42,    35,   144,   124,   144,   157,
     158,   159,    35,   144,   144,    35,    37,   113,   125,   126,
      36,    35,    37,    44,    45,    90,    91,   146,    76,    77,
      78,    74,    75,    72,    73,    68,    69,    70,    71,    66,
      67,    61,    62,    60,    59,    46,    58,    36,    36,   109,
     113,   105,   112,     4,    40,    41,    79,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    92,    98,   100,   101,
     102,   103,   132,   133,   134,   135,   136,   137,   138,   140,
     159,    39,   130,   158,   100,   103,    36,   106,   127,   128,
     129,   143,   158,    38,   158,    40,   160,    43,    41,    42,
      40,    40,   123,   124,    36,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    36,    42,   125,   127,
      38,    99,   126,    35,    37,    36,   143,   159,     4,     4,
     146,   146,   146,   147,   147,   148,   148,   149,   149,   149,
     149,   150,   150,   151,   152,   153,   154,   159,   155,    43,
      35,    35,     4,    41,    41,    35,    35,   160,    43,   132,
      41,   159,    40,    98,    41,   130,   131,    35,   112,   113,
     125,    36,    42,    36,    42,    38,   160,   120,    36,   146,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,    36,    36,   158,   127,   158,    36,    38,    43,
     132,   159,   159,    41,   108,   159,    43,   132,    81,    41,
      40,    42,    34,   129,   158,    38,    36,    38,   157,    36,
      36,   140,    36,   132,    35,    40,   130,   132,   132,   140,
     132,   159,    80,   139,   159,    36,   132,    36,    41,   132
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    95,    96,    96,    96,    97,    97,    98,
      98,    98,    99,    99,   100,   100,   101,   101,   102,   102,
     103,   103,   104,   104,   105,   105,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   107,   107,   107,   107,
     107,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   109,   109,   109,   110,   110,   111,
     111,   112,   112,   113,   113,   113,   113,   114,   114,   114,
     114,   114,   114,   114,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   116,   116,   117,   117,   118,   118,
     118,   118,   118,   118,   119,   119,   120,   120,   120,   121,
     121,   121,   121,   121,   122,   122,   123,   124,   124,   125,
     125,   125,   126,   126,   126,   126,   126,   126,   127,   127,
     128,   128,   129,   129,   129,   130,   130,   130,   131,   131,
     132,   132,   132,   132,   132,   132,   133,   133,   134,   134,
     134,   134,   134,   135,   135,   135,   136,   136,   137,   138,
     138,   138,   139,   140,   140,   141,   141,   141,   141,   141,
     142,   142,   142,   142,   142,   142,   142,   142,   143,   143,
     144,   144,   144,   144,   144,   144,   145,   145,   145,   145,
     145,   145,   146,   146,   147,   147,   147,   147,   148,   148,
     148,   149,   149,   149,   150,   150,   150,   150,   150,   151,
     151,   151,   152,   152,   153,   153,   154,   154,   155,   155,
     156,   156,   157,   157,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   159,   159,   160
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     2,     2,     3,     1,     2,     4,     3,
       2,     3,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       4,     2,     1,     1,     2,     2,     3,     1,     3,     3,
       4,     3,     4,     4,     3,     4,     4,     5,     2,     3,
       4,     4,     5,     2,     1,     2,     2,     3,     1,     2,
       1,     2,     1,     2,     1,     3,     1,     3,     2,     3,
       4,     4,     5,     2,     1,     3,     1,     1,     2,     1,
       2,     1,     3,     2,     4,     4,     3,     4,     1,     3,
       1,     3,     2,     2,     1,     1,     3,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       2,     2,     3,     7,     5,     8,     5,     7,     5,     3,
       4,     3,     1,     1,     2,     1,     1,     1,     1,     3,
       1,     4,     3,     3,     4,     3,     2,     2,     1,     3,
       1,     2,     2,     2,     2,     4,     1,     1,     1,     1,
       1,     1,     1,     4,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     5,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* translation_unit: external_declaration  */
#line 111 "AST.y"
                           { root = (yyvsp[0].node); (yyval.node) = (yyvsp[0].node); }
#line 2074 "../build/parser.cpp"
    break;

  case 3: /* translation_unit: translation_unit external_declaration  */
#line 112 "AST.y"
                                            { 
            (yyval.node) = create_ast_node(AST_TRANSLATION_UNIT, 2, (yyvsp[-1].node), (yyvsp[0].node));
            root = (yyval.node); 
        }
#line 2083 "../build/parser.cpp"
    break;

  case 4: /* external_declaration: function_definition  */
#line 119 "AST.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2089 "../build/parser.cpp"
    break;

  case 5: /* external_declaration: declaration  */
#line 120 "AST.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2095 "../build/parser.cpp"
    break;

  case 6: /* external_declaration: PREPROCESSOR  */
#line 121 "AST.y"
                   {
         (yyval.node) = NULL ;  /* For Preprocessor normalization*/
        /* $$ = create_leaf_node(AST_PREPROCESSOR, $1); */
    }
#line 2104 "../build/parser.cpp"
    break;

  case 7: /* declaration_list: declaration  */
#line 129 "AST.y"
                  { (yyval.node) = makelist((yyvsp[0].node)); }
#line 2110 "../build/parser.cpp"
    break;

  case 8: /* declaration_list: declaration_list declaration  */
#line 130 "AST.y"
                                   { (yyval.node) = append_list((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2116 "../build/parser.cpp"
    break;

  case 9: /* block_item: declaration  */
#line 134 "AST.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2122 "../build/parser.cpp"
    break;

  case 10: /* block_item: statement  */
#line 135 "AST.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 2128 "../build/parser.cpp"
    break;

  case 11: /* block_item: function_definition  */
#line 136 "AST.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2134 "../build/parser.cpp"
    break;

  case 12: /* type_qualifier_list: type_qualifier  */
#line 141 "AST.y"
                     { (yyval.node) = makelist((yyvsp[0].node)); }
#line 2140 "../build/parser.cpp"
    break;

  case 13: /* type_qualifier_list: type_qualifier_list type_qualifier  */
#line 142 "AST.y"
                                         { (yyval.node) = append_list((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2146 "../build/parser.cpp"
    break;

  case 14: /* compound_statement: LBRACE RBRACE  */
#line 147 "AST.y"
                    { (yyval.node) = NULL; /* Empty blocks normalized to NULL at grammar level */ }
#line 2152 "../build/parser.cpp"
    break;

  case 15: /* compound_statement: LBRACE non_empty_block_item_list RBRACE  */
#line 148 "AST.y"
                                              { (yyval.node) = create_ast_node(AST_COMPOUND_STMT, 1, (yyvsp[-1].node)); }
#line 2158 "../build/parser.cpp"
    break;

  case 16: /* non_empty_block_item_list: block_item  */
#line 152 "AST.y"
                 { (yyval.node) = makelist((yyvsp[0].node)); }
#line 2164 "../build/parser.cpp"
    break;

  case 17: /* non_empty_block_item_list: non_empty_block_item_list block_item  */
#line 153 "AST.y"
                                           { (yyval.node) = append_list((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2170 "../build/parser.cpp"
    break;

  case 18: /* function_definition: declaration_specifiers declarator declaration_list compound_statement  */
#line 159 "AST.y"
        { 
            // Grammar-level dead function elimination
            if ((yyvsp[0].node) == NULL) {
                // Empty function body - track as dead and return NULL
                ASTNode *function_name = extract_ast_element((yyvsp[-2].node), AST_IDENTIFIER, 0);
                if (function_name && function_name->value.c_str()) {
                    add_dead_function(function_name->value.c_str());
                }
                (yyval.node) = NULL; /* Dead function eliminated at grammar level */
            } else {
                // Extract the function name from the declarator
                ASTNode *function_name = extract_ast_element((yyvsp[-2].node), AST_IDENTIFIER, 0);
                // Extract the parameter list from the declarator
                ASTNode *param_list = extract_ast_element((yyvsp[-2].node), AST_PARAM_LIST, 0);
                (yyval.node) = create_ast_node(AST_FUNCTION_DEF, 5, (yyvsp[-3].node), function_name, param_list, (yyvsp[-1].node), (yyvsp[0].node));
            }
        }
#line 2192 "../build/parser.cpp"
    break;

  case 19: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 177 "AST.y"
        { 
            // Grammar-level dead function elimination
            if ((yyvsp[0].node) == NULL) {
                // Empty function body - track as dead and return NULL
                ASTNode *function_name = extract_ast_element((yyvsp[-1].node), AST_IDENTIFIER, 0);
                if (function_name && function_name->value.c_str()) {
                    add_dead_function(function_name->value.c_str());
                }
                (yyval.node) = NULL; /* Dead function eliminated at grammar level */
            } else {
                // Extract the function name from the declarator
                ASTNode *function_name = extract_ast_element((yyvsp[-1].node), AST_IDENTIFIER, 0);
                // Extract the parameter list from the declarator
                ASTNode *param_list = extract_ast_element((yyvsp[-1].node), AST_PARAM_LIST, 0);
                (yyval.node) = create_ast_node(AST_FUNCTION_DEF, 4, (yyvsp[-2].node), function_name, param_list, (yyvsp[0].node));
            }
        }
#line 2214 "../build/parser.cpp"
    break;

  case 20: /* declaration: declaration_specifiers SEMICOLON  */
#line 197 "AST.y"
                                       { (yyval.node) = create_ast_node(AST_DECLARATION, 1, (yyvsp[-1].node)); }
#line 2220 "../build/parser.cpp"
    break;

  case 21: /* declaration: declaration_specifiers init_declarator_list SEMICOLON  */
#line 198 "AST.y"
                                                            { 
        if (is_function_prototype((yyvsp[-1].node))){
            (yyval.node) = NULL ;  /* for AST Normalization */
            /*  $$ = create_ast_node(AST_FUNCTION_PROTOTYPE, 2, $1, $2); */
        }
         else (yyval.node) = create_ast_node(AST_DECLARATION, 2, (yyvsp[-2].node), (yyvsp[-1].node));
    }
#line 2232 "../build/parser.cpp"
    break;

  case 22: /* init_declarator_list: init_declarator  */
#line 208 "AST.y"
                      { (yyval.node) = makelist((yyvsp[0].node)); }
#line 2238 "../build/parser.cpp"
    break;

  case 23: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 209 "AST.y"
                                                 { (yyval.node) = append_list((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2244 "../build/parser.cpp"
    break;

  case 24: /* init_declarator: declarator ASSIGN initializer  */
#line 213 "AST.y"
                                    { (yyval.node) = create_ast_node(AST_INIT_DECLARATOR, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2250 "../build/parser.cpp"
    break;

  case 25: /* init_declarator: declarator  */
#line 214 "AST.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2256 "../build/parser.cpp"
    break;

  case 26: /* declaration_specifiers: storage_class_specifier  */
#line 218 "AST.y"
                              { (yyval.node) = makelist((yyvsp[0].node)); }
#line 2262 "../build/parser.cpp"
    break;

  case 27: /* declaration_specifiers: type_specifier  */
#line 219 "AST.y"
                     { (yyval.node) = makelist((yyvsp[0].node)); }
#line 2268 "../build/parser.cpp"
    break;

  case 28: /* declaration_specifiers: type_qualifier  */
#line 220 "AST.y"
                     { (yyval.node) = makelist((yyvsp[0].node)); }
#line 2274 "../build/parser.cpp"
    break;

  case 29: /* declaration_specifiers: function_specifier  */
#line 221 "AST.y"
                         { (yyval.node) = makelist((yyvsp[0].node)); }
#line 2280 "../build/parser.cpp"
    break;

  case 30: /* declaration_specifiers: alignment_specifier  */
#line 222 "AST.y"
                          { (yyval.node) = makelist((yyvsp[0].node)); }
#line 2286 "../build/parser.cpp"
    break;

  case 31: /* declaration_specifiers: declaration_specifiers storage_class_specifier  */
#line 223 "AST.y"
                                                     { (yyval.node) = append_list((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2292 "../build/parser.cpp"
    break;

  case 32: /* declaration_specifiers: declaration_specifiers type_specifier  */
#line 224 "AST.y"
                                            { (yyval.node) = append_list((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2298 "../build/parser.cpp"
    break;

  case 33: /* declaration_specifiers: declaration_specifiers type_qualifier  */
#line 225 "AST.y"
                                            { (yyval.node) = append_list((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2304 "../build/parser.cpp"
    break;

  case 34: /* declaration_specifiers: declaration_specifiers function_specifier  */
#line 226 "AST.y"
                                                { (yyval.node) = append_list((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2310 "../build/parser.cpp"
    break;

  case 35: /* declaration_specifiers: declaration_specifiers alignment_specifier  */
#line 227 "AST.y"
                                                 { (yyval.node) = append_list((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2316 "../build/parser.cpp"
    break;

  case 36: /* storage_class_specifier: TYPEDEF  */
#line 231 "AST.y"
              { (yyval.node) = create_leaf_node(AST_STORAGE_CLASS_SPECIFIER, "typedef"); }
#line 2322 "../build/parser.cpp"
    break;

  case 37: /* storage_class_specifier: EXTERN  */
#line 232 "AST.y"
             { (yyval.node) = create_leaf_node(AST_STORAGE_CLASS_SPECIFIER, "extern"); }
#line 2328 "../build/parser.cpp"
    break;

  case 38: /* storage_class_specifier: STATIC  */
#line 233 "AST.y"
             { (yyval.node) = create_leaf_node(AST_STORAGE_CLASS_SPECIFIER, "static"); }
#line 2334 "../build/parser.cpp"
    break;

  case 39: /* storage_class_specifier: AUTO  */
#line 234 "AST.y"
           { (yyval.node) = create_leaf_node(AST_STORAGE_CLASS_SPECIFIER, "auto"); }
#line 2340 "../build/parser.cpp"
    break;

  case 40: /* storage_class_specifier: REGISTER  */
#line 235 "AST.y"
               { (yyval.node) = create_leaf_node(AST_STORAGE_CLASS_SPECIFIER, "register"); }
#line 2346 "../build/parser.cpp"
    break;

  case 41: /* type_specifier: VOID  */
#line 239 "AST.y"
           { (yyval.node) = create_leaf_node(AST_TYPE_SPECIFIER, "void"); }
#line 2352 "../build/parser.cpp"
    break;

  case 42: /* type_specifier: CHAR  */
#line 240 "AST.y"
           { (yyval.node) = create_leaf_node(AST_TYPE_SPECIFIER, "char"); }
#line 2358 "../build/parser.cpp"
    break;

  case 43: /* type_specifier: SHORT  */
#line 241 "AST.y"
            { (yyval.node) = create_leaf_node(AST_TYPE_SPECIFIER, "short"); }
#line 2364 "../build/parser.cpp"
    break;

  case 44: /* type_specifier: INT  */
#line 242 "AST.y"
          { (yyval.node) = create_leaf_node(AST_TYPE_SPECIFIER, "int"); }
#line 2370 "../build/parser.cpp"
    break;

  case 45: /* type_specifier: LONG  */
#line 243 "AST.y"
           { (yyval.node) = create_leaf_node(AST_TYPE_SPECIFIER, "long"); }
#line 2376 "../build/parser.cpp"
    break;

  case 46: /* type_specifier: FLOAT  */
#line 244 "AST.y"
            { (yyval.node) = create_leaf_node(AST_TYPE_SPECIFIER, "float"); }
#line 2382 "../build/parser.cpp"
    break;

  case 47: /* type_specifier: DOUBLE  */
#line 245 "AST.y"
             { (yyval.node) = create_leaf_node(AST_TYPE_SPECIFIER, "double"); }
#line 2388 "../build/parser.cpp"
    break;

  case 48: /* type_specifier: SIGNED  */
#line 246 "AST.y"
             { (yyval.node) = create_leaf_node(AST_TYPE_SPECIFIER, "signed"); }
#line 2394 "../build/parser.cpp"
    break;

  case 49: /* type_specifier: UNSIGNED  */
#line 247 "AST.y"
               { (yyval.node) = create_leaf_node(AST_TYPE_SPECIFIER, "unsigned"); }
#line 2400 "../build/parser.cpp"
    break;

  case 50: /* type_specifier: BOOL  */
#line 248 "AST.y"
           { (yyval.node) = create_leaf_node(AST_TYPE_SPECIFIER, "bool"); }
#line 2406 "../build/parser.cpp"
    break;

  case 51: /* type_specifier: struct_or_union_specifier  */
#line 249 "AST.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 2412 "../build/parser.cpp"
    break;

  case 52: /* type_specifier: enum_specifier  */
#line 250 "AST.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2418 "../build/parser.cpp"
    break;

  case 53: /* type_specifier: TYPEDEF_NAME  */
#line 251 "AST.y"
                   { (yyval.node) = create_leaf_node(AST_TYPE_SPECIFIER, (yyvsp[0].sval)); }
#line 2424 "../build/parser.cpp"
    break;

  case 54: /* type_qualifier: CONST  */
#line 255 "AST.y"
            { (yyval.node) = create_leaf_node(AST_TYPE_QUALIFIER, "const"); }
#line 2430 "../build/parser.cpp"
    break;

  case 55: /* type_qualifier: RESTRICT  */
#line 256 "AST.y"
               { (yyval.node) = create_leaf_node(AST_TYPE_QUALIFIER, "restrict"); }
#line 2436 "../build/parser.cpp"
    break;

  case 56: /* type_qualifier: VOLATILE  */
#line 257 "AST.y"
               { (yyval.node) = create_leaf_node(AST_TYPE_QUALIFIER, "volatile"); }
#line 2442 "../build/parser.cpp"
    break;

  case 57: /* function_specifier: INLINE  */
#line 261 "AST.y"
             { (yyval.node) = create_leaf_node(AST_FUNCTION_SPECIFIER, "inline"); }
#line 2448 "../build/parser.cpp"
    break;

  case 58: /* function_specifier: NORETURN  */
#line 262 "AST.y"
               { (yyval.node) = create_leaf_node(AST_FUNCTION_SPECIFIER, "noreturn"); }
#line 2454 "../build/parser.cpp"
    break;

  case 59: /* alignment_specifier: ALIGNAS LPAREN type_name RPAREN  */
#line 266 "AST.y"
                                      { (yyval.node) = create_ast_node(AST_ALIGNMENT_SPECIFIER, 1, (yyvsp[-1].node)); }
#line 2460 "../build/parser.cpp"
    break;

  case 60: /* alignment_specifier: ALIGNAS LPAREN constant_expression RPAREN  */
#line 267 "AST.y"
                                                { 
           (yyval.node) = create_ast_node(AST_ALIGNMENT_SPECIFIER, 1, (yyvsp[-1].node)); 
        }
#line 2468 "../build/parser.cpp"
    break;

  case 61: /* declarator: pointer direct_declarator  */
#line 274 "AST.y"
                                { (yyval.node) = create_ast_node(AST_DECLARATOR, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2474 "../build/parser.cpp"
    break;

  case 62: /* declarator: direct_declarator  */
#line 275 "AST.y"
                        { (yyval.node) = create_ast_node(AST_DECLARATOR, 1, (yyvsp[0].node)); }
#line 2480 "../build/parser.cpp"
    break;

  case 63: /* pointer: MULTIPLY  */
#line 279 "AST.y"
               { (yyval.node) = create_ast_node(AST_POINTER, 1, NULL);}
#line 2486 "../build/parser.cpp"
    break;

  case 64: /* pointer: MULTIPLY type_qualifier_list  */
#line 280 "AST.y"
                                   { (yyval.node) = create_ast_node(AST_POINTER, 1, (yyvsp[0].node));}
#line 2492 "../build/parser.cpp"
    break;

  case 65: /* pointer: MULTIPLY pointer  */
#line 281 "AST.y"
                       { (yyval.node) = create_ast_node(AST_POINTER, 1, (yyvsp[0].node)); }
#line 2498 "../build/parser.cpp"
    break;

  case 66: /* pointer: MULTIPLY type_qualifier_list pointer  */
#line 282 "AST.y"
                                           { (yyval.node) = create_ast_node(AST_POINTER, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2504 "../build/parser.cpp"
    break;

  case 67: /* direct_declarator: IDENTIFIER  */
#line 286 "AST.y"
                 { (yyval.node) = create_leaf_node(AST_IDENTIFIER, (yyvsp[0].sval)); }
#line 2510 "../build/parser.cpp"
    break;

  case 68: /* direct_declarator: LPAREN declarator RPAREN  */
#line 287 "AST.y"
                               { (yyval.node) = (yyvsp[-1].node); }
#line 2516 "../build/parser.cpp"
    break;

  case 69: /* direct_declarator: direct_declarator LSQBRACKET RSQBRACKET  */
#line 288 "AST.y"
                                              { (yyval.node) = create_ast_node(AST_ARRAY_ACCESS, 1, (yyvsp[-2].node)); }
#line 2522 "../build/parser.cpp"
    break;

  case 70: /* direct_declarator: direct_declarator LSQBRACKET assignment_expression RSQBRACKET  */
#line 289 "AST.y"
                                                                    { (yyval.node) = create_ast_node(AST_ARRAY_ACCESS, 2, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2528 "../build/parser.cpp"
    break;

  case 71: /* direct_declarator: direct_declarator LPAREN RPAREN  */
#line 290 "AST.y"
                                      { (yyval.node) = create_ast_node(AST_FUNCTION_DECLARATOR, 1, (yyvsp[-2].node)); }
#line 2534 "../build/parser.cpp"
    break;

  case 72: /* direct_declarator: direct_declarator LPAREN argument_expression_list RPAREN  */
#line 291 "AST.y"
                                                                { (yyval.node) = create_ast_node(AST_FUNCTION_CALL, 2, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2540 "../build/parser.cpp"
    break;

  case 73: /* direct_declarator: direct_declarator LPAREN parameter_type_list RPAREN  */
#line 292 "AST.y"
                                                           { (yyval.node) = create_ast_node(AST_FUNCTION_DECLARATOR, 2, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2546 "../build/parser.cpp"
    break;

  case 74: /* struct_or_union_specifier: STRUCT LBRACE RBRACE  */
#line 296 "AST.y"
                           { (yyval.node) = NULL; /* Empty struct normalized to NULL at grammar level */ }
#line 2552 "../build/parser.cpp"
    break;

  case 75: /* struct_or_union_specifier: STRUCT LBRACE struct_declaration_list RBRACE  */
#line 297 "AST.y"
                                                   { (yyval.node) = create_ast_node(AST_STRUCT_DECL, 1, (yyvsp[-1].node)); }
#line 2558 "../build/parser.cpp"
    break;

  case 76: /* struct_or_union_specifier: STRUCT IDENTIFIER LBRACE RBRACE  */
#line 298 "AST.y"
                                      { (yyval.node) = NULL; /* Empty named struct normalized to NULL at grammar level */ }
#line 2564 "../build/parser.cpp"
    break;

  case 77: /* struct_or_union_specifier: STRUCT IDENTIFIER LBRACE struct_declaration_list RBRACE  */
#line 299 "AST.y"
                                                              { (yyval.node) = create_ast_node(AST_STRUCT_DECL, 2, create_leaf_node(AST_IDENTIFIER, (yyvsp[-3].sval)), (yyvsp[-1].node)); }
#line 2570 "../build/parser.cpp"
    break;

  case 78: /* struct_or_union_specifier: STRUCT IDENTIFIER  */
#line 300 "AST.y"
                        { (yyval.node) = create_ast_node(AST_STRUCT_DECL, 1, create_leaf_node(AST_IDENTIFIER, (yyvsp[0].sval))); }
#line 2576 "../build/parser.cpp"
    break;

  case 79: /* struct_or_union_specifier: UNION LBRACE RBRACE  */
#line 301 "AST.y"
                          { (yyval.node) = NULL; /* Empty union normalized to NULL at grammar level */ }
#line 2582 "../build/parser.cpp"
    break;

  case 80: /* struct_or_union_specifier: UNION LBRACE struct_declaration_list RBRACE  */
#line 302 "AST.y"
                                                  { (yyval.node) = create_ast_node(AST_STRUCT_DECL, 1, (yyvsp[-1].node)); }
#line 2588 "../build/parser.cpp"
    break;

  case 81: /* struct_or_union_specifier: UNION IDENTIFIER LBRACE RBRACE  */
#line 303 "AST.y"
                                     { (yyval.node) = NULL; /* Empty named union normalized to NULL at grammar level */ }
#line 2594 "../build/parser.cpp"
    break;

  case 82: /* struct_or_union_specifier: UNION IDENTIFIER LBRACE struct_declaration_list RBRACE  */
#line 304 "AST.y"
                                                             { (yyval.node) = create_ast_node(AST_STRUCT_DECL, 2, create_leaf_node(AST_IDENTIFIER, (yyvsp[-3].sval)), (yyvsp[-1].node)); }
#line 2600 "../build/parser.cpp"
    break;

  case 83: /* struct_or_union_specifier: UNION IDENTIFIER  */
#line 305 "AST.y"
                       { (yyval.node) = create_ast_node(AST_STRUCT_DECL, 1, create_leaf_node(AST_IDENTIFIER, (yyvsp[0].sval))); }
#line 2606 "../build/parser.cpp"
    break;

  case 84: /* struct_declaration_list: struct_declaration  */
#line 309 "AST.y"
                         { (yyval.node) = makelist((yyvsp[0].node)); }
#line 2612 "../build/parser.cpp"
    break;

  case 85: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 310 "AST.y"
                                                 { (yyval.node) = append_list((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2618 "../build/parser.cpp"
    break;

  case 86: /* struct_declaration: specifier_qualifier_list SEMICOLON  */
#line 314 "AST.y"
                                         { (yyval.node) = (yyvsp[-1].node); }
#line 2624 "../build/parser.cpp"
    break;

  case 87: /* struct_declaration: specifier_qualifier_list struct_declarator_list SEMICOLON  */
#line 315 "AST.y"
                                                                { (yyval.node) = create_ast_node(AST_DECLARATION, 2, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 2630 "../build/parser.cpp"
    break;

  case 88: /* specifier_qualifier_list: type_specifier  */
#line 319 "AST.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2636 "../build/parser.cpp"
    break;

  case 89: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 320 "AST.y"
                                              { (yyval.node) = append_list((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2642 "../build/parser.cpp"
    break;

  case 90: /* specifier_qualifier_list: type_qualifier  */
#line 321 "AST.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2648 "../build/parser.cpp"
    break;

  case 91: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 322 "AST.y"
                                              { (yyval.node) = append_list((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2654 "../build/parser.cpp"
    break;

  case 92: /* specifier_qualifier_list: alignment_specifier  */
#line 323 "AST.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2660 "../build/parser.cpp"
    break;

  case 93: /* specifier_qualifier_list: alignment_specifier specifier_qualifier_list  */
#line 324 "AST.y"
                                                   { (yyval.node) = append_list((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2666 "../build/parser.cpp"
    break;

  case 94: /* struct_declarator_list: struct_declarator  */
#line 328 "AST.y"
                        { (yyval.node) = makelist((yyvsp[0].node)); }
#line 2672 "../build/parser.cpp"
    break;

  case 95: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 329 "AST.y"
                                                     { (yyval.node) = append_list((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2678 "../build/parser.cpp"
    break;

  case 96: /* struct_declarator: declarator  */
#line 333 "AST.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2684 "../build/parser.cpp"
    break;

  case 97: /* struct_declarator: declarator COLON constant_expression  */
#line 334 "AST.y"
                                           { (yyval.node) = create_ast_node(AST_DECLARATOR, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2690 "../build/parser.cpp"
    break;

  case 98: /* struct_declarator: COLON constant_expression  */
#line 335 "AST.y"
                                { (yyval.node) = create_ast_node(AST_DECLARATOR, 1, (yyvsp[0].node)); }
#line 2696 "../build/parser.cpp"
    break;

  case 99: /* enum_specifier: ENUM LBRACE RBRACE  */
#line 339 "AST.y"
                         { (yyval.node) = NULL; /* Empty enum normalized to NULL at grammar level */ }
#line 2702 "../build/parser.cpp"
    break;

  case 100: /* enum_specifier: ENUM LBRACE enumerator_list RBRACE  */
#line 340 "AST.y"
                                         { (yyval.node) = create_ast_node(AST_ENUM, 1, (yyvsp[-1].node)); }
#line 2708 "../build/parser.cpp"
    break;

  case 101: /* enum_specifier: ENUM IDENTIFIER LBRACE RBRACE  */
#line 341 "AST.y"
                                    { (yyval.node) = NULL; /* Empty named enum normalized to NULL at grammar level */ }
#line 2714 "../build/parser.cpp"
    break;

  case 102: /* enum_specifier: ENUM IDENTIFIER LBRACE enumerator_list RBRACE  */
#line 342 "AST.y"
                                                    { (yyval.node) = create_ast_node(AST_ENUM, 2, create_leaf_node(AST_IDENTIFIER, (yyvsp[-3].sval)), (yyvsp[-1].node)); }
#line 2720 "../build/parser.cpp"
    break;

  case 103: /* enum_specifier: ENUM IDENTIFIER  */
#line 343 "AST.y"
                      { (yyval.node) = create_ast_node(AST_ENUM, 1, create_leaf_node(AST_IDENTIFIER, (yyvsp[0].sval))); }
#line 2726 "../build/parser.cpp"
    break;

  case 104: /* enumerator_list: enumeration_constant  */
#line 347 "AST.y"
                           { (yyval.node) = makelist((yyvsp[0].node)); }
#line 2732 "../build/parser.cpp"
    break;

  case 105: /* enumerator_list: enumerator_list COMMA enumeration_constant  */
#line 348 "AST.y"
                                                 { (yyval.node) = append_list((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2738 "../build/parser.cpp"
    break;

  case 106: /* enumeration_constant: IDENTIFIER  */
#line 352 "AST.y"
                 { (yyval.node) = create_leaf_node(AST_IDENTIFIER, (yyvsp[0].sval)); }
#line 2744 "../build/parser.cpp"
    break;

  case 107: /* type_name: specifier_qualifier_list  */
#line 356 "AST.y"
                               { (yyval.node) = (yyvsp[0].node); }
#line 2750 "../build/parser.cpp"
    break;

  case 108: /* type_name: specifier_qualifier_list abstract_declarator  */
#line 357 "AST.y"
                                                   { (yyval.node) = create_ast_node(AST_TYPE_NAME, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2756 "../build/parser.cpp"
    break;

  case 109: /* abstract_declarator: pointer  */
#line 361 "AST.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2762 "../build/parser.cpp"
    break;

  case 110: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 362 "AST.y"
                                         { (yyval.node) = create_ast_node(AST_DECLARATOR, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2768 "../build/parser.cpp"
    break;

  case 111: /* abstract_declarator: direct_abstract_declarator  */
#line 363 "AST.y"
                                 { (yyval.node) = (yyvsp[0].node); }
#line 2774 "../build/parser.cpp"
    break;

  case 112: /* direct_abstract_declarator: LPAREN abstract_declarator RPAREN  */
#line 367 "AST.y"
                                        { (yyval.node) = (yyvsp[-1].node); }
#line 2780 "../build/parser.cpp"
    break;

  case 113: /* direct_abstract_declarator: LSQBRACKET RSQBRACKET  */
#line 368 "AST.y"
                            { (yyval.node) = create_ast_node(AST_ARRAY_ACCESS, 0); }
#line 2786 "../build/parser.cpp"
    break;

  case 114: /* direct_abstract_declarator: LSQBRACKET type_qualifier_list assignment_expression RSQBRACKET  */
#line 369 "AST.y"
                                                                      { (yyval.node) = create_ast_node(AST_ARRAY_ACCESS, 2, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 2792 "../build/parser.cpp"
    break;

  case 115: /* direct_abstract_declarator: direct_abstract_declarator LSQBRACKET assignment_expression RSQBRACKET  */
#line 370 "AST.y"
                                                                             { (yyval.node) = create_ast_node(AST_ARRAY_ACCESS, 2, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2798 "../build/parser.cpp"
    break;

  case 116: /* direct_abstract_declarator: LPAREN parameter_type_list RPAREN  */
#line 371 "AST.y"
                                        { (yyval.node) = create_ast_node(AST_FUNCTION_DECLARATOR, 1, (yyvsp[-1].node)); }
#line 2804 "../build/parser.cpp"
    break;

  case 117: /* direct_abstract_declarator: direct_abstract_declarator LPAREN parameter_type_list RPAREN  */
#line 372 "AST.y"
                                                                   { (yyval.node) = create_ast_node(AST_FUNCTION_DECLARATOR, 2, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2810 "../build/parser.cpp"
    break;

  case 118: /* parameter_type_list: parameter_list  */
#line 376 "AST.y"
                     { (yyval.node) = create_ast_node(AST_PARAM_LIST, 1, (yyvsp[0].node)); }
#line 2816 "../build/parser.cpp"
    break;

  case 119: /* parameter_type_list: parameter_list COMMA ELLIPSIS  */
#line 377 "AST.y"
                                    { (yyval.node) = create_ast_node(AST_PARAM_LIST, 2, (yyvsp[-2].node), create_leaf_node(AST_IDENTIFIER, "...")); }
#line 2822 "../build/parser.cpp"
    break;

  case 120: /* parameter_list: parameter_declaration  */
#line 381 "AST.y"
                            { (yyval.node) = makelist((yyvsp[0].node)); }
#line 2828 "../build/parser.cpp"
    break;

  case 121: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 382 "AST.y"
                                                 { (yyval.node) = append_list((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2834 "../build/parser.cpp"
    break;

  case 122: /* parameter_declaration: declaration_specifiers declarator  */
#line 386 "AST.y"
                                        { (yyval.node) = create_ast_node(AST_PARAM, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2840 "../build/parser.cpp"
    break;

  case 123: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 387 "AST.y"
                                                 { (yyval.node) = create_ast_node(AST_PARAM, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2846 "../build/parser.cpp"
    break;

  case 124: /* parameter_declaration: declaration_specifiers  */
#line 388 "AST.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 2852 "../build/parser.cpp"
    break;

  case 125: /* initializer: assignment_expression  */
#line 392 "AST.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2858 "../build/parser.cpp"
    break;

  case 126: /* initializer: LBRACE initializer_list RBRACE  */
#line 393 "AST.y"
                                     { (yyval.node) = create_ast_node(AST_INIT_LIST, 1, (yyvsp[-1].node)); }
#line 2864 "../build/parser.cpp"
    break;

  case 127: /* initializer: LBRACE initializer_list COMMA RBRACE  */
#line 394 "AST.y"
                                           { (yyval.node) = create_ast_node(AST_INIT_LIST, 1, (yyvsp[-2].node)); }
#line 2870 "../build/parser.cpp"
    break;

  case 128: /* initializer_list: initializer  */
#line 398 "AST.y"
                  { (yyval.node) = makelist((yyvsp[0].node)); }
#line 2876 "../build/parser.cpp"
    break;

  case 129: /* initializer_list: initializer_list COMMA initializer  */
#line 399 "AST.y"
                                         { (yyval.node) = append_list((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2882 "../build/parser.cpp"
    break;

  case 130: /* statement: expression_statement  */
#line 404 "AST.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2888 "../build/parser.cpp"
    break;

  case 131: /* statement: selection_statement  */
#line 405 "AST.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2894 "../build/parser.cpp"
    break;

  case 132: /* statement: iteration_statement  */
#line 406 "AST.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2900 "../build/parser.cpp"
    break;

  case 133: /* statement: jump_statement  */
#line 407 "AST.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2906 "../build/parser.cpp"
    break;

  case 134: /* statement: compound_statement  */
#line 408 "AST.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2912 "../build/parser.cpp"
    break;

  case 135: /* statement: labeled_statement  */
#line 409 "AST.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2918 "../build/parser.cpp"
    break;

  case 136: /* selection_statement: conditional_statement  */
#line 414 "AST.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2924 "../build/parser.cpp"
    break;

  case 137: /* selection_statement: switch_statement  */
#line 415 "AST.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2930 "../build/parser.cpp"
    break;

  case 138: /* jump_statement: RETURN expression SEMICOLON  */
#line 420 "AST.y"
                                  { (yyval.node) = create_ast_node(AST_RETURN, 1, (yyvsp[-1].node)); }
#line 2936 "../build/parser.cpp"
    break;

  case 139: /* jump_statement: RETURN SEMICOLON  */
#line 421 "AST.y"
                       { (yyval.node) = create_ast_node(AST_RETURN, 0); }
#line 2942 "../build/parser.cpp"
    break;

  case 140: /* jump_statement: BREAK SEMICOLON  */
#line 422 "AST.y"
                      { (yyval.node) = create_ast_node(AST_BREAK, 0); }
#line 2948 "../build/parser.cpp"
    break;

  case 141: /* jump_statement: CONTINUE SEMICOLON  */
#line 423 "AST.y"
                         { (yyval.node) = create_ast_node(AST_CONTINUE, 0); }
#line 2954 "../build/parser.cpp"
    break;

  case 142: /* jump_statement: GOTO IDENTIFIER SEMICOLON  */
#line 424 "AST.y"
                                { 
        (yyval.node) = create_ast_node(AST_GOTO_STMT, 1, create_leaf_node(AST_IDENTIFIER, (yyvsp[-1].sval))); 
    }
#line 2962 "../build/parser.cpp"
    break;

  case 143: /* iteration_statement: DO statement WHILE LPAREN expression RPAREN SEMICOLON  */
#line 430 "AST.y"
                                                            { 
        // Grammar-level dead loop elimination: empty body or always-false condition
        if (is_empty_statement((yyvsp[-5].node)) || is_always_false_condition((yyvsp[-2].node))) {
            (yyval.node) = NULL; /* Dead do-while loop eliminated at grammar level */
        } else {
            (yyval.node) = create_ast_node(AST_ITERATION_STMT, 2, (yyvsp[-5].node), (yyvsp[-2].node));
        }
    }
#line 2975 "../build/parser.cpp"
    break;

  case 144: /* iteration_statement: WHILE LPAREN expression RPAREN statement  */
#line 438 "AST.y"
                                               { 
        // Grammar-level dead loop elimination: always-false condition or empty body
        if (is_always_false_condition((yyvsp[-2].node)) || is_empty_statement((yyvsp[0].node))) {
            (yyval.node) = NULL; /* Dead while loop eliminated at grammar level */
        } else {
            (yyval.node) = create_ast_node(AST_ITERATION_STMT, 2, (yyvsp[-2].node), (yyvsp[0].node));
        }
    }
#line 2988 "../build/parser.cpp"
    break;

  case 145: /* iteration_statement: FOR LPAREN type_specifier expression_statement expression_statement expression_opt RPAREN statement  */
#line 446 "AST.y"
                                                                                                          { 
        // Grammar-level dead loop elimination: always-false condition or empty body
        if (is_always_false_condition((yyvsp[-3].node)) || is_empty_statement((yyvsp[0].node))) {
            (yyval.node) = NULL; /* Dead for loop eliminated at grammar level */
        } else {
            (yyval.node) = create_ast_node(AST_ITERATION_STMT, 4, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
        }
    }
#line 3001 "../build/parser.cpp"
    break;

  case 146: /* conditional_statement: IF LPAREN expression RPAREN statement  */
#line 458 "AST.y"
                                                                  { 
        /* Grammar-level condition optimization */
        if (is_always_false_condition((yyvsp[-2].node))) {
            (yyval.node) = NULL; /* Always-false if eliminated */
        } else if (is_empty_statement((yyvsp[0].node))) {
            (yyval.node) = NULL; /* If with empty body eliminated */
        } else {
            (yyval.node) = create_ast_node(AST_IF, 2, (yyvsp[-2].node), (yyvsp[0].node)); 
        }
    }
#line 3016 "../build/parser.cpp"
    break;

  case 147: /* conditional_statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 468 "AST.y"
                                                           { 
        /* Grammar-level condition optimization with else */
        if (is_always_false_condition((yyvsp[-4].node))) {
            /* Always false - replace with else branch */
            if (is_empty_statement((yyvsp[0].node))) {
                (yyval.node) = NULL; /* Both branches empty */
            } else {
                (yyval.node) = (yyvsp[0].node); /* Use else branch directly */
            }
        } else if (is_empty_statement((yyvsp[-2].node)) && is_empty_statement((yyvsp[0].node))) {
            (yyval.node) = NULL; /* Both branches empty */
        } 
        else if (is_empty_statement((yyvsp[0].node))) {
            // Else branch empty, keep only if branch
            (yyval.node) = create_ast_node(AST_IF, 2, (yyvsp[-4].node), (yyvsp[-2].node)); 
        }
        else {
            ASTNode* else_node = create_ast_node(AST_ELSE, 1, (yyvsp[0].node));
            (yyval.node) = create_ast_node(AST_IF, 3, (yyvsp[-4].node), (yyvsp[-2].node), else_node); 
        }
    }
#line 3042 "../build/parser.cpp"
    break;

  case 148: /* switch_statement: SWITCH LPAREN expression RPAREN statement  */
#line 492 "AST.y"
                                                {
        (yyval.node) = create_ast_node(AST_SWITCH, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3050 "../build/parser.cpp"
    break;

  case 149: /* labeled_statement: IDENTIFIER COLON statement  */
#line 498 "AST.y"
                                 { 
        (yyval.node) = create_ast_node(AST_LABELED_STMT, 2, create_leaf_node(AST_IDENTIFIER, (yyvsp[-2].sval)), (yyvsp[0].node)); 
    }
#line 3058 "../build/parser.cpp"
    break;

  case 150: /* labeled_statement: CASE constant_expression COLON statement  */
#line 501 "AST.y"
                                               {
        (yyval.node) = create_ast_node(AST_CASE, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3066 "../build/parser.cpp"
    break;

  case 151: /* labeled_statement: DEFAULT COLON statement  */
#line 504 "AST.y"
                              {
        (yyval.node) = create_ast_node(AST_DEFAULT, 1, (yyvsp[0].node));
    }
#line 3074 "../build/parser.cpp"
    break;

  case 152: /* expression_opt: expression  */
#line 509 "AST.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 3080 "../build/parser.cpp"
    break;

  case 153: /* expression_statement: SEMICOLON  */
#line 512 "AST.y"
                { (yyval.node) = NULL; }
#line 3086 "../build/parser.cpp"
    break;

  case 154: /* expression_statement: expression SEMICOLON  */
#line 513 "AST.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 3092 "../build/parser.cpp"
    break;

  case 155: /* primary_expression: IDENTIFIER  */
#line 517 "AST.y"
                 { (yyval.node) = create_leaf_node(AST_IDENTIFIER, (yyvsp[0].sval)); }
#line 3098 "../build/parser.cpp"
    break;

  case 156: /* primary_expression: NUMBER  */
#line 518 "AST.y"
             { (yyval.node) = create_leaf_node(AST_NUMBER, (yyvsp[0].sval)); }
#line 3104 "../build/parser.cpp"
    break;

  case 157: /* primary_expression: CHAR_LITERAL  */
#line 519 "AST.y"
                   { (yyval.node) = create_leaf_node(AST_LITERAL, (yyvsp[0].sval)); }
#line 3110 "../build/parser.cpp"
    break;

  case 158: /* primary_expression: STRING_LITERAL  */
#line 520 "AST.y"
                     { (yyval.node) = create_leaf_node(AST_LITERAL, (yyvsp[0].sval)); }
#line 3116 "../build/parser.cpp"
    break;

  case 159: /* primary_expression: LPAREN expression RPAREN  */
#line 521 "AST.y"
                               { (yyval.node) = (yyvsp[-1].node); }
#line 3122 "../build/parser.cpp"
    break;

  case 160: /* postfix_expression: primary_expression  */
#line 526 "AST.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 3128 "../build/parser.cpp"
    break;

  case 161: /* postfix_expression: postfix_expression LSQBRACKET expression RSQBRACKET  */
#line 528 "AST.y"
        { (yyval.node) = create_ast_node(AST_ARRAY_ACCESS, 2, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 3134 "../build/parser.cpp"
    break;

  case 162: /* postfix_expression: postfix_expression DOT IDENTIFIER  */
#line 530 "AST.y"
        { (yyval.node) = create_ast_node(AST_MEMBER_ACCESS, 2, (yyvsp[-2].node), create_leaf_node(AST_IDENTIFIER, (yyvsp[0].sval))); }
#line 3140 "../build/parser.cpp"
    break;

  case 163: /* postfix_expression: postfix_expression ARROW IDENTIFIER  */
#line 532 "AST.y"
        { (yyval.node) = create_ast_node(AST_PTR_MEMBER_ACCESS, 2, (yyvsp[-2].node), create_leaf_node(AST_IDENTIFIER, (yyvsp[0].sval))); }
#line 3146 "../build/parser.cpp"
    break;

  case 164: /* postfix_expression: postfix_expression LPAREN argument_expression_list RPAREN  */
#line 534 "AST.y"
        { 
            // Grammar-level dead function call elimination
            if ((yyvsp[-3].node) && (yyvsp[-3].node)->type == AST_IDENTIFIER && is_dead_function_call((yyvsp[-3].node)->value.c_str())) {
                (yyval.node) = NULL; /* Dead function call eliminated at grammar level */
            } else {
                (yyval.node) = create_ast_node(AST_FUNCTION_CALL, 2, (yyvsp[-3].node), (yyvsp[-1].node));
            }
        }
#line 3159 "../build/parser.cpp"
    break;

  case 165: /* postfix_expression: postfix_expression LPAREN RPAREN  */
#line 543 "AST.y"
        { 
            // Grammar-level dead function call elimination
            if ((yyvsp[-2].node) && (yyvsp[-2].node)->type == AST_IDENTIFIER && is_dead_function_call((yyvsp[-2].node)->value.c_str())) {
                (yyval.node) = NULL; /* Dead function call eliminated at grammar level */
            } else {
                (yyval.node) = create_ast_node(AST_FUNCTION_CALL, 1, (yyvsp[-2].node));
            }
        }
#line 3172 "../build/parser.cpp"
    break;

  case 166: /* postfix_expression: postfix_expression INCREMENT  */
#line 552 "AST.y"
        { 
            // x++ becomes x = x + 1
            ASTNode* one = create_leaf_node(AST_NUMBER, "1");
            ASTNode* binary_op = create_ast_node(AST_PLUS, 2, (yyvsp[-1].node), one);
            (yyval.node) = create_ast_node(AST_ASSIGNMENT, 2, (yyvsp[-1].node), binary_op); 
        }
#line 3183 "../build/parser.cpp"
    break;

  case 167: /* postfix_expression: postfix_expression DECREMENT  */
#line 559 "AST.y"
        { 
            // x-- becomes x = x - 1
            ASTNode* one = create_leaf_node(AST_NUMBER, "1");
            ASTNode* binary_op = create_ast_node(AST_MINUS, 2, (yyvsp[-1].node), one);
            (yyval.node) = create_ast_node(AST_ASSIGNMENT, 2, (yyvsp[-1].node), binary_op); 
        }
#line 3194 "../build/parser.cpp"
    break;

  case 168: /* argument_expression_list: assignment_expression  */
#line 569 "AST.y"
                            { (yyval.node) = makelist((yyvsp[0].node)); }
#line 3200 "../build/parser.cpp"
    break;

  case 169: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 570 "AST.y"
                                                           { (yyval.node) = append_list((yyvsp[-2].node), (yyvsp[0].node)); }
#line 3206 "../build/parser.cpp"
    break;

  case 170: /* unary_expression: postfix_expression  */
#line 574 "AST.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 3212 "../build/parser.cpp"
    break;

  case 171: /* unary_expression: INCREMENT unary_expression  */
#line 575 "AST.y"
                                 { 
        // ++x becomes x = x + 1
        ASTNode* one = create_leaf_node(AST_NUMBER, "1");
        ASTNode* binary_op = create_ast_node(AST_PLUS, 2, (yyvsp[0].node), one);
        (yyval.node) = create_ast_node(AST_ASSIGNMENT, 2, (yyvsp[0].node), binary_op); 
    }
#line 3223 "../build/parser.cpp"
    break;

  case 172: /* unary_expression: DECREMENT unary_expression  */
#line 581 "AST.y"
                                 { 
        // --x becomes x = x - 1
        ASTNode* one = create_leaf_node(AST_NUMBER, "1");
        ASTNode* binary_op = create_ast_node(AST_MINUS, 2, (yyvsp[0].node), one);
        (yyval.node) = create_ast_node(AST_ASSIGNMENT, 2, (yyvsp[0].node), binary_op); 
    }
#line 3234 "../build/parser.cpp"
    break;

  case 173: /* unary_expression: unary_operator cast_expression  */
#line 586 "AST.y"
                                          { 
        // Handle unary operators with appropriate node types
        if ((yyvsp[-1].node)->type == AST_UNARY_MINUS) {
            (yyval.node) = create_ast_node(AST_UNARY_MINUS, 1, (yyvsp[0].node));
        } else if ((yyvsp[-1].node)->type == AST_UNARY_PLUS) {
            (yyval.node) = create_ast_node(AST_UNARY_PLUS, 1, (yyvsp[0].node));
        } else if ((yyvsp[-1].node)->type == AST_BIT_NOT) {
            (yyval.node) = create_ast_node(AST_BIT_NOT, 1, (yyvsp[0].node));
        } else if ((yyvsp[-1].node)->type == AST_LOGICAL_NOT) {
            (yyval.node) = create_ast_node(AST_LOGICAL_NOT, 1, (yyvsp[0].node));
        } else if ((yyvsp[-1].node)->type == AST_ADDRESS_OF) {
            (yyval.node) = create_ast_node(AST_ADDRESS_OF, 1, (yyvsp[0].node));
        } else if ((yyvsp[-1].node)->type == AST_POINTER_DEREF) {
            (yyval.node) = create_ast_node(AST_POINTER_DEREF, 1, (yyvsp[0].node));
        } else {
            (yyval.node) = create_ast_node(AST_TRANS, 2, (yyvsp[-1].node), (yyvsp[0].node));
        }
    }
#line 3257 "../build/parser.cpp"
    break;

  case 174: /* unary_expression: SIZEOF unary_expression  */
#line 604 "AST.y"
                              { (yyval.node) = create_ast_node(AST_SIZEOF, 1, (yyvsp[0].node)); }
#line 3263 "../build/parser.cpp"
    break;

  case 175: /* unary_expression: SIZEOF LPAREN type_name RPAREN  */
#line 605 "AST.y"
                                     { (yyval.node) = create_ast_node(AST_SIZEOF, 1, (yyvsp[-1].node)); }
#line 3269 "../build/parser.cpp"
    break;

  case 176: /* unary_operator: BIT_AND  */
#line 609 "AST.y"
              { (yyval.node) = create_leaf_node(AST_ADDRESS_OF, "&"); }
#line 3275 "../build/parser.cpp"
    break;

  case 177: /* unary_operator: MULTIPLY  */
#line 610 "AST.y"
               { (yyval.node) = create_leaf_node(AST_POINTER_DEREF, "*"); }
#line 3281 "../build/parser.cpp"
    break;

  case 178: /* unary_operator: PLUS  */
#line 611 "AST.y"
           { (yyval.node) = create_leaf_node(AST_UNARY_PLUS, "+"); }
#line 3287 "../build/parser.cpp"
    break;

  case 179: /* unary_operator: MINUS  */
#line 612 "AST.y"
            { (yyval.node) = create_leaf_node(AST_UNARY_MINUS, "-"); }
#line 3293 "../build/parser.cpp"
    break;

  case 180: /* unary_operator: BIT_NOT  */
#line 613 "AST.y"
              { (yyval.node) = create_leaf_node(AST_BIT_NOT, "~"); }
#line 3299 "../build/parser.cpp"
    break;

  case 181: /* unary_operator: NOT  */
#line 614 "AST.y"
          { (yyval.node) = create_leaf_node(AST_LOGICAL_NOT, "!"); }
#line 3305 "../build/parser.cpp"
    break;

  case 182: /* cast_expression: unary_expression  */
#line 618 "AST.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 3311 "../build/parser.cpp"
    break;

  case 183: /* cast_expression: LPAREN type_name RPAREN cast_expression  */
#line 619 "AST.y"
                                              { 
        /* Grammar-level type cast elimination for plagiarism detection 
        Converts: (float)(x + y) -> (x + y) */
        (yyval.node) = (yyvsp[0].node); 
        }
#line 3321 "../build/parser.cpp"
    break;

  case 184: /* multiplicative_expression: cast_expression  */
#line 627 "AST.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 3327 "../build/parser.cpp"
    break;

  case 185: /* multiplicative_expression: multiplicative_expression MULTIPLY cast_expression  */
#line 628 "AST.y"
                                                         { (yyval.node) = create_ast_node(AST_MUL, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3333 "../build/parser.cpp"
    break;

  case 186: /* multiplicative_expression: multiplicative_expression DIVIDE cast_expression  */
#line 629 "AST.y"
                                                       { (yyval.node) = create_ast_node(AST_DIV, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3339 "../build/parser.cpp"
    break;

  case 187: /* multiplicative_expression: multiplicative_expression MODULO cast_expression  */
#line 630 "AST.y"
                                                       { (yyval.node) = create_ast_node(AST_MOD, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3345 "../build/parser.cpp"
    break;

  case 188: /* additive_expression: multiplicative_expression  */
#line 634 "AST.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 3351 "../build/parser.cpp"
    break;

  case 189: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 635 "AST.y"
                                                         { (yyval.node) = create_ast_node(AST_PLUS, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3357 "../build/parser.cpp"
    break;

  case 190: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 636 "AST.y"
                                                          { (yyval.node) = create_ast_node(AST_MINUS, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3363 "../build/parser.cpp"
    break;

  case 191: /* shift_expression: additive_expression  */
#line 640 "AST.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 3369 "../build/parser.cpp"
    break;

  case 192: /* shift_expression: shift_expression SHIFT_LEFT additive_expression  */
#line 641 "AST.y"
                                                      { (yyval.node) = create_ast_node(AST_SHIFT_LEFT, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3375 "../build/parser.cpp"
    break;

  case 193: /* shift_expression: shift_expression SHIFT_RIGHT additive_expression  */
#line 642 "AST.y"
                                                       { (yyval.node) = create_ast_node(AST_SHIFT_RIGHT, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3381 "../build/parser.cpp"
    break;

  case 194: /* relational_expression: shift_expression  */
#line 646 "AST.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 3387 "../build/parser.cpp"
    break;

  case 195: /* relational_expression: relational_expression LESS shift_expression  */
#line 647 "AST.y"
                                                  { (yyval.node) = create_ast_node(AST_LT, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3393 "../build/parser.cpp"
    break;

  case 196: /* relational_expression: relational_expression GREATER shift_expression  */
#line 648 "AST.y"
                                                     { (yyval.node) = create_ast_node(AST_GT, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3399 "../build/parser.cpp"
    break;

  case 197: /* relational_expression: relational_expression LESS_EQUAL shift_expression  */
#line 649 "AST.y"
                                                        { (yyval.node) = create_ast_node(AST_LE, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3405 "../build/parser.cpp"
    break;

  case 198: /* relational_expression: relational_expression GREATER_EQUAL shift_expression  */
#line 650 "AST.y"
                                                           { (yyval.node) = create_ast_node(AST_GE, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3411 "../build/parser.cpp"
    break;

  case 199: /* equality_expression: relational_expression  */
#line 654 "AST.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 3417 "../build/parser.cpp"
    break;

  case 200: /* equality_expression: equality_expression EQUAL relational_expression  */
#line 655 "AST.y"
                                                      { (yyval.node) = create_ast_node(AST_EQUALS, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3423 "../build/parser.cpp"
    break;

  case 201: /* equality_expression: equality_expression NOT_EQUAL relational_expression  */
#line 656 "AST.y"
                                                          { (yyval.node) = create_ast_node(AST_NOT_EQUALS, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3429 "../build/parser.cpp"
    break;

  case 202: /* and_expression: equality_expression  */
#line 660 "AST.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 3435 "../build/parser.cpp"
    break;

  case 203: /* and_expression: and_expression BIT_AND equality_expression  */
#line 661 "AST.y"
                                                 { (yyval.node) = create_ast_node(AST_BIT_AND, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3441 "../build/parser.cpp"
    break;

  case 204: /* exclusive_or_expression: and_expression  */
#line 665 "AST.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 3447 "../build/parser.cpp"
    break;

  case 205: /* exclusive_or_expression: exclusive_or_expression BIT_XOR and_expression  */
#line 666 "AST.y"
                                                     { (yyval.node) = create_ast_node(AST_BIT_XOR, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3453 "../build/parser.cpp"
    break;

  case 206: /* inclusive_or_expression: exclusive_or_expression  */
#line 670 "AST.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 3459 "../build/parser.cpp"
    break;

  case 207: /* inclusive_or_expression: inclusive_or_expression BIT_OR exclusive_or_expression  */
#line 671 "AST.y"
                                                             { (yyval.node) = create_ast_node(AST_BIT_OR, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3465 "../build/parser.cpp"
    break;

  case 208: /* logical_and_expression: inclusive_or_expression  */
#line 675 "AST.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 3471 "../build/parser.cpp"
    break;

  case 209: /* logical_and_expression: logical_and_expression AND inclusive_or_expression  */
#line 676 "AST.y"
                                                         { (yyval.node) = create_ast_node(AST_LOGICAL_AND, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3477 "../build/parser.cpp"
    break;

  case 210: /* logical_or_expression: logical_and_expression  */
#line 680 "AST.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 3483 "../build/parser.cpp"
    break;

  case 211: /* logical_or_expression: logical_or_expression OR logical_and_expression  */
#line 681 "AST.y"
                                                      { (yyval.node) = create_ast_node(AST_LOGICAL_OR, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3489 "../build/parser.cpp"
    break;

  case 212: /* conditional_expression: logical_or_expression  */
#line 685 "AST.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 3495 "../build/parser.cpp"
    break;

  case 213: /* conditional_expression: logical_or_expression QUESTION expression COLON conditional_expression  */
#line 686 "AST.y"
                                                                             { (yyval.node) = create_ast_node(AST_CONDITIONAL, 3, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3501 "../build/parser.cpp"
    break;

  case 214: /* assignment_expression: conditional_expression  */
#line 690 "AST.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 3507 "../build/parser.cpp"
    break;

  case 215: /* assignment_expression: unary_expression ASSIGN assignment_expression  */
#line 691 "AST.y"
                                                    { (yyval.node) = create_ast_node(AST_ASSIGNMENT, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3513 "../build/parser.cpp"
    break;

  case 216: /* assignment_expression: unary_expression PLUS_ASSIGN assignment_expression  */
#line 692 "AST.y"
                                                         { 
        // x += y becomes x = x + y
        ASTNode* binary_op = create_ast_node(AST_PLUS, 2, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = create_ast_node(AST_ASSIGNMENT, 2, (yyvsp[-2].node), binary_op); 
    }
#line 3523 "../build/parser.cpp"
    break;

  case 217: /* assignment_expression: unary_expression MINUS_ASSIGN assignment_expression  */
#line 697 "AST.y"
                                                          { 
        // x -= y becomes x = x - y
        ASTNode* binary_op = create_ast_node(AST_MINUS, 2, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = create_ast_node(AST_ASSIGNMENT, 2, (yyvsp[-2].node), binary_op); 
    }
#line 3533 "../build/parser.cpp"
    break;

  case 218: /* assignment_expression: unary_expression MUL_ASSIGN assignment_expression  */
#line 702 "AST.y"
                                                        { 
        // x *= y becomes x = x * y
        ASTNode* binary_op = create_ast_node(AST_MUL, 2, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = create_ast_node(AST_ASSIGNMENT, 2, (yyvsp[-2].node), binary_op); 
    }
#line 3543 "../build/parser.cpp"
    break;

  case 219: /* assignment_expression: unary_expression DIV_ASSIGN assignment_expression  */
#line 707 "AST.y"
                                                        { 
        // x /= y becomes x = x / y
        ASTNode* binary_op = create_ast_node(AST_DIV, 2, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = create_ast_node(AST_ASSIGNMENT, 2, (yyvsp[-2].node), binary_op); 
    }
#line 3553 "../build/parser.cpp"
    break;

  case 220: /* assignment_expression: unary_expression MOD_ASSIGN assignment_expression  */
#line 712 "AST.y"
                                                        { 
        // x %= y becomes x = x % y
        ASTNode* binary_op = create_ast_node(AST_MOD, 2, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = create_ast_node(AST_ASSIGNMENT, 2, (yyvsp[-2].node), binary_op); 
    }
#line 3563 "../build/parser.cpp"
    break;

  case 221: /* assignment_expression: unary_expression SHIFT_LEFT_ASSIGN assignment_expression  */
#line 716 "AST.y"
                                                                    { 
        // x <<= y becomes x = x << y
        ASTNode* binary_op = create_ast_node(AST_SHIFT_LEFT, 2, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = create_ast_node(AST_ASSIGNMENT, 2, (yyvsp[-2].node), binary_op); 
    }
#line 3573 "../build/parser.cpp"
    break;

  case 222: /* assignment_expression: unary_expression SHIFT_RIGHT_ASSIGN assignment_expression  */
#line 721 "AST.y"
                                                                { 
        // x >>= y becomes x = x >> y
        ASTNode* binary_op = create_ast_node(AST_SHIFT_RIGHT, 2, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = create_ast_node(AST_ASSIGNMENT, 2, (yyvsp[-2].node), binary_op); 
    }
#line 3583 "../build/parser.cpp"
    break;

  case 223: /* assignment_expression: unary_expression BIT_AND_ASSIGN assignment_expression  */
#line 726 "AST.y"
                                                            { 
        // x &= y becomes x = x & y
        ASTNode* binary_op = create_ast_node(AST_BIT_AND, 2, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = create_ast_node(AST_ASSIGNMENT, 2, (yyvsp[-2].node), binary_op); 
    }
#line 3593 "../build/parser.cpp"
    break;

  case 224: /* assignment_expression: unary_expression BIT_XOR_ASSIGN assignment_expression  */
#line 731 "AST.y"
                                                            { 
        // x ^= y becomes x = x ^ y
        ASTNode* binary_op = create_ast_node(AST_BIT_XOR, 2, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = create_ast_node(AST_ASSIGNMENT, 2, (yyvsp[-2].node), binary_op); 
    }
#line 3603 "../build/parser.cpp"
    break;

  case 225: /* assignment_expression: unary_expression BIT_OR_ASSIGN assignment_expression  */
#line 736 "AST.y"
                                                           { 
        // x |= y becomes x = x | y
        ASTNode* binary_op = create_ast_node(AST_BIT_OR, 2, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = create_ast_node(AST_ASSIGNMENT, 2, (yyvsp[-2].node), binary_op); 
    }
#line 3613 "../build/parser.cpp"
    break;

  case 226: /* expression: assignment_expression  */
#line 744 "AST.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 3619 "../build/parser.cpp"
    break;

  case 227: /* expression: expression COMMA assignment_expression  */
#line 745 "AST.y"
                                             { (yyval.node) = create_ast_node(AST_COMMA, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3625 "../build/parser.cpp"
    break;

  case 228: /* constant_expression: conditional_expression  */
#line 749 "AST.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 3631 "../build/parser.cpp"
    break;


#line 3635 "../build/parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 752 "AST.y"
