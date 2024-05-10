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

#include "sql/operator/groupby_physical_operator.h"
#include "common/log/log.h"


GroupByPhysicalOperator::GroupByPhysicalOperator(std::vector<std::unique_ptr<Expression>> &&groupby_exprs,
                std::vector<std::unique_ptr<AggrFunctionExpr>> &&aggr_exprs,
                std::vector<std::unique_ptr<FieldExpr>> &&field_exprs)
    : groupby_exprs_(std::move(groupby_exprs))
{ tuple_.init(std::move(aggr_exprs), std::move(field_exprs)); }

RC GroupByPhysicalOperator::open(Trx *trx) {
  if (children_.empty()) {
    LOG_WARN("GroupBy physical operator must has a child operator");
    return RC::INTERNAL;
  }
  RC rc = RC::SUCCESS;
  rc = children_[0]->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  tuple_.reset();
  tuple_.set_tuple(children_[0]->current_tuple());
  is_record_eof_ = false;
  is_first_ = true;
  is_new_group_ = true;
  return rc;
}

RC GroupByPhysicalOperator::next() {
  if (is_record_eof_) {
    return RC::RECORD_EOF;
  }
  RC rc = RC::SUCCESS;
  if (is_first_) {
    is_first_ = false;
    is_new_group_ = true;

    rc = children_[0]->next();
    if (RC::SUCCESS != rc) {
      if (RC::RECORD_EOF == rc) {
        is_record_eof_ = true;
        if (groupby_exprs_.empty()) {
          tuple_.do_aggregate_done();
          return RC::SUCCESS;
        }
      }
      return rc;
    }
    
    
    for (const std::unique_ptr<Expression>& expr : groupby_exprs_) {
      Value val;
      expr->get_value(*children_[0]->current_tuple(), val);
      pre_groupby_values_.emplace_back(val);
    }
    LOG_INFO("GroupByOperator set first success!");
  }

  while (1) {
    if (is_new_group_) {
      is_new_group_ = false;
      tuple_.do_aggregate_first();
    }
    rc = children_[0]->next();
    if (rc != RC::SUCCESS) break;
    // update group
    if (!groupby_exprs_.empty()) {
      int i = 0;
      for (auto &expr : groupby_exprs_) {
        Value value;
        expr->get_value(*children_[0]->current_tuple(), value);
        if (value.compare(pre_groupby_values_[i]) != 0) {
          pre_groupby_values_[i] = value;
          is_new_group_ = true;
        }
        i++;
        std::vector<std::vector<int>> my_matrix(2, std::vector<int>(3));
      }
    }
    if (is_new_group_) {
      tuple_.do_aggregate_done();
      return rc;
    }
    tuple_.do_aggregate();
  }

  if (RC::RECORD_EOF == rc) {
    is_record_eof_ = true;
    tuple_.do_aggregate_done();
    return RC::SUCCESS;
  }
  return rc;
}

RC GroupByPhysicalOperator::close()
{
  return children_[0]->close();
}