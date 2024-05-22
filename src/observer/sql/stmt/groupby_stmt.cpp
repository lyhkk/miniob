//
// Created by Lyu Yiheng on 2024/5/7.
//

#include "common/rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/groupby_stmt.h"
#include "sql/stmt/filter_stmt.h"

RC GroupByStmt::create(const std::vector<Expression*>& groupby_expr, GroupByStmt *&stmt,
    std::vector<std::unique_ptr<AggrFunctionExpr>> &&aggr_exprs,
    std::vector<std::unique_ptr<FieldExpr>> &&field_exprs)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  std::vector<std::unique_ptr<Expression>> groupby_exprs;
  for(auto expr : groupby_expr)
  {
    groupby_exprs.emplace_back(expr);
  }
  stmt = new GroupByStmt();
  stmt->aggr_exprs_ = std::move(aggr_exprs);
  stmt->field_exprs_ = std::move(field_exprs);
  stmt->groupby_exprs_ = std::move(groupby_exprs);
  return rc;
}