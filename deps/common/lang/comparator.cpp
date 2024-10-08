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
// Created by wangyunlai on 2021/6/11.
//

#include "common/defs.h"
#include <algorithm>
#include <string.h>

namespace common {

int compare_int(void *arg1, void *arg2)
{
  int v1 = *(int *)arg1;
  int v2 = *(int *)arg2;
  if (v1 > v2) {
    return 1;
  } else if (v1 < v2) {
    return -1;
  } else {
    return 0;
  }
}

int compare_float(void *arg1, void *arg2)
{
  float v1  = *(float *)arg1;
  float v2  = *(float *)arg2;
  float cmp = v1 - v2;
  if (cmp > EPSILON) {
    return 1;
  }
  if (cmp < -EPSILON) {
    return -1;
  }
  return 0;
}

int compare_string(void *arg1, int arg1_max_length, void *arg2, int arg2_max_length)
{
  const char *s1     = (const char *)arg1;
  const char *s2     = (const char *)arg2;
  int         maxlen = std::min(arg1_max_length, arg2_max_length);
  int         result = strncmp(s1, s2, maxlen);
  if (0 != result) {
    return result;
  }

  if (arg1_max_length > maxlen) {
    return s1[maxlen] - 0;
  }

  if (arg2_max_length > maxlen) {
    return 0 - s2[maxlen];
  }
  return 0;
}

int like_compare_string(void *arg1, int arg1_max_length, void *arg2, int arg2_max_length)
{
  const char *s1     = (const char *)arg1;
  const char *s2     = (const char *)arg2;
  int         maxlen = arg1_max_length;
  int         i      = 0; 
  int         j      = 0;
  while (i < maxlen) {
    if (s1[i] == s2[j]) {
      i++, j++;
      continue;
    }
    if ('%' == s2[j]) {
      j++;
      if (j == arg2_max_length) {
        return 0;
      }
      while (i < maxlen) {
        while(s1[i] != s2[j] && i < maxlen)
          i++;
        if (i == maxlen) {
          return 1;
        }
        if (0 == like_compare_string((void*)(s1 + i), arg1_max_length - i, (void*)(s2 + j), arg2_max_length - j)) {
          return 0;
        }
        else {
          i++;
        }
      }
      if (i == maxlen) {
        return 1;
      }
      return 1; // should not reach here
    }
    if ('_' == s2[j]) {
      i++, j++;
      continue;
    }
    break;
  }
  if ( i == maxlen ) {
    if (j == arg2_max_length) {
      return 0;
    }
    while (j < arg2_max_length) {
      if (s2[j] != '%') {
        return 1;
      }
      j++;
    }
    return 0;
  }
  return 1;
}

}  // namespace common
