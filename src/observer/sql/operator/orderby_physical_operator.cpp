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

#include "sql/operator/orderby_physical_operator.h"
#include "common/log/log.h"
#include "sql/parser/value.h"

OrderByPhysicalOperator::OrderByPhysicalOperator(std::vector<std::unique_ptr<OrderByUnit>> &&orderby_units,
  std::vector<std::unique_ptr<Expression>> &&exprs)
  : orderby_units_(std::move(orderby_units))
{
  tuple_.init(std::move(exprs));
}

RC OrderByPhysicalOperator::open(Trx *trx) {
  if (children_.empty()) {
    LOG_WARN("OrderBy physical operator must has a child operator");
    return RC::INTERNAL;
  }
  RC rc = RC::SUCCESS;
  rc = children_[0]->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  rc = order_main();
  return rc;
}

RC OrderByPhysicalOperator::order_main() {
  RC rc = RC::SUCCESS;

  int index = 0;
  typedef std::pair<std::vector<Value>, int> IdxValPair;
  std::vector<IdxValPair> pair_sort_table; // 要排序的内容
  std::vector<Value> pair_cell; // 参与排序的cell -> from orderby_units_
  std::vector<Value> row_values(tuple_.exprs().size()); // 参与排序的row -> from tuple_
  int row_values_index = 0;
  
  while (children_[0]->next() == RC::SUCCESS) { // 从child中取出所有的数据
    pair_cell.clear();
    row_values_index = 0;
    for (auto &unit : orderby_units_) {
      Value cell;
      rc = unit->expr()->get_value(*children_[0]->current_tuple(), cell); // 取出每行中要参与排序的cell
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to evaluate expression: %s", strrc(rc));
        return rc;
      }
      pair_cell.emplace_back(cell);
    }
    pair_sort_table.emplace_back(std::make_pair(pair_cell, index));
    index++;

    // 存储select子句的fieldexpr和aggexpr
    Value expr_cell;
    for(auto &expr : tuple_.exprs()){
      if(expr->get_value(*children_[0]->current_tuple(), expr_cell) != RC::SUCCESS)
      {
        LOG_WARN("error in sort");
        return RC::INTERNAL;
      }
      row_values[row_values_index++] = expr_cell;
    }
    sorted_proj_values_.emplace_back(row_values); // values 中缓存每一行
  }

  bool is_asc[orderby_units_.size()];
  for (size_t i = 0; i < orderby_units_.size(); i++) {
    is_asc[i] = orderby_units_[i]->order_type(); // true: asc, false: desc
  }

  std::sort(pair_sort_table.begin(), pair_sort_table.end(), [&is_asc](const IdxValPair &a, const IdxValPair &b) {
    // lambda: return true if a should go before b, return true = swap a and b
    auto &cells_a = a.first;
    auto &cells_b = b.first;
    assert(cells_a.size() == cells_b.size());
    for (size_t i = 0; i < cells_a.size(); ++i) {
      // if one of the cells is null, the null cell is the smallest
      if (cells_a[i].is_null() && cells_b[i].is_null()) {
        continue;
      }
      else if (cells_a[i].is_null()) {
        return is_asc[i] ? true : false;
      }
      else if (cells_b[i].is_null()) {
        return is_asc[i] ? false : true;
      }
      else if (cells_a[i].compare(cells_b[i]) < 0) {
        return is_asc[i];
      } 
      else if (cells_a[i].compare(cells_b[i]) > 0) {
        return !is_asc[i];
      }
    }
    // 如果所有的cell都相等，那么就不需要交换
    return false;
  });

  for (size_t i = 0; i < pair_sort_table.size(); ++i) {
    ordered_indices_.emplace_back(pair_sort_table[i].second); // 索引排序
  }
  return rc;
}

RC OrderByPhysicalOperator::next() {
  if (current_index_ >= ordered_indices_.size()) {
    return RC::RECORD_EOF;
  }
  // assert(sorted_proj_values_[ordered_indices_[current_index_]])
  tuple_.set_cells(&sorted_proj_values_[ordered_indices_[current_index_]]);
  current_index_++;
  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::close() {
  RC rc = children_[0]->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close child operator: %s", strrc(rc));
    return rc;
  }
  return RC::SUCCESS;
}

Tuple *OrderByPhysicalOperator::current_tuple() {
  return &tuple_;
}