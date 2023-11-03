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
// Created by WangYunlai on 2023/06/28.
//
#include <cmath>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "sql/parser/value.h"
#include "storage/field/field.h"
#include "common/log/log.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"


const char *ATTR_TYPE_NAME[] = {"undefined", "chars", "ints", "floats", "dates", "booleans"};

bool check_date(int y, int m, int d)
{
  static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  bool leap = (y%400==0 || (y%100 && y%4==0));

  //LOG_DEBUG("y:%d m:%d d:%d res:%d", y, m, d, y > 0
    //&& (m > 0)&&(m <= 12)
    //&& (d > 0)&&(d <= ((m==2 && leap)?1:0) + mon[m]));

  return y > 0
    && (m > 0)&&(m <= 12)
    && (d > 0)&&(d <= ((m==2 && leap)?1:0) + mon[m]);
}

const char *attr_type_to_string(AttrType type)
{
  if (type >= UNDEFINED && type <= DATES) {
    return ATTR_TYPE_NAME[type];
  }
  return "unknown";
}
AttrType attr_type_from_string(const char *s)
{
  for (unsigned int i = 0; i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
    if (0 == strcmp(ATTR_TYPE_NAME[i], s)) {
      return (AttrType)i;
    }
  }
  return UNDEFINED;
}

bool Value::null_helper(const char* s, int len) {
  if(len == 0) {
    this->set_null(false);
    return false;
  }

  bool null_data = true;
  for(int i = 0;i < std::min(len, (int)sizeof(num_value_.int_value_)); i++) {
    if(s[i] != null_magic_byte) {
      null_data = false;
      break;
    }
  }
  if(null_data) {
    this->set_null(true);
    this->length_ = std::min(len, (int)sizeof(num_value_.int_value_));
    return true;
  }

  this->set_null(false);
  return false;
}

Value::Value(int val)
{
  if(null_helper(static_cast<const char*>(static_cast<const void*>(&val)), sizeof(val))) return;
  set_int(val);
}

Value::Value(float val)
{
  if(null_helper(static_cast<const char*>(static_cast<const void*>(&val)), sizeof(val))) return;

  set_float(val);
}

Value::Value(bool val)
{
  if(null_helper(static_cast<const char*>(static_cast<const void*>(&val)), sizeof(val))) return;
  set_boolean(val);
}

Value::Value(const char *s, int len /*= 0*/)
{
  if(null_helper(s, len)) return;
  set_string(s, len);
}

void Value::set_data(char *data, int length)
{
  if(null_helper(data, length)) return;
  switch (attr_type_) {
    case CHARS: {
      set_string(data, length);
    } break;
    case INTS: {
      num_value_.int_value_ = *(int *)data;
      length_ = length;
    } break;
    case DATES: {
      num_value_.int_value_ = *(int *) data;
      length_ = length;
    }
    case FLOATS: {
      num_value_.float_value_ = *(float *)data;
      length_ = length;
    } break;
    case BOOLEANS: {
      num_value_.bool_value_ = *(int *)data != 0;
      length_ = length;
    } break;
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
    } break;
  }
}
void Value::set_int(int val)
{
  if(null_helper(static_cast<const char*>(static_cast<const void*>(&val)), sizeof(val))) return;
  attr_type_ = INTS;
  num_value_.int_value_ = val;
  length_ = sizeof(val);
}

void Value::set_float(float val)
{
  if(null_helper(static_cast<const char*>(static_cast<const void*>(&val)), sizeof(val))) return;
  attr_type_ = FLOATS;
  num_value_.float_value_ = val;
  length_ = sizeof(val);
}
void Value::set_boolean(bool val)
{
  if(null_helper(static_cast<const char*>(static_cast<const void*>(&val)), sizeof(val))) return;
  attr_type_ = BOOLEANS;
  num_value_.bool_value_ = val;
  length_ = sizeof(val);
}
void Value::set_string(const char *s, int len /*= 0*/)
{
  if(null_helper(s, len)) return;
  attr_type_ = CHARS;
  if (len > 0) {
    len = strnlen(s, len);
    str_value_.assign(s, len);
  } else {
    str_value_.assign(s);
  }
  length_ = str_value_.length();
}

void Value::set_value(const Value &value)
{
  if (value.is_null()) {
    this->is_null_ = true;
    this->attr_type_ = value.attr_type_;
    this->length_ = value.length();
    return;
  }

  switch (value.attr_type_) {
    case INTS: {
      set_int(value.get_int());
    } break;
    case FLOATS: {
      set_float(value.get_float());
    } break;
    case CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    case DATES: {
      set_date(value.get_date());
    } break;
    case UNDEFINED: {
      ASSERT(false, "got an invalid value type");
    } break;
  }
}

void Value::set_date(const char* s) {
  if(null_helper(s, strlen(s))) return;
  this->attr_type_ = DATES;
  int y,m,d;
  sscanf(s, "%d-%d-%d", &y, &m, &d);//not check return value eq 3, lex guarantee
  //bool b = check_date(y,m,d);
  //if(!b) return -1;
  int dv = y*10000+m*100+d;
  this->num_value_.date_value_ = dv;
  this->length_ = 4; // ADD for length
}

void Value::set_date(int s) {
  if(null_helper(static_cast<const char*>(static_cast<const void*>(&s)), sizeof(s))) return;
  this->attr_type_ = DATES;
  this->num_value_.date_value_ = s;
}

void Value::set_null(bool s) {
  if(s) {
    this->num_value_.int_value_ = null_magic;
  }
  this->is_null_ = s;
}

bool Value::can_interpret(AttrType a) const {
  if(this->attr_type() == a) return true;
  if(this->attr_type() == AttrType::INTS){
    if(a == AttrType::FLOATS)return true;
    if(a == AttrType::CHARS) return true;
    else return false;
  }
  if(this->attr_type() == AttrType::FLOATS){
    if(a == AttrType::INTS) return true;
    if(a == AttrType::CHARS) return true;
    else return false;
  }
  if(this->attr_type() == AttrType::CHARS){
    if(a == AttrType::INTS) return true;
    if(a == AttrType::FLOATS) return true;
    else return false;
  }
  return false;
}
bool Value::can_interpret_and_set(AttrType a, int len){
  if(!can_interpret(a)) return false;
  
  //can interpret to any type if this is null
  if(this->is_null()){
    this->set_type(a);
    this->set_length(len);
    return true;
  }
  //do nothing when type is the same.
  if(this->attr_type() == a) return true;
  
  else if(this->attr_type() == AttrType::INTS){
    //this int -> floats
    if(a == AttrType::FLOATS){
      this->set_float(this->get_int());
      return true;
    }
    //this int -> chars
    else if(a == AttrType::CHARS){
      std::string tmp = this->get_string();
      if(tmp.length() > len){ // 输入的长度大于本身长度
        LOG_WARN("Data to Long");
        return false;
      }
      else{
        this->set_string(tmp.c_str(), len);
        return true;
      }
    }
    else return false;
  }
  else if(this->attr_type() == AttrType::FLOATS){
    //this floats -> int
    if(a == AttrType::INTS){
      this->set_int(std::round(this->get_float()));
      return true;
    }
    //this floats -> chars
    else if(a == AttrType::CHARS){
      std::string tmp = this->get_string();
      if(tmp.length() > len){ // 输入的长度大于本身长度
        LOG_WARN("Data to Long");
        return false;
      }
      else{
        this->set_string(tmp.c_str(), len);
        return true;
      }
    }
    else return false;
  }
  else if(this->attr_type() == AttrType::CHARS){
    //this chars -> int
    if(a == AttrType::INTS){
      std::string s = this->get_string();
      float tmp;
      if(!string2float(s,tmp)) return false;     
      this->set_int(std::round(tmp));
      return true;
    }
    //this chars -> floats
    else if(a == AttrType::FLOATS){
      std::string s = this->get_string();
      float tmp;
      if(!string2float(s,tmp)) return false; 
      this->set_float(tmp);
      return true;
    }
    else return false;
  }
  else return false;
}
bool Value::string2float(const std::string& b, float& result){
  std::string a;
  if(b.empty()) return false;
  if(b.at(0) == '-') a = std::string(b, 1, b.length() - 1);
  else a = b;
  int dot_pos = a.length();
  if(a.length() == 0) return false;
  if(a.length() == 1 && a.at(0) == '.') return false;
  for(int i = 0; i < a.length(); i++){
    if(a.at(i) == '.'){
      if(dot_pos!= a.length()) return false;
      else dot_pos = i;
    }
    else if(a.at(i) <= '9' && a.at(i) >='1') continue;
    else return false;
  }
  result = 0.0;
  for(int i = 0; i < dot_pos; i++){
    result = result * 10 + a.at(i) - '0';
  }
  float tmp = 0;
  for(int i = a.length() - 1; i > dot_pos; i--){
    tmp = tmp/10 + a.at(i) - '0';
  }
  tmp /= 10;
  result += tmp;
  if(b.at(0) == '-') result = -result;
  return true;
}
bool Value::can_interpret_and_set(const Value &v) {
  // true : can an set , false: can not and do nothing.
  if(!can_interpret(v)) return false;
  
  //can interpret to any type if this is null
  if(this->is_null()){
    this->set_type(v.attr_type());
    this->set_length(v.length());
    return true;
  }
  //do nothing when type is the same.
  if(this->attr_type() == v.attr_type()) return true;
  
  //this int -> floats
  else if(this->attr_type() == AttrType::INTS){
    if(v.attr_type() == AttrType::FLOATS){
      this->set_float(this->get_int());
      return true;
    }
    else return false;
  }
  
  //this floats -> int
  else if(this->attr_type() == AttrType::FLOATS){
    if(v.attr_type() == AttrType::INTS){
      this->set_int(this->get_float());
      return true;
    }
    else return false;
  }
  else return false; 
}

bool Value::can_interpret(const Value &v) const {
  if (this->is_null()) {
    return true;
  }

  return this->can_interpret(v.attr_type());
}


void Value::set_length(int len) {
  this->length_ = len;
}


int Value::get_date() const {
  if(this->is_null_) {
    return this->num_value_.int_value_;
  }
  return this->num_value_.date_value_;
}

const char *Value::data() const
{
  if(this->is_null()) {
    return (const char *)&num_value_;
  }
  
  switch (attr_type_) {
    case CHARS: {
      return str_value_.c_str();
    } break;
    default: {
      return (const char *)&num_value_;
    } break;
  }
}

std::string Value::to_string() const
{
  if(this->is_null()) {
    return std::string("NULL");
  }
  std::stringstream os;
  switch (attr_type_) {
    case INTS: {
      os << num_value_.int_value_;
    } break;
    case DATES: {
      int value = this->num_value_.date_value_;
      char buf[16] = {0};
      snprintf(buf,sizeof(buf),"%04d-%02d-%02d",value/10000, (value%10000)/100,value%100); // 注意这里月份和天数，不足两位时需要填充0
      os << buf;
    } break;
    case FLOATS: {
      os << common::double_to_str(num_value_.float_value_);
    } break;
    case BOOLEANS: {
      os << num_value_.bool_value_;
    } break;
    case CHARS: {
      os << str_value_;
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
  return os.str();
}

float parse_float(const char* c, int len) {
  int max_dot_cnt = 1, end_pos = -1, dot_pos = -1;
  for(int i = 0;i < len; i++) {
    if(!std::isdigit(c[i])) {
      if(c[i] == '.' && max_dot_cnt > 0) {
        max_dot_cnt --;
        dot_pos = i;
      } else {
        break;
      }
    }
    end_pos = i;
  }

  float res = 0.0;
  for(int i = 0; i <= end_pos; i++) {
    if(c[i] == '.') continue;
    res = res * 10 + c[i] - '0';
  }

  if(dot_pos == -1 || dot_pos >= end_pos) {
    return res;
  }

  for (int i = 1; i <= end_pos - dot_pos; i++) {
    res /= 10.0;
  }
  return res;
}


int Value::compare(const Value &other) const
{
  if(this->is_null() || other.is_null()) {
    return null_magic;
  }

  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case INTS: {
        return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      case DATES: {
        return common::compare_int((void *)&this->num_value_.date_value_, (void *)&other.num_value_.date_value_);
      } break;
      case FLOATS: {
        return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other.num_value_.float_value_);
      } break;
      case CHARS: {
        return common::compare_string((void *)this->str_value_.c_str(),
            this->str_value_.length(),
            (void *)other.str_value_.c_str(),
            other.str_value_.length());
      } break;
      case BOOLEANS: {
        return common::compare_int((void *)&this->num_value_.bool_value_, (void *)&other.num_value_.bool_value_);
      } break;
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = this->num_value_.int_value_;
    return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = other.num_value_.int_value_;
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == CHARS) {
  
    float d = parse_float(other.str_value_.c_str(), other.str_value_.length());
    return common::compare_float((void*)&this->num_value_.float_value_, (void *)&d);
  
  } else if (this->attr_type_ == CHARS && other.attr_type_ == FLOATS) {

    float d = parse_float(this->str_value_.c_str(), this->str_value_.length()); 
    return common::compare_float((void*)&d, (void*)&other.num_value_.float_value_);
  
  } else if (this->attr_type_ == INTS && other.attr_type_ == CHARS) {
  
    float d = parse_float(other.str_value_.c_str(), other.str_value_.length());
    float i = this->num_value_.int_value_;
    return common::compare_float((void*)&i, (void *)&d);
  
  } else if (this->attr_type_ == CHARS && other.attr_type_ == INTS) {

    float d = parse_float(this->str_value_.c_str(), this->str_value_.length());
    float i = other.num_value_.int_value_;
    return common::compare_float((void*)&d, (void*)&i); 
  
  }
  LOG_WARN("not supported");
  return -1;  // TODO return rc?
}

bool allStars(const char* str, int left, int right) {
    for (int i = left; i < right; ++i) {
        if (str[i] != '%') {
            return false;
        }
    }
    return true;
}
bool charMatch(char u, char v) { return u == v || v == '_'; };

bool isMatch(const char* s, const char* p) {
    int len_s = strlen(s), len_p = strlen(p);
    while (len_s && len_p && p[len_p - 1] != '%') {
        if (charMatch(s[len_s - 1], p[len_p - 1])) {
            len_s--;
            len_p--;
        } else {
            return false;
        }
    }
    if (len_p == 0) {
        return len_s == 0;
    }

    int sIndex = 0, pIndex = 0;
    int sRecord = -1, pRecord = -1;
    while (sIndex < len_s && pIndex < len_p) {
        if (p[pIndex] == '%') {
            ++pIndex;
            sRecord = sIndex;
            pRecord = pIndex;
        } else if (charMatch(s[sIndex], p[pIndex])) {
            ++sIndex;
            ++pIndex;
        } else if (sRecord != -1 && sRecord + 1 < len_s) {
            ++sRecord;
            sIndex = sRecord;
            pIndex = pRecord;
        } else {
            return false;
        }
    }
    return allStars(p, pIndex, len_p);
}

int Value::like(const Value& v) const {
  if(this->is_null() || v.is_null()) {
    return null_magic;
  }

  if (this->attr_type_ != CHARS) {
    LOG_WARN("not supported");
    return -1;
  }

  if (this->attr_type_ == v.attr_type_) {
    //LOG_DEBUG("%s %s %d", *this->data(), *v.data(), isMatch(this->data(), v.data()));
    return isMatch(this->data(), v.data());
  }
  return -1;
}

int Value::get_int() const
{
  if(this->is_null()) {
    return num_value_.int_value_;
  }

  switch (attr_type_) {
    case CHARS: {
      try {
        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case INTS: {
      return num_value_.int_value_;
    }
    case DATES: {
      return num_value_.date_value_;
    }
    case FLOATS: {
      return (int)(num_value_.float_value_);
    }
    case BOOLEANS: {
      return (int)(num_value_.bool_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const
{
  if(this->is_null()) {
    return *static_cast<const float*> (static_cast<const void*> (&num_value_.int_value_));
  }

  switch (attr_type_) {
    case CHARS: {
      try {
        return std::stof(str_value_);
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0.0;
      }
    } break;
    case INTS: {
      return float(num_value_.int_value_);
    } break;
    case DATES: {
      return float(num_value_.date_value_);
    } break;
    case FLOATS: {
      return num_value_.float_value_;
    } break;
    case BOOLEANS: {
      return float(num_value_.bool_value_);
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

std::string Value::get_string() const
{
  //TODO how to fix get string with null
  return this->to_string();
}

int Value::get_boolean() const
{
  if(this->is_null()) {
    return false;
  }

  switch (attr_type_) {
    case CHARS: {
      try {
        float val = std::stof(str_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(str_value_);
        if (int_val != 0) {
          return true;
        }

        return !str_value_.empty();
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return !str_value_.empty();
      }
    } break;
    case INTS: {
      return num_value_.int_value_ != 0;
    } break;
    case DATES: {
      return num_value_.date_value_ != 0;
    } break;
    case FLOATS: {
      float val = num_value_.float_value_;
      return val >= EPSILON || val <= -EPSILON;
    } break;
    case BOOLEANS: {
      return num_value_.bool_value_;
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false;
    }
  }
  return false;
}

bool Value::is_null() const {
  return this->is_null_;
}

bool Value::validate() const {
  switch (this->attr_type_)
  {
  case DATES:{
    return check_date(this->num_value_.date_value_ / 10000,
      (this->num_value_.date_value_ % 10000) / 100,
      this->num_value_.date_value_ % 100);
  } break;
  default:
    return true;
  }
  return true;
}
