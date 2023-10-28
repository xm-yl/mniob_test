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
// Created by Wangyunlai.wyl on 2021/5/18.
//

#include "storage/index/index_meta.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");
const static Json::StaticString IS_UNIQUE("is_unique");
static void string_split(std::string str, const char split, std::vector<std::string>& res){
  std::istringstream iss(str);
  std::string token;
  while(getline(iss, token, split)){
    res.push_back(token);
  }
}
//TODO ready to delete this function.
// RC IndexMeta::init(const char *name, const FieldMeta &field)
// {
//   if (common::is_blank(name)) {
//     LOG_ERROR("Failed to init index, name is empty.");
//     return RC::INVALID_ARGUMENT;
//   }

//   name_ = name;
//   field_ = field.name();
//   return RC::SUCCESS;
// }
RC IndexMeta::init_multi_index(const char* name, const std::vector<const FieldMeta*> & field_metas, bool is_unique){
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }
  name_ = name;
  for(const FieldMeta* field_meta:field_metas){
    FieldMeta new_field_meta = *field_meta;
    field_metas_.push_back(new_field_meta);
    fields_.push_back(new_field_meta.name());
    fields_type_.push_back(new_field_meta.type());
  }
  is_unique_ = is_unique;
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME] = name_;
  std::string field_;
  //记录多个field，在一个的时候和扩展前情况相同，更多的field_name用，隔开
  for(int i = 0; i < field_metas_.size(); i++){
    field_ += field_metas_.at(i).name();
    if(i != field_metas_.size() - 1){
      field_ += ",";
    }
  }
  json_value[FIELD_FIELD_NAME] = field_;
  if(is_unique_) json_value[IS_UNIQUE] = true;
  else json_value[IS_UNIQUE] = false;
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  const Json::Value &is_unique = json_value[IS_UNIQUE];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!field_value.isString()) {
    LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
        name_value.asCString(),
        field_value.toStyledString().c_str());
    return RC::INTERNAL;
  }
  std::string field_names = field_value.asCString();
  std::vector<std::string> field_name_list; 
  string_split(field_names, ',', field_name_list);
  std::vector<const FieldMeta*> field_metas;
  for(int i = 0; i < field_name_list.size(); i++){
    const FieldMeta *field = table.field(field_name_list[i].c_str());
    if (nullptr == field) {
    LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value.asCString());
    return RC::SCHEMA_FIELD_MISSING;
    }
    field_metas.push_back(field);
  }
  bool unique = is_unique.asBool();
  return index.init_multi_index(name_value.asCString(),field_metas,unique);
  //return index.init(name_value.asCString(), *field);
}

const char *IndexMeta::name() const
{
  return name_.c_str();
}

void IndexMeta::desc(std::ostream &os) const
{
  os << "index name=" << name_ ;
  os << ", fields=";
  for(int i = 0; i < field_metas_.size(); i++){
    os << field_metas_[i].name();
    if(i!= field_metas_.size()-1){
      os << ", ";
    }
  }
}

std::vector<FieldMeta> IndexMeta::field_metas() const {
  return  field_metas_;
}

std::vector<AttrType> IndexMeta::fields_type() const {
  return fields_type_;
}

bool IndexMeta::is_unique() const {
  return is_unique_;
}