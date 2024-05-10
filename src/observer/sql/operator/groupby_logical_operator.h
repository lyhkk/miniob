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
// Created by Lyu Yiheng on 2024/05/07
//

#pragma once

#include <memory>
#include <vector>

#include "sql/expr/expression.h"
#include "sql/stmt/groupby_stmt.h"
#include "sql/operator/logical_operator.h"

/**
 * @brief Group By 的逻辑算子
 * @details 作为stmt与物理算子之间的承接
 */
class GroupByLogicalOperator: public LogicalOperator
{
public:
  GroupByLogicalOperator(std::vector<std::unique_ptr<Expression>>&& groupby_fields,
    std::vector<std::unique_ptr<AggrFunctionExpr>> &&aggr_exprs,
    std::vector<std::unique_ptr<FieldExpr>> &&field_exprs);
  virtual ~GroupByLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::GROUPBY; }
  std::vector<std::unique_ptr<Expression>>& groupby_exprs()
  {
    return groupby_exprs_;
  }
  std::vector<std::unique_ptr<AggrFunctionExpr>> &aggr_exprs()
  {
    return aggr_exprs_;
  }
  std::vector<std::unique_ptr<FieldExpr>> &field_exprs()
  {
    return field_exprs_;
  }

private:
  std::vector<std::unique_ptr<Expression>> groupby_exprs_;
  std::vector<std::unique_ptr<AggrFunctionExpr>> aggr_exprs_;
  std::vector<std::unique_ptr<FieldExpr>> field_exprs_;
};
