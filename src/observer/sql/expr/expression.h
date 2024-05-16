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

#pragma once

#include "gtest/gtest.h"
#include <cxxabi.h>
#include <memory>
#include <string>
#include <vector>

#include "sql/parser/value.h"
#include "storage/field/field.h"

class Tuple;

/**
 * @defgroup Expression
 * @brief 表达式
 */

/**
 * @brief 表达式类型
 * @ingroup Expression
 */
enum class ExprType
{
  NONE,
  STAR,         ///< 星号，表示所有字段
  FIELD,        ///< 字段。在实际执行时，根据行数据内容提取对应字段的值
  VALUE,        ///< 常量值
  CAST,         ///< 需要做类型转换的表达式
  COMPARISON,   ///< 需要做比较的表达式
  CONJUNCTION,  ///< 多个表达式使用同一种关系(AND或OR)来联结
  ARITHMETIC,   ///< 算术运算
  AGGRFUNCTION, ///< 聚合函数
  FUNCTION
};

/**
 * @brief 表达式的抽象描述
 * @ingroup Expression
 * @details 在SQL的元素中，任何需要得出值的元素都可以使用表达式来描述
 * 比如获取某个字段的值、比较运算、类型转换
 * 当然还有一些当前没有实现的表达式，比如算术运算。
 *
 * 通常表达式的值，是在真实的算子运算过程中，拿到具体的tuple后
 * 才能计算出来真实的值。但是有些表达式可能就表示某一个固定的
 * 值，比如ValueExpr。
 */
class Expression
{
public:
  Expression()          = default;
  virtual ~Expression() = default;

  /**
   * @brief 根据具体的tuple，来计算当前表达式的值。tuple有可能是一个具体某个表的行数据
   */
  virtual RC get_value(const Tuple &tuple, Value &value) const = 0;

  /**
   * @brief 在没有实际运行的情况下，也就是无法获取tuple的情况下，尝试获取表达式的值
   * @details 有些表达式的值是固定的，比如ValueExpr，这种情况下可以直接获取值
   */
  virtual RC try_get_value(Value &value) const { return RC::UNIMPLENMENT; }

  virtual void traverse(const std::function<void(Expression*)>& func, const std::function<bool(Expression*)>& filter)
  {
    if (filter(this)) {
      func(this);
    }
  }
  virtual RC traverse_check(const std::function<RC(Expression *)>& check_func) { return check_func(this); }

  /**
   * @brief 表达式的类型
   * 可以根据表达式类型来转换为具体的子类
   */
  virtual ExprType type() const = 0;

  /**
   * @brief 表达式值的类型
   * @details 一个表达式运算出结果后，只有一个值
   */
  virtual AttrType value_type() const = 0;

  /**
   * unique_ptr的释放
   */
  virtual std::unique_ptr<Expression> unique_ptr_copy() const = 0;
  /**
   * @brief 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容
   */
  virtual std::string name() const { return name_; }
  virtual void        set_name(std::string name) { name_ = name; }
  virtual std::string alias() const { return alias_; }
  virtual void        set_alias(std::string alias) { alias_ = alias; }

private:
  std::string name_;
  std::string alias_{};
};

/**
 * @brief 字段表达式
 * @ingroup Expression
 */
class FieldExpr : public Expression
{
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field) {}
  FieldExpr(const std::string& table_name, const std::string& field_name) : table_name_(table_name), field_name_(field_name) {}
  FieldExpr(const Field &field) : field_(field) {}

  virtual ~FieldExpr() = default;

  std::unique_ptr<Expression> unique_ptr_copy() const override {
    return std::unique_ptr<FieldExpr>(new FieldExpr(*this));
  }
  ExprType type() const override { return ExprType::FIELD; }
  AttrType value_type() const override { return field_.attr_type(); }
  RC check_field(const std::unordered_map<std::string, Table *> &table_map,
    const std::vector<Table *> &tables, Table* default_table, 
    const std::unordered_map<std::string, std::string> & table_alias_map = {});

  Field &field() { return field_; }
  const Field &field() const { return field_; }
  void set_field(const Table *table, const FieldMeta *field) {
    field_ = Field(table, field);
  }

  const char *table_name() const { return table_name_.c_str(); }
  const char *field_name() const { return field_name_.c_str(); }

  RC get_value(const Tuple &tuple, Value &value) const override;

private:
  Field field_;
  std::string table_name_;
  std::string field_name_;

  // for GroupBy
  int index_ = -1;
  bool is_first_ = true;
};

/**
 * @brief 常量值表达式
 * @ingroup Expression
 */
class ValueExpr : public Expression
{
public:
  ValueExpr() = default;
  explicit ValueExpr(const Value &value) : value_(value) {}

  virtual ~ValueExpr() = default;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override
  {
    value = value_;
    return RC::SUCCESS;
  }

  std::unique_ptr<Expression> unique_ptr_copy() const override {
    return std::unique_ptr<ValueExpr>(new ValueExpr(*this));
  }

  ExprType type() const override { return ExprType::VALUE; }
  AttrType value_type() const override { return value_.attr_type(); }

  void         get_value(Value &value) const { value = value_; }
  const Value &get_value() const { return value_; }

private:
  Value value_;
};

/**
 * @brief 类型转换表达式
 * @ingroup Expression
 */
class CastExpr : public Expression
{
public:
  CastExpr(std::unique_ptr<Expression> child, AttrType cast_type);
  virtual ~CastExpr();

  ExprType type() const override { return ExprType::CAST; }
  RC       get_value(const Tuple &tuple, Value &value) const override;

  RC try_get_value(Value &value) const override;

  AttrType value_type() const override { return cast_type_; }

  std::unique_ptr<Expression> &child() { return child_; }
  std::unique_ptr<Expression> unique_ptr_copy() const override {
    auto new_expr = std::make_unique<CastExpr>(child_->unique_ptr_copy(), cast_type_);
    new_expr->set_name(name());
    return new_expr;
  }

  RC traverse_check(const std::function<RC(Expression*)>& check_func) override
  {
    if (RC rc = child_->traverse_check(check_func); RC::SUCCESS != rc) {
      return rc;
    } else if (rc = check_func(this); RC::SUCCESS != rc) {
      return rc;
    }
    return RC::SUCCESS;
  }

  void traverse(const std::function<void(Expression*)>& func, const std::function<bool(Expression*)>& filter) override
  {
    if (filter(this)) {
      child_->traverse(func, filter);
      func(this);
    }
  }

private:
  RC cast(const Value &value, Value &cast_value) const;

private:
  std::unique_ptr<Expression> child_;      ///< 从这个表达式转换
  AttrType                    cast_type_;  ///< 想要转换成这个类型
};

/**
 * @brief 比较表达式
 * @ingroup Expression
 */
class ComparisonExpr : public Expression
{
public:
  ComparisonExpr(CompOp comp, Expression* left, Expression* right): comp_(comp), left_(left), right_(right){}
  ComparisonExpr(CompOp comp, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ComparisonExpr();

  ExprType type() const override { return ExprType::COMPARISON; }
  RC       get_value(const Tuple &tuple, Value &value) const override;
  AttrType value_type() const override { return BOOLEANS; }
  CompOp   comp() const { return comp_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  std::unique_ptr<Expression> unique_ptr_copy() const override {
    std::unique_ptr<Expression> new_left_ = left_->unique_ptr_copy();
    std::unique_ptr<Expression> new_right_ = nullptr;
    if (right_ != nullptr) {
      new_right_ = right_->unique_ptr_copy();
    }
    auto new_expr = std::make_unique<ComparisonExpr> (comp_, std::move(new_left_), std::move(new_right_));
    new_expr->set_name(name());
    return new_expr;
  }

  /**
   * 尝试在没有tuple的情况下获取当前表达式的值
   * 在优化的时候，可能会使用到
   */
  RC try_get_value(Value &value) const override;

  void traverse(const std::function<void(Expression*)>& func, const std::function<bool(Expression*)>& filter) override
  {
    if (filter(this)) {
      if (left_ != nullptr) left_->traverse(func, filter);
      if (right_ != nullptr) right_->traverse(func, filter);
      func(this);
    }
  }


  RC traverse_check(const std::function<RC(Expression*)>& check_func) override
  {
    RC rc = RC::SUCCESS;
    if (left_ != nullptr && RC::SUCCESS != (rc = left_->traverse_check(check_func))) {
      return rc;
    } else if (right_ != nullptr && RC::SUCCESS != (rc = right_->traverse_check(check_func))) {
      return rc;
    } else if (RC::SUCCESS != (rc = check_func(this))) {
      return rc;
    }
    return RC::SUCCESS;
  }

  /**
   * compare the two tuple cells
   * @param value the result of comparison
   */
  RC compare_value(const Value &left, const Value &right, bool &value) const;

private:
  CompOp                      comp_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

/**
 * @brief 联结表达式
 * @ingroup Expression
 * 多个表达式使用同一种关系(AND或OR)来联结
 * 当前miniob仅有AND操作
 */
class ConjunctionExpr : public Expression
{
public:
  enum class Type
  {
    AND,
    OR,
  };

public:
  ConjunctionExpr(Type type, std::vector<std::unique_ptr<Expression>> &children);
  ConjunctionExpr(Type type, Expression* left, Expression* right)
    : conjunction_type_(type)
  {
    children_.emplace_back(left);
    children_.emplace_back(right);
  }
  virtual ~ConjunctionExpr() = default;

  ExprType type() const override { return ExprType::CONJUNCTION; }
  AttrType value_type() const override { return BOOLEANS; }
  RC       get_value(const Tuple &tuple, Value &value) const override;

  Type conjunction_type() const { return conjunction_type_; }

  std::vector<std::unique_ptr<Expression>> &children() { return children_; }

    std::unique_ptr<Expression> unique_ptr_copy() const override
  {
    std::vector<std::unique_ptr<Expression>> new_children;
    for (auto& child : children_) {
      new_children.emplace_back(child->unique_ptr_copy());
    }
    auto new_expr = std::make_unique<ConjunctionExpr>(conjunction_type_, new_children);
    new_expr->set_name(name());
    return new_expr;
  }

  void traverse(const std::function<void(Expression*)>& func, const std::function<bool(Expression*)>& filter) override
  {
    if (filter(this)) {
      for (auto& child : children_) {
        child->traverse(func, filter);
      }
      func(this);
    }
  }

  RC traverse_check(const std::function<RC(Expression*)>& check_func) override
  {
    RC rc = RC::SUCCESS;
    for (auto& child : children_) {
      if (RC::SUCCESS != (rc = child->traverse_check(check_func))) {
        return rc;
      }
    }
    if (RC::SUCCESS != (rc = check_func(this))) {
      return rc;
    }
    return RC::SUCCESS;
  }

private:
  Type                                     conjunction_type_;
  std::vector<std::unique_ptr<Expression>> children_;
};

/**
 * @brief 算术表达式
 * @ingroup Expression
 */
class ArithmeticExpr : public Expression
{
public:
  enum class Type
  {
    ADD,
    SUB,
    MUL,
    DIV,
    NEGATIVE,
  };

public:
  ArithmeticExpr(Type type, Expression *left, Expression *right);
  ArithmeticExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ArithmeticExpr() = default;

  ExprType type() const override { return ExprType::ARITHMETIC; }

  AttrType value_type() const override;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override;

  Type arithmetic_type() const { return arithmetic_type_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  std::unique_ptr<Expression> unique_ptr_copy() const override
  {
    std::unique_ptr<Expression> new_left = left_ ->unique_ptr_copy();
    std::unique_ptr<Expression> new_right;
    if (right_) { // NOTE: not has_rhs
      new_right = right_->unique_ptr_copy();
    }
    auto new_expr = std::make_unique<ArithmeticExpr>(arithmetic_type_, std::move(new_left), std::move(new_right));
    new_expr->set_name(name());
    return new_expr;
  }

  void traverse(const std::function<void(Expression*)>& func, const std::function<bool(Expression*)>& filter) override
  {
    if (filter(this)) {
      left_->traverse(func, filter);
      if (right_ != nullptr) {
        right_->traverse(func, filter);
      }
      func(this);
    }
  }

  RC traverse_check(const std::function<RC(Expression*)>& check_func) override
  {
    RC rc = RC::SUCCESS;
    if (RC::SUCCESS != (rc = left_->traverse_check(check_func))) {
      return rc;
    } else if (right_ != nullptr && RC::SUCCESS != (rc = right_->traverse_check(check_func))) {
      return rc;
    } else if (RC::SUCCESS != (rc = check_func(this))) {
      return rc;
    }
    return RC::SUCCESS;
  }

private:
  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;

private:
  Type                        arithmetic_type_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

/*
 * @brief 聚合函数
 * @ingroup Expression
*/
class AggrFunctionExpr : public Expression
{
public:
  AggrFunctionExpr() = default;
  AggrFunctionExpr(AggregateType aggr_type, std::unique_ptr<Expression> &param);
  AggrFunctionExpr(AggregateType aggr_type, Expression* param);
  virtual ~AggrFunctionExpr() = default;

  std::unique_ptr<Expression> unique_ptr_copy() const override
  {
    std::unique_ptr<Expression> new_param;
    if (param_) {
      new_param = param_->unique_ptr_copy();
    }
    auto new_expr = std::make_unique<AggrFunctionExpr>(aggr_type_, new_param);
    new_expr->set_name(name());
    return new_expr;
  }

  ExprType type() const override { return ExprType::AGGRFUNCTION; }
  AttrType value_type() const override { return get_aggr_attr_type(param_->value_type()); }
  RC check_aggregate_func_type() const;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override;

  AggregateType aggr_type() const { return aggr_type_; }
  AggregateType &aggr_type() { return aggr_type_; }
  AttrType get_aggr_attr_type(AttrType type) const;

  std::unique_ptr<Expression> &param() { return param_; }

  void traverse(const std::function<void (Expression *)> &func, const std::function<bool(Expression *)> &filter) override {
    if (filter(this)) {
      param_->traverse(func, filter);
      func(this);
    }
  }

  RC traverse_check(const std::function<RC (Expression *)> &check_func) override {
    RC rc = RC::SUCCESS;
    if (RC::SUCCESS != (rc = param_->traverse_check(check_func))) {
      return rc;
    }
    if (RC::SUCCESS != (rc = check_func(this))) {
      return rc;
    }
    return RC::SUCCESS;
  }

private:
  AggregateType                            aggr_type_;
  std::unique_ptr<Expression>              param_;
  bool                                     is_first_ = true;
  int                                      index_ = -1;
};

class FuncExpr : public Expression
{
public:
  FuncExpr() = default;
  FuncExpr(FunctionType func_type, std::vector<Expression*>& params);
  FuncExpr(FunctionType func_type, std::vector<std::unique_ptr<Expression>>& params) : func_type_(func_type) {
    for (auto& param : params) {
      params_.emplace_back(std::move(param));
    }
  }
  virtual ~FuncExpr() = default;

  ExprType type() const override { return ExprType::FUNCTION; }
  AttrType value_type() const override { 
    assert(params_.size() != 0);
    return get_func_attr_type(params_[0]->value_type()); 
  }

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override;

  FunctionType func_type() const { return func_type_; }
  AttrType get_func_attr_type(const AttrType type) const;
  RC check_function_param_type() const;

  std::vector<std::unique_ptr<Expression>> &param() { return params_; }

  std::unique_ptr<Expression> unique_ptr_copy() const override
  {
    std::vector<std::unique_ptr<Expression>> new_params;
    for (auto& param : params_) {
      new_params.emplace_back(param->unique_ptr_copy());
    }
    auto new_expr = std::make_unique<FuncExpr>(func_type_, new_params);
    new_expr->set_name(name());
    return new_expr;
  }

  void traverse(const std::function<void (Expression *)> &func, const std::function<bool(Expression *)> &filter) override {
    if (filter(this)) {
      for (auto& param : params_) {
        param->traverse(func, filter);
      } 
      func(this);
    }
  }

  RC traverse_check(const std::function<RC (Expression *)> &check_func) override {
    RC rc = RC::SUCCESS;
    for (auto& param : params_) {
      if (RC::SUCCESS != (rc = param->traverse_check(check_func))) {
        return rc;
      }
    }
    if (RC::SUCCESS != (rc = check_func(this))) {
      return rc;
    }
    return RC::SUCCESS;
  }

private:
  FunctionType                             func_type_;
  std::vector<std::unique_ptr<Expression>> params_;
};