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

#pragma once

#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field_meta.h"
#include <memory>
#include <vector>

class Table;

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt
{
public:
  UpdateStmt() = default;
  UpdateStmt(Table *table, std::vector<FieldMeta> fields, 
             std::vector<std::unique_ptr<Expression>>&& values, FilterStmt *filter_stmt);
  ~UpdateStmt() override;
  StmtType type() const override { return StmtType::UPDATE; }
public:
  static RC create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt);

public:
  Table *table() const { return table_; }
  std::vector<FieldMeta> &fields() {return fields_; }
  std::vector<std::unique_ptr<Expression>> &values() {return values_; }
  FilterStmt *filter_stmt() {return filter_stmt_; }

private:
  Table *table_        = nullptr;
  std::vector<FieldMeta> fields_; //需要更新的列
  std::vector<std::unique_ptr<Expression>> values_; //更新的值
  FilterStmt *filter_stmt_ = nullptr; //条件
};
