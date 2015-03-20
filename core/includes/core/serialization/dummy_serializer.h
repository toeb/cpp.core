#pragma once
#include <core/core.h>

#include <core/serialization/serialization_config.h>
#include <core/serialization/serializer.h>

NS_BEGIN(CORE_SERIALIZATION_NAMESPACE)


struct dummy_serializer : public serializer{
  virtual void serialize(serialization_context & stream, any value) override{
    
  }

};

NS_END(CORE_SERIALIZATION_NAMESPACE)
