
%{

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

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        LIKE
        NOT_LIKE
        IN
        NOT_IN
        EXISTS
        NOT_EXISTS
        UPDATE
        LENGTH
        ROUND
        DATE_FORMAT
        MAX
        MIN
        AVG
        SUM
        COUNT
        AS
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        OR
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        INNER
        JOIN
        EQ
        LT
        GT
        LE
        GE
        NE

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
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
}

%token <string> DATE_STR
%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <expression>          condition
%type <value>               value
%type <number>              number
%type <comp>                comp_op
%type <comp>                exists_op
%type <expression>          where
%type <rel_attr>            rel_attr
// %type <rel_attr>            func_for_imm
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
// %type <aggregate_type>      aggregate_type
// %type <function_type>       func_type
%type <value_list>          value_list
%type <relation_list>       rel_list
%type <relation_list>       from
%type <relation_list>       join_table
%type <relation_list>       join_table_inner
%type <expression>          join_on
%type <string>              as_info 
%type <expression>          expression
// %type <expression>          aggregate_expr
// %type <expression>          func_expr
%type <expression_list>     expression_list
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left AND OR
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;
      create_index.attribute_name = $7;
      free($3);
      free($5);
      free($7);
    }
    ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE 
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      free($1);
    }
    | ID type
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      free($1);
    }
    ;
number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$=INTS; }
    | DATE_T  { $$=DATES; }
    | STRING_T { $$=CHARS; }
    | FLOAT_T  { $$=FLOATS; }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE 
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($7 != nullptr) {
        $$->insertion.values.swap(*$7);
        delete $7;
      }
      $$->insertion.values.emplace_back(*$6);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $6;
      free($3);
    }
    ;

value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA value value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |DATE_STR {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
      free($1);
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
      free($1);
    }
    ;
    
// aggregate_type:
//     MAX { $$ = AggregateType::MAX; }
//     | MIN { $$ = AggregateType::MIN; }
//     | AVG { $$ = AggregateType::AVG; }
//     | SUM { $$ = AggregateType::SUM; }
//     | COUNT { $$ = AggregateType::COUNT; }
//     ;
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      $$->deletion.conditions = nullptr;
      if ($4 != nullptr) {
        $$->deletion.conditions = $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      $$->update.attribute_name = $4;
      $$->update.value = *$6;
      if ($7 != nullptr) {
        $$->update.conditions = $7;
      }
      free($2);
      free($4);
    }
    ;
select_stmt:        /*  select 语句的语法解析树*/
    SELECT expression_list FROM ID as_info rel_list where
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        std::reverse($2->begin(), $2->end());
        $$->selection.proj_exprs.swap(*$2);
        delete $2;
      }
      
      JoinTableSqlNode *joinTable = new JoinTableSqlNode();
      joinTable->relation_name = $4;
      if ($5 != nullptr) {
        joinTable->alias_name = $5;
      }
      if ($6 != nullptr) {
        joinTable->sub_join = $6;
      } 
      $$->selection.table = joinTable;

      if ($7 != nullptr) {
        $$->selection.conditions = $7;
      }
      free($4);
    }
    | SELECT expression_list
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      std::reverse($2->begin(), $2->end());
      $$->selection.proj_exprs.swap(*$2);
      delete $2;
    }
    | SELECT expression_list from where
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        std::reverse($2->begin(), $2->end());
        $$->selection.proj_exprs.swap(*$2);
        delete $2;
      }

      $$->selection.table = $3;

      if ($4 != nullptr) {
        $$->selection.conditions = $4;
      }
    }
    ;

from: 
    FROM rel_list 
    {
      $$ = $2;
    }
    | FROM join_table
    {
      $$ = $2;
    }

join_table:
    ID as_info join_table_inner
    {
      $$ = new JoinTableSqlNode;
      $$->relation_name = $1;
      free($1);
      if ($2 != nullptr) {
        $$->alias_name = $2;
      }
      $$->sub_join = $3;
    }

join_table_inner:
    INNER JOIN ID as_info join_on
    {
      $$ = new JoinTableSqlNode;
      $$->relation_name = $3;
      free($3);
      if ($4 != nullptr) {
        $$->alias_name = $4;
      }
      if ($5 != nullptr) {
        $$->join_condition = $5;
      }
    }
    | INNER JOIN ID as_info join_on join_table_inner
    {
      $$ = new JoinTableSqlNode;
      $$->relation_name = $3;
      free($3);
      if ($4 != nullptr) {
        $$->alias_name = $4;
      }
      if ($5 != nullptr) {
        $$->join_condition = $5;
      }
      $$->sub_join = $6;
    }
    ;

join_on:
    {
      $$ = nullptr;
    }
    | ON condition
    {
      $$ = $2;
    }
    ;

calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      std::reverse($2->begin(), $2->end());
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression as_info
    {
      $$ = new std::vector<Expression*>;
      $$->emplace_back($1);
      if (nullptr != $2) {
        $1->set_alias($2);
      }
    }
    | expression as_info COMMA expression_list
    {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<Expression *>;
      }
      if (nullptr != $2) {
        $1->set_alias($2);
      }
      $$->emplace_back($1);
    }
    ;

expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | rel_attr {
      $$ = new FieldExpr($1->relation_name, $1->attribute_name);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    ;

// aggregate_expr:
//     aggregate_type LBRACE expression RBRACE {
      // $$ = $3;
      // if ($3->relation_name  = "" && $3->attribute_name = "*") {
      //   if ($1 == AggregateType::COUNT) {
      //     $$->aggregate_type = AggregateType::COUNT_STAR;
      //   }
      // }
      // $$->aggregate_type = $1;
    // }
    // ;

// func_expr:
//     func_type LBRACE expression_list RBRACE {
    //   $$ = $3;
    //   $$->func_type = $1;
    // }
    // ;

// func_type:
//     LENGTH { $$ = FunctionType::LENGTH; }
//     | ROUND { $$ = FunctionType::ROUND; }
//     | DATE_FORMAT { $$ = FunctionType::DATE_FORMAT; }
//     ;

rel_attr:
    '*' {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = "*";
      $$->attribute_name = "*";
    }
    | '*' DOT '*' {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = "*";
      $$->attribute_name = "*";
    }
    | ID DOT '*' {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = "*";
      free($1);
    }
    | ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    ;
    // | LENGTH LBRACE rel_attr RBRACE {
    //   $$ = $3;
    //   $$->is_length_func = 1;
    // }
    // | ROUND LBRACE rel_attr RBRACE {
    //   $$ = $3;
    //   $$->is_round_func = 1;
    //   $$->round_num = 0;
    // }
    // | ROUND LBRACE rel_attr COMMA NUMBER RBRACE{
    //   $$ = $3;
    //   $$->is_round_func = 1;
    //   $$->round_num = $5;
    // }
    // | DATE_FORMAT LBRACE rel_attr COMMA SSS RBRACE {
    //   char *date_format = common::substr($5, 1, strlen($5) - 2);
    //   $$ = $3;
    //   $$->date_format.assign(date_format);
    //   free(date_format);
    // }
    // | aggregate_type LBRACE rel_attr RBRACE {
    //   $$ = $3;
    //   if ($3->relation_name  = "" && $3->attribute_name = "*") {
    //     if ($1 == AggregateType::COUNT) {
    //       $$->aggregate_type = AggregateType::COUNT_STAR;
    //     }
    //   }
    //   $$->aggregate_type = $1;
    // }
    // | aggregate_type LBRACE RBRACE {
    //   $$ = new RelAttrSqlNode();
    //   $$->aggregate_type = $1;
    //   $$->attribute_name = "*";
    //   $$->relation_name = "*";
    // }
    // | aggregate_type LBRACE rel_attr COMMA rel_attr RBRACE {
    //   $$ = new RelAttrSqlNode();
    //   $$->relation_name  = "*";
    //   $$->attribute_name = "*";
    //   $$->aggregate_type = $1;
    // }
    // | func_for_imm {
    //   $$ = $1;
    // }
    // ;

// func_for_imm:
//     LENGTH LBRACE SSS RBRACE {
//       $$ = new RelAttrSqlNode();
//       char *tmp = common::substr($3, 1, strlen($3) - 2);

//       // 字符串长度，得到需要输出的别名和值
//       Value len_val = Value(tmp);
//       len_val.is_length_func_ = 1;
//       $$->function_value = len_val.function_data();
//       $$->is_length_func = 1;
//       $$->alias_name = "LENGTH(" + string(tmp) + ")";

//       free(tmp);
//       free($3);
//     }
//     | ROUND LBRACE FLOAT RBRACE {
//       $$ = new RelAttrSqlNode();

//       // 四舍五入，得到需要输出的别名和值
//       Value round_val = Value((float)$3);
//       round_val.is_round_func_ = 1;
//       round_val.round_num_ = 0;
//       $$->function_value = round_val.function_data();
//       $$->is_round_func = 1;
//       $$->alias_name = "ROUND(" + std::to_string($3) + ")";
//     }
//     | ROUND LBRACE FLOAT COMMA NUMBER RBRACE {
//       $$ = new RelAttrSqlNode();

//       // 四舍五入，得到需要输出的别名和值
//       Value round_val = Value((float)$3);
//       round_val.is_round_func_ = 1;
//       round_val.round_num_ = $5;
//       $$->function_value = round_val.function_data();
//       $$->is_round_func = 1;
//       $$->round_num = $5;
//       $$->alias_name = "ROUND(" + std::to_string($3) + ", " + std::to_string($5) + ")";
//     }
//     | DATE_FORMAT LBRACE DATE_STR COMMA SSS RBRACE {
//       char *date_format = common::substr($5, 1, strlen($5) - 2);
//       char *date_str = common::substr($3, 1, strlen($3) - 2);
//       $$ = new RelAttrSqlNode();

//       // 日期格式化，得到需要输出的别名和值
//       Value format_date_val = Value(date_str);
//       format_date_val.is_date_format_func_ = 1;
//       $$->function_value = format_date_val.function_data(date_format);
//       $$->date_format.assign(date_format);
//       $$->alias_name = "DATE_FORMAT(" + string(date_str) + ", " + string(date_format) + ")";

//       // 释放内存
//       free(date_format);
//       free(date_str);
//       free($3);
//       free($5);
//     }
//     ;

as_info:
    {
      $$ = nullptr;
    }
    | ID {
      $$ = $1;
    }
    | AS ID {
      $$ = $2;
    }
    ;

rel_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID as_info rel_list {
      $$ = new JoinTableSqlNode;
      if ($4 != nullptr) {
        $$->sub_join = $4;
      }
      $$->relation_name = $2;
      if ($3 != nullptr) {
        $$->alias_name = $3;
      }
    }
    ;

where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition {
      $$ = $2;  
    }
    ;

condition:
    expression comp_op expression {
      $$ = new ComparisonExpr($2, $1, $3);
    }
    | condition AND condition {
      $$ = new ConjunctionExpr(ConjunctionExpr::Type::AND, $1, $3);
    }
    | condition OR condition {
      $$ = new ConjunctionExpr(ConjunctionExpr::Type::OR, $1, $3);
    }
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE { $$ = LIKE_OP; }
    | NOT_LIKE { $$ = NOT_LIKE_OP; }
    | IN { $$ = IN_OP; }
    | NOT_IN { $$ = NOT_IN_OP; }
    ;

exists_op:
    EXISTS { $$ = EXISTS_OP; }
    | NOT_EXISTS { $$ = NOT_EXISTS_OP; }
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
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
