#pragma once
#include <core/core.h>
#include <core/serialization/serialization_config.h>
#include <core/serialization/utility.h>
#include <core/any.h>
#include <core/dynamic/DynamicObject.h>
NS_BEGIN(CORE_SERIALIZATION_NAMESPACE)

composite_serializer & json_serializer();


std::string json(::NS(CORE_NAMESPACE)::any value);
std::string json(::NS(CORE_NAMESPACE)::dynamic::DynamicObject obj);



custom_serializer_declaration(JsonFormat, int);
custom_serializer_declaration(JsonFormat, double);
custom_serializer_declaration(JsonFormat, bool);
custom_serializer_declaration(JsonFormat, std::nullptr_t);
custom_serializer_declaration(JsonFormat, const char *);
custom_serializer_declaration(JsonFormat, std::string);
custom_serializer_declaration(JsonFormat, ::NS(CORE_NAMESPACE)::dynamic::DynamicObject);
template<typename T> custom_template_serializer_declaration(JsonFormat, std::vector<T>);

custom_serializer_declaration(JsonFormat, std::vector<any>);



/// implementation
template<typename T> custom_serializer_definition(JsonFormat, std::vector<T>){
  context.stream << "[";
  bool first = true;
  for (auto it : value){
    if (first)first = false;
    else  context.stream << ",";
    typed_serializer<T, JsonFormat>::serialize(context, it);
  }
  context.stream << "]";
}



template<typename T> std::string json(const T & val){
  return json((any)val);
}

NS_END(CORE_SERIALIZATION_NAMESPACE)
