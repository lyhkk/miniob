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
    IS = 280,                      /* IS  */
    NOT = 281,                     /* NOT  */
    NULL_T = 282,                  /* NULL_T  */
    LENGTH = 283,                  /* LENGTH  */
    ROUND = 284,                   /* ROUND  */
    DATE_FORMAT = 285,             /* DATE_FORMAT  */
    MAX = 286,                     /* MAX  */
    MIN = 287,                     /* MIN  */
    AVG = 288,                     /* AVG  */
    SUM = 289,                     /* SUM  */
    COUNT = 290,                   /* COUNT  */
    AS = 291,                      /* AS  */
    LBRACE = 292,                  /* LBRACE  */
    RBRACE = 293,                  /* RBRACE  */
    COMMA = 294,                   /* COMMA  */
    TRX_BEGIN = 295,               /* TRX_BEGIN  */
    TRX_COMMIT = 296,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 297,            /* TRX_ROLLBACK  */
    INT_T = 298,                   /* INT_T  */
    STRING_T = 299,                /* STRING_T  */
    FLOAT_T = 300,                 /* FLOAT_T  */
    DATE_T = 301,                  /* DATE_T  */
    HELP = 302,                    /* HELP  */
    EXIT = 303,                    /* EXIT  */
    DOT = 304,                     /* DOT  */
    INTO = 305,                    /* INTO  */
    VALUES = 306,                  /* VALUES  */
    FROM = 307,                    /* FROM  */
    WHERE = 308,                   /* WHERE  */
    AND = 309,                     /* AND  */
    OR = 310,                      /* OR  */
    SET = 311,                     /* SET  */
    ON = 312,                      /* ON  */
    LOAD = 313,                    /* LOAD  */
    DATA = 314,                    /* DATA  */
    INFILE = 315,                  /* INFILE  */
    EXPLAIN = 316,                 /* EXPLAIN  */
    INNER = 317,                   /* INNER  */
    JOIN = 318,                    /* JOIN  */
    EQ = 319,                      /* EQ  */
    LT = 320,                      /* LT  */
    GT = 321,                      /* GT  */
    LE = 322,                      /* LE  */
    GE = 323,                      /* GE  */
    NE = 324,                      /* NE  */
    DATE_STR = 325,                /* DATE_STR  */
    NUMBER = 326,                  /* NUMBER  */
    FLOAT = 327,                   /* FLOAT  */
    ID = 328,                      /* ID  */
    SSS = 329,                     /* SSS  */
    UMINUS = 330                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 126 "yacc_sql.y"

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
  bool                              boolean;

#line 158 "yacc_sql.hpp"

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
