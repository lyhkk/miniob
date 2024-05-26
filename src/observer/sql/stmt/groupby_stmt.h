//
// Created by Lyu Yiheng on 2024/5/7.
//

#pragma once

#include <memory>
#include <vector>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "sql/expr/expression.h"
#include "sql/stmt/orderby_stmt.h"

/**
 * @brief 表示group by clause
 * @ingroup Statement
 */
class GroupByStmt : public Stmt
{
public:
  GroupByStmt() = default;
  ~GroupByStmt() override = default;

  StmtType type() const override { return StmtType::GROUPBY; }

public:
  static RC create(const std::vector<Expression*>& groupby_expr, GroupByStmt *&stmt,
    std::vector<std::unique_ptr<AggrFunctionExpr>> &&aggr_exprs,
    std::vector<std::unique_ptr<FieldExpr>> &&field_exprs, OrderByStmt *sortby_stmt = nullptr);

public:
  std::vector<std::unique_ptr<Expression>>& groupby_exprs() { return groupby_exprs_; }
  std::vector<std::unique_ptr<AggrFunctionExpr>>& aggr_exprs() { return aggr_exprs_; }
  std::vector<std::unique_ptr<FieldExpr>>& field_exprs() { return field_exprs_; }
  OrderByStmt *sortby_stmt() { return sortby_stmt_; }
  
private:
  std::vector<std::unique_ptr<Expression>> groupby_exprs_; // group by的表达式
  std::vector<std::unique_ptr<AggrFunctionExpr>> aggr_exprs_;   // 聚合函数表达式
  std::vector<std::unique_ptr<FieldExpr>>  field_exprs_; // group by中的字段表达式
  OrderByStmt *sortby_stmt_ = nullptr;
};
