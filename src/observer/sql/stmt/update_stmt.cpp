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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "sql/parser/value.h"
#include "sql/stmt/select_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <utility>

UpdateStmt::UpdateStmt(Table *table, std::vector<FieldMeta> fields, std::vector<std::unique_ptr<Expression>> &&values, FilterStmt *filter_stmt)
  : table_(table), fields_(std::move(fields)), values_(std::move(values)), filter_stmt_(filter_stmt)
{}

UpdateStmt::~UpdateStmt()
{
  if(nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, UpdateSqlNode &update, Stmt *&stmt)
{
  const char *table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid update argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  if (update.attribute_names.size() != update.values.size()) {
    LOG_WARN("invalid update argument. attribute amount does not match value amount");
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  auto check_field = [&db](Expression *expr) {
    if (expr->type() == ExprType::SUBQUERY) {
      SubQueryExpr* subquery_expr = static_cast<SubQueryExpr*>(expr);
      return subquery_expr->generate_subquery_stmt(db);
    }
    return RC::SUCCESS;
  };

  std::vector<std::unique_ptr<Expression>> values;
  std::vector<FieldMeta> fields;
  const TableMeta &table_meta = table->table_meta();
  for (size_t i = 0; i < update.attribute_names.size(); i++) {
    const FieldMeta* update_field = table_meta.field(update.attribute_names[i].c_str());
    bool valid = false;
    if (nullptr != update_field) {
      if (update.values[i]->type() == ExprType::VALUE) {
        const Value& value = static_cast<ValueExpr*>(update.values[i])->get_value();
        if (update_field->type() == value.attr_type() || (value.is_null() && update_field->nullable())) {
          if (update_field->type() == CHARS && update_field->len() < value.length()) {
            LOG_WARN("update chars with longer length");
          }
          else {
            valid = true;
          }
        }
      }
      else {
        if (RC rc = update.values[i]->traverse_check(check_field); RC::SUCCESS != rc) {
          return rc;
        }
      }
    }
    if(!valid) {
      LOG_WARN("update field type mismatch. table=%s",table_name);
      return RC::INVALID_ARGUMENT;
    }
    fields.emplace_back(*update_field);
    values.emplace_back(update.values[i]);
  }
  update.values.clear();

  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(
      db, table, &table_map, update.conditions, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  // everything alright
  stmt = new UpdateStmt(table, std::move(fields), std::move(values), filter_stmt);
  return RC::SUCCESS;
}