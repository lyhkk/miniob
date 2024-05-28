/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON 30704

/* Bison version string.  */
#define YYBISON_VERSION "3.7.4"

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
  YYSYMBOL_select_stmt = 112,              /* select_stmt  */
  YYSYMBOL_from = 113,                     /* from  */
  YYSYMBOL_join_table = 114,               /* join_table  */
  YYSYMBOL_join_table_inner = 115,         /* join_table_inner  */
  YYSYMBOL_join_on = 116,                  /* join_on  */
  YYSYMBOL_group_by_expr = 117,            /* group_by_expr  */
  YYSYMBOL_having_expr = 118,              /* having_expr  */
  YYSYMBOL_calc_stmt = 119,                /* calc_stmt  */
  YYSYMBOL_expression_list = 120,          /* expression_list  */
  YYSYMBOL_expression = 121,               /* expression  */
  YYSYMBOL_sub_query_expr = 122,           /* sub_query_expr  */
  YYSYMBOL_aggr_func_expr = 123,           /* aggr_func_expr  */
  YYSYMBOL_func_expr = 124,                /* func_expr  */
  YYSYMBOL_func_type = 125,                /* func_type  */
  YYSYMBOL_rel_attr = 126,                 /* rel_attr  */
  YYSYMBOL_as_info = 127,                  /* as_info  */
  YYSYMBOL_rel_list = 128,                 /* rel_list  */
  YYSYMBOL_where = 129,                    /* where  */
  YYSYMBOL_is_null_comp = 130,             /* is_null_comp  */
  YYSYMBOL_condition = 131,                /* condition  */
  YYSYMBOL_comp_op = 132,                  /* comp_op  */
  YYSYMBOL_exists_op = 133,                /* exists_op  */
  YYSYMBOL_load_data_stmt = 134,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 135,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 136,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 137             /* opt_semicolon  */
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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYLAST   259

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  140
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  242

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
       0,   219,   219,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   250,   256,   261,   267,   273,   279,   285,
     292,   298,   306,   320,   330,   350,   353,   366,   375,   386,
     389,   393,   399,   402,   403,   404,   405,   408,   423,   426,
     433,   439,   445,   453,   460,   469,   472,   481,   492,   496,
     500,   513,   519,   526,   530,   536,   537,   538,   539,   540,
     543,   555,   569,   607,   640,   644,   650,   662,   674,   690,
     693,   700,   703,   710,   713,   720,   727,   737,   745,   760,
     763,   766,   769,   772,   782,   785,   790,   795,   798,   801,
     807,   814,   839,   848,   849,   850,   854,   859,   865,   870,
     880,   883,   886,   893,   896,   910,   913,   918,   922,   928,
     931,   938,   945,   948,   954,   955,   956,   957,   958,   959,
     960,   961,   962,   963,   967,   968,   972,   985,   993,  1003,
    1004
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
  "delete_stmt", "update_stmt", "select_stmt", "from", "join_table",
  "join_table_inner", "join_on", "group_by_expr", "having_expr",
  "calc_stmt", "expression_list", "expression", "sub_query_expr",
  "aggr_func_expr", "func_expr", "func_type", "rel_attr", "as_info",
  "rel_list", "where", "is_null_comp", "condition", "comp_op", "exists_op",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
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

#define YYPACT_NINF (-168)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     175,    18,    25,   173,   173,    23,  -168,   -29,    -5,   -33,
     -20,  -168,  -168,  -168,  -168,  -168,   -17,     4,   175,    79,
      88,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,    33,    42,    62,    66,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,    99,  -168,  -168,  -168,    49,  -168,
     173,  -168,  -168,    54,  -168,     3,  -168,  -168,  -168,    59,
    -168,    68,  -168,    67,    70,  -168,    55,    77,    84,  -168,
    -168,  -168,  -168,   108,   101,  -168,   102,   173,   118,   122,
     -50,  -168,   173,    89,  -168,   173,   173,   173,   173,   124,
     173,   -27,   111,   110,   111,    92,    38,    93,    95,   106,
     107,    68,  -168,  -168,  -168,  -168,    17,  -168,   -40,   -40,
    -168,  -168,   173,   143,   115,   -32,  -168,  -168,   120,   170,
     158,  -168,   145,  -168,   161,    57,   174,   177,  -168,  -168,
    -168,  -168,   -32,   -37,  -168,  -168,    -7,   -12,   173,   173,
     192,    38,    38,   214,  -168,  -168,  -168,  -168,   -11,    95,
     181,   147,   182,   162,  -168,   111,  -168,  -168,  -168,  -168,
      56,  -168,  -168,  -168,  -168,  -168,  -168,  -168,   173,   120,
     120,    47,  -168,   120,   203,   187,   111,   154,   201,  -168,
     159,  -168,   174,  -168,   191,  -168,   164,   170,   205,  -168,
      47,  -168,  -168,   -12,   173,  -168,   -22,   196,  -168,  -168,
    -168,  -168,   197,  -168,  -168,   -32,   192,  -168,   199,  -168,
      -3,    16,   187,   187,  -168,    78,   183,   203,   173,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,   120,   179,  -168,  -168,
     -12,  -168
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,    25,     0,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     139,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,    62,   103,   104,   105,    65,
      66,    67,    68,    69,     0,    60,    58,    59,   108,    61,
       0,   106,    95,     0,    85,   110,    99,    97,    98,     0,
      96,    86,    30,     0,     0,    31,     0,     0,     0,   137,
       1,   140,     2,     0,     0,    29,     0,     0,     0,     0,
       0,    94,     0,     0,   111,     0,     0,     0,     0,    87,
       0,   113,   115,     0,   115,     0,     0,     0,     0,     0,
       0,     0,   100,    93,   109,   107,     0,   112,    89,    90,
      91,    92,     0,     0,     0,   110,    75,    74,     0,    81,
       0,    70,     0,   138,     0,     0,    35,     0,    33,   101,
      88,   102,   110,   113,   134,   135,     0,   116,     0,     0,
      83,     0,     0,     0,    43,    45,    46,    44,    39,     0,
       0,     0,   113,     0,    76,   115,   130,   131,   132,   133,
       0,   124,   125,   126,   127,   128,   129,   120,     0,     0,
       0,   121,    82,     0,    48,    55,   115,     0,     0,    40,
       0,    38,    35,    34,     0,   114,     0,    81,     0,   117,
     119,   122,   123,    84,     0,    73,     0,     0,    71,   136,
      41,    42,     0,    36,    32,   110,    83,   118,    53,    49,
      52,     0,    55,    55,    47,    39,    79,    48,     0,    50,
      51,    63,    64,    56,    57,    37,     0,    77,    72,    54,
      80,    78
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -168,  -168,   223,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,    52,    91,    28,  -168,  -168,
    -168,    27,  -168,    29,  -107,  -105,  -168,  -168,  -168,  -168,
     202,  -168,  -168,    21,  -168,    58,    43,  -168,    -1,   -60,
    -168,  -168,  -168,  -168,  -168,  -123,  -128,   -99,  -168,  -167,
    -168,  -168,  -168,  -168,  -168,  -168
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,   160,   136,   191,   212,   158,
      33,   205,   218,   219,   207,    62,   223,    63,    34,    35,
      36,   102,   126,   164,   237,   150,   184,    37,    64,    65,
      66,    67,    68,    69,    70,    99,   127,   129,   177,   147,
     178,   148,    38,    39,    40,    82
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      91,   133,   143,    71,   124,   131,    93,    45,   166,   167,
     168,   169,   201,   202,   124,   165,   203,   188,   189,   162,
     170,   229,   230,    73,    41,   114,    42,   163,   190,   115,
      72,    43,   116,    44,   195,   118,   119,   120,   121,    97,
      98,    93,    75,    94,   179,   180,   185,   186,   125,    74,
      55,    56,    57,    89,    59,    76,   221,   139,    77,   171,
     172,   173,   174,   175,   176,    78,   197,    45,   146,   240,
      95,    96,    97,    98,    95,    96,    97,    98,    94,    80,
      95,    96,    97,    98,   198,   199,   111,   208,   181,   231,
     232,    81,   226,    92,    95,    96,    97,    98,   100,   123,
      90,   222,   154,   155,   156,   157,   188,   189,    83,    87,
      55,    56,    57,   105,    59,   233,   234,    84,   200,   146,
     146,   140,   101,   146,    95,    96,    97,    98,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    85,    54,   144,
     145,    86,   103,   106,   220,   104,   107,   108,   182,    45,
      46,    47,    48,    49,    50,    51,    52,    53,   112,    54,
     109,   110,   113,   130,   117,   122,   128,   132,   220,   134,
     135,    55,    56,    57,    58,    59,   146,    60,    61,     1,
       2,   137,   138,   141,     3,     4,     5,     6,     7,     8,
     142,   149,    55,    56,    57,    58,    59,   151,    60,    61,
       9,    10,    45,    46,    47,    48,    49,    50,    51,    52,
      53,   152,    54,   153,   183,   159,   161,    11,    12,    13,
     187,   193,   194,   124,    14,    15,   204,   196,   206,   209,
     210,   214,   211,    16,   217,    17,   224,   225,    18,   215,
     228,    79,   236,   163,   213,    55,    56,    57,    58,    59,
     192,    60,    61,   235,   238,   216,    88,   239,   241,   227
};

static const yytype_uint8 yycheck[] =
{
      60,   106,   125,     4,    41,   104,    38,    29,    15,    16,
      17,    18,   179,   180,    41,   143,   183,    28,    29,   142,
      27,    24,    25,    52,     6,    75,     8,    64,    39,    79,
       7,     6,    92,     8,   162,    95,    96,    97,    98,    79,
      80,    38,    75,    75,    56,    57,   151,   152,    75,    54,
      72,    73,    74,    54,    76,    75,    78,    40,    75,    66,
      67,    68,    69,    70,    71,    61,   165,    29,   128,   236,
      77,    78,    79,    80,    77,    78,    79,    80,    75,     0,
      77,    78,    79,    80,    28,    29,    87,   186,   148,    73,
      74,     3,   215,    39,    77,    78,    79,    80,    39,   100,
      51,   206,    45,    46,    47,    48,    28,    29,    75,    10,
      72,    73,    74,    58,    76,   222,   223,    75,   178,   179,
     180,   122,    54,   183,    77,    78,    79,    80,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    75,    39,    19,
      20,    75,    75,    66,   204,    75,    62,    39,   149,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    40,    39,
      59,    59,    40,    53,    75,    41,    55,    75,   228,    76,
      75,    72,    73,    74,    75,    76,   236,    78,    79,     4,
       5,    75,    75,    40,     9,    10,    11,    12,    13,    14,
      75,    21,    72,    73,    74,    75,    76,    39,    78,    79,
      25,    26,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    66,    39,    52,    22,    41,    39,    42,    43,    44,
       6,    40,    75,    41,    49,    50,    23,    65,    41,    75,
      29,    40,    73,    58,    29,    60,    40,    40,    63,    75,
      41,    18,    59,    64,   192,    72,    73,    74,    75,    76,
     159,    78,    79,   225,   227,   197,    54,   228,   237,   216
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    25,
      26,    42,    43,    44,    49,    50,    58,    60,    63,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,   102,   110,   111,   112,   119,   134,   135,
     136,     6,     8,     6,     8,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    39,    72,    73,    74,    75,    76,
      78,    79,   107,   109,   120,   121,   122,   123,   124,   125,
     126,   120,     7,    52,    54,    75,    75,    75,    61,    84,
       0,     3,   137,    75,    75,    75,    75,    10,   112,   120,
      51,   121,    39,    38,    75,    77,    78,    79,    80,   127,
      39,    54,   113,    75,    75,    58,    66,    62,    39,    59,
      59,   120,    40,    40,    75,    79,   121,    75,   121,   121,
     121,   121,    41,   120,    41,    75,   114,   128,    55,   129,
      53,   129,    75,   107,    76,    75,    98,    75,    75,    40,
     120,    40,    75,   127,    19,    20,   121,   131,   133,    21,
     117,    39,    66,    52,    45,    46,    47,    48,   101,    41,
      97,    39,   127,    64,   115,   128,    15,    16,    17,    18,
      27,    66,    67,    68,    69,    70,    71,   130,   132,    56,
      57,   121,   120,    22,   118,   107,   107,     6,    28,    29,
      39,    99,    98,    40,    75,   128,    65,   129,    28,    29,
     121,   131,   131,   131,    23,   103,    41,   106,   129,    75,
      29,    73,   100,    97,    40,    75,   117,    29,   104,   105,
     121,    78,   107,   108,    40,    40,   127,   118,    41,    24,
      25,    73,    74,   106,   106,    99,    59,   116,   103,   105,
     131,   115
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    97,    98,    98,    99,
      99,    99,   100,   101,   101,   101,   101,   102,   103,   103,
     104,   104,   104,   105,   105,   106,   106,   106,   107,   107,
     107,   107,   107,   108,   108,   109,   109,   109,   109,   109,
     110,   111,   112,   112,   113,   113,   114,   115,   115,   116,
     116,   117,   117,   118,   118,   119,   119,   120,   120,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     122,   123,   124,   125,   125,   125,   126,   126,   126,   126,
     127,   127,   127,   128,   128,   129,   129,   130,   130,   131,
     131,   131,   131,   131,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   133,   133,   134,   135,   136,   137,
     137
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     8,     5,     7,     0,     3,     6,     3,     0,
       1,     2,     1,     1,     1,     1,     1,     8,     0,     2,
       2,     2,     1,     1,     3,     0,     3,     3,     1,     1,
       1,     1,     1,     2,     2,     1,     1,     1,     1,     1,
       4,     7,    10,     7,     2,     2,     3,     5,     6,     0,
       2,     0,     2,     0,     2,     2,     2,     2,     4,     3,
       3,     3,     3,     3,     2,     1,     1,     1,     1,     1,
       3,     4,     4,     1,     1,     1,     1,     3,     1,     3,
       0,     1,     2,     0,     4,     0,     2,     2,     3,     3,
       2,     2,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     7,     2,     4,     0,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


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
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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

  YY_LOCATION_PRINT (yyo, *yylocationp);
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
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
#line 220 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1817 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 250 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1826 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 256 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1834 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 261 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1842 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 267 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1850 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 273 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1858 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 279 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1866 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 285 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1876 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 292 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1884 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 298 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1894 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID RBRACE  */
#line 307 "yacc_sql.y"
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
#line 1909 "yacc_sql.cpp"
    break;

  case 33: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 321 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1921 "yacc_sql.cpp"
    break;

  case 34: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 331 "yacc_sql.y"
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
#line 1942 "yacc_sql.cpp"
    break;

  case 35: /* attr_def_list: %empty  */
#line 350 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1950 "yacc_sql.cpp"
    break;

  case 36: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 354 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 1964 "yacc_sql.cpp"
    break;

  case 37: /* attr_def: ID type LBRACE number RBRACE null_option  */
#line 367 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-5].string));
    }
#line 1977 "yacc_sql.cpp"
    break;

  case 38: /* attr_def: ID type null_option  */
#line 376 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 1990 "yacc_sql.cpp"
    break;

  case 39: /* null_option: %empty  */
#line 386 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 1998 "yacc_sql.cpp"
    break;

  case 40: /* null_option: NULL_T  */
#line 390 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2006 "yacc_sql.cpp"
    break;

  case 41: /* null_option: NOT NULL_T  */
#line 394 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2014 "yacc_sql.cpp"
    break;

  case 42: /* number: NUMBER  */
#line 399 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2020 "yacc_sql.cpp"
    break;

  case 43: /* type: INT_T  */
#line 402 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2026 "yacc_sql.cpp"
    break;

  case 44: /* type: DATE_T  */
#line 403 "yacc_sql.y"
              { (yyval.number)=DATES; }
#line 2032 "yacc_sql.cpp"
    break;

  case 45: /* type: STRING_T  */
#line 404 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2038 "yacc_sql.cpp"
    break;

  case 46: /* type: FLOAT_T  */
#line 405 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2044 "yacc_sql.cpp"
    break;

  case 47: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 409 "yacc_sql.y"
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
#line 2061 "yacc_sql.cpp"
    break;

  case 48: /* order_by_list: %empty  */
#line 423 "yacc_sql.y"
                    {
    (yyval.orderby_unit_list) = nullptr;
  }
#line 2069 "yacc_sql.cpp"
    break;

  case 49: /* order_by_list: ORDER_BY sort_list  */
#line 427 "yacc_sql.y"
        {
    (yyval.orderby_unit_list) = (yyvsp[0].orderby_unit_list);
    std::reverse((yyval.orderby_unit_list)->begin(),(yyval.orderby_unit_list)->end());
	}
#line 2078 "yacc_sql.cpp"
    break;

  case 50: /* sort_unit: expression ASC  */
#line 434 "yacc_sql.y"
    {
      (yyval.orderby_unit) = new OrderBySqlNode;
      (yyval.orderby_unit)->expr = (yyvsp[-1].expression);
      (yyval.orderby_unit)->is_asc = true;
    }
#line 2088 "yacc_sql.cpp"
    break;

  case 51: /* sort_unit: expression DESC  */
#line 440 "yacc_sql.y"
    {
      (yyval.orderby_unit) = new OrderBySqlNode;
      (yyval.orderby_unit)->expr = (yyvsp[-1].expression);
      (yyval.orderby_unit)->is_asc = false;
    }
#line 2098 "yacc_sql.cpp"
    break;

  case 52: /* sort_unit: expression  */
#line 446 "yacc_sql.y"
    {
      (yyval.orderby_unit) = new OrderBySqlNode;
      (yyval.orderby_unit)->expr = (yyvsp[0].expression);
      (yyval.orderby_unit)->is_asc = true;
    }
#line 2108 "yacc_sql.cpp"
    break;

  case 53: /* sort_list: sort_unit  */
#line 454 "yacc_sql.y"
        {
    (yyval.orderby_unit_list) = new std::vector<OrderBySqlNode>;
    (yyval.orderby_unit_list)->emplace_back(*(yyvsp[0].orderby_unit));
    delete (yyvsp[0].orderby_unit);
	}
#line 2118 "yacc_sql.cpp"
    break;

  case 54: /* sort_list: sort_unit COMMA sort_list  */
#line 461 "yacc_sql.y"
        {
    (yyvsp[0].orderby_unit_list)->emplace_back(*(yyvsp[-2].orderby_unit));
    (yyval.orderby_unit_list) = (yyvsp[0].orderby_unit_list);
    delete (yyvsp[-2].orderby_unit);
	}
#line 2128 "yacc_sql.cpp"
    break;

  case 55: /* value_list: %empty  */
#line 469 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2136 "yacc_sql.cpp"
    break;

  case 56: /* value_list: COMMA value value_list  */
#line 472 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2150 "yacc_sql.cpp"
    break;

  case 57: /* value_list: COMMA negative_value value_list  */
#line 481 "yacc_sql.y"
                                       { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2164 "yacc_sql.cpp"
    break;

  case 58: /* value: NUMBER  */
#line 492 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2173 "yacc_sql.cpp"
    break;

  case 59: /* value: FLOAT  */
#line 496 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2182 "yacc_sql.cpp"
    break;

  case 60: /* value: DATE_STR  */
#line 500 "yacc_sql.y"
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
#line 2200 "yacc_sql.cpp"
    break;

  case 61: /* value: SSS  */
#line 513 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2211 "yacc_sql.cpp"
    break;

  case 62: /* value: NULL_T  */
#line 519 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2220 "yacc_sql.cpp"
    break;

  case 63: /* negative_value: '-' NUMBER  */
#line 526 "yacc_sql.y"
               {
      (yyval.value) = new Value((int)-(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2229 "yacc_sql.cpp"
    break;

  case 64: /* negative_value: '-' FLOAT  */
#line 530 "yacc_sql.y"
                {
      (yyval.value) = new Value((float)-(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2238 "yacc_sql.cpp"
    break;

  case 65: /* aggregate_type: MAX  */
#line 536 "yacc_sql.y"
        { (yyval.aggregate_type) = AggregateType::MAX; }
#line 2244 "yacc_sql.cpp"
    break;

  case 66: /* aggregate_type: MIN  */
#line 537 "yacc_sql.y"
          { (yyval.aggregate_type) = AggregateType::MIN; }
#line 2250 "yacc_sql.cpp"
    break;

  case 67: /* aggregate_type: AVG  */
#line 538 "yacc_sql.y"
          { (yyval.aggregate_type) = AggregateType::AVG; }
#line 2256 "yacc_sql.cpp"
    break;

  case 68: /* aggregate_type: SUM  */
#line 539 "yacc_sql.y"
          { (yyval.aggregate_type) = AggregateType::SUM; }
#line 2262 "yacc_sql.cpp"
    break;

  case 69: /* aggregate_type: COUNT  */
#line 540 "yacc_sql.y"
            { (yyval.aggregate_type) = AggregateType::COUNT; }
#line 2268 "yacc_sql.cpp"
    break;

  case 70: /* delete_stmt: DELETE FROM ID where  */
#line 544 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      (yyval.sql_node)->deletion.conditions = nullptr;
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-1].string));
    }
#line 2282 "yacc_sql.cpp"
    break;

  case 71: /* update_stmt: UPDATE ID SET ID EQ value where  */
#line 556 "yacc_sql.y"
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
#line 2298 "yacc_sql.cpp"
    break;

  case 72: /* select_stmt: SELECT expression_list FROM ID as_info rel_list where group_by_expr having_expr order_by_list  */
#line 570 "yacc_sql.y"
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
#line 2340 "yacc_sql.cpp"
    break;

  case 73: /* select_stmt: SELECT expression_list from where group_by_expr having_expr order_by_list  */
#line 608 "yacc_sql.y"
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
#line 2374 "yacc_sql.cpp"
    break;

  case 74: /* from: FROM rel_list  */
#line 641 "yacc_sql.y"
    {
      (yyval.relation_list) = (yyvsp[0].relation_list);
    }
#line 2382 "yacc_sql.cpp"
    break;

  case 75: /* from: FROM join_table  */
#line 645 "yacc_sql.y"
    {
      (yyval.relation_list) = (yyvsp[0].relation_list);
    }
#line 2390 "yacc_sql.cpp"
    break;

  case 76: /* join_table: ID as_info join_table_inner  */
#line 651 "yacc_sql.y"
    {
      (yyval.relation_list) = new JoinTableSqlNode;
      (yyval.relation_list)->relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
      if ((yyvsp[-1].string) != nullptr) {
        (yyval.relation_list)->alias_name = (yyvsp[-1].string);
      }
      (yyval.relation_list)->sub_join = (yyvsp[0].relation_list);
    }
#line 2404 "yacc_sql.cpp"
    break;

  case 77: /* join_table_inner: INNER JOIN ID as_info join_on  */
#line 663 "yacc_sql.y"
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
#line 2420 "yacc_sql.cpp"
    break;

  case 78: /* join_table_inner: INNER JOIN ID as_info join_on join_table_inner  */
#line 675 "yacc_sql.y"
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
#line 2437 "yacc_sql.cpp"
    break;

  case 79: /* join_on: %empty  */
#line 690 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2445 "yacc_sql.cpp"
    break;

  case 80: /* join_on: ON condition  */
#line 694 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2453 "yacc_sql.cpp"
    break;

  case 81: /* group_by_expr: %empty  */
#line 700 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2461 "yacc_sql.cpp"
    break;

  case 82: /* group_by_expr: GROUP_BY expression_list  */
#line 704 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2469 "yacc_sql.cpp"
    break;

  case 83: /* having_expr: %empty  */
#line 710 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2477 "yacc_sql.cpp"
    break;

  case 84: /* having_expr: HAVING condition  */
#line 714 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2485 "yacc_sql.cpp"
    break;

  case 85: /* calc_stmt: CALC expression_list  */
#line 721 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2496 "yacc_sql.cpp"
    break;

  case 86: /* calc_stmt: SELECT expression_list  */
#line 728 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2507 "yacc_sql.cpp"
    break;

  case 87: /* expression_list: expression as_info  */
#line 738 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      if (nullptr != (yyvsp[0].string)) {
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
      }
    }
#line 2519 "yacc_sql.cpp"
    break;

  case 88: /* expression_list: expression as_info COMMA expression_list  */
#line 746 "yacc_sql.y"
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
#line 2535 "yacc_sql.cpp"
    break;

  case 89: /* expression: expression '+' expression  */
#line 760 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2543 "yacc_sql.cpp"
    break;

  case 90: /* expression: expression '-' expression  */
#line 763 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2551 "yacc_sql.cpp"
    break;

  case 91: /* expression: expression '*' expression  */
#line 766 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2559 "yacc_sql.cpp"
    break;

  case 92: /* expression: expression '/' expression  */
#line 769 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2567 "yacc_sql.cpp"
    break;

  case 93: /* expression: LBRACE expression_list RBRACE  */
#line 772 "yacc_sql.y"
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
#line 2582 "yacc_sql.cpp"
    break;

  case 94: /* expression: '-' expression  */
#line 782 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2590 "yacc_sql.cpp"
    break;

  case 95: /* expression: value  */
#line 785 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2600 "yacc_sql.cpp"
    break;

  case 96: /* expression: rel_attr  */
#line 790 "yacc_sql.y"
               {
      (yyval.expression) = new FieldExpr((yyvsp[0].rel_attr)->relation_name, (yyvsp[0].rel_attr)->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2610 "yacc_sql.cpp"
    break;

  case 97: /* expression: aggr_func_expr  */
#line 795 "yacc_sql.y"
                    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2618 "yacc_sql.cpp"
    break;

  case 98: /* expression: func_expr  */
#line 798 "yacc_sql.y"
               {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2626 "yacc_sql.cpp"
    break;

  case 99: /* expression: sub_query_expr  */
#line 801 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2634 "yacc_sql.cpp"
    break;

  case 100: /* sub_query_expr: LBRACE select_stmt RBRACE  */
#line 807 "yacc_sql.y"
                              {
      (yyval.expression) = new SubQueryExpr((yyvsp[-1].sql_node)->selection);
      delete (yyvsp[-1].sql_node);
    }
#line 2643 "yacc_sql.cpp"
    break;

  case 101: /* aggr_func_expr: aggregate_type LBRACE expression RBRACE  */
#line 814 "yacc_sql.y"
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
#line 2670 "yacc_sql.cpp"
    break;

  case 102: /* func_expr: func_type LBRACE expression_list RBRACE  */
#line 839 "yacc_sql.y"
                                            {
      std::reverse((yyvsp[-1].expression_list)->begin(),(yyvsp[-1].expression_list)->end());
      (yyval.expression) = new FuncExpr((yyvsp[-3].function_type), *(yyvsp[-1].expression_list));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list);
    }
#line 2681 "yacc_sql.cpp"
    break;

  case 103: /* func_type: LENGTH  */
#line 848 "yacc_sql.y"
           { (yyval.function_type) = FunctionType::LENGTH; }
#line 2687 "yacc_sql.cpp"
    break;

  case 104: /* func_type: ROUND  */
#line 849 "yacc_sql.y"
            { (yyval.function_type) = FunctionType::ROUND; }
#line 2693 "yacc_sql.cpp"
    break;

  case 105: /* func_type: DATE_FORMAT  */
#line 850 "yacc_sql.y"
                  { (yyval.function_type) = FunctionType::DATE_FORMAT; }
#line 2699 "yacc_sql.cpp"
    break;

  case 106: /* rel_attr: '*'  */
#line 854 "yacc_sql.y"
        {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = "*";
      (yyval.rel_attr)->attribute_name = "*";
    }
#line 2709 "yacc_sql.cpp"
    break;

  case 107: /* rel_attr: ID DOT '*'  */
#line 859 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = "*";
      free((yyvsp[-2].string));
    }
#line 2720 "yacc_sql.cpp"
    break;

  case 108: /* rel_attr: ID  */
#line 865 "yacc_sql.y"
         {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2730 "yacc_sql.cpp"
    break;

  case 109: /* rel_attr: ID DOT ID  */
#line 870 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2742 "yacc_sql.cpp"
    break;

  case 110: /* as_info: %empty  */
#line 880 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2750 "yacc_sql.cpp"
    break;

  case 111: /* as_info: ID  */
#line 883 "yacc_sql.y"
         {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2758 "yacc_sql.cpp"
    break;

  case 112: /* as_info: AS ID  */
#line 886 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2766 "yacc_sql.cpp"
    break;

  case 113: /* rel_list: %empty  */
#line 893 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2774 "yacc_sql.cpp"
    break;

  case 114: /* rel_list: COMMA ID as_info rel_list  */
#line 896 "yacc_sql.y"
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
#line 2789 "yacc_sql.cpp"
    break;

  case 115: /* where: %empty  */
#line 910 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2797 "yacc_sql.cpp"
    break;

  case 116: /* where: WHERE condition  */
#line 913 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 2805 "yacc_sql.cpp"
    break;

  case 117: /* is_null_comp: IS NULL_T  */
#line 919 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2813 "yacc_sql.cpp"
    break;

  case 118: /* is_null_comp: IS NOT NULL_T  */
#line 923 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2821 "yacc_sql.cpp"
    break;

  case 119: /* condition: expression comp_op expression  */
#line 928 "yacc_sql.y"
                                  {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2829 "yacc_sql.cpp"
    break;

  case 120: /* condition: expression is_null_comp  */
#line 932 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[0].boolean) ? IS_NULL : IS_NOT_NULL, (yyvsp[-1].expression), value_expr);
    }
#line 2840 "yacc_sql.cpp"
    break;

  case 121: /* condition: exists_op expression  */
#line 939 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), value_expr, (yyvsp[0].expression));
    }
#line 2851 "yacc_sql.cpp"
    break;

  case 122: /* condition: condition AND condition  */
#line 945 "yacc_sql.y"
                              {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2859 "yacc_sql.cpp"
    break;

  case 123: /* condition: condition OR condition  */
#line 948 "yacc_sql.y"
                             {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2867 "yacc_sql.cpp"
    break;

  case 124: /* comp_op: EQ  */
#line 954 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2873 "yacc_sql.cpp"
    break;

  case 125: /* comp_op: LT  */
#line 955 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2879 "yacc_sql.cpp"
    break;

  case 126: /* comp_op: GT  */
#line 956 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2885 "yacc_sql.cpp"
    break;

  case 127: /* comp_op: LE  */
#line 957 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2891 "yacc_sql.cpp"
    break;

  case 128: /* comp_op: GE  */
#line 958 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2897 "yacc_sql.cpp"
    break;

  case 129: /* comp_op: NE  */
#line 959 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2903 "yacc_sql.cpp"
    break;

  case 130: /* comp_op: LIKE  */
#line 960 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 2909 "yacc_sql.cpp"
    break;

  case 131: /* comp_op: NOT_LIKE  */
#line 961 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP; }
#line 2915 "yacc_sql.cpp"
    break;

  case 132: /* comp_op: IN  */
#line 962 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 2921 "yacc_sql.cpp"
    break;

  case 133: /* comp_op: NOT_IN  */
#line 963 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP; }
#line 2927 "yacc_sql.cpp"
    break;

  case 134: /* exists_op: EXISTS  */
#line 967 "yacc_sql.y"
           { (yyval.comp) = EXISTS_OP; }
#line 2933 "yacc_sql.cpp"
    break;

  case 135: /* exists_op: NOT_EXISTS  */
#line 968 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS_OP; }
#line 2939 "yacc_sql.cpp"
    break;

  case 136: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 973 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 2953 "yacc_sql.cpp"
    break;

  case 137: /* explain_stmt: EXPLAIN command_wrapper  */
#line 986 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 2962 "yacc_sql.cpp"
    break;

  case 138: /* set_variable_stmt: SET ID EQ value  */
#line 994 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 2974 "yacc_sql.cpp"
    break;


#line 2978 "yacc_sql.cpp"

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
          goto yyexhaustedlab;
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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
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

#line 1006 "yacc_sql.y"

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
