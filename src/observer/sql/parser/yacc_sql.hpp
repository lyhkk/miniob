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

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
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
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    TABLE = 261,                   /* TABLE  */
    TABLES = 262,                  /* TABLES  */
    INDEX = 263,                   /* INDEX  */
    CALC = 264,                    /* CALC  */
    SELECT = 265,                  /* SELECT  */
    SHOW = 266,                    /* SHOW  */
    SYNC = 267,                    /* SYNC  */
    INSERT = 268,                  /* INSERT  */
    DELETE = 269,                  /* DELETE  */
    LIKE = 270,                    /* LIKE  */
    NOT_LIKE = 271,                /* NOT_LIKE  */
    IN = 272,                      /* IN  */
    NOT_IN = 273,                  /* NOT_IN  */
    EXISTS = 274,                  /* EXISTS  */
    NOT_EXISTS = 275,              /* NOT_EXISTS  */
    GROUP_BY = 276,                /* GROUP_BY  */
    HAVING = 277,                  /* HAVING  */
    ORDER_BY = 278,                /* ORDER_BY  */
    ASC = 279,                     /* ASC  */
    DESC = 280,                    /* DESC  */
    UPDATE = 281,                  /* UPDATE  */
    IS = 282,                      /* IS  */
    NOT = 283,                     /* NOT  */
    NULL_T = 284,                  /* NULL_T  */
    UNIQUE = 285,                  /* UNIQUE  */
    LENGTH = 286,                  /* LENGTH  */
    ROUND = 287,                   /* ROUND  */
    DATE_FORMAT = 288,             /* DATE_FORMAT  */
    MAX = 289,                     /* MAX  */
    MIN = 290,                     /* MIN  */
    AVG = 291,                     /* AVG  */
    SUM = 292,                     /* SUM  */
    COUNT = 293,                   /* COUNT  */
    AS = 294,                      /* AS  */
    LBRACE = 295,                  /* LBRACE  */
    RBRACE = 296,                  /* RBRACE  */
    COMMA = 297,                   /* COMMA  */
    TRX_BEGIN = 298,               /* TRX_BEGIN  */
    TRX_COMMIT = 299,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 300,            /* TRX_ROLLBACK  */
    INT_T = 301,                   /* INT_T  */
    STRING_T = 302,                /* STRING_T  */
    FLOAT_T = 303,                 /* FLOAT_T  */
    DATE_T = 304,                  /* DATE_T  */
    HELP = 305,                    /* HELP  */
    EXIT = 306,                    /* EXIT  */
    DOT = 307,                     /* DOT  */
    INTO = 308,                    /* INTO  */
    VALUES = 309,                  /* VALUES  */
    FROM = 310,                    /* FROM  */
    WHERE = 311,                   /* WHERE  */
    AND = 312,                     /* AND  */
    OR = 313,                      /* OR  */
    SET = 314,                     /* SET  */
    ON = 315,                      /* ON  */
    LOAD = 316,                    /* LOAD  */
    DATA = 317,                    /* DATA  */
    INFILE = 318,                  /* INFILE  */
    EXPLAIN = 319,                 /* EXPLAIN  */
    INNER = 320,                   /* INNER  */
    JOIN = 321,                    /* JOIN  */
    EQ = 322,                      /* EQ  */
    LT = 323,                      /* LT  */
    GT = 324,                      /* GT  */
    LE = 325,                      /* LE  */
    GE = 326,                      /* GE  */
    NE = 327,                      /* NE  */
    DATE_STR = 328,                /* DATE_STR  */
    NUMBER = 329,                  /* NUMBER  */
    FLOAT = 330,                   /* FLOAT  */
    ID = 331,                      /* ID  */
    SSS = 332,                     /* SSS  */
    UMINUS = 333                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 129 "yacc_sql.y"

  ParsedSqlNode *                   sql_node;
  Value *                           value;
  enum CompOp                       comp;
  RelAttrSqlNode *                  rel_attr;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  AggregateType                     aggregate_type;
  FunctionType                      function_type;
  Expression *                      expression;
  std::vector<Expression *> *       expression_list;
  UpdateKV *                        update_kv;
  std::vector<UpdateKV> *           update_kv_list;
  OrderBySqlNode*                   orderby_unit;
  std::vector<OrderBySqlNode>*     orderby_unit_list;
  std::vector<Value> *              value_list;
  JoinTableSqlNode *                relation_list;
  std::vector<std::string> *        idx_relation_list;
  char *                            string;
  int                               number;
  float                             floats;
  bool                              boolean;

#line 166 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);


#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
