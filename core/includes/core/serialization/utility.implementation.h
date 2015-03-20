#pragma once
#include <core/core.h>

#include <core/serialization/serialization_config.h>
#include <core/serialization/dummy_serializer.h>
NS_BEGIN(CORE_SERIALIZATION_NAMESPACE)



template<int format, typename T>
void serialize(typename std::ostream & out, const T & value){
  auto f = format;
  dummy_serializer serializer;
  typed_serializer<T, format>::serialize(serialization_context(out, serializer), value);
}



template<int format, typename T >
std::string serialize(const T & value){
  std::stringstream ss;
  serialize<format>(ss, value);
  return ss.str();
}


NS_END(CORE_SERIALIZATION_NAMESPACE)
