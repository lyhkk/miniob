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
// Created by Meiyi & Wangyunlai on 2021/5/12.
//

#include "storage/field/field_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"

#include "json/json.h"
#include <ctime>
#include <string>

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_TYPE("type");
const static Json::StaticString FIELD_OFFSET("offset");
const static Json::StaticString FIELD_LEN("len");
const static Json::StaticString FIELD_VISIBLE("visible");

FieldMeta::FieldMeta() : attr_type_(AttrType::UNDEFINED), attr_offset_(-1), attr_len_(0), visible_(false) {}

FieldMeta::FieldMeta(const char *name, AttrType attr_type, int attr_offset, int attr_len, bool visible, bool is_length_func, bool is_round_func, std::string date_format)
{
  [[maybe_unused]] RC rc = this->init(name, attr_type, attr_offset, attr_len, visible, is_length_func, is_round_func, date_format);
  ASSERT(rc == RC::SUCCESS, "failed to init field meta. rc=%s", strrc(rc));
}

RC FieldMeta::init(const char *name, AttrType attr_type, int attr_offset, int attr_len, bool visible, bool is_length_func, bool is_round_func, std::string date_format)
{
  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }

  if (AttrType::UNDEFINED == attr_type || attr_offset < 0 || attr_len <= 0) {
    LOG_WARN("Invalid argument. name=%s, attr_type=%d, attr_offset=%d, attr_len=%d",
              name, attr_type, attr_offset, attr_len);
    return RC::INVALID_ARGUMENT;
  }

  name_        = name;
  attr_type_   = attr_type;
  attr_len_    = attr_len;
  attr_offset_ = attr_offset;
  visible_     = visible;
  is_length_func = false;
  is_round_func = false;
  date_format = "";

  LOG_INFO("Init a field with name=%s", name);
  return RC::SUCCESS;
}

const char *FieldMeta::name() const { return name_.c_str(); }

AttrType FieldMeta::type() const { return attr_type_; }

AttrType FieldMeta::function_type(AttrType type) const {
  if (this->is_length_func) {
    return AttrType::INTS;
  }
  else if (this->is_round_func) {
    return AttrType::INTS;
  }
  else if (this->date_format != "") {
    return AttrType::CHARS;
  }
  else {
    return type;
  }
}

const char* FieldMeta::function_alias(const char *table_name, const char *field_name) const{
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
  if (this->is_length_func == 1) {
    std::string tmp = "LENGTH(" + whole_name_str + ")";
    strcpy(alias, tmp.c_str());
  }
  else if (this->is_round_func == 1) {
    std::string tmp = "ROUND(" + whole_name_str + ")";
    strcpy(alias, tmp.c_str());
  }
  else if (this->date_format != "") {
    std::string tmp = "DATE_FORMAT(" + whole_name_str + ", '" + this->date_format + "')";
    strcpy(alias, tmp.c_str());
  }
  else {
    return nullptr;
  }
  return alias;
}

void FieldMeta::function_data(Value &cell) const
{
  if (this->is_length_func == 1) {
    std::string temp = cell.get_string();
    cell.set_int(temp.length());
    cell.flag_for_func_.is_length_func_ = 1;
    // this->is_length_func = 0;
  } 
  else if (this->is_round_func == 1) {
    float value = cell.get_float();
    int temp = (int)value;
    if (value - (int)value >= 0.5) {
      temp = temp + 1;
    }
    cell.set_int(temp);
    cell.flag_for_func_.is_round_func_ = 1;
    // this->is_round_func = 0;
  }
  else if (this->date_format != "") {
    std::string date_format = this->date_format;
    int date = cell.get_int();
    std::string date_str = std::to_string(date);
    std::stringstream ss(date_str);
    tm tm = {};
    char* formatted_date = strptime(date_str.c_str(), "%Y%m%d", &tm);
    if (formatted_date == NULL) {
      LOG_ERROR("Failed to parse date. date=%s", date_str.c_str()); // 理论上不会出现这种情况，为了完整性
    }
    else {
      char buffer[80];
      strftime(buffer, 80, date_format.c_str(), &tm);
      cell.set_string(buffer);
      cell.flag_for_func_.is_date_format_func_ = 1;
      // this->date_format = "";
    }
  }
  else {
    cell.flag_for_func_.is_length_func_ = 0;
    cell.flag_for_func_.is_round_func_ = 0;
    cell.flag_for_func_.is_date_format_func_ = 0;
  }
}

void FieldMeta::reset_function_flag()
{
  this->is_length_func = 0;
  this->is_round_func = 0;
  this->date_format = "";
}

int FieldMeta::offset() const { return attr_offset_; }

int FieldMeta::len() const { return attr_len_; }

bool FieldMeta::visible() const { return visible_; }

void FieldMeta::desc(std::ostream &os) const
{
  os << "field name=" << name_ << ", type=" << attr_type_to_string(attr_type_) << ", len=" << attr_len_
    << ", visible=" << (visible_ ? "yes" : "no");
}

void FieldMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME]    = name_;
  json_value[FIELD_TYPE]    = attr_type_to_string(attr_type_);
  json_value[FIELD_OFFSET]  = attr_offset_;
  json_value[FIELD_LEN]     = attr_len_;
  json_value[FIELD_VISIBLE] = visible_;
}

RC FieldMeta::from_json(const Json::Value &json_value, FieldMeta &field)
{
  if (!json_value.isObject()) {
    LOG_ERROR("Failed to deserialize field. json is not an object. json value=%s", json_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  const Json::Value &name_value    = json_value[FIELD_NAME];
  const Json::Value &type_value    = json_value[FIELD_TYPE];
  const Json::Value &offset_value  = json_value[FIELD_OFFSET];
  const Json::Value &len_value     = json_value[FIELD_LEN];
  const Json::Value &visible_value = json_value[FIELD_VISIBLE];

  if (!name_value.isString()) {
    LOG_ERROR("Field name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }
  if (!type_value.isString()) {
    LOG_ERROR("Field type is not a string. json value=%s", type_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!offset_value.isInt()) {
    LOG_ERROR("Offset is not an integer. json value=%s", offset_value.toStyledString().c_str());
    return RC::INTERNAL;
  }
  if (!len_value.isInt()) {
    LOG_ERROR("Len is not an integer. json value=%s", len_value.toStyledString().c_str());
    return RC::INTERNAL;
  }
  if (!visible_value.isBool()) {
    LOG_ERROR("Visible field is not a bool value. json value=%s", visible_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  AttrType type = attr_type_from_string(type_value.asCString());
  if (UNDEFINED == type) {
    LOG_ERROR("Got invalid field type. type=%d", type);
    return RC::INTERNAL;
  }

  const char *name    = name_value.asCString();
  int         offset  = offset_value.asInt();
  int         len     = len_value.asInt();
  bool        visible = visible_value.asBool();
  return field.init(name, type, offset, len, visible);
}
