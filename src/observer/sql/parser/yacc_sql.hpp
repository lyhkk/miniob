/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison interface for Yacc-like parsers in C

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
    DESC = 266,                    /* DESC  */
    SHOW = 267,                    /* SHOW  */
    SYNC = 268,                    /* SYNC  */
    INSERT = 269,                  /* INSERT  */
    DELETE = 270,                  /* DELETE  */
    LIKE = 271,                    /* LIKE  */
    NOT_LIKE = 272,                /* NOT_LIKE  */
    IN = 273,                      /* IN  */
    NOT_IN = 274,                  /* NOT_IN  */
    EXISTS = 275,                  /* EXISTS  */
    NOT_EXISTS = 276,              /* NOT_EXISTS  */
    GROUP_BY = 277,                /* GROUP_BY  */
    HAVING = 278,                  /* HAVING  */
    UPDATE = 279,                  /* UPDATE  */
    LENGTH = 280,                  /* LENGTH  */
    ROUND = 281,                   /* ROUND  */
    DATE_FORMAT = 282,             /* DATE_FORMAT  */
    MAX = 283,                     /* MAX  */
    MIN = 284,                     /* MIN  */
    AVG = 285,                     /* AVG  */
    SUM = 286,                     /* SUM  */
    COUNT = 287,                   /* COUNT  */
    AS = 288,                      /* AS  */
    LBRACE = 289,                  /* LBRACE  */
    RBRACE = 290,                  /* RBRACE  */
    COMMA = 291,                   /* COMMA  */
    TRX_BEGIN = 292,               /* TRX_BEGIN  */
    TRX_COMMIT = 293,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 294,            /* TRX_ROLLBACK  */
    INT_T = 295,                   /* INT_T  */
    STRING_T = 296,                /* STRING_T  */
    FLOAT_T = 297,                 /* FLOAT_T  */
    DATE_T = 298,                  /* DATE_T  */
    HELP = 299,                    /* HELP  */
    EXIT = 300,                    /* EXIT  */
    DOT = 301,                     /* DOT  */
    INTO = 302,                    /* INTO  */
    VALUES = 303,                  /* VALUES  */
    FROM = 304,                    /* FROM  */
    WHERE = 305,                   /* WHERE  */
    AND = 306,                     /* AND  */
    OR = 307,                      /* OR  */
    SET = 308,                     /* SET  */
    ON = 309,                      /* ON  */
    LOAD = 310,                    /* LOAD  */
    DATA = 311,                    /* DATA  */
    INFILE = 312,                  /* INFILE  */
    EXPLAIN = 313,                 /* EXPLAIN  */
    INNER = 314,                   /* INNER  */
    JOIN = 315,                    /* JOIN  */
    EQ = 316,                      /* EQ  */
    LT = 317,                      /* LT  */
    GT = 318,                      /* GT  */
    LE = 319,                      /* LE  */
    GE = 320,                      /* GE  */
    NE = 321,                      /* NE  */
    DATE_STR = 322,                /* DATE_STR  */
    NUMBER = 323,                  /* NUMBER  */
    FLOAT = 324,                   /* FLOAT  */
    ID = 325,                      /* ID  */
    SSS = 326,                     /* SSS  */
    UMINUS = 327                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 123 "yacc_sql.y"

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
  std::vector<Value> *              value_list;
  JoinTableSqlNode *                relation_list;
  char *                            string;
  int                               number;
  float                             floats;

#line 154 "yacc_sql.hpp"

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
