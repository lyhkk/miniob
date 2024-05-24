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
// Created by Lyu Yiheng on 2024/05/23
//

#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include "common/rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/expr/expression.h"

class Db;
class Table;

class OrderByUnit {
public:
  OrderByUnit(Expression* expr, bool is_asc) : expr_(expr), is_asc_(is_asc) {}

  bool order_type() { return is_asc_; }
  std::unique_ptr<Expression>& expr() { return expr_; }

private:
  std::unique_ptr<Expression> expr_;
  bool is_asc_;
};

class OrderByStmt : public Stmt {
public:
  OrderByStmt() = default;
  ~OrderByStmt() override = default;

  StmtType type() const override { return StmtType::ORDERBY; }

  std::vector<std::unique_ptr<OrderByUnit>>& order_units() { return order_units_; }
  std::vector<std::unique_ptr<Expression>>& exprs() { return exprs_; }

  void set_orderby_units(std::vector<std::unique_ptr<OrderByUnit>> &&units) { order_units_ = std::move(units); }
  void set_exprs(std::vector<std::unique_ptr<Expression>> &&exprs) { exprs_ = std::move(exprs); }

  static RC create(Db *db, std::vector<OrderBySqlNode> &orderby_sql, std::vector<std::unique_ptr<Expression>> &&exprs, OrderByStmt *&stmt);

private:
  std::vector<std::unique_ptr<OrderByUnit>> order_units_;
  std::vector<std::unique_ptr<Expression>>  exprs_; // select list
};