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

#include "sql/operator/groupby_logical_operator.h"

GroupByLogicalOperator::GroupByLogicalOperator(
  std::vector<std::unique_ptr<Expression>>&& groupby_exprs,
  std::vector<std::unique_ptr<AggrFunctionExpr>> &&aggr_exprs,
  std::vector<std::unique_ptr<FieldExpr>> &&field_exprs) 
    : groupby_exprs_(std::move(groupby_exprs)),
      aggr_exprs_(std::move(aggr_exprs)),
      field_exprs_(std::move(field_exprs))
{
}

