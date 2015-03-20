#pragma once 

#include <core/values/ValueAdapter.h>
#include <memory>
NS_BEGIN(CORE_VALUES_NAMESPACE)

/// creates a shared ptr of a IValue implementation (MemoryValue)
template<typename T>
std::shared_ptr<IValue> make_value(){
  return std::make_shared<MemoryValue>(core::values::MemoryValue::provider::typeOf<T>());
}
/// creates a shared ptr of a IValue implementation (MemoryValue)
/// sets the initial value to initial
template<typename T>
std::shared_ptr<IValue> make_value(T && initial){
  auto res = std::make_shared<MemoryValue>();
  res->consume(initial);
  return res;
}


/// creates a value adapter
template<typename TValue, typename THolder>
std::shared_ptr<ValueAdapter<THolder, TValue>> value_adapter(THolder value){
  return std::make_shared<ValueAdapter<THolder, TValue>>(value);
}




NS_END(CORE_VALUES_NAMESPACE)