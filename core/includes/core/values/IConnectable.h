#pragma once
#include <core/core.h>
#include <core/values/values.h>
#include <core/any.h>
#include <core/values/InvalidValueVersion.h>
#include <core.events.h>

NS_BEGIN(CORE_VALUES_NAMESPACE)


// the basic interface for a connectable value
class IConnectable {
public:
  virtual ~IConnectable(){}
  //typedef type_provider provider;
  //typedef type_provider::type_id value_type;
  typedef any value_holder;

  //virtual value_type getValueType()const = 0;
  //virtual const IValueVersion & getVersion()const{ static InvalidValueVersion _invalid; return _invalid; };

};

NS_END(CORE_VALUES_NAMESPACE)



NS_BEGIN(CORE_VALUES_NAMESPACE)
class IObservableConnectable :public virtual IConnectable{
public:
  typedef NS(CORE_EVENTS_NAMESPACE)::IEvent event;

};


NS_END(CORE_VALUES_NAMESPACE)
