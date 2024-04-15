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
// Created by Wangyunlai on 2023/04/24.
//

#include "storage/field/field.h"
#include "common/log/log.h"
#include "sql/parser/value.h"
#include "storage/record/record.h"
#include <cmath>

void Field::set_int(Record &record, int value)
{
  ASSERT(field_->type() == AttrType::INTS, "could not set int value to a non-int field");
  ASSERT(field_->len() == sizeof(value), "invalid field len");

  char *field_data = record.data() + field_->offset();
  memcpy(field_data, &value, sizeof(value));
}

int Field::get_int(const Record &record)
{
  Value value(field_->type(), const_cast<char *>(record.data() + field_->offset()), field_->len());
  return value.get_int();
}

RC Field::check_function_type(const RelAttrSqlNode rel_attr_sql_node) {
  if (rel_attr_sql_node.is_length_func == 1 && this->field_->type() != AttrType::CHARS) {
    return RC::INVALID_ARGUMENT;
  }
  else if (rel_attr_sql_node.is_round_func == 1 && this->field_->type() != AttrType::FLOATS) {
    return RC::INVALID_ARGUMENT;
  }
  else if (rel_attr_sql_node.date_format != "" && this->field_->type() != AttrType::DATES){
    return RC::INVALID_ARGUMENT;
  }
  return RC::SUCCESS;
}

AttrType Field::get_function_type() const{
  if (is_length_func_ == 1) {
    return AttrType::INTS;
  }
  else if (is_round_func_ == 1 && round_num_ <= 0) {
    return AttrType::INTS;
  }
  else if (is_round_func_ == 1 && round_num_ > 0) {
    return AttrType::FLOATS;
  }
  else if (date_format_ != "") {
    return AttrType::CHARS;
  }
  return field_->type();
}

const char* Field::function_alias(const char *table_name, const char *field_name) const{
  char *alias = new char[100];

  // 得到完整的字段名
  char *whole_name = new char[100];
  if (table_name != nullptr) {
    strcpy(whole_name, table_name);
    strcat(whole_name, ".");
    strcat(whole_name, field_name);
  }
  else {
    strcpy(whole_name, field_name);
  }

  // 判断是否是函数
  std::string whole_name_str = whole_name; 
  if (is_length_func_ == 1) {
    std::string tmp = "LENGTH(" + whole_name_str + ")";
    strcpy(alias, tmp.c_str());
  }
  else if (is_round_func_ == 1) {
    std::string tmp = "ROUND(" + whole_name_str + ")";
    strcpy(alias, tmp.c_str());
  }
  else if (date_format_ != "") {
    std::string tmp = "DATE_FORMAT(" + whole_name_str + ", '" + date_format_ + "')";
    strcpy(alias, tmp.c_str());
  }
  else {
    return nullptr;
  }
  return alias;
}

void Field::function_data(Value &cell)
{
  if (is_length_func_ == 1) {
    std::string temp = cell.get_string();
    cell.set_int(temp.size());
    cell.is_length_func_ = 1;
    is_length_func_ = 0;
  } 
  else if (is_round_func_ == 1) {
    float value = cell.get_float();
    // 根据round_num_进行四舍五入, round_num_为0时，四舍五入到整数, round_num_为1时，四舍五入到小数点后一位, 以此类推
    float temp = value * std::pow(10, round_num_);
    temp = std::round(temp);
    temp = temp / std::pow(10, round_num_);
    if (round_num_ <= 0) {
      cell.set_int(temp);
    }
    else {
      cell.set_float(temp);
    }
    cell.is_round_func_ = 1;
    cell.round_num_ = round_num_;
    is_round_func_ = 0;
    round_num_ = 0;
  }
  else if (date_format_ != "") {
    std::string date_format = date_format_;
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
      cell.set_string(buffer);
      cell.is_date_format_func_ = 1;
      date_format_ = "";
    }
  }
  else {
    cell.is_length_func_ = 0;
    cell.is_round_func_ = 0;
    cell.round_num_ = 0;
    cell.is_date_format_func_ = 0;
  }
}

const char *Field::get_data(const Record &record) { return record.data() + field_->offset(); }