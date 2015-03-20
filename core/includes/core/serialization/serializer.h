#pragma once
#include <core/core.h>
#include <core/serialization/serialization_config.h>
#include <core/serialization/serialization_context.h>
#include <core/any.h>

NS_BEGIN(CORE_SERIALIZATION_NAMESPACE)


struct serializer{
  
  std::string serialize(any value){
    std::stringstream ss;
    serialization_context context(ss, *this);
    this->serialize(context, value);
    return ss.str();
  }

  virtual void serialize(serialization_context & stream, any value) = 0;
};

NS_END(CORE_SERIALIZATION_NAMESPACE)

