#pragma once
#include <core/core.h>
#include <core/values/values.h>


#include <core/values/ObservableSource.h>
#include <core/values/BaseConnector.h>

#include <functional>

NS_BEGIN(CORE_VALUES_NAMESPACE)


  class DelegateSource : public ObservableSource, public virtual BaseConnector{
  private:
    std::function<value_holder()> _producer;
  public:
    DelegateSource(std::function<value_holder()> producer/*, value_type type*/) :_producer(producer)/*, BaseConnector(type)*/{
    }
    template<typename T>
    DelegateSource(std::function<T()> producer) : _producer([producer](){return(value_holder)producer(); })/*, BaseConnector(type_provider::typeOf<T>())*/{}
    virtual any produceValue(){
      return _producer();
    }
  };
NS_END(CORE_VALUES_NAMESPACE)
