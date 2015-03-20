#pragma once
#include <core/core.h>
#include <core/values/values.h>

#include <core/values/ObservableSink.h>
#include <core/values/BaseConnector.h>
#include <functional>
NS_BEGIN(CORE_VALUES_NAMESPACE)


  //todo: switch to functors instead of functions
  class DelegateSink : public ObservableSink, public virtual BaseConnector{
  private:
    std::function<void(value_holder)> _consumer;
  public:
    template<typename T> DelegateSink(std::function<void(T)> consumer) : _consumer([consumer](value_holder arg){consumer(arg); })/*, BaseConnector(type_provider::typeOf<T>())*/ {}
    DelegateSink(std::function<void(value_holder)> consumer/*, value_type type*/) :_consumer(consumer)/*, BaseConnector(type)*/{
    }
    virtual void consumeValue(value_holder arg)override{
      _consumer(arg);
    }
  };
NS_END(CORE_VALUES_NAMESPACE)
