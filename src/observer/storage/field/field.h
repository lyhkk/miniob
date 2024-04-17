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

#include "storage/field/field_meta.h"
#include "storage/table/table.h"

/**
 * @brief 字段
 *
 */
class Field
{
public:
  Field() = default;
  Field(const Table *table, const FieldMeta *field, int is_length_func = 0, int is_round_func = 0, int round_num = 0, std::string date_format = "",
      AggregateType aggregate_type = AggregateType::NONE) {
    this->table_ = table;
    this->field_ = field;
    this->is_length_func_ = is_length_func;
    this->is_round_func_ = is_round_func;
    this->round_num_ = round_num;
    this->date_format_ = date_format;
    this->aggregate_type_ = aggregate_type;
  }
  Field(const Field &) = default;

  const Table     *table() const { return table_; }
  const FieldMeta *meta() const { return field_; }

  AttrType attr_type() const { return field_->type(); }

  const char *table_name() const { return table_->name(); }
  const char *field_name() const { return field_->name(); }

  void set_table(const Table *table) { this->table_ = table; }
  void set_field(const FieldMeta *field) { this->field_ = field; }

public:
  // for "function"
  RC          check_function_type(const RelAttrSqlNode rel_attr_sql_node); // 检验这个字段是否是可以进行对应函数运算的type eg: LENGTH(type), type = AttrType::CHARS
  AttrType    get_function_type() const; // 获取函数运算的type eg: LENGTH(type), 返回AttrType::INTS
  const char* function_alias(const char *table_name, const char *field_name) const;
  void        function_data(Value &cell);

  // for "aggregate function"
  RC          check_aggregate_func_type(const RelAttrSqlNode rel_attr_sql_node);

  void set_int(Record &record, int value);
  int  get_int(const Record &record);

  const char *get_data(const Record &record);

public:
  int      is_length_func_;
  int      is_round_func_;
  int      round_num_;
  std::string    date_format_;
  AggregateType aggregate_type_;

private:
  const Table     *table_ = nullptr;
  const FieldMeta *field_ = nullptr;
};
