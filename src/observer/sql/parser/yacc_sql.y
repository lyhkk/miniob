
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
        GROUP_BY
        HAVING
        ORDER_BY
        ASC
        DESC
        UPDATE
        IS
        NOT
        NULL_T
        UNIQUE
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
%type <value>               negative_value
%type <number>              number
%type <boolean>             is_null_comp
%type <boolean>             null_option
%type <boolean>             unique_option
%type <comp>                comp_op
%type <comp>                exists_op
%type <expression>          where
%type <rel_attr>            rel_attr
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <aggregate_type>      aggregate_type
%type <function_type>       func_type
%type <value_list>          value_list
%type <relation_list>       rel_list
%type <relation_list>       from
%type <relation_list>       join_table
%type <relation_list>       join_table_inner
%type <idx_relation_list>   index_list
%type <expression>          join_on
%type <string>              as_info 
%type <expression>          expression
%type <expression>          aggr_func_expr
%type <expression>          func_expr
%type <expression_list>     group_by_expr
%type <orderby_unit>        sort_unit
%type <orderby_unit_list>   sort_list
%type <orderby_unit_list>   order_by_list
%type <expression>          having_expr
%type <expression>          sub_query_expr
%type <expression_list>     expression_list
%type <update_kv>           update_kv
%type <update_kv_list>      update_kv_list
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
    CREATE unique_option INDEX ID ON ID LBRACE ID index_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.unique = $2;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      std::vector<std::string> *indexes = $9;
      if (nullptr != indexes) {
        create_index.attribute_names.swap(*indexes);
        delete $9;
      }
      create_index.attribute_names.emplace_back($8);
      std::reverse(create_index.attribute_names.begin(), create_index.attribute_names.end());
      free($4);
      free($6);
      free($8);
    }
    ;
unique_option:
    /* empty */
    {
      $$ = false;
    }
    | UNIQUE
    {
      $$ = true;
    }
index_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID index_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      }
      else {
        $$ = new std::vector<std::string>;
      }
      $$->emplace_back($2);
      free($2);
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
    ID type LBRACE number RBRACE null_option
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->nullable = $6;
      free($1);
    }
    | ID type null_option
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->nullable = $3;
      free($1);
    }
    ;
null_option:
    {
      $$ = true;
    }
    | NULL_T
    {
      $$ = true;
    }
    | NOT NULL_T
    {
      $$ = false;
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
    | INSERT INTO ID VALUES LBRACE negative_value value_list RBRACE 
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
order_by_list:
	/* empty */ {
    $$ = nullptr;
  }
	| ORDER_BY sort_list
	{
    $$ = $2;
    std::reverse($$->begin(),$$->end());
	}
	;
sort_unit:
    expression ASC
    {
      $$ = new OrderBySqlNode;
      $$->expr = $1;
      $$->is_asc = true;
    }
    | expression DESC
    {
      $$ = new OrderBySqlNode;
      $$->expr = $1;
      $$->is_asc = false;
    }
    | expression
    {
      $$ = new OrderBySqlNode;
      $$->expr = $1;
      $$->is_asc = true;
    }
    ;
sort_list:
	sort_unit
	{
    $$ = new std::vector<OrderBySqlNode>;
    $$->emplace_back(*$1);
    delete $1;
	}
  |
	sort_unit COMMA sort_list
	{
    $3->emplace_back(*$1);
    $$ = $3;
    delete $1;
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
    | COMMA negative_value value_list  { 
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
      Value *value = new Value(tmp);
      if (value->attr_type() == AttrType::UNDEFINED) {
        yyerror(&@$,sql_string,sql_result,scanner,"date invaid");
        YYERROR;
      }
      else {
        $$ = value;
      }
      free(tmp);
      free($1);
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
      free($1);
    }
    | NULL_T {
      $$ = new Value();
      $$->set_null();
    }
    ;

negative_value:
    '-' NUMBER {
      $$ = new Value((int)-$2);
      @$ = @2;
    }
    | '-' FLOAT {
      $$ = new Value((float)-$2);
      @$ = @2;
    }
    ;
aggregate_type:
    MAX { $$ = AggregateType::MAX; }
    | MIN { $$ = AggregateType::MIN; }
    | AVG { $$ = AggregateType::AVG; }
    | SUM { $$ = AggregateType::SUM; }
    | COUNT { $$ = AggregateType::COUNT; }
    ;
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
    UPDATE ID SET update_kv update_kv_list where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      $$->update.attribute_names.emplace_back($4->attribute_name);
      $$->update.values.emplace_back($4->value);
      if (nullptr != $5) {
        for (UpdateKV kv : *$5) {
          $$->update.attribute_names.emplace_back(kv.attribute_name);
          $$->update.values.emplace_back(kv.value);
        }
        delete $5;
      }
      $$->update.conditions = nullptr;
      if ($6 != nullptr) {
        $$->update.conditions = $6;
      }
      free($2);
      delete $4;
    }
    ;
update_kv_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA update_kv update_kv_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<UpdateKV>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
update_kv:
    ID EQ expression
    {
      $$ = new UpdateKV;
      $$->attribute_name = $1;
      $$->value = $3;
      free($1);
    }
    ;
select_stmt:        /*  select 语句的语法解析树*/
    SELECT expression_list FROM ID as_info rel_list where group_by_expr having_expr order_by_list
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
      if ($8 != nullptr) {
        std::reverse($8->begin(), $8->end());
        $$->selection.groupby_exprs.swap(*$8);
        delete $8;
      }

      if ($9 != nullptr) {
        $$->selection.having_condition = $9;
      }

      if ($10 != nullptr) {
        $$->selection.orderby_nodes.swap(*$10);
        delete $10;
      }
    }
    | SELECT expression_list from where group_by_expr having_expr order_by_list
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

      if ($5 != nullptr) {
        std::reverse($5->begin(), $5->end());
        $$->selection.groupby_exprs.swap(*$5);
        delete $5;
      }

      if ($6 != nullptr) {
        $$->selection.having_condition = $6;
      }

      if ($7 != nullptr) {
        $$->selection.orderby_nodes.swap(*$7);
        delete $7;
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

group_by_expr:
    {
      $$ = nullptr;
    }
    | GROUP_BY expression_list
    {
      $$ = $2;
    }
    ;

having_expr:
    {
      $$ = nullptr;
    }
    | HAVING condition
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
    | SELECT expression_list
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
    | LBRACE expression_list RBRACE {
      if ($2->size() == 1) {
        $$ = $2->front();
      } else {
        std::reverse($2->begin(), $2->end());
        $$ = new ExprListExpr(std::move(*$2));
      }
      $$->set_name(token_name(sql_string, &@$));
      delete $2;
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
    | aggr_func_expr{
      $$ = $1;
    }
    | func_expr{
      $$ = $1;
    }
    | sub_query_expr {
      $$ = $1;
    }
    ;

sub_query_expr:
    LBRACE select_stmt RBRACE {
      $$ = new SubQueryExpr($2->selection);
      delete $2;
    }
    ;

aggr_func_expr:
    aggregate_type LBRACE expression RBRACE {
      AggregateType aggr_type = $1;
      ValueExpr *value_expr;
      if ($3->type() == ExprType::FIELD) {
        FieldExpr *field_expr = static_cast<FieldExpr *>($3);
        if (std::string(field_expr->field_name()) == "*") {
          if (aggr_type == AggregateType::COUNT) {
            aggr_type = AggregateType::COUNT_STAR;
            value_expr = new ValueExpr(Value(1));
            $$ = new AggrFunctionExpr(aggr_type, value_expr);
          }
          else {
            yyerror(&@$,sql_string,sql_result,scanner,"'*' can only be used with COUNT");
            YYERROR;
          }
        }
        else {
          $$ = new AggrFunctionExpr(aggr_type, $3);
        }
      }
      $$->set_name(token_name(sql_string, &@$));
    }
    ;

func_expr:
    func_type LBRACE expression_list RBRACE {
      std::reverse($3->begin(),$3->end());
      $$ = new FuncExpr($1, *$3);
      $$->set_name(token_name(sql_string, &@$));
      delete $3;
    }
    ;

func_type:
    LENGTH { $$ = FunctionType::LENGTH; }
    | ROUND { $$ = FunctionType::ROUND; }
    | DATE_FORMAT { $$ = FunctionType::DATE_FORMAT; }
    ;

rel_attr:
    '*' {
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
is_null_comp:
    IS NULL_T
    {
      $$ = true;
    }
    | IS NOT NULL_T
    {
      $$ = false;
    }
    ;
condition:
    expression comp_op expression {
      $$ = new ComparisonExpr($2, $1, $3);
    }
    | expression is_null_comp
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      $$ = new ComparisonExpr($2 ? IS_NULL : IS_NOT_NULL, $1, value_expr);
    }
    | exists_op expression
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      $$ = new ComparisonExpr($1, value_expr, $2);
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
