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
// Created by Wangyunlai on 2022/07/05.
//

#include "sql/expr/expression.h"
#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "common/lang/string.h"
#include "sql/parser/value.h"
#include <memory>
#include <cmath>
using namespace std;

RC FieldExpr::get_value(const Tuple &tuple, Value &value) const
{
  if(is_first_)
  {
    // GroupTuple *group_tuple = static_cast<GroupTuple*>(const_cast<Tuple*>(&tuple));
    bool & is_first_ref = const_cast<bool&>(is_first_);
    is_first_ref = false;
    return tuple.find_cell(TupleCellSpec(table_name(), field_name()), value, const_cast<int&>(index_));
  }
  else
  {
    return tuple.cell_at(index_,value);
  }
}

RC FieldExpr::check_field(const std::unordered_map<std::string, Table *> &table_map,
  const std::vector<Table *> &tables, Table* default_table,
  const std::unordered_map<std::string, std::string> & table_alias_map) {
  ASSERT(field_name_ != "*", "ERROR!");
  const char* table_name = table_name_.c_str();
  const char* field_name = field_name_.c_str();
  Table * table = nullptr;
  if(!common::is_blank(table_name)) { //表名不为空
    // check table
    auto iter = table_map.find(table_name);
    if (iter == table_map.end()) {
      LOG_WARN("no such table in from list: %s", table_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    table = iter->second;
  } else { // 表名为空，只有列名
    if (tables.size() != 1 && default_table == nullptr) {
      LOG_WARN("invalid. I do not know the attr's table. attr=%s", this->field_name());
      return RC::SCHEMA_FIELD_MISSING;
    }
    table = default_table ? default_table : tables[0];
  }
  ASSERT(nullptr != table, "ERROR!");
  // set table_name
  table_name_ = table->name();
  // check field
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("no such field. field=%s.%s", table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }
  // set field_
  field_ = Field(table, field_meta);
  // set name 没用了 暂时保留它
  bool is_single_table = (tables.size() == 1);
  if(is_single_table) {
    set_name(field_name_);
  } else {
    set_name(table_name_ + "." + field_name_);
  }
  // set alias
  if (alias().empty()) {
    if (is_single_table) {
      set_alias(field_name_);
    } else {
      auto iter = table_alias_map.find(table_name_);
      if (iter != table_alias_map.end()) {
        set_alias(iter->second + "." + field_name_);
      } else {
        set_alias(table_name_ + "." + field_name_);
      }
    }
  }
  return RC::SUCCESS;
}

RC ValueExpr::get_value(const Tuple &tuple, Value &value) const
{
  value = value_;
  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type) : child_(std::move(child)), cast_type_(cast_type)
{}

CastExpr::~CastExpr() {}

RC CastExpr::cast(const Value &value, Value &cast_value) const
{
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }

  switch (cast_type_) {
    case BOOLEANS: {
      bool val = value.get_boolean();
      cast_value.set_boolean(val);
    } break;
    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported convert from type %d to %d", child_->value_type(), cast_type_);
    }
  }
  return rc;
}

RC CastExpr::get_value(const Tuple &tuple, Value &cell) const
{
  RC rc = child_->get_value(tuple, cell);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(cell, cell);
}

RC CastExpr::try_get_value(Value &value) const
{
  RC rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, value);
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right))
{}

ComparisonExpr::~ComparisonExpr() {}

RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
{
  RC  rc         = RC::SUCCESS;
  result         = false;

  if (comp_ == IS_NULL || comp_ == IS_NOT_NULL) {
    ASSERT(right.is_null(), "Right-hand side shoule be null.");
    result = comp_ == IS_NULL ? left.is_null() : !left.is_null();
    return rc;
  }
  if (left.is_null() || right.is_null()) {
    result = false;
    return rc;
  }

  if (comp_ == LIKE_OP) {
    result = (left.like_type_compare(right) == 0);
  }
  else if (comp_ == NOT_LIKE_OP) {
    result = (left.like_type_compare(right) != 0);
  }
  else {
    int cmp_result = left.compare(right);
    switch (comp_){
      case EQUAL_TO: {
        result = (0 == cmp_result);
      } break;
      case LESS_EQUAL: {
        result = (cmp_result <= 0);
      } break;
      case NOT_EQUAL: {
        result = (cmp_result != 0);
      } break;
      case LESS_THAN: {
        result = (cmp_result < 0);
      } break;
      case GREAT_EQUAL: {
        result = (cmp_result >= 0);
      } break;
      case GREAT_THAN: {
        result = (cmp_result > 0);
      } break;
      default: {
        LOG_WARN("unsupported comparison. %d", comp_);
        rc = RC::INTERNAL;
      } break;
    }
  }
  return rc;
}

RC ComparisonExpr::try_get_value(Value &cell) const
{
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr   *left_value_expr  = static_cast<ValueExpr *>(left_.get());
    ValueExpr   *right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell        = left_value_expr->get_value();
    const Value &right_cell       = right_value_expr->get_value();

    bool value = false;
    RC   rc    = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) const
{
  Value left_value;
  Value right_value;

  RC rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }

  bool bool_value = false;

  rc = compare_value(left_value, right_value, bool_value);
  if (rc == RC::SUCCESS) {
    value.set_boolean(bool_value);
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
ConjunctionExpr::ConjunctionExpr(Type type, vector<unique_ptr<Expression>> &children)
    : conjunction_type_(type), children_(std::move(children))
{}

RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  value.set_boolean(default_value);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right)
    : arithmetic_type_(type), left_(left), right_(right)
{}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right))
{}

AttrType ArithmeticExpr::value_type() const
{
  if (!right_) {
    return left_->value_type();
  }

  if (left_->value_type() == AttrType::INTS && right_->value_type() == AttrType::INTS &&
      arithmetic_type_ != Type::DIV) {
    return AttrType::INTS;
  }

  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();

  switch (arithmetic_type_) {
    case Type::ADD: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() + right_value.get_int());
      } else {
        value.set_float(left_value.get_float() + right_value.get_float());
      }
    } break;

    case Type::SUB: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() - right_value.get_int());
      } else {
        value.set_float(left_value.get_float() - right_value.get_float());
      }
    } break;

    case Type::MUL: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() * right_value.get_int());
      } else {
        value.set_float(left_value.get_float() * right_value.get_float());
      }
    } break;

    case Type::DIV: {
      if (target_type == AttrType::INTS) {
        if (right_value.get_int() == 0) {
          // NOTE:
          // 设置为整数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为整数最大值。
          value.set_int(numeric_limits<int>::max());
        } else {
          value.set_int(left_value.get_int() / right_value.get_int());
        }
      } else {
        if (right_value.get_float() > -EPSILON && right_value.get_float() < EPSILON) {
          // NOTE:
          // 设置为浮点数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为浮点数最大值。
          value.set_float(numeric_limits<float>::max());
        } else {
          value.set_float(left_value.get_float() / right_value.get_float());
        }
      }
    } break;

    case Type::NEGATIVE: {
      if (target_type == AttrType::INTS) {
        value.set_int(-left_value.get_int());
      } else {
        value.set_float(-left_value.get_float());
      }
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
    } break;
  }
  return rc;
}

RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  if (right_) {
    rc = right_->get_value(tuple, right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }
  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

AggrFunctionExpr::AggrFunctionExpr(AggregateType aggr_type, std::unique_ptr<Expression> &param) 
  : aggr_type_(aggr_type), param_(std::move(param))
{}

AggrFunctionExpr::AggrFunctionExpr(AggregateType aggr_type, Expression* param)
  : aggr_type_(aggr_type), param_(param)
{}

RC AggrFunctionExpr::check_aggregate_func_type() const {
  AttrType type = param_->value_type();
  if (aggr_type_ == AggregateType::AVG || aggr_type_ == AggregateType::SUM) {
    if (type != AttrType::INTS && type != AttrType::FLOATS) {
      return RC::INVALID_ARGUMENT;
    }
  }
  return RC::SUCCESS;
}

AttrType AggrFunctionExpr::get_aggr_attr_type(AttrType type) const {
  if (aggr_type_ == AggregateType::AVG) {
    return AttrType::FLOATS;
  }
  else if (aggr_type_ == AggregateType::COUNT || aggr_type_ == AggregateType::COUNT_STAR) {
    return AttrType::INTS;
  }
  else if (aggr_type_ == AggregateType::MAX || aggr_type_ == AggregateType::MIN || aggr_type_ == AggregateType::SUM) {
    return type;
  }
  return AttrType::UNDEFINED;
}

RC AggrFunctionExpr::get_value(const Tuple &tuple, Value &value) const {
  RC rc = RC::SUCCESS;
  TupleCellSpec spec(name().c_str());
  //int index = 0;
  // spec.set_agg_type(get_aggr_func_type());
  if(is_first_)
  {
    bool & is_first_ref = const_cast<bool&>(is_first_);
    is_first_ref = false;
    GroupTuple *group_tuple = static_cast<GroupTuple*>(const_cast<Tuple*>(&tuple));
    rc = group_tuple->find_cell(spec, value, const_cast<int&>(index_));
  }
  else
  {
    return tuple.cell_at(index_, value);
  }
  return rc;
}

RC AggrFunctionExpr::try_get_value(Value &value) const {
  RC rc = RC::SUCCESS;
  Value cell;
  rc = param_->try_get_value(cell);
  return rc;
}

AttrType FuncExpr::get_func_attr_type(AttrType type) const
{  // function功能，需要修改type
  if (FunctionType::LENGTH == func_type_) {
    return AttrType::INTS;
  } else if (FunctionType::ROUND == func_type_) {
    return AttrType::FLOATS;
  } else if (FunctionType::DATE_FORMAT == func_type_) {
    return AttrType::CHARS;
  }
  return type;
}

FuncExpr::FuncExpr(FunctionType func_type, vector<Expression*> &params)
  : func_type_(func_type) 
{
  for (auto& param : params) {
    params_.emplace_back(param);
  }
}

RC FuncExpr::check_function_param_type() const{
  switch(func_type_) {
    case FunctionType::LENGTH: {
      if (params_.size() != 1) {
        return RC::INVALID_ARGUMENT;
      }
      if (params_[0]->value_type() != AttrType::CHARS) {
        return RC::INVALID_ARGUMENT;
      }
    } break;
    case FunctionType::ROUND: {
      if (params_.size() != 1 && params_.size() != 2) {
        return RC::INVALID_ARGUMENT;
      }
      if (params_[0]->value_type() != AttrType::FLOATS) {
        return RC::INVALID_ARGUMENT;
      }
      if (params_.size() == 2 && params_[1]->value_type() != AttrType::INTS) {
        return RC::INVALID_ARGUMENT;
      }
    } break;
    case FunctionType::DATE_FORMAT: {
      if (params_.size() != 2) {
        return RC::INVALID_ARGUMENT;
      }
      if (params_[0]->value_type() != AttrType::DATES) {
        return RC::INVALID_ARGUMENT;
      }
      if (params_[1]->value_type() != AttrType::CHARS) {
        return RC::INVALID_ARGUMENT;
      }
    } break;
  }
  return RC::SUCCESS;
}

RC FuncExpr::try_get_value(Value &value) const{
  RC rc = RC::SUCCESS;
  Value cell; // 用于存储待计算子表达式的值
  switch(func_type_) {
    case FunctionType::LENGTH: {
      assert(params_.size() == 1);
      rc = params_[0]->try_get_value(cell);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get value of child expression. rc=%s", strrc(rc));
        return rc;
      }
      value.set_int(cell.get_string().size());
    } break;
    case FunctionType::ROUND: {
      assert(params_.size() == 2 || params_.size() == 1);

      // 1. get round_num(四舍五入的位数)
      int round_num = 0;
      if (params_.size() == 1) {
        round_num = 0;
      }
      else {
        Value tmp;
        rc = params_[1]->try_get_value(tmp);
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to get value of child expression. rc=%s", strrc(rc));
          return rc;
        }
        round_num = tmp.get_int();
      }

      // 2. get cell
      rc = params_[0]->try_get_value(cell);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get value of child expression. rc=%s", strrc(rc));
        return rc;
      }

      // 3. round && set value
      float round_value = cell.get_float();
      // 根据round_num_进行四舍五入, round_num_为0时，四舍五入到整数, round_num_为1时，四舍五入到小数点后一位, 以此类推
      float temp = round_value * std::pow(10, round_num);
      temp = std::round(temp);
      temp = temp / std::pow(10, round_num);
      if (round_num <= 0) {
        value.set_int(temp);
      }
      else {
        value.set_float(temp);
      }
    } break;
    case FunctionType::DATE_FORMAT: {
      assert(params_.size() == 2);
      // 1. get cell && check type
      rc = params_[0]->try_get_value(cell);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get value of child expression. rc=%s", strrc(rc));
        return rc;
      }
      // 2. get date_format
      Value format_value;
      rc = params_[1]->try_get_value(format_value);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get value of child expression. rc=%s", strrc(rc));
        return rc;
      }
      std::string date_format = format_value.get_string();

      // 3. format date && set value
      int date = cell.get_int();
      std::string date_str = std::to_string(date);
      std::stringstream ss(date_str);
      tm tm = {};
      char* formatted_date = strptime(date_str.c_str(), "%Y%m%d", &tm);
      if (formatted_date == NULL) {
        LOG_INFO("A weird date. date=%s", date_str.c_str()); // 理论上不会出现这种情况，为了完整性
      }
      else {
        char buffer[80];
        strftime(buffer, 80, date_format.c_str(), &tm);
        value.set_string(buffer);
      }
    } break;
  }
  return rc;
}

RC FuncExpr::get_value(const Tuple &tuple, Value &value) const{
  RC rc = RC::SUCCESS;
  Value cell; // 用于存储待计算子表达式的值
  switch(func_type_) {
    case FunctionType::LENGTH: {
      assert(params_.size() == 1);
      rc = params_[0]->get_value(tuple, cell);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get value of child expression. rc=%s", strrc(rc));
        return rc;
      }
      
      value.set_int(cell.get_string().size());
    } break;
    case FunctionType::ROUND: {
      assert(params_.size() == 2 || params_.size() == 1);

      // 1. get round_num(四舍五入的位数)
      int round_num = 0;
      if (params_.size() == 1) {
        round_num = 0;
      }
      else {
        Value tmp;
        rc = params_[1]->try_get_value(tmp);
        if (rc != RC::SUCCESS || tmp.attr_type() != AttrType::INTS) {
          LOG_WARN("failed to get value of child expression. rc=%s", RC::INTERNAL);
          return RC::INTERNAL;
        }
        round_num = tmp.get_int();
      }

      // 2. get cell
      rc = params_[0]->get_value(tuple, cell);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get value of child expression. rc=%s", strrc(rc));
        return rc;
      }
      // 3. round
      float round_value = cell.get_float();
      // 根据round_num_进行四舍五入, round_num_为0时，四舍五入到整数, round_num_为1时，四舍五入到小数点后一位, 以此类推
      float temp = round_value * std::pow(10, round_num);
      temp = std::round(temp);
      temp = temp / std::pow(10, round_num);
      if (round_num <= 0) {
        value.set_int(temp);
      }
      else {
        value.set_float(temp);
      }
    } break;
    case FunctionType::DATE_FORMAT: {
      assert(params_.size() == 2);
      // 1. get cell && check type
      rc = params_[0]->get_value(tuple, cell);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get value of child expression. rc=%s", strrc(rc));
        return rc;
      }

      // 2. get date_format
      Value format_value;
      rc = params_[1]->try_get_value(format_value);
      if (rc != RC::SUCCESS || format_value.attr_type() != AttrType::CHARS) {
        LOG_WARN("failed to get value of child expression. rc=RC::INTERNAL");
        return RC::INTERNAL;
      }
      std::string date_format = format_value.get_string();

      // 3. format date && set value
      int date = cell.get_int();
      std::string date_str = std::to_string(date);
      std::stringstream ss(date_str);
      tm tm = {};
      char* formatted_date = strptime(date_str.c_str(), "%Y%m%d", &tm);
      if (formatted_date == NULL) {
        LOG_INFO("A weird date. date=%s", date_str.c_str()); // 理论上不会出现这种情况，为了完整性
      }
      else {
        char buffer[80];
        strftime(buffer, 80, date_format.c_str(), &tm);
        value.set_string(buffer);
      }
    } break;
  }
  return rc;
}