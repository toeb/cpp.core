#pragma once
#include <core/core.h>
#include <core/serialization/serializer.h>

NS_BEGIN(CORE_SERIALIZATION_NAMESPACE)


template<typename T, int format, typename TDerived >
struct typed_serializer_base :public serializer{
  typedef T value_type;
  typedef TDerived derived_type;
  virtual void serialize(serialization_context& context, any value)override{
    auto cast_value = value.as<value_type>();
    TDerived::serialize(context, cast_value);
  }
};

NS_END(CORE_SERIALIZATION_NAMESPACE)
