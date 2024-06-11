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
// Created by Wangyunlai 2023/6/27
//

#pragma once

#include <cstddef>
#include <string>
#include "common/rc.h"

static constexpr int MAX_TEXT_LENGTH = 65535;

/**
 * @brief 属性的类型
 *
 */
enum AttrType
{
  UNDEFINED,
  CHARS,     ///< 字符串类型
  INTS,      ///< 整数类型(4字节)
  DATES,   ///< 日期类型
  FLOATS,    ///< 浮点数类型(4字节)
  NULLS,   ///< NULL
  BOOLEANS,  ///< boolean类型，当前不是由parser解析出来的，是程序内部使用的
  LONGS,          ///< Int64
  TEXTS,          ///< text
};

/**
 * @brief 表达式使用的聚合函数类型
 */
enum class AggregateType {
  NONE,
  COUNT,
  COUNT_STAR,
  SUM,
  AVG,
  MAX,
  MIN
};

/**
 * @brief 表达式使用的函数类型
 */
enum class FunctionType
{
  LENGTH,
  ROUND,
  DATE_FORMAT,
};


const char *attr_type_to_string(AttrType type);
AttrType    attr_type_from_string(const char *s);

/**
 * @brief 属性的值
 *
 */
class Value
{
public:
  Value() = default;

  Value(AttrType attr_type, char *data, int length = 4) : attr_type_(attr_type) { this->set_data(data, length); }

  explicit Value(int val);
  explicit Value(float val);
  explicit Value(bool val);
  explicit Value(int64_t val);
  explicit Value(const char *s, int len = 0);

  Value(const Value &other)            = default;
  Value &operator=(const Value &other) = default;

  void set_null() { this->attr_type_ = NULLS; }
  bool is_null() const { return this->attr_type_ == NULLS; }
  bool is_string() const { return this->attr_type_ == CHARS; }
  void set_type(AttrType type) { this->attr_type_ = type; }
  void set_data(char *data, int length);
  void set_data(const char *data, int length) { this->set_data(const_cast<char *>(data), length); }
  void set_int(int val);
  void set_float(float val);
  void set_date(int val);
  void set_long(int64_t val);
  void set_boolean(bool val);
  void set_string(const char *s, int len = 0);
  void set_value(const Value &value);
  bool check_date(int y, int m, int d);
  void set_undefined();

  std::string to_string() const;
  std::string function_data(const char *date_format = nullptr); // 只用于function题目中，不查表只计算的情况下，返回数据

  int compare(const Value &other) const;
  int like_type_compare(const Value &other) const;
  void add(const Value &other);
  void div(const Value &other);

  const char *data() const;
  int         length() const { return length_; }

  AttrType attr_type() const { return attr_type_; }

public:
  /**
   * 获取对应的值
   * 如果当前的类型与期望获取的类型不符，就会执行转换操作
   */
  RC typecast(AttrType target_type);
  int         get_int() const;
  int         get_int_round() const; //四舍五入
  float       get_float() const;
  std::string get_string() const;
  bool        get_boolean() const;
  int64_t     get_long() const;
  int         undefined_value(); // date类型数据如果invalid，通过这个接口传回1/0，表示是否有效

private:
  AttrType attr_type_ = UNDEFINED;
  int      length_    = 0;

  union
  {
    int   int_value_;
    float float_value_;
    bool  bool_value_;
    int64_t long_;
  } num_value_;
  std::string str_value_;
};