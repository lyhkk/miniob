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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}


#line 115 "yacc_sql.cpp"

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

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_CALC = 9,                       /* CALC  */
  YYSYMBOL_SELECT = 10,                    /* SELECT  */
  YYSYMBOL_SHOW = 11,                      /* SHOW  */
  YYSYMBOL_SYNC = 12,                      /* SYNC  */
  YYSYMBOL_INSERT = 13,                    /* INSERT  */
  YYSYMBOL_DELETE = 14,                    /* DELETE  */
  YYSYMBOL_LIKE = 15,                      /* LIKE  */
  YYSYMBOL_NOT_LIKE = 16,                  /* NOT_LIKE  */
  YYSYMBOL_IN = 17,                        /* IN  */
  YYSYMBOL_NOT_IN = 18,                    /* NOT_IN  */
  YYSYMBOL_EXISTS = 19,                    /* EXISTS  */
  YYSYMBOL_NOT_EXISTS = 20,                /* NOT_EXISTS  */
  YYSYMBOL_GROUP_BY = 21,                  /* GROUP_BY  */
  YYSYMBOL_HAVING = 22,                    /* HAVING  */
  YYSYMBOL_ORDER_BY = 23,                  /* ORDER_BY  */
  YYSYMBOL_ASC = 24,                       /* ASC  */
  YYSYMBOL_DESC = 25,                      /* DESC  */
  YYSYMBOL_UPDATE = 26,                    /* UPDATE  */
  YYSYMBOL_IS = 27,                        /* IS  */
  YYSYMBOL_NOT = 28,                       /* NOT  */
  YYSYMBOL_NULL_T = 29,                    /* NULL_T  */
  YYSYMBOL_LENGTH = 30,                    /* LENGTH  */
  YYSYMBOL_ROUND = 31,                     /* ROUND  */
  YYSYMBOL_DATE_FORMAT = 32,               /* DATE_FORMAT  */
  YYSYMBOL_MAX = 33,                       /* MAX  */
  YYSYMBOL_MIN = 34,                       /* MIN  */
  YYSYMBOL_AVG = 35,                       /* AVG  */
  YYSYMBOL_SUM = 36,                       /* SUM  */
  YYSYMBOL_COUNT = 37,                     /* COUNT  */
  YYSYMBOL_AS = 38,                        /* AS  */
  YYSYMBOL_LBRACE = 39,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 40,                    /* RBRACE  */
  YYSYMBOL_COMMA = 41,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 42,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 43,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 44,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 45,                     /* INT_T  */
  YYSYMBOL_STRING_T = 46,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 47,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 48,                    /* DATE_T  */
  YYSYMBOL_HELP = 49,                      /* HELP  */
  YYSYMBOL_EXIT = 50,                      /* EXIT  */
  YYSYMBOL_DOT = 51,                       /* DOT  */
  YYSYMBOL_INTO = 52,                      /* INTO  */
  YYSYMBOL_VALUES = 53,                    /* VALUES  */
  YYSYMBOL_FROM = 54,                      /* FROM  */
  YYSYMBOL_WHERE = 55,                     /* WHERE  */
  YYSYMBOL_AND = 56,                       /* AND  */
  YYSYMBOL_OR = 57,                        /* OR  */
  YYSYMBOL_SET = 58,                       /* SET  */
  YYSYMBOL_ON = 59,                        /* ON  */
  YYSYMBOL_LOAD = 60,                      /* LOAD  */
  YYSYMBOL_DATA = 61,                      /* DATA  */
  YYSYMBOL_INFILE = 62,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 63,                   /* EXPLAIN  */
  YYSYMBOL_INNER = 64,                     /* INNER  */
  YYSYMBOL_JOIN = 65,                      /* JOIN  */
  YYSYMBOL_EQ = 66,                        /* EQ  */
  YYSYMBOL_LT = 67,                        /* LT  */
  YYSYMBOL_GT = 68,                        /* GT  */
  YYSYMBOL_LE = 69,                        /* LE  */
  YYSYMBOL_GE = 70,                        /* GE  */
  YYSYMBOL_NE = 71,                        /* NE  */
  YYSYMBOL_DATE_STR = 72,                  /* DATE_STR  */
  YYSYMBOL_NUMBER = 73,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 74,                     /* FLOAT  */
  YYSYMBOL_ID = 75,                        /* ID  */
  YYSYMBOL_SSS = 76,                       /* SSS  */
  YYSYMBOL_77_ = 77,                       /* '+'  */
  YYSYMBOL_78_ = 78,                       /* '-'  */
  YYSYMBOL_79_ = 79,                       /* '*'  */
  YYSYMBOL_80_ = 80,                       /* '/'  */
  YYSYMBOL_UMINUS = 81,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 82,                  /* $accept  */
  YYSYMBOL_commands = 83,                  /* commands  */
  YYSYMBOL_command_wrapper = 84,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 85,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 86,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 87,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 88,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 89,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 90,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 91,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 92,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 93,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 94,         /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 95,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 96,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 97,             /* attr_def_list  */
  YYSYMBOL_attr_def = 98,                  /* attr_def  */
  YYSYMBOL_null_option = 99,               /* null_option  */
  YYSYMBOL_number = 100,                   /* number  */
  YYSYMBOL_type = 101,                     /* type  */
  YYSYMBOL_insert_stmt = 102,              /* insert_stmt  */
  YYSYMBOL_order_by_list = 103,            /* order_by_list  */
  YYSYMBOL_sort_unit = 104,                /* sort_unit  */
  YYSYMBOL_sort_list = 105,                /* sort_list  */
  YYSYMBOL_value_list = 106,               /* value_list  */
  YYSYMBOL_value = 107,                    /* value  */
  YYSYMBOL_negative_value = 108,           /* negative_value  */
  YYSYMBOL_aggregate_type = 109,           /* aggregate_type  */
  YYSYMBOL_delete_stmt = 110,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 111,              /* update_stmt  */
  YYSYMBOL_update_kv_list = 112,           /* update_kv_list  */
  YYSYMBOL_update_kv = 113,                /* update_kv  */
  YYSYMBOL_select_stmt = 114,              /* select_stmt  */
  YYSYMBOL_from = 115,                     /* from  */
  YYSYMBOL_join_table = 116,               /* join_table  */
  YYSYMBOL_join_table_inner = 117,         /* join_table_inner  */
  YYSYMBOL_join_on = 118,                  /* join_on  */
  YYSYMBOL_group_by_expr = 119,            /* group_by_expr  */
  YYSYMBOL_having_expr = 120,              /* having_expr  */
  YYSYMBOL_calc_stmt = 121,                /* calc_stmt  */
  YYSYMBOL_expression_list = 122,          /* expression_list  */
  YYSYMBOL_expression = 123,               /* expression  */
  YYSYMBOL_sub_query_expr = 124,           /* sub_query_expr  */
  YYSYMBOL_aggr_func_expr = 125,           /* aggr_func_expr  */
  YYSYMBOL_func_expr = 126,                /* func_expr  */
  YYSYMBOL_func_type = 127,                /* func_type  */
  YYSYMBOL_rel_attr = 128,                 /* rel_attr  */
  YYSYMBOL_as_info = 129,                  /* as_info  */
  YYSYMBOL_rel_list = 130,                 /* rel_list  */
  YYSYMBOL_where = 131,                    /* where  */
  YYSYMBOL_is_null_comp = 132,             /* is_null_comp  */
  YYSYMBOL_condition = 133,                /* condition  */
  YYSYMBOL_comp_op = 134,                  /* comp_op  */
  YYSYMBOL_exists_op = 135,                /* exists_op  */
  YYSYMBOL_load_data_stmt = 136,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 137,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 138,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 139             /* opt_semicolon  */
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
typedef yytype_uint8 yy_state_t;

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  80
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   262

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  143
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  247

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   332


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
       2,     2,    79,    77,     2,    78,     2,    80,     2,     2,
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
      75,    76,    81
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   223,   223,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   254,   260,   265,   271,   277,   283,   289,
     296,   302,   310,   324,   334,   354,   357,   370,   379,   390,
     393,   397,   403,   406,   407,   408,   409,   412,   427,   430,
     437,   443,   449,   457,   464,   473,   476,   485,   496,   500,
     504,   517,   523,   530,   534,   540,   541,   542,   543,   544,
     547,   559,   582,   585,   597,   606,   644,   677,   681,   687,
     699,   711,   727,   730,   737,   740,   747,   750,   757,   764,
     774,   782,   797,   800,   803,   806,   809,   819,   822,   827,
     832,   835,   838,   844,   851,   876,   885,   886,   887,   891,
     896,   902,   907,   917,   920,   923,   930,   933,   947,   950,
     955,   959,   965,   968,   975,   982,   985,   991,   992,   993,
     994,   995,   996,   997,   998,   999,  1000,  1004,  1005,  1009,
    1022,  1030,  1040,  1041
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
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "CALC", "SELECT", "SHOW", "SYNC",
  "INSERT", "DELETE", "LIKE", "NOT_LIKE", "IN", "NOT_IN", "EXISTS",
  "NOT_EXISTS", "GROUP_BY", "HAVING", "ORDER_BY", "ASC", "DESC", "UPDATE",
  "IS", "NOT", "NULL_T", "LENGTH", "ROUND", "DATE_FORMAT", "MAX", "MIN",
  "AVG", "SUM", "COUNT", "AS", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "OR",
  "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "INNER", "JOIN", "EQ",
  "LT", "GT", "LE", "GE", "NE", "DATE_STR", "NUMBER", "FLOAT", "ID", "SSS",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "drop_index_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "null_option",
  "number", "type", "insert_stmt", "order_by_list", "sort_unit",
  "sort_list", "value_list", "value", "negative_value", "aggregate_type",
  "delete_stmt", "update_stmt", "update_kv_list", "update_kv",
  "select_stmt", "from", "join_table", "join_table_inner", "join_on",
  "group_by_expr", "having_expr", "calc_stmt", "expression_list",
  "expression", "sub_query_expr", "aggr_func_expr", "func_expr",
  "func_type", "rel_attr", "as_info", "rel_list", "where", "is_null_comp",
  "condition", "comp_op", "exists_op", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,    43,    45,    42,
      47,   332
};
#endif

#define YYPACT_NINF (-171)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     157,    21,    79,   155,   155,     1,  -171,   -41,   -37,   -36,
     -25,  -171,  -171,  -171,  -171,  -171,    11,   -35,   157,    34,
      52,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,    20,    24,    62,    73,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,    30,  -171,  -171,  -171,    95,  -171,
     155,  -171,  -171,   113,  -171,   -34,  -171,  -171,  -171,   119,
    -171,   111,  -171,    97,   102,  -171,   120,   127,   117,  -171,
    -171,  -171,  -171,   141,   136,  -171,   137,   155,   158,   162,
     -61,  -171,   155,   128,  -171,   155,   155,   155,   155,   156,
     155,   -26,   149,   152,   149,   133,    18,   134,   138,   139,
     143,   111,  -171,  -171,  -171,  -171,    56,  -171,   -49,   -49,
    -171,  -171,   155,   169,   144,   -33,  -171,  -171,    81,   190,
     173,  -171,   150,   180,  -171,   170,   -23,   182,   185,  -171,
    -171,  -171,  -171,   -33,   -31,  -171,  -171,    61,    68,   155,
     155,   203,    18,   155,   133,   149,   220,  -171,  -171,  -171,
    -171,   135,   138,   192,   160,   195,   172,  -171,   149,  -171,
    -171,  -171,  -171,   114,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,   155,    81,    81,     3,  -171,    81,   215,   198,     3,
     180,  -171,   165,   212,  -171,   171,  -171,   182,  -171,   202,
    -171,   168,   190,   216,  -171,     3,  -171,  -171,    68,   155,
    -171,   -20,   206,  -171,  -171,  -171,  -171,   207,  -171,  -171,
     -33,   203,  -171,   208,  -171,    -5,    71,   198,   198,  -171,
     122,   189,   215,   155,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,    81,   186,  -171,  -171,    68,  -171
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,    25,     0,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     142,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,    62,   106,   107,   108,    65,
      66,    67,    68,    69,     0,    60,    58,    59,   111,    61,
       0,   109,    98,     0,    88,   113,   102,   100,   101,     0,
      99,    89,    30,     0,     0,    31,     0,     0,     0,   140,
       1,   143,     2,     0,     0,    29,     0,     0,     0,     0,
       0,    97,     0,     0,   114,     0,     0,     0,     0,    90,
       0,   116,   118,     0,   118,     0,     0,     0,     0,     0,
       0,     0,   103,    96,   112,   110,     0,   115,    92,    93,
      94,    95,     0,     0,     0,   113,    78,    77,     0,    84,
       0,    70,     0,    72,   141,     0,     0,    35,     0,    33,
     104,    91,   105,   113,   116,   137,   138,     0,   119,     0,
       0,    86,     0,     0,     0,   118,     0,    43,    45,    46,
      44,    39,     0,     0,     0,   116,     0,    79,   118,   133,
     134,   135,   136,     0,   127,   128,   129,   130,   131,   132,
     123,     0,     0,     0,   124,    85,     0,    48,    55,    74,
      72,    71,     0,     0,    40,     0,    38,    35,    34,     0,
     117,     0,    84,     0,   120,   122,   125,   126,    87,     0,
      76,     0,     0,    73,   139,    41,    42,     0,    36,    32,
     113,    86,   121,    53,    49,    52,     0,    55,    55,    47,
      39,    82,    48,     0,    50,    51,    63,    64,    56,    57,
      37,     0,    80,    75,    54,    83,    81
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -171,  -171,   233,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,    55,    91,    25,  -171,  -171,
    -171,    22,  -171,    23,   -52,  -104,  -171,  -171,  -171,  -171,
      67,   104,   205,  -171,  -171,    19,  -171,    58,    41,  -171,
      -3,   -60,  -171,  -171,  -171,  -171,  -171,  -122,  -137,   -98,
    -171,  -170,  -171,  -171,  -171,  -171,  -171,  -171
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,   163,   137,   196,   217,   161,
      33,   210,   223,   224,   212,    62,   228,    63,    34,    35,
     155,   133,    36,   102,   126,   167,   242,   151,   187,    37,
      64,    65,    66,    67,    68,    69,    70,    99,   127,   129,
     180,   148,   181,   149,    38,    39,    40,    82
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      91,    71,   134,   144,    93,    93,   131,   168,    72,    45,
     124,    73,   206,   207,   114,   124,   208,    74,   115,   234,
     235,   165,   157,   158,   159,   160,    78,    41,   200,    42,
      97,    98,   116,   166,    80,   118,   119,   120,   121,    75,
      87,    94,    94,    95,    96,    97,    98,    45,   188,   125,
      76,    89,    55,    56,    57,    81,    59,   191,   226,    45,
      46,    47,    48,    49,    50,    51,    52,    53,   147,    54,
     202,   245,    95,    96,    97,    98,   169,   170,   171,   172,
      95,    96,    97,    98,   111,    43,    77,    44,   173,   184,
      55,    56,    57,   189,    59,    83,   140,   123,   231,    84,
     145,   146,    55,    56,    57,    58,    59,   227,    60,    61,
      45,    46,    47,    48,    49,    50,    51,    52,    53,   141,
      54,   205,   147,   147,   182,   183,   147,   174,   175,   176,
     177,   178,   179,    95,    96,    97,    98,    85,    95,    96,
      97,    98,   203,   204,   236,   237,    90,   185,    86,   225,
     193,   194,    92,    55,    56,    57,    58,    59,   100,    60,
      61,     1,     2,   193,   194,   101,     3,     4,     5,     6,
       7,     8,   103,   225,   195,   238,   239,   104,   105,   107,
     108,   147,     9,    10,    45,    46,    47,    48,    49,    50,
      51,    52,    53,   106,    54,   109,   110,   122,   112,    11,
      12,    13,   113,   117,   128,   130,    14,    15,   132,   142,
     135,   150,   152,   136,   138,    16,   153,    17,   139,   143,
      18,   154,   156,   162,   164,   186,   192,    55,    56,    57,
      58,    59,   198,    60,    61,   199,   124,   201,   209,   211,
     214,   215,   219,   220,   216,   222,   229,   230,   241,   233,
     166,    79,   218,   197,   243,   240,   244,   213,   190,    88,
     221,   246,   232
};

static const yytype_uint8 yycheck[] =
{
      60,     4,   106,   125,    38,    38,   104,   144,     7,    29,
      41,    52,   182,   183,    75,    41,   186,    54,    79,    24,
      25,   143,    45,    46,    47,    48,    61,     6,   165,     8,
      79,    80,    92,    64,     0,    95,    96,    97,    98,    75,
      10,    75,    75,    77,    78,    79,    80,    29,   152,    75,
      75,    54,    72,    73,    74,     3,    76,   155,    78,    29,
      30,    31,    32,    33,    34,    35,    36,    37,   128,    39,
     168,   241,    77,    78,    79,    80,    15,    16,    17,    18,
      77,    78,    79,    80,    87,     6,    75,     8,    27,   149,
      72,    73,    74,   153,    76,    75,    40,   100,   220,    75,
      19,    20,    72,    73,    74,    75,    76,   211,    78,    79,
      29,    30,    31,    32,    33,    34,    35,    36,    37,   122,
      39,   181,   182,   183,    56,    57,   186,    66,    67,    68,
      69,    70,    71,    77,    78,    79,    80,    75,    77,    78,
      79,    80,    28,    29,    73,    74,    51,   150,    75,   209,
      28,    29,    39,    72,    73,    74,    75,    76,    39,    78,
      79,     4,     5,    28,    29,    54,     9,    10,    11,    12,
      13,    14,    75,   233,    39,   227,   228,    75,    58,    62,
      39,   241,    25,    26,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    66,    39,    59,    59,    41,    40,    42,
      43,    44,    40,    75,    55,    53,    49,    50,    75,    40,
      76,    21,    39,    75,    75,    58,    66,    60,    75,    75,
      63,    41,    52,    41,    39,    22,     6,    72,    73,    74,
      75,    76,    40,    78,    79,    75,    41,    65,    23,    41,
      75,    29,    40,    75,    73,    29,    40,    40,    59,    41,
      64,    18,   197,   162,   232,   230,   233,   190,   154,    54,
     202,   242,   221
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    25,
      26,    42,    43,    44,    49,    50,    58,    60,    63,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,   102,   110,   111,   114,   121,   136,   137,
     138,     6,     8,     6,     8,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    39,    72,    73,    74,    75,    76,
      78,    79,   107,   109,   122,   123,   124,   125,   126,   127,
     128,   122,     7,    52,    54,    75,    75,    75,    61,    84,
       0,     3,   139,    75,    75,    75,    75,    10,   114,   122,
      51,   123,    39,    38,    75,    77,    78,    79,    80,   129,
      39,    54,   115,    75,    75,    58,    66,    62,    39,    59,
      59,   122,    40,    40,    75,    79,   123,    75,   123,   123,
     123,   123,    41,   122,    41,    75,   116,   130,    55,   131,
      53,   131,    75,   113,   107,    76,    75,    98,    75,    75,
      40,   122,    40,    75,   129,    19,    20,   123,   133,   135,
      21,   119,    39,    66,    41,   112,    52,    45,    46,    47,
      48,   101,    41,    97,    39,   129,    64,   117,   130,    15,
      16,    17,    18,    27,    66,    67,    68,    69,    70,    71,
     132,   134,    56,    57,   123,   122,    22,   120,   107,   123,
     113,   131,     6,    28,    29,    39,    99,    98,    40,    75,
     130,    65,   131,    28,    29,   123,   133,   133,   133,    23,
     103,    41,   106,   112,    75,    29,    73,   100,    97,    40,
      75,   119,    29,   104,   105,   123,    78,   107,   108,    40,
      40,   129,   120,    41,    24,    25,    73,    74,   106,   106,
      99,    59,   118,   103,   105,   133,   117
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    97,    98,    98,    99,
      99,    99,   100,   101,   101,   101,   101,   102,   103,   103,
     104,   104,   104,   105,   105,   106,   106,   106,   107,   107,
     107,   107,   107,   108,   108,   109,   109,   109,   109,   109,
     110,   111,   112,   112,   113,   114,   114,   115,   115,   116,
     117,   117,   118,   118,   119,   119,   120,   120,   121,   121,
     122,   122,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   124,   125,   126,   127,   127,   127,   128,
     128,   128,   128,   129,   129,   129,   130,   130,   131,   131,
     132,   132,   133,   133,   133,   133,   133,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   135,   135,   136,
     137,   138,   139,   139
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     8,     5,     7,     0,     3,     6,     3,     0,
       1,     2,     1,     1,     1,     1,     1,     8,     0,     2,
       2,     2,     1,     1,     3,     0,     3,     3,     1,     1,
       1,     1,     1,     2,     2,     1,     1,     1,     1,     1,
       4,     6,     0,     3,     3,    10,     7,     2,     2,     3,
       5,     6,     0,     2,     0,     2,     0,     2,     2,     2,
       2,     4,     3,     3,     3,     3,     3,     2,     1,     1,
       1,     1,     1,     3,     4,     4,     1,     1,     1,     1,
       3,     1,     3,     0,     1,     2,     0,     4,     0,     2,
       2,     3,     3,     2,     2,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     7,
       2,     4,     0,     1
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
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
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
  YYLTYPE *yylloc;
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc, scanner);
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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 224 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1822 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 254 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1831 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 260 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1839 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 265 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1847 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 271 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1855 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 277 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1863 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 283 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1871 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 289 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1881 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 296 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1889 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 302 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1899 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID RBRACE  */
#line 311 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      create_index.attribute_name = (yyvsp[-1].string);
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 1914 "yacc_sql.cpp"
    break;

  case 33: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 325 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1926 "yacc_sql.cpp"
    break;

  case 34: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 335 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 1947 "yacc_sql.cpp"
    break;

  case 35: /* attr_def_list: %empty  */
#line 354 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1955 "yacc_sql.cpp"
    break;

  case 36: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 358 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 1969 "yacc_sql.cpp"
    break;

  case 37: /* attr_def: ID type LBRACE number RBRACE null_option  */
#line 371 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-5].string));
    }
#line 1982 "yacc_sql.cpp"
    break;

  case 38: /* attr_def: ID type null_option  */
#line 380 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 1995 "yacc_sql.cpp"
    break;

  case 39: /* null_option: %empty  */
#line 390 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2003 "yacc_sql.cpp"
    break;

  case 40: /* null_option: NULL_T  */
#line 394 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2011 "yacc_sql.cpp"
    break;

  case 41: /* null_option: NOT NULL_T  */
#line 398 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2019 "yacc_sql.cpp"
    break;

  case 42: /* number: NUMBER  */
#line 403 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2025 "yacc_sql.cpp"
    break;

  case 43: /* type: INT_T  */
#line 406 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2031 "yacc_sql.cpp"
    break;

  case 44: /* type: DATE_T  */
#line 407 "yacc_sql.y"
              { (yyval.number)=DATES; }
#line 2037 "yacc_sql.cpp"
    break;

  case 45: /* type: STRING_T  */
#line 408 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2043 "yacc_sql.cpp"
    break;

  case 46: /* type: FLOAT_T  */
#line 409 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2049 "yacc_sql.cpp"
    break;

  case 47: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 413 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
        delete (yyvsp[-1].value_list);
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-5].string));
    }
#line 2066 "yacc_sql.cpp"
    break;

  case 48: /* order_by_list: %empty  */
#line 427 "yacc_sql.y"
                    {
    (yyval.orderby_unit_list) = nullptr;
  }
#line 2074 "yacc_sql.cpp"
    break;

  case 49: /* order_by_list: ORDER_BY sort_list  */
#line 431 "yacc_sql.y"
        {
    (yyval.orderby_unit_list) = (yyvsp[0].orderby_unit_list);
    std::reverse((yyval.orderby_unit_list)->begin(),(yyval.orderby_unit_list)->end());
	}
#line 2083 "yacc_sql.cpp"
    break;

  case 50: /* sort_unit: expression ASC  */
#line 438 "yacc_sql.y"
    {
      (yyval.orderby_unit) = new OrderBySqlNode;
      (yyval.orderby_unit)->expr = (yyvsp[-1].expression);
      (yyval.orderby_unit)->is_asc = true;
    }
#line 2093 "yacc_sql.cpp"
    break;

  case 51: /* sort_unit: expression DESC  */
#line 444 "yacc_sql.y"
    {
      (yyval.orderby_unit) = new OrderBySqlNode;
      (yyval.orderby_unit)->expr = (yyvsp[-1].expression);
      (yyval.orderby_unit)->is_asc = false;
    }
#line 2103 "yacc_sql.cpp"
    break;

  case 52: /* sort_unit: expression  */
#line 450 "yacc_sql.y"
    {
      (yyval.orderby_unit) = new OrderBySqlNode;
      (yyval.orderby_unit)->expr = (yyvsp[-1].expression);
      (yyval.orderby_unit)->is_asc = true;
    }
#line 2113 "yacc_sql.cpp"
    break;

  case 51: /* sort_unit: expression DESC  */
#line 444 "yacc_sql.y"
    {
      (yyval.orderby_unit) = new OrderBySqlNode;
      (yyval.orderby_unit)->expr = (yyvsp[-1].expression);
      (yyval.orderby_unit)->is_asc = false;
    }
#line 2118 "yacc_sql.cpp"
    break;

  case 52: /* sort_unit: expression  */
#line 450 "yacc_sql.y"
    {
      (yyval.orderby_unit) = new OrderBySqlNode;
      (yyval.orderby_unit)->expr = (yyvsp[0].expression);
      (yyval.orderby_unit)->is_asc = true;
    }
#line 2128 "yacc_sql.cpp"
    break;

  case 53: /* sort_list: sort_unit  */
#line 458 "yacc_sql.y"
        {
    (yyval.orderby_unit_list) = new std::vector<OrderBySqlNode>;
    (yyval.orderby_unit_list)->emplace_back(*(yyvsp[0].orderby_unit));
    delete (yyvsp[0].orderby_unit);
	}
#line 2123 "yacc_sql.cpp"
    break;

  case 54: /* sort_list: sort_unit COMMA sort_list  */
#line 465 "yacc_sql.y"
        {
    (yyvsp[0].orderby_unit_list)->emplace_back(*(yyvsp[-2].orderby_unit));
    (yyval.orderby_unit_list) = (yyvsp[0].orderby_unit_list);
    delete (yyvsp[-2].orderby_unit);
	}
#line 2133 "yacc_sql.cpp"
    break;

  case 55: /* value_list: %empty  */
#line 473 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2141 "yacc_sql.cpp"
    break;

  case 56: /* value_list: COMMA value value_list  */
#line 476 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2155 "yacc_sql.cpp"
    break;

  case 57: /* value_list: COMMA negative_value value_list  */
#line 485 "yacc_sql.y"
                                       { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2169 "yacc_sql.cpp"
    break;

  case 58: /* value: NUMBER  */
#line 496 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2178 "yacc_sql.cpp"
    break;

  case 59: /* value: FLOAT  */
#line 500 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2187 "yacc_sql.cpp"
    break;

  case 60: /* value: DATE_STR  */
#line 504 "yacc_sql.y"
              {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      Value *value = new Value(tmp);
      if (value->attr_type() == AttrType::UNDEFINED) {
        yyerror(&(yyloc),sql_string,sql_result,scanner,"date invaid");
        YYERROR;
      }
      else {
        (yyval.value) = value;
      }
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2205 "yacc_sql.cpp"
    break;

  case 61: /* value: SSS  */
#line 517 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2216 "yacc_sql.cpp"
    break;

  case 62: /* value: NULL_T  */
#line 523 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2225 "yacc_sql.cpp"
    break;

  case 63: /* negative_value: '-' NUMBER  */
#line 530 "yacc_sql.y"
               {
      (yyval.value) = new Value((int)-(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2234 "yacc_sql.cpp"
    break;

  case 64: /* negative_value: '-' FLOAT  */
#line 534 "yacc_sql.y"
                {
      (yyval.value) = new Value((float)-(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2243 "yacc_sql.cpp"
    break;

  case 65: /* aggregate_type: MAX  */
#line 540 "yacc_sql.y"
        { (yyval.aggregate_type) = AggregateType::MAX; }
#line 2249 "yacc_sql.cpp"
    break;

  case 66: /* aggregate_type: MIN  */
#line 541 "yacc_sql.y"
          { (yyval.aggregate_type) = AggregateType::MIN; }
#line 2255 "yacc_sql.cpp"
    break;

  case 67: /* aggregate_type: AVG  */
#line 542 "yacc_sql.y"
          { (yyval.aggregate_type) = AggregateType::AVG; }
#line 2261 "yacc_sql.cpp"
    break;

  case 68: /* aggregate_type: SUM  */
#line 543 "yacc_sql.y"
          { (yyval.aggregate_type) = AggregateType::SUM; }
#line 2267 "yacc_sql.cpp"
    break;

  case 69: /* aggregate_type: COUNT  */
#line 544 "yacc_sql.y"
            { (yyval.aggregate_type) = AggregateType::COUNT; }
#line 2273 "yacc_sql.cpp"
    break;

  case 70: /* delete_stmt: DELETE FROM ID where  */
#line 548 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      (yyval.sql_node)->deletion.conditions = nullptr;
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-1].string));
    }
#line 2287 "yacc_sql.cpp"
    break;

  case 71: /* update_stmt: UPDATE ID SET update_kv update_kv_list where  */
#line 560 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-4].string);
      (yyval.sql_node)->update.attribute_names.emplace_back((yyvsp[-2].update_kv)->attribute_name);
      (yyval.sql_node)->update.values.emplace_back((yyvsp[-2].update_kv)->value);
      if (nullptr != (yyvsp[-1].update_kv_list)) {
        for (UpdateKV kv : *(yyvsp[-1].update_kv_list)) {
          (yyval.sql_node)->update.attribute_names.emplace_back(kv.attribute_name);
          (yyval.sql_node)->update.values.emplace_back(kv.value);
        }
        delete (yyvsp[-1].update_kv_list);
      }
      (yyval.sql_node)->update.conditions = nullptr;
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->update.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-4].string));
      delete (yyvsp[-2].update_kv);
    }
#line 2311 "yacc_sql.cpp"
    break;

  case 72: /* update_kv_list: %empty  */
#line 582 "yacc_sql.y"
    {
      (yyval.update_kv_list) = nullptr;
    }
#line 2319 "yacc_sql.cpp"
    break;

  case 73: /* update_kv_list: COMMA update_kv update_kv_list  */
#line 586 "yacc_sql.y"
    {
      if ((yyvsp[0].update_kv_list) != nullptr) {
        (yyval.update_kv_list) = (yyvsp[0].update_kv_list);
      } else {
        (yyval.update_kv_list) = new std::vector<UpdateKV>;
      }
      (yyval.update_kv_list)->emplace_back(*(yyvsp[-1].update_kv));
      delete (yyvsp[-1].update_kv);
    }
#line 2333 "yacc_sql.cpp"
    break;

  case 74: /* update_kv: ID EQ expression  */
#line 598 "yacc_sql.y"
    {
      (yyval.update_kv) = new UpdateKV;
      (yyval.update_kv)->attribute_name = (yyvsp[-2].string);
      (yyval.update_kv)->value = (yyvsp[0].expression);
      free((yyvsp[-2].string));
    }
#line 2359 "yacc_sql.cpp"
    break;

  case 75: /* select_stmt: SELECT expression_list FROM ID as_info rel_list where group_by_expr having_expr order_by_list  */
#line 607 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-8].expression_list) != nullptr) {
        std::reverse((yyvsp[-8].expression_list)->begin(), (yyvsp[-8].expression_list)->end());
        (yyval.sql_node)->selection.proj_exprs.swap(*(yyvsp[-8].expression_list));
        delete (yyvsp[-8].expression_list);
      }
      
      JoinTableSqlNode *joinTable = new JoinTableSqlNode();
      joinTable->relation_name = (yyvsp[-6].string);
      if ((yyvsp[-5].string) != nullptr) {
        joinTable->alias_name = (yyvsp[-5].string);
      }
      if ((yyvsp[-4].relation_list) != nullptr) {
        joinTable->sub_join = (yyvsp[-4].relation_list);
      } 
      (yyval.sql_node)->selection.table = joinTable;

      if ((yyvsp[-3].expression) != nullptr) {
        (yyval.sql_node)->selection.conditions = (yyvsp[-3].expression);
      }
      free((yyvsp[-6].string));
      if ((yyvsp[-2].expression_list) != nullptr) {
        std::reverse((yyvsp[-2].expression_list)->begin(), (yyvsp[-2].expression_list)->end());
        (yyval.sql_node)->selection.groupby_exprs.swap(*(yyvsp[-2].expression_list));
        delete (yyvsp[-2].expression_list);
      }

      if ((yyvsp[-1].expression) != nullptr) {
        (yyval.sql_node)->selection.having_condition = (yyvsp[-1].expression);
      }

      if ((yyvsp[0].orderby_unit_list) != nullptr) {
        (yyval.sql_node)->selection.orderby_nodes.swap(*(yyvsp[0].orderby_unit_list));
        delete (yyvsp[0].orderby_unit_list);
      }
    }
#line 2401 "yacc_sql.cpp"
    break;

  case 76: /* select_stmt: SELECT expression_list from where group_by_expr having_expr order_by_list  */
#line 645 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-5].expression_list) != nullptr) {
        std::reverse((yyvsp[-5].expression_list)->begin(), (yyvsp[-5].expression_list)->end());
        (yyval.sql_node)->selection.proj_exprs.swap(*(yyvsp[-5].expression_list));
        delete (yyvsp[-5].expression_list);
      }

      (yyval.sql_node)->selection.table = (yyvsp[-4].relation_list);

      if ((yyvsp[-3].expression) != nullptr) {
        (yyval.sql_node)->selection.conditions = (yyvsp[-3].expression);
      }

      if ((yyvsp[-2].expression_list) != nullptr) {
        std::reverse((yyvsp[-2].expression_list)->begin(), (yyvsp[-2].expression_list)->end());
        (yyval.sql_node)->selection.groupby_exprs.swap(*(yyvsp[-2].expression_list));
        delete (yyvsp[-2].expression_list);
      }

      if ((yyvsp[-1].expression) != nullptr) {
        (yyval.sql_node)->selection.having_condition = (yyvsp[-1].expression);
      }

      if ((yyvsp[0].orderby_unit_list) != nullptr) {
        (yyval.sql_node)->selection.orderby_nodes.swap(*(yyvsp[0].orderby_unit_list));
        delete (yyvsp[0].orderby_unit_list);
      }
    }
#line 2435 "yacc_sql.cpp"
    break;

  case 77: /* from: FROM rel_list  */
#line 678 "yacc_sql.y"
    {
      (yyval.relation_list) = (yyvsp[0].relation_list);
    }
#line 2443 "yacc_sql.cpp"
    break;

  case 78: /* from: FROM join_table  */
#line 682 "yacc_sql.y"
    {
      (yyval.relation_list) = (yyvsp[0].relation_list);
    }
#line 2451 "yacc_sql.cpp"
    break;

  case 79: /* join_table: ID as_info join_table_inner  */
#line 688 "yacc_sql.y"
    {
      (yyval.relation_list) = new JoinTableSqlNode;
      (yyval.relation_list)->relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
      if ((yyvsp[-1].string) != nullptr) {
        (yyval.relation_list)->alias_name = (yyvsp[-1].string);
      }
      (yyval.relation_list)->sub_join = (yyvsp[0].relation_list);
    }
#line 2465 "yacc_sql.cpp"
    break;

  case 80: /* join_table_inner: INNER JOIN ID as_info join_on  */
#line 700 "yacc_sql.y"
    {
      (yyval.relation_list) = new JoinTableSqlNode;
      (yyval.relation_list)->relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
      if ((yyvsp[-1].string) != nullptr) {
        (yyval.relation_list)->alias_name = (yyvsp[-1].string);
      }
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.relation_list)->join_condition = (yyvsp[0].expression);
      }
    }
#line 2481 "yacc_sql.cpp"
    break;

  case 81: /* join_table_inner: INNER JOIN ID as_info join_on join_table_inner  */
#line 712 "yacc_sql.y"
    {
      (yyval.relation_list) = new JoinTableSqlNode;
      (yyval.relation_list)->relation_name = (yyvsp[-3].string);
      free((yyvsp[-3].string));
      if ((yyvsp[-2].string) != nullptr) {
        (yyval.relation_list)->alias_name = (yyvsp[-2].string);
      }
      if ((yyvsp[-1].expression) != nullptr) {
        (yyval.relation_list)->join_condition = (yyvsp[-1].expression);
      }
      (yyval.relation_list)->sub_join = (yyvsp[0].relation_list);
    }
#line 2498 "yacc_sql.cpp"
    break;

  case 82: /* join_on: %empty  */
#line 727 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2506 "yacc_sql.cpp"
    break;

  case 83: /* join_on: ON condition  */
#line 731 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2514 "yacc_sql.cpp"
    break;

  case 84: /* group_by_expr: %empty  */
#line 737 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2522 "yacc_sql.cpp"
    break;

  case 85: /* group_by_expr: GROUP_BY expression_list  */
#line 741 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2530 "yacc_sql.cpp"
    break;

  case 86: /* having_expr: %empty  */
#line 747 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2538 "yacc_sql.cpp"
    break;

  case 87: /* having_expr: HAVING condition  */
#line 751 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2546 "yacc_sql.cpp"
    break;

  case 88: /* calc_stmt: CALC expression_list  */
#line 758 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2557 "yacc_sql.cpp"
    break;

  case 89: /* calc_stmt: SELECT expression_list  */
#line 765 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2568 "yacc_sql.cpp"
    break;

  case 90: /* expression_list: expression as_info  */
#line 775 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      if (nullptr != (yyvsp[0].string)) {
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
      }
    }
#line 2580 "yacc_sql.cpp"
    break;

  case 91: /* expression_list: expression as_info COMMA expression_list  */
#line 783 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      if (nullptr != (yyvsp[-2].string)) {
        (yyvsp[-3].expression)->set_alias((yyvsp[-2].string));
      }
      (yyval.expression_list)->emplace_back((yyvsp[-3].expression));
    }
#line 2596 "yacc_sql.cpp"
    break;

  case 92: /* expression: expression '+' expression  */
#line 797 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2604 "yacc_sql.cpp"
    break;

  case 93: /* expression: expression '-' expression  */
#line 800 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2612 "yacc_sql.cpp"
    break;

  case 94: /* expression: expression '*' expression  */
#line 803 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2620 "yacc_sql.cpp"
    break;

  case 95: /* expression: expression '/' expression  */
#line 806 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2628 "yacc_sql.cpp"
    break;

  case 96: /* expression: LBRACE expression_list RBRACE  */
#line 809 "yacc_sql.y"
                                    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = (yyvsp[-1].expression_list)->front();
      } else {
        std::reverse((yyvsp[-1].expression_list)->begin(), (yyvsp[-1].expression_list)->end());
        (yyval.expression) = new ExprListExpr(std::move(*(yyvsp[-1].expression_list)));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list);
    }
#line 2643 "yacc_sql.cpp"
    break;

  case 97: /* expression: '-' expression  */
#line 819 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2651 "yacc_sql.cpp"
    break;

  case 98: /* expression: value  */
#line 822 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2661 "yacc_sql.cpp"
    break;

  case 99: /* expression: rel_attr  */
#line 827 "yacc_sql.y"
               {
      (yyval.expression) = new FieldExpr((yyvsp[0].rel_attr)->relation_name, (yyvsp[0].rel_attr)->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2671 "yacc_sql.cpp"
    break;

  case 100: /* expression: aggr_func_expr  */
#line 832 "yacc_sql.y"
                    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2679 "yacc_sql.cpp"
    break;

  case 101: /* expression: func_expr  */
#line 835 "yacc_sql.y"
               {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2687 "yacc_sql.cpp"
    break;

  case 102: /* expression: sub_query_expr  */
#line 838 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2695 "yacc_sql.cpp"
    break;

  case 103: /* sub_query_expr: LBRACE select_stmt RBRACE  */
#line 844 "yacc_sql.y"
                              {
      (yyval.expression) = new SubQueryExpr((yyvsp[-1].sql_node)->selection);
      delete (yyvsp[-1].sql_node);
    }
#line 2704 "yacc_sql.cpp"
    break;

  case 104: /* aggr_func_expr: aggregate_type LBRACE expression RBRACE  */
#line 851 "yacc_sql.y"
                                            {
      AggregateType aggr_type = (yyvsp[-3].aggregate_type);
      ValueExpr *value_expr;
      if ((yyvsp[-1].expression)->type() == ExprType::FIELD) {
        FieldExpr *field_expr = static_cast<FieldExpr *>((yyvsp[-1].expression));
        if (std::string(field_expr->field_name()) == "*") {
          if (aggr_type == AggregateType::COUNT) {
            aggr_type = AggregateType::COUNT_STAR;
            value_expr = new ValueExpr(Value(1));
            (yyval.expression) = new AggrFunctionExpr(aggr_type, value_expr);
          }
          else {
            yyerror(&(yyloc),sql_string,sql_result,scanner,"'*' can only be used with COUNT");
            YYERROR;
          }
        }
        else {
          (yyval.expression) = new AggrFunctionExpr(aggr_type, (yyvsp[-1].expression));
        }
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2731 "yacc_sql.cpp"
    break;

  case 105: /* func_expr: func_type LBRACE expression_list RBRACE  */
#line 876 "yacc_sql.y"
                                            {
      std::reverse((yyvsp[-1].expression_list)->begin(),(yyvsp[-1].expression_list)->end());
      (yyval.expression) = new FuncExpr((yyvsp[-3].function_type), *(yyvsp[-1].expression_list));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list);
    }
#line 2742 "yacc_sql.cpp"
    break;

  case 106: /* func_type: LENGTH  */
#line 885 "yacc_sql.y"
           { (yyval.function_type) = FunctionType::LENGTH; }
#line 2748 "yacc_sql.cpp"
    break;

  case 107: /* func_type: ROUND  */
#line 886 "yacc_sql.y"
            { (yyval.function_type) = FunctionType::ROUND; }
#line 2754 "yacc_sql.cpp"
    break;

  case 108: /* func_type: DATE_FORMAT  */
#line 887 "yacc_sql.y"
                  { (yyval.function_type) = FunctionType::DATE_FORMAT; }
#line 2760 "yacc_sql.cpp"
    break;

  case 109: /* rel_attr: '*'  */
#line 891 "yacc_sql.y"
        {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = "*";
      (yyval.rel_attr)->attribute_name = "*";
    }
#line 2770 "yacc_sql.cpp"
    break;

  case 110: /* rel_attr: ID DOT '*'  */
#line 896 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = "*";
      free((yyvsp[-2].string));
    }
#line 2781 "yacc_sql.cpp"
    break;

  case 111: /* rel_attr: ID  */
#line 902 "yacc_sql.y"
         {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2791 "yacc_sql.cpp"
    break;

  case 112: /* rel_attr: ID DOT ID  */
#line 907 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2803 "yacc_sql.cpp"
    break;

  case 113: /* as_info: %empty  */
#line 917 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2811 "yacc_sql.cpp"
    break;

  case 114: /* as_info: ID  */
#line 920 "yacc_sql.y"
         {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2819 "yacc_sql.cpp"
    break;

  case 115: /* as_info: AS ID  */
#line 923 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2827 "yacc_sql.cpp"
    break;

  case 116: /* rel_list: %empty  */
#line 930 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2835 "yacc_sql.cpp"
    break;

  case 117: /* rel_list: COMMA ID as_info rel_list  */
#line 933 "yacc_sql.y"
                                {
      (yyval.relation_list) = new JoinTableSqlNode;
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list)->sub_join = (yyvsp[0].relation_list);
      }
      (yyval.relation_list)->relation_name = (yyvsp[-2].string);
      if ((yyvsp[-1].string) != nullptr) {
        (yyval.relation_list)->alias_name = (yyvsp[-1].string);
      }
    }
#line 2850 "yacc_sql.cpp"
    break;

  case 118: /* where: %empty  */
#line 947 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2858 "yacc_sql.cpp"
    break;

  case 119: /* where: WHERE condition  */
#line 950 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 2866 "yacc_sql.cpp"
    break;

  case 120: /* is_null_comp: IS NULL_T  */
#line 956 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2874 "yacc_sql.cpp"
    break;

  case 121: /* is_null_comp: IS NOT NULL_T  */
#line 960 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2882 "yacc_sql.cpp"
    break;

  case 122: /* condition: expression comp_op expression  */
#line 965 "yacc_sql.y"
                                  {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2890 "yacc_sql.cpp"
    break;

  case 123: /* condition: expression is_null_comp  */
#line 969 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[0].boolean) ? IS_NULL : IS_NOT_NULL, (yyvsp[-1].expression), value_expr);
    }
#line 2901 "yacc_sql.cpp"
    break;

  case 124: /* condition: exists_op expression  */
#line 976 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), value_expr, (yyvsp[0].expression));
    }
#line 2912 "yacc_sql.cpp"
    break;

  case 125: /* condition: condition AND condition  */
#line 982 "yacc_sql.y"
                              {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2920 "yacc_sql.cpp"
    break;

  case 126: /* condition: condition OR condition  */
#line 985 "yacc_sql.y"
                             {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2928 "yacc_sql.cpp"
    break;

  case 127: /* comp_op: EQ  */
#line 991 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2934 "yacc_sql.cpp"
    break;

  case 128: /* comp_op: LT  */
#line 992 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2940 "yacc_sql.cpp"
    break;

  case 129: /* comp_op: GT  */
#line 993 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2946 "yacc_sql.cpp"
    break;

  case 130: /* comp_op: LE  */
#line 994 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2952 "yacc_sql.cpp"
    break;

  case 131: /* comp_op: GE  */
#line 995 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2958 "yacc_sql.cpp"
    break;

  case 132: /* comp_op: NE  */
#line 996 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2964 "yacc_sql.cpp"
    break;

  case 133: /* comp_op: LIKE  */
#line 997 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 2970 "yacc_sql.cpp"
    break;

  case 134: /* comp_op: NOT_LIKE  */
#line 998 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP; }
#line 2976 "yacc_sql.cpp"
    break;

  case 135: /* comp_op: IN  */
#line 999 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 2982 "yacc_sql.cpp"
    break;

  case 136: /* comp_op: NOT_IN  */
#line 1000 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP; }
#line 2988 "yacc_sql.cpp"
    break;

  case 137: /* exists_op: EXISTS  */
#line 1004 "yacc_sql.y"
           { (yyval.comp) = EXISTS_OP; }
#line 2994 "yacc_sql.cpp"
    break;

  case 138: /* exists_op: NOT_EXISTS  */
#line 1005 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS_OP; }
#line 3000 "yacc_sql.cpp"
    break;

  case 139: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1010 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3014 "yacc_sql.cpp"
    break;

  case 140: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1023 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3023 "yacc_sql.cpp"
    break;

  case 141: /* set_variable_stmt: SET ID EQ value  */
#line 1031 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3035 "yacc_sql.cpp"
    break;


#line 3039 "yacc_sql.cpp"

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
  *++yylsp = yyloc;

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
          = {yyssp, yytoken, &yylloc};
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
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
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

#line 1043 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
