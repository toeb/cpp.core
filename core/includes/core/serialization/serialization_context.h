#pragma once
#include <core/core.h>
#include <ostream>
#include <core/serialization/serialization_config.h>
NS_BEGIN(CORE_SERIALIZATION_NAMESPACE)



struct serializer;


struct serialization_context{
  serialization_context(std::ostream & stream, serializer & serializer) :stream(stream), serializer(serializer){}
  std::ostream & stream;
  serializer & serializer;
};

NS_END(CORE_SERIALIZATION_NAMESPACE)

