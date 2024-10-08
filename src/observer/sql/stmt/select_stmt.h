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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <memory>
#include <vector>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include "sql/stmt/join_stmt.h"
#include "sql/stmt/groupby_stmt.h"
#include "sql/stmt/orderby_stmt.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt
{
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }

public:
  static RC create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt);

public:
  std::unique_ptr<JoinStmt>                &join_stmt() { return join_stmt_; }
  const std::vector<Table *>               &tables() const { return tables_; }
  std::vector<std::unique_ptr<Expression>> &projects() { return projects_query_;}
  FilterStmt                               *filter_stmt() { return filter_stmt_; }
  GroupByStmt                              *groupby_stmt() { return groupby_stmt_; }
  FilterStmt                               *having_filter_stmt() { return having_filter_stmt_; }
  OrderByStmt                              *orderby_stmt() { return orderby_stmt_; }
  
private:
  std::unique_ptr<JoinStmt>                join_stmt_;
  std::vector<std::unique_ptr<Expression>> projects_query_;
  std::vector<Table *>                     tables_;
  FilterStmt                              *filter_stmt_ = nullptr;
  GroupByStmt                             *groupby_stmt_ = nullptr;
  FilterStmt                              *having_filter_stmt_ = nullptr;
  OrderByStmt                             *orderby_stmt_ = nullptr;
};
