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

#pragma once

#include <string>

#include "common/rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"

namespace Json {
class Value;
}  // namespace Json

/**
 * @brief 字段元数据
 *
 */
class FieldMeta
{
public:
  FieldMeta();
  FieldMeta(const char *name, AttrType attr_type, int attr_offset, int attr_len, bool visible, bool is_length_func = false, bool is_round_func = false, std::string date_format = "");
  ~FieldMeta() = default;

  RC init(const char *name, AttrType attr_type, int attr_offset, int attr_len, bool visible, bool is_length_func = false, bool is_round_func = false, std::string date_format = "");

public:
  const char *name() const;
  AttrType    type() const;
  AttrType    function_type(AttrType type) const; // 支持function的类型检查
  const char* function_alias(const char* table_name, const char* field_name) const; // 返回字段的别名
  void        function_data(Value &cell) const; // 支持function的数据处理，复位field_meta
  void        reset_function_flag(); // 重置function的标志位
  int         offset() const;
  int         len() const;
  bool        visible() const;

public:
  void desc(std::ostream &os) const;

public:
  void      to_json(Json::Value &json_value) const;
  static RC from_json(const Json::Value &json_value, FieldMeta &field);

public:
  bool      is_length_func;
  bool      is_round_func;
  std::string    date_format;

protected:
  std::string name_;
  AttrType    attr_type_;
  int         attr_offset_;
  int         attr_len_;
  bool        visible_;
};
