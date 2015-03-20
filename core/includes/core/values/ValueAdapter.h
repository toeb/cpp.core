#pragma once
#include <core/values/IValue.h>

NS_BEGIN(CORE_VALUES_NAMESPACE)

/// assumes THolder is assignable from TValue  and TValue is assignable from THolder
template<typename THolder, typename TValue>
struct ValueAdapter : public IValue {
  THolder _value;
  ValueAdapter(THolder holder) :_value(holder){}
  /*auto getValueType()const -> value_type{
    return provider::typeOf<TValue>();
  }*/
  auto consume(value_holder holder)->void{
    _value = (TValue)holder;
  }
  auto produce() -> value_holder{
    return (TValue)_value;
  }
};



NS_END(CORE_VALUES_NAMESPACE)