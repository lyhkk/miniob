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
  YYSYMBOL_DESC = 11,                      /* DESC  */
  YYSYMBOL_SHOW = 12,                      /* SHOW  */
  YYSYMBOL_SYNC = 13,                      /* SYNC  */
  YYSYMBOL_INSERT = 14,                    /* INSERT  */
  YYSYMBOL_DELETE = 15,                    /* DELETE  */
  YYSYMBOL_LIKE = 16,                      /* LIKE  */
  YYSYMBOL_NOT_LIKE = 17,                  /* NOT_LIKE  */
  YYSYMBOL_IN = 18,                        /* IN  */
  YYSYMBOL_NOT_IN = 19,                    /* NOT_IN  */
  YYSYMBOL_EXISTS = 20,                    /* EXISTS  */
  YYSYMBOL_NOT_EXISTS = 21,                /* NOT_EXISTS  */
  YYSYMBOL_GROUP_BY = 22,                  /* GROUP_BY  */
  YYSYMBOL_HAVING = 23,                    /* HAVING  */
  YYSYMBOL_UPDATE = 24,                    /* UPDATE  */
  YYSYMBOL_IS = 25,                        /* IS  */
  YYSYMBOL_NOT = 26,                       /* NOT  */
  YYSYMBOL_NULL_T = 27,                    /* NULL_T  */
  YYSYMBOL_LENGTH = 28,                    /* LENGTH  */
  YYSYMBOL_ROUND = 29,                     /* ROUND  */
  YYSYMBOL_DATE_FORMAT = 30,               /* DATE_FORMAT  */
  YYSYMBOL_MAX = 31,                       /* MAX  */
  YYSYMBOL_MIN = 32,                       /* MIN  */
  YYSYMBOL_AVG = 33,                       /* AVG  */
  YYSYMBOL_SUM = 34,                       /* SUM  */
  YYSYMBOL_COUNT = 35,                     /* COUNT  */
  YYSYMBOL_AS = 36,                        /* AS  */
  YYSYMBOL_LBRACE = 37,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 38,                    /* RBRACE  */
  YYSYMBOL_COMMA = 39,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 40,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 41,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 42,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 43,                     /* INT_T  */
  YYSYMBOL_STRING_T = 44,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 45,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 46,                    /* DATE_T  */
  YYSYMBOL_HELP = 47,                      /* HELP  */
  YYSYMBOL_EXIT = 48,                      /* EXIT  */
  YYSYMBOL_DOT = 49,                       /* DOT  */
  YYSYMBOL_INTO = 50,                      /* INTO  */
  YYSYMBOL_VALUES = 51,                    /* VALUES  */
  YYSYMBOL_FROM = 52,                      /* FROM  */
  YYSYMBOL_WHERE = 53,                     /* WHERE  */
  YYSYMBOL_AND = 54,                       /* AND  */
  YYSYMBOL_OR = 55,                        /* OR  */
  YYSYMBOL_SET = 56,                       /* SET  */
  YYSYMBOL_ON = 57,                        /* ON  */
  YYSYMBOL_LOAD = 58,                      /* LOAD  */
  YYSYMBOL_DATA = 59,                      /* DATA  */
  YYSYMBOL_INFILE = 60,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 61,                   /* EXPLAIN  */
  YYSYMBOL_INNER = 62,                     /* INNER  */
  YYSYMBOL_JOIN = 63,                      /* JOIN  */
  YYSYMBOL_EQ = 64,                        /* EQ  */
  YYSYMBOL_LT = 65,                        /* LT  */
  YYSYMBOL_GT = 66,                        /* GT  */
  YYSYMBOL_LE = 67,                        /* LE  */
  YYSYMBOL_GE = 68,                        /* GE  */
  YYSYMBOL_NE = 69,                        /* NE  */
  YYSYMBOL_DATE_STR = 70,                  /* DATE_STR  */
  YYSYMBOL_NUMBER = 71,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 72,                     /* FLOAT  */
  YYSYMBOL_ID = 73,                        /* ID  */
  YYSYMBOL_SSS = 74,                       /* SSS  */
  YYSYMBOL_75_ = 75,                       /* '+'  */
  YYSYMBOL_76_ = 76,                       /* '-'  */
  YYSYMBOL_77_ = 77,                       /* '*'  */
  YYSYMBOL_78_ = 78,                       /* '/'  */
  YYSYMBOL_UMINUS = 79,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 80,                  /* $accept  */
  YYSYMBOL_commands = 81,                  /* commands  */
  YYSYMBOL_command_wrapper = 82,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 83,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 84,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 85,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 86,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 87,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 88,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 89,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 90,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 91,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 92,         /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 93,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 94,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 95,             /* attr_def_list  */
  YYSYMBOL_attr_def = 96,                  /* attr_def  */
  YYSYMBOL_null_option = 97,               /* null_option  */
  YYSYMBOL_number = 98,                    /* number  */
  YYSYMBOL_type = 99,                      /* type  */
  YYSYMBOL_insert_stmt = 100,              /* insert_stmt  */
  YYSYMBOL_value_list = 101,               /* value_list  */
  YYSYMBOL_value = 102,                    /* value  */
  YYSYMBOL_negative_value = 103,           /* negative_value  */
  YYSYMBOL_aggregate_type = 104,           /* aggregate_type  */
  YYSYMBOL_delete_stmt = 105,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 106,              /* update_stmt  */
  YYSYMBOL_select_stmt = 107,              /* select_stmt  */
  YYSYMBOL_from = 108,                     /* from  */
  YYSYMBOL_join_table = 109,               /* join_table  */
  YYSYMBOL_join_table_inner = 110,         /* join_table_inner  */
  YYSYMBOL_join_on = 111,                  /* join_on  */
  YYSYMBOL_group_by_expr = 112,            /* group_by_expr  */
  YYSYMBOL_having_expr = 113,              /* having_expr  */
  YYSYMBOL_calc_stmt = 114,                /* calc_stmt  */
  YYSYMBOL_expression_list = 115,          /* expression_list  */
  YYSYMBOL_expression = 116,               /* expression  */
  YYSYMBOL_aggr_func_expr = 117,           /* aggr_func_expr  */
  YYSYMBOL_func_expr = 118,                /* func_expr  */
  YYSYMBOL_func_type = 119,                /* func_type  */
  YYSYMBOL_rel_attr = 120,                 /* rel_attr  */
  YYSYMBOL_as_info = 121,                  /* as_info  */
  YYSYMBOL_rel_list = 122,                 /* rel_list  */
  YYSYMBOL_where = 123,                    /* where  */
  YYSYMBOL_is_null_comp = 124,             /* is_null_comp  */
  YYSYMBOL_condition = 125,                /* condition  */
  YYSYMBOL_comp_op = 126,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 127,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 128,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 129,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 130             /* opt_semicolon  */
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
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   210

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  128
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  223

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   330


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
       2,     2,    77,    75,     2,    76,     2,    78,     2,     2,
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
      79
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   211,   211,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   242,   248,   253,   259,   265,   271,   277,
     284,   290,   298,   312,   322,   342,   345,   358,   367,   378,
     381,   385,   391,   394,   395,   396,   397,   400,   417,   420,
     429,   440,   444,   448,   461,   467,   474,   478,   484,   485,
     486,   487,   488,   491,   503,   517,   550,   578,   582,   588,
     600,   612,   628,   631,   638,   641,   648,   651,   658,   665,
     675,   683,   698,   701,   704,   707,   710,   714,   717,   722,
     727,   730,   736,   761,   770,   771,   772,   776,   781,   787,
     792,   802,   805,   808,   815,   818,   832,   835,   840,   844,
     850,   853,   860,   863,   869,   870,   871,   872,   873,   874,
     875,   876,   877,   878,   887,   900,   908,   918,   919
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
  "DROP", "TABLE", "TABLES", "INDEX", "CALC", "SELECT", "DESC", "SHOW",
  "SYNC", "INSERT", "DELETE", "LIKE", "NOT_LIKE", "IN", "NOT_IN", "EXISTS",
  "NOT_EXISTS", "GROUP_BY", "HAVING", "UPDATE", "IS", "NOT", "NULL_T",
  "LENGTH", "ROUND", "DATE_FORMAT", "MAX", "MIN", "AVG", "SUM", "COUNT",
  "AS", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT",
  "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T", "HELP", "EXIT",
  "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "OR", "SET", "ON",
  "LOAD", "DATA", "INFILE", "EXPLAIN", "INNER", "JOIN", "EQ", "LT", "GT",
  "LE", "GE", "NE", "DATE_STR", "NUMBER", "FLOAT", "ID", "SSS", "'+'",
  "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "drop_index_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "null_option",
  "number", "type", "insert_stmt", "value_list", "value", "negative_value",
  "aggregate_type", "delete_stmt", "update_stmt", "select_stmt", "from",
  "join_table", "join_table_inner", "join_on", "group_by_expr",
  "having_expr", "calc_stmt", "expression_list", "expression",
  "aggr_func_expr", "func_expr", "func_type", "rel_attr", "as_info",
  "rel_list", "where", "is_null_comp", "condition", "comp_op",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-165)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      87,    24,    45,   122,   122,   -44,    26,  -165,   -13,   -10,
     -12,  -165,  -165,  -165,  -165,  -165,    -1,    47,    87,    85,
     112,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,    52,    53,    63,    64,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,   122,  -165,  -165,  -165,    70,  -165,
     122,  -165,  -165,    10,  -165,    32,  -165,  -165,   102,  -165,
      88,  -165,  -165,    68,    69,    90,    80,    98,  -165,  -165,
    -165,  -165,   110,   103,  -165,   104,    46,   -55,  -165,   122,
      89,  -165,   122,   122,   122,   122,   124,   122,   -28,   111,
     115,   111,    94,     7,    95,    97,    99,   100,  -165,  -165,
    -165,    55,  -165,   -21,   -21,  -165,  -165,   122,   130,   101,
     -27,  -165,  -165,   122,   149,   138,  -165,   113,  -165,   126,
     -19,   139,   142,  -165,  -165,  -165,  -165,   -27,   -26,    -2,
       4,   122,   157,     7,     7,   175,  -165,  -165,  -165,  -165,
      -6,    97,   144,   114,   145,   120,  -165,   111,  -165,  -165,
    -165,  -165,    44,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
     122,   122,   122,  -165,   122,  -165,   146,   111,   116,   159,
    -165,   117,  -165,   139,  -165,   152,  -165,   118,   149,   170,
    -165,    12,  -165,  -165,     4,   -22,   162,  -165,  -165,  -165,
    -165,   163,  -165,  -165,   -27,   157,  -165,    11,   146,   146,
    -165,    77,   147,  -165,  -165,  -165,  -165,  -165,  -165,   122,
     140,     4,  -165
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     127,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,    55,    94,    95,    96,    58,
      59,    60,    61,    62,     0,    53,    51,    52,    99,    54,
       0,    97,    88,     0,    78,   101,    90,    91,     0,    89,
      79,    31,    30,     0,     0,     0,     0,     0,   125,     1,
     128,     2,     0,     0,    29,     0,     0,     0,    87,     0,
       0,   102,     0,     0,     0,     0,    80,     0,   104,   106,
       0,   106,     0,     0,     0,     0,     0,     0,    86,   100,
      98,     0,   103,    82,    83,    84,    85,     0,     0,     0,
     101,    68,    67,     0,    74,     0,    63,     0,   126,     0,
       0,    35,     0,    33,    92,    81,    93,   101,   104,     0,
     107,     0,    76,     0,     0,     0,    43,    45,    46,    44,
      39,     0,     0,     0,   104,     0,    69,   106,   120,   121,
     122,   123,     0,   114,   115,   116,   117,   118,   119,   111,
       0,     0,     0,    75,     0,    66,    48,   106,     0,     0,
      40,     0,    38,    35,    34,     0,   105,     0,    74,     0,
     108,   110,   112,   113,    77,     0,     0,    64,   124,    41,
      42,     0,    36,    32,   101,    76,   109,     0,    48,    48,
      47,    39,    72,    65,    56,    57,    49,    50,    37,     0,
      70,    73,    71
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -165,  -165,   185,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,    22,    56,    -5,  -165,  -165,
    -165,   -96,  -100,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
     -11,  -165,    20,     5,  -165,    -3,   -54,  -165,  -165,  -165,
    -165,  -118,  -126,   -97,  -165,  -164,  -165,  -165,  -165,  -165,
    -165
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,   152,   131,   182,   201,   150,
      33,   196,    62,   209,    63,    34,    35,    36,    99,   121,
     156,   220,   142,   175,    37,    64,    65,    66,    67,    68,
      69,    96,   122,   124,   169,   140,   170,    38,    39,    40,
      81
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      86,    70,   138,   128,   126,    45,    88,   192,   193,    90,
     194,   119,   157,   119,   158,   159,   160,   161,   109,   154,
     179,   180,   110,   162,   146,   147,   148,   149,   186,    71,
      41,   181,    42,    72,    45,   111,   155,    73,   113,   114,
     115,   116,    74,   176,   177,   120,    91,    89,    55,    56,
      57,    43,    59,    44,   207,   221,    94,    95,   171,   172,
     188,    75,   163,   164,   165,   166,   167,   168,    90,   139,
     189,   190,    76,    92,    93,    94,    95,    55,    56,    57,
     197,    59,   214,   215,   108,    79,   212,    92,    93,    94,
      95,     1,     2,   134,   118,   208,     3,     4,     5,     6,
       7,     8,     9,   179,   180,    91,    77,    92,    93,    94,
      95,    10,   216,   217,   135,    80,   191,   139,   139,    87,
     139,    92,    93,    94,    95,    82,    83,    11,    12,    13,
      92,    93,    94,    95,    14,    15,    84,    85,   173,    97,
      98,   100,   101,    16,   103,    17,   102,   105,    18,    45,
      46,    47,    48,    49,    50,    51,    52,    53,   104,    54,
     106,   107,   112,   117,   123,   139,   125,   127,   136,   129,
     130,   141,   132,   133,   137,   143,   145,   144,   151,   153,
     174,   178,   184,   187,   119,   195,   199,   185,   200,   198,
     203,   204,    55,    56,    57,    58,    59,   206,    60,    61,
     210,   211,   155,    78,   219,   202,   218,   183,   205,   222,
     213
};

static const yytype_uint8 yycheck[] =
{
      54,     4,   120,   103,   101,    27,    60,   171,   172,    36,
     174,    39,   138,    39,    16,    17,    18,    19,    73,   137,
      26,    27,    77,    25,    43,    44,    45,    46,   154,    73,
       6,    37,     8,     7,    27,    89,    62,    50,    92,    93,
      94,    95,    52,   143,   144,    73,    73,    37,    70,    71,
      72,     6,    74,     8,    76,   219,    77,    78,    54,    55,
     157,    73,    64,    65,    66,    67,    68,    69,    36,   123,
      26,    27,    73,    75,    76,    77,    78,    70,    71,    72,
     177,    74,    71,    72,    38,     0,   204,    75,    76,    77,
      78,     4,     5,    38,    97,   195,     9,    10,    11,    12,
      13,    14,    15,    26,    27,    73,    59,    75,    76,    77,
      78,    24,   208,   209,   117,     3,   170,   171,   172,    49,
     174,    75,    76,    77,    78,    73,    73,    40,    41,    42,
      75,    76,    77,    78,    47,    48,    73,    73,   141,    37,
      52,    73,    73,    56,    64,    58,    56,    37,    61,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    60,    37,
      57,    57,    73,    39,    53,   219,    51,    73,    38,    74,
      73,    22,    73,    73,    73,    37,    50,    64,    39,    37,
      23,     6,    38,    63,    39,    39,    27,    73,    71,    73,
      38,    73,    70,    71,    72,    73,    74,    27,    76,    77,
      38,    38,    62,    18,    57,   183,   211,   151,   188,   220,
     205
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    15,
      24,    40,    41,    42,    47,    48,    56,    58,    61,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,   100,   105,   106,   107,   114,   127,   128,
     129,     6,     8,     6,     8,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    37,    70,    71,    72,    73,    74,
      76,    77,   102,   104,   115,   116,   117,   118,   119,   120,
     115,    73,     7,    50,    52,    73,    73,    59,    82,     0,
       3,   130,    73,    73,    73,    73,   116,    49,   116,    37,
      36,    73,    75,    76,    77,    78,   121,    37,    52,   108,
      73,    73,    56,    64,    60,    37,    57,    57,    38,    73,
      77,   116,    73,   116,   116,   116,   116,    39,   115,    39,
      73,   109,   122,    53,   123,    51,   123,    73,   102,    74,
      73,    96,    73,    73,    38,   115,    38,    73,   121,   116,
     125,    22,   112,    37,    64,    50,    43,    44,    45,    46,
      99,    39,    95,    37,   121,    62,   110,   122,    16,    17,
      18,    19,    25,    64,    65,    66,    67,    68,    69,   124,
     126,    54,    55,   115,    23,   113,   102,   102,     6,    26,
      27,    37,    97,    96,    38,    73,   122,    63,   123,    26,
      27,   116,   125,   125,   125,    39,   101,   123,    73,    27,
      71,    98,    95,    38,    73,   112,    27,    76,   102,   103,
      38,    38,   121,   113,    71,    72,   101,   101,    97,    57,
     111,   125,   110
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    95,    96,    96,    97,
      97,    97,    98,    99,    99,    99,    99,   100,   101,   101,
     101,   102,   102,   102,   102,   102,   103,   103,   104,   104,
     104,   104,   104,   105,   106,   107,   107,   108,   108,   109,
     110,   110,   111,   111,   112,   112,   113,   113,   114,   114,
     115,   115,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   117,   118,   119,   119,   119,   120,   120,   120,
     120,   121,   121,   121,   122,   122,   123,   123,   124,   124,
     125,   125,   125,   125,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   127,   128,   129,   130,   130
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     8,     5,     7,     0,     3,     6,     3,     0,
       1,     2,     1,     1,     1,     1,     1,     8,     0,     3,
       3,     1,     1,     1,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     4,     7,     9,     6,     2,     2,     3,
       5,     6,     0,     2,     0,     2,     0,     2,     2,     2,
       2,     4,     3,     3,     3,     3,     3,     2,     1,     1,
       1,     1,     4,     4,     1,     1,     1,     1,     3,     1,
       3,     0,     1,     2,     0,     4,     0,     2,     2,     3,
       3,     2,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     7,     2,     4,     0,     1
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
#line 212 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1804 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 242 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1813 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 248 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1821 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 253 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1829 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 259 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1837 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 265 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1845 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 271 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1853 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 277 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1863 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 284 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1871 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 290 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1881 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID RBRACE  */
#line 299 "yacc_sql.y"
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
#line 1896 "yacc_sql.cpp"
    break;

  case 33: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 313 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1908 "yacc_sql.cpp"
    break;

  case 34: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 323 "yacc_sql.y"
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
#line 1929 "yacc_sql.cpp"
    break;

  case 35: /* attr_def_list: %empty  */
#line 342 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1937 "yacc_sql.cpp"
    break;

  case 36: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 346 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 1951 "yacc_sql.cpp"
    break;

  case 37: /* attr_def: ID type LBRACE number RBRACE null_option  */
#line 359 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-5].string));
    }
#line 1964 "yacc_sql.cpp"
    break;

  case 38: /* attr_def: ID type null_option  */
#line 368 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 1977 "yacc_sql.cpp"
    break;

  case 39: /* null_option: %empty  */
#line 378 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 1985 "yacc_sql.cpp"
    break;

  case 40: /* null_option: NULL_T  */
#line 382 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 1993 "yacc_sql.cpp"
    break;

  case 41: /* null_option: NOT NULL_T  */
#line 386 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2001 "yacc_sql.cpp"
    break;

  case 42: /* number: NUMBER  */
#line 391 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2007 "yacc_sql.cpp"
    break;

  case 43: /* type: INT_T  */
#line 394 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2013 "yacc_sql.cpp"
    break;

  case 44: /* type: DATE_T  */
#line 395 "yacc_sql.y"
              { (yyval.number)=DATES; }
#line 2019 "yacc_sql.cpp"
    break;

  case 45: /* type: STRING_T  */
#line 396 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2025 "yacc_sql.cpp"
    break;

  case 46: /* type: FLOAT_T  */
#line 397 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2031 "yacc_sql.cpp"
    break;

  case 47: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 401 "yacc_sql.y"
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
#line 2048 "yacc_sql.cpp"
    break;

  case 48: /* value_list: %empty  */
#line 417 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2056 "yacc_sql.cpp"
    break;

  case 49: /* value_list: COMMA value value_list  */
#line 420 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2070 "yacc_sql.cpp"
    break;

  case 50: /* value_list: COMMA negative_value value_list  */
#line 429 "yacc_sql.y"
                                       { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2084 "yacc_sql.cpp"
    break;

  case 51: /* value: NUMBER  */
#line 440 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2093 "yacc_sql.cpp"
    break;

  case 52: /* value: FLOAT  */
#line 444 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2102 "yacc_sql.cpp"
    break;

  case 53: /* value: DATE_STR  */
#line 448 "yacc_sql.y"
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
#line 2120 "yacc_sql.cpp"
    break;

  case 54: /* value: SSS  */
#line 461 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2131 "yacc_sql.cpp"
    break;

  case 55: /* value: NULL_T  */
#line 467 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2140 "yacc_sql.cpp"
    break;

  case 56: /* negative_value: '-' NUMBER  */
#line 474 "yacc_sql.y"
               {
      (yyval.value) = new Value((int)-(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2149 "yacc_sql.cpp"
    break;

  case 57: /* negative_value: '-' FLOAT  */
#line 478 "yacc_sql.y"
                {
      (yyval.value) = new Value((float)-(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2158 "yacc_sql.cpp"
    break;

  case 58: /* aggregate_type: MAX  */
#line 484 "yacc_sql.y"
        { (yyval.aggregate_type) = AggregateType::MAX; }
#line 2164 "yacc_sql.cpp"
    break;

  case 59: /* aggregate_type: MIN  */
#line 485 "yacc_sql.y"
          { (yyval.aggregate_type) = AggregateType::MIN; }
#line 2170 "yacc_sql.cpp"
    break;

  case 60: /* aggregate_type: AVG  */
#line 486 "yacc_sql.y"
          { (yyval.aggregate_type) = AggregateType::AVG; }
#line 2176 "yacc_sql.cpp"
    break;

  case 61: /* aggregate_type: SUM  */
#line 487 "yacc_sql.y"
          { (yyval.aggregate_type) = AggregateType::SUM; }
#line 2182 "yacc_sql.cpp"
    break;

  case 62: /* aggregate_type: COUNT  */
#line 488 "yacc_sql.y"
            { (yyval.aggregate_type) = AggregateType::COUNT; }
#line 2188 "yacc_sql.cpp"
    break;

  case 63: /* delete_stmt: DELETE FROM ID where  */
#line 492 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      (yyval.sql_node)->deletion.conditions = nullptr;
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-1].string));
    }
#line 2202 "yacc_sql.cpp"
    break;

  case 64: /* update_stmt: UPDATE ID SET ID EQ value where  */
#line 504 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-5].string);
      (yyval.sql_node)->update.attribute_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.value = *(yyvsp[-1].value);
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->update.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 2218 "yacc_sql.cpp"
    break;

  case 65: /* select_stmt: SELECT expression_list FROM ID as_info rel_list where group_by_expr having_expr  */
#line 518 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-7].expression_list) != nullptr) {
        std::reverse((yyvsp[-7].expression_list)->begin(), (yyvsp[-7].expression_list)->end());
        (yyval.sql_node)->selection.proj_exprs.swap(*(yyvsp[-7].expression_list));
        delete (yyvsp[-7].expression_list);
      }
      
      JoinTableSqlNode *joinTable = new JoinTableSqlNode();
      joinTable->relation_name = (yyvsp[-5].string);
      if ((yyvsp[-4].string) != nullptr) {
        joinTable->alias_name = (yyvsp[-4].string);
      }
      if ((yyvsp[-3].relation_list) != nullptr) {
        joinTable->sub_join = (yyvsp[-3].relation_list);
      } 
      (yyval.sql_node)->selection.table = joinTable;

      if ((yyvsp[-2].expression) != nullptr) {
        (yyval.sql_node)->selection.conditions = (yyvsp[-2].expression);
      }
      free((yyvsp[-5].string));
      if ((yyvsp[-1].expression_list) != nullptr) {
        std::reverse((yyvsp[-1].expression_list)->begin(), (yyvsp[-1].expression_list)->end());
        (yyval.sql_node)->selection.groupby_exprs.swap(*(yyvsp[-1].expression_list));
        delete (yyvsp[-1].expression_list);
      }

      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->selection.having_condition = (yyvsp[0].expression);
      }
    }
#line 2255 "yacc_sql.cpp"
    break;

  case 66: /* select_stmt: SELECT expression_list from where group_by_expr having_expr  */
#line 551 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-4].expression_list) != nullptr) {
        std::reverse((yyvsp[-4].expression_list)->begin(), (yyvsp[-4].expression_list)->end());
        (yyval.sql_node)->selection.proj_exprs.swap(*(yyvsp[-4].expression_list));
        delete (yyvsp[-4].expression_list);
      }

      (yyval.sql_node)->selection.table = (yyvsp[-3].relation_list);

      if ((yyvsp[-2].expression) != nullptr) {
        (yyval.sql_node)->selection.conditions = (yyvsp[-2].expression);
      }

      if ((yyvsp[-1].expression_list) != nullptr) {
        std::reverse((yyvsp[-1].expression_list)->begin(), (yyvsp[-1].expression_list)->end());
        (yyval.sql_node)->selection.groupby_exprs.swap(*(yyvsp[-1].expression_list));
        delete (yyvsp[-1].expression_list);
      }

      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->selection.having_condition = (yyvsp[0].expression);
      }
    }
#line 2284 "yacc_sql.cpp"
    break;

  case 67: /* from: FROM rel_list  */
#line 579 "yacc_sql.y"
    {
      (yyval.relation_list) = (yyvsp[0].relation_list);
    }
#line 2292 "yacc_sql.cpp"
    break;

  case 68: /* from: FROM join_table  */
#line 583 "yacc_sql.y"
    {
      (yyval.relation_list) = (yyvsp[0].relation_list);
    }
#line 2300 "yacc_sql.cpp"
    break;

  case 69: /* join_table: ID as_info join_table_inner  */
#line 589 "yacc_sql.y"
    {
      (yyval.relation_list) = new JoinTableSqlNode;
      (yyval.relation_list)->relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
      if ((yyvsp[-1].string) != nullptr) {
        (yyval.relation_list)->alias_name = (yyvsp[-1].string);
      }
      (yyval.relation_list)->sub_join = (yyvsp[0].relation_list);
    }
#line 2314 "yacc_sql.cpp"
    break;

  case 70: /* join_table_inner: INNER JOIN ID as_info join_on  */
#line 601 "yacc_sql.y"
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
#line 2330 "yacc_sql.cpp"
    break;

  case 71: /* join_table_inner: INNER JOIN ID as_info join_on join_table_inner  */
#line 613 "yacc_sql.y"
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
#line 2347 "yacc_sql.cpp"
    break;

  case 72: /* join_on: %empty  */
#line 628 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2355 "yacc_sql.cpp"
    break;

  case 73: /* join_on: ON condition  */
#line 632 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2363 "yacc_sql.cpp"
    break;

  case 74: /* group_by_expr: %empty  */
#line 638 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2371 "yacc_sql.cpp"
    break;

  case 75: /* group_by_expr: GROUP_BY expression_list  */
#line 642 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2379 "yacc_sql.cpp"
    break;

  case 76: /* having_expr: %empty  */
#line 648 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2387 "yacc_sql.cpp"
    break;

  case 77: /* having_expr: HAVING condition  */
#line 652 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2395 "yacc_sql.cpp"
    break;

  case 78: /* calc_stmt: CALC expression_list  */
#line 659 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2406 "yacc_sql.cpp"
    break;

  case 79: /* calc_stmt: SELECT expression_list  */
#line 666 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2417 "yacc_sql.cpp"
    break;

  case 80: /* expression_list: expression as_info  */
#line 676 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      if (nullptr != (yyvsp[0].string)) {
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
      }
    }
#line 2429 "yacc_sql.cpp"
    break;

  case 81: /* expression_list: expression as_info COMMA expression_list  */
#line 684 "yacc_sql.y"
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
#line 2445 "yacc_sql.cpp"
    break;

  case 82: /* expression: expression '+' expression  */
#line 698 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2453 "yacc_sql.cpp"
    break;

  case 83: /* expression: expression '-' expression  */
#line 701 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2461 "yacc_sql.cpp"
    break;

  case 84: /* expression: expression '*' expression  */
#line 704 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2469 "yacc_sql.cpp"
    break;

  case 85: /* expression: expression '/' expression  */
#line 707 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2477 "yacc_sql.cpp"
    break;

  case 86: /* expression: LBRACE expression RBRACE  */
#line 710 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2486 "yacc_sql.cpp"
    break;

  case 87: /* expression: '-' expression  */
#line 714 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2494 "yacc_sql.cpp"
    break;

  case 88: /* expression: value  */
#line 717 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2504 "yacc_sql.cpp"
    break;

  case 89: /* expression: rel_attr  */
#line 722 "yacc_sql.y"
               {
      (yyval.expression) = new FieldExpr((yyvsp[0].rel_attr)->relation_name, (yyvsp[0].rel_attr)->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2514 "yacc_sql.cpp"
    break;

  case 90: /* expression: aggr_func_expr  */
#line 727 "yacc_sql.y"
                    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2522 "yacc_sql.cpp"
    break;

  case 91: /* expression: func_expr  */
#line 730 "yacc_sql.y"
               {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2530 "yacc_sql.cpp"
    break;

  case 92: /* aggr_func_expr: aggregate_type LBRACE expression RBRACE  */
#line 736 "yacc_sql.y"
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
#line 2557 "yacc_sql.cpp"
    break;

  case 93: /* func_expr: func_type LBRACE expression_list RBRACE  */
#line 761 "yacc_sql.y"
                                            {
      std::reverse((yyvsp[-1].expression_list)->begin(),(yyvsp[-1].expression_list)->end());
      (yyval.expression) = new FuncExpr((yyvsp[-3].function_type), *(yyvsp[-1].expression_list));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list);
    }
#line 2568 "yacc_sql.cpp"
    break;

  case 94: /* func_type: LENGTH  */
#line 770 "yacc_sql.y"
           { (yyval.function_type) = FunctionType::LENGTH; }
#line 2574 "yacc_sql.cpp"
    break;

  case 95: /* func_type: ROUND  */
#line 771 "yacc_sql.y"
            { (yyval.function_type) = FunctionType::ROUND; }
#line 2580 "yacc_sql.cpp"
    break;

  case 96: /* func_type: DATE_FORMAT  */
#line 772 "yacc_sql.y"
                  { (yyval.function_type) = FunctionType::DATE_FORMAT; }
#line 2586 "yacc_sql.cpp"
    break;

  case 97: /* rel_attr: '*'  */
#line 776 "yacc_sql.y"
        {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = "*";
      (yyval.rel_attr)->attribute_name = "*";
    }
#line 2596 "yacc_sql.cpp"
    break;

  case 98: /* rel_attr: ID DOT '*'  */
#line 781 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = "*";
      free((yyvsp[-2].string));
    }
#line 2607 "yacc_sql.cpp"
    break;

  case 99: /* rel_attr: ID  */
#line 787 "yacc_sql.y"
         {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2617 "yacc_sql.cpp"
    break;

  case 100: /* rel_attr: ID DOT ID  */
#line 792 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2629 "yacc_sql.cpp"
    break;

  case 101: /* as_info: %empty  */
#line 802 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2637 "yacc_sql.cpp"
    break;

  case 102: /* as_info: ID  */
#line 805 "yacc_sql.y"
         {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2645 "yacc_sql.cpp"
    break;

  case 103: /* as_info: AS ID  */
#line 808 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2653 "yacc_sql.cpp"
    break;

  case 104: /* rel_list: %empty  */
#line 815 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2661 "yacc_sql.cpp"
    break;

  case 105: /* rel_list: COMMA ID as_info rel_list  */
#line 818 "yacc_sql.y"
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
#line 2676 "yacc_sql.cpp"
    break;

  case 106: /* where: %empty  */
#line 832 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2684 "yacc_sql.cpp"
    break;

  case 107: /* where: WHERE condition  */
#line 835 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 2692 "yacc_sql.cpp"
    break;

  case 108: /* is_null_comp: IS NULL_T  */
#line 841 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2700 "yacc_sql.cpp"
    break;

  case 109: /* is_null_comp: IS NOT NULL_T  */
#line 845 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2708 "yacc_sql.cpp"
    break;

  case 110: /* condition: expression comp_op expression  */
#line 850 "yacc_sql.y"
                                  {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2716 "yacc_sql.cpp"
    break;

  case 111: /* condition: expression is_null_comp  */
#line 854 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[0].boolean) ? IS_NULL : IS_NOT_NULL, (yyvsp[-1].expression), value_expr);
    }
#line 2727 "yacc_sql.cpp"
    break;

  case 112: /* condition: condition AND condition  */
#line 860 "yacc_sql.y"
                              {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2735 "yacc_sql.cpp"
    break;

  case 113: /* condition: condition OR condition  */
#line 863 "yacc_sql.y"
                             {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2743 "yacc_sql.cpp"
    break;

  case 114: /* comp_op: EQ  */
#line 869 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2749 "yacc_sql.cpp"
    break;

  case 115: /* comp_op: LT  */
#line 870 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2755 "yacc_sql.cpp"
    break;

  case 116: /* comp_op: GT  */
#line 871 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2761 "yacc_sql.cpp"
    break;

  case 117: /* comp_op: LE  */
#line 872 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2767 "yacc_sql.cpp"
    break;

  case 118: /* comp_op: GE  */
#line 873 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2773 "yacc_sql.cpp"
    break;

  case 119: /* comp_op: NE  */
#line 874 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2779 "yacc_sql.cpp"
    break;

  case 120: /* comp_op: LIKE  */
#line 875 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 2785 "yacc_sql.cpp"
    break;

  case 121: /* comp_op: NOT_LIKE  */
#line 876 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP; }
#line 2791 "yacc_sql.cpp"
    break;

  case 122: /* comp_op: IN  */
#line 877 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 2797 "yacc_sql.cpp"
    break;

  case 123: /* comp_op: NOT_IN  */
#line 878 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP; }
#line 2803 "yacc_sql.cpp"
    break;

  case 124: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 888 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 2817 "yacc_sql.cpp"
    break;

  case 125: /* explain_stmt: EXPLAIN command_wrapper  */
#line 901 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 2826 "yacc_sql.cpp"
    break;

  case 126: /* set_variable_stmt: SET ID EQ value  */
#line 909 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 2838 "yacc_sql.cpp"
    break;


#line 2842 "yacc_sql.cpp"

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

#line 921 "yacc_sql.y"

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
