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

# include "orderby_stmt.h"

RC OrderByStmt::create(Db *db, std::vector<OrderBySqlNode> &orderby_sql, std::vector<std::unique_ptr<Expression>> &&exprs, OrderByStmt *&stmt) {
  OrderByStmt *orderby_stmt = new OrderByStmt();
  std::vector<std::unique_ptr<OrderByUnit >> tmp_units;
  for (auto &orderby : orderby_sql) {
    tmp_units.emplace_back(std::make_unique<OrderByUnit>(orderby.expr, orderby.is_asc));
  }
  orderby_stmt->set_orderby_units(std::move(tmp_units));
  orderby_stmt->set_exprs(std::move(exprs));
  stmt = orderby_stmt;
  return RC::SUCCESS;
}