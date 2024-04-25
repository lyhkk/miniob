/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <memory>
#include <type_traits>
#include <vector>

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<std::unique_ptr<Expression>> &projects_exprs_, bool is_single_table)
{
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    const FieldMeta* field_meta = table_meta.field(i);
    if (field_meta->visible()) {
      FieldExpr *tmp = new FieldExpr(table, field_meta);
      if (is_single_table) {
        tmp->set_name(tmp->field_name());
      } else {
        tmp->set_name(std::string(tmp->table_name()) + "." + tmp->field_name());
      }
      projects_exprs_.emplace_back(tmp);
    }
    // int           is_length_func = relation_attr.is_length_func;
    // int           is_round_func  = relation_attr.is_round_func;
    // std::string   date_format    = relation_attr.date_format;
    // int           round_num      = relation_attr.round_num;
    // AggregateType aggregate_type = relation_attr.aggregate_type;
    // aggregation function: 只有count可以做count(*)
    // if (aggregate_type != AggregateType::NONE && aggregate_type != AggregateType::COUNT_STAR) {
    //   LOG_WARN("invalid query field. The aggregate function cannot receive more than one field.");
    //   return RC::SCHEMA_FIELD_MISSING;
    // }
    // field_metas.push_back(
    //     Field(table, table_meta.field(i), is_length_func, is_round_func, round_num, date_format, aggregate_type));
    // if (aggregate_type == AggregateType::COUNT_STAR) {
    //   break;
    // }
  }
  return;
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *>                     tables;
  std::unordered_map<std::string, Table *> table_map;

  RC                        rc = RC::SUCCESS;
  std::unique_ptr<JoinStmt> join_stmt;
  JoinTableSqlNode         *join_table = select_sql.table;
  if (join_table != nullptr) {
    JoinStmt *join = nullptr;
    rc             = JoinStmt::create(db, join_table, join, tables, table_map);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create join stmt");
      return rc;
    }
    join_stmt.reset(join);
  }

  // TODO： join_stmt的condition合并->为ConjunctionExpr
  // JoinStmt                 *join_stmt_tmp = join_stmt.get();
  // JoinStmt                 *sub_join_tmp  = nullptr;
  // FilterStmt               *condition_tmp = new FilterStmt();
  // std::vector<FilterUnit *> filter_units_tmp;
  // while (join_stmt_tmp != nullptr) {
  //   sub_join_tmp = join_stmt_tmp->sub_join().get();
  //   if (sub_join_tmp == nullptr)  break;
  //   if (join_stmt_tmp->condition() != nullptr && sub_join_tmp->condition() != nullptr) {
  //     condition_tmp->condition() = new ConjunctionExpr(ConjunctionExpr::Type::AND, expr, expr2);
  //     join_stmt_tmp->condition() = nullptr;
  //   }
  //   join_stmt_tmp = sub_join_tmp;
    // join_stmt_tmp = join_stmt_tmp->sub_join().get();
  // }
  // if (!filter_units_tmp.empty()) {
  //   condition_tmp->filter_units().swap(filter_units_tmp);
  //   join_stmt.get()->condition() = condition_tmp;
  // }

  bool is_single_table = (tables.size() == 1);
  Table *default_table = nullptr;
  if (is_single_table) {
    default_table = tables[0];
  }
  // projection in `select` statement
  std::vector<std::unique_ptr<Expression>> projects_query;
  for (int i = 0; i < static_cast<int>(select_sql.proj_exprs.size()); i++) {
    Expression *expr = select_sql.proj_exprs[i];
    auto check_project_expr = [&table_map, &tables, &default_table](Expression *expr) -> RC {
      // TODO add check for project expression
      /* aggregation function: 对于count(a, b)和count()这种聚合函数调用的方法, 就要报错 -> Failure
      * aggregation function: 对于count(*) 的特判，因为其它两个不支持
      * function_type和aggregate_type的检查
      * Aggregate function: select id, max(age) from student 这种混合使用是不考虑的
      */
      if (expr->type() == ExprType::FIELD) {
        FieldExpr *field_expr = static_cast<FieldExpr*>(expr);
        if (field_expr->check_field(table_map, tables, default_table) != RC::SUCCESS) {
          return RC::SCHEMA_FIELD_MISSING;
        }
      }
      return RC::SUCCESS;
    };

    ExprType expr_type = expr->type();
    if (expr_type == ExprType::FIELD) {
      FieldExpr  *field_expr = static_cast<FieldExpr*>(expr);
      const char *table_name = field_expr->table_name();
      const char *field_name = field_expr->field_name();
      ASSERT(!common::is_blank(field_name), "Parse ERROR!");

      if (0 == strcmp(table_name, "*") && 0 == strcmp(field_name, "*")) {
        if (tables.empty() || !field_expr->alias().empty()) {
          return RC::INVALID_ARGUMENT; // not allow: select *; select * as xxx;
        }
        for (Table *table : tables) {
          wildcard_fields(table, projects_query, is_single_table);
        }
      } 
      else if (0 == strcmp(field_name, "*")) {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        wildcard_fields(table, projects_query, is_single_table);
      }
      else {
        if(field_expr->check_field(table_map, tables, default_table) != RC::SUCCESS) {
          LOG_INFO("expr->check_field error!");
          return RC::SCHEMA_FIELD_MISSING;
        }
        projects_query.emplace_back(expr);
      }
    }
    else {
      if (rc = expr->traverse_check(check_project_expr); rc != RC::SUCCESS) {
        LOG_WARN("project expr traverse check_field error!");
        return rc;
      }
      projects_query.emplace_back(expr);
    }
  }
  select_sql.proj_exprs.clear();
  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), projects_query.size());

  // Aggregate function: select id, max(age) from student 这种混合使用是不考虑的
  // for (long unsigned int i = 0; i < query_fields.size(); i++) {
  //   if (query_fields[i].aggregate_type_ != AggregateType::NONE) {
  //     for (long unsigned int j = i + 1; j < query_fields.size(); j++) {
  //       if (query_fields[j].aggregate_type_ == AggregateType::NONE) {
  //         LOG_WARN("invalid query field. The aggregate function cannot mix with other common fields.");
  //         return RC::SCHEMA_FIELD_MISSING;
  //       }
  //     }
  //     break;
  //   } else {
  //     for (long unsigned int j = i + 1; j < query_fields.size(); j++) {
  //       if (query_fields[j].aggregate_type_ != AggregateType::NONE) {
  //         LOG_WARN("invalid query field. The aggregate function cannot mix with other common fields.");
  //         return RC::SCHEMA_FIELD_MISSING;
  //       }
  //     }
  //     break;
  //   }
  // }


  // create filter statement in `where` statement
  FilterStmt * filter_stmt = nullptr;
  rc                      = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions,
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->projects_query_.swap(projects_query);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->join_stmt_.swap(join_stmt);
  stmt = select_stmt;
  return RC::SUCCESS;
}
