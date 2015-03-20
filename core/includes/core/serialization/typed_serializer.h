#pragma once
#include <core/core.h>

#include <core/serialization/typed_serializer_base.h>
NS_BEGIN(CORE_SERIALIZATION_NAMESPACE)


// specializable class for serialization
template<typename T, int format>
struct typed_serializer : public serializer{
  static void serialize(serialization_context & context, const T & value){}
};



NS_END(CORE_SERIALIZATION_NAMESPACE)