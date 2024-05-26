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
#include "sql/operator/physical_operator.h"
#include "sql/expr/expression.h"
#include "sql/stmt/orderby_stmt.h"
#include "sql/expr/tuple.h"

class OrderByPhysicalOperator : public PhysicalOperator
{
public:
  OrderByPhysicalOperator(std::vector<std::unique_ptr<OrderByUnit>> &&orderby_units,
    std::vector<std::unique_ptr<Expression>> &&exprs);
  virtual ~OrderByPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::ORDERBY; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  RC order_main();

  Tuple *current_tuple() override;
private:
  std::vector<std::unique_ptr<OrderByUnit>> orderby_units_;
  SortedTuple tuple_;

  std::vector<std::vector<Value>> sorted_proj_values_; // select字段的值
  std::vector<int> ordered_indices_; // 排序后的索引
  std::vector<int>::size_type current_index_ = 0;
};
