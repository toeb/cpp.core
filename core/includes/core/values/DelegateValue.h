#pragma once
#include <core/core.h>
#include <core/values/values.h>

#include <core/values/DelegateSource.h>
#include <core/values/DelegateSink.h>

NS_BEGIN(CORE_VALUES_NAMESPACE)

  class DelegateValue : public DelegateSource, public DelegateSink{
  public:
    template<typename T>  DelegateValue(std::function<T()> getter, std::function<void(T)> setter) :DelegateSource(getter), DelegateSink(setter)/*, BaseConnector(type_provider::typeOf<T>())*/{}
    DelegateValue(std::function<value_holder()> getter, std::function<void(value_holder)> setter/*, value_type type*/) : DelegateSource(getter), DelegateSink(setter)/*, BaseConnector(type)*/{}
  };

NS_END(CORE_VALUES_NAMESPACE)
