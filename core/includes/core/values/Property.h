#pragma once
#include <core/core.h>

#include <core/events/IEvent.h>
#include <core/events/Event.h>

#include <core/reflection/type/Type.h>

#include <core/values/values.h>
#include <core/values/IProperty.h>
#include <core/values/MemoryValue.h>
NS_BEGIN(CORE_VALUES_NAMESPACE)


  class Property : public virtual IProperty, public virtual IObservableValue{//, public IValue{
  public:
    event & OnBeforeProduced()override{ return _value.OnBeforeProduced(); }
    event & OnAfterProduced()override{ return _value.OnAfterProduced(); }
    event & OnAfterConsumed()override{ return _value.OnAfterConsumed(); }
    event & OnBeforeConsumed()override{ return _value.OnBeforeConsumed(); }
    event & OnValueChanged()override{ return _value.OnValueChanged(); }


    Property(key_type name) :_value(), _name(name){}

    void setName(const std::string & name){
      _name = name;
    }

    const key_type name()const override{
      return _name;
    }

    void setFullName(const std::string & name){
      _fullName = name;
    }

    const key_type fullName()const override{
      return _fullName;
    }
    IValue & value() override{
      return _value;
    }
    const IValue & value()const override{
      return _value;
    }

    value_holder produce(){
      return _value.produce();
    }

    void consume(value_holder arg){
      _value.consume(arg);
    }

    template<typename T>
    Property & operator=(T rhs){
      _value.consume(rhs);
      return *this;
    }


  private:
    MemoryValue _value;
    key_type _name;
    key_type _fullName;
  };



  inline std::shared_ptr<Property> make_property(IProperty::key_type name){
    auto ptr = std::make_shared<Property>(name);
    return ptr;
  }
  template<typename T>
  std::shared_ptr<Property> make_property(IProperty::key_type name, T initialValue){
    auto prop = make_property(name);
    prop->consume(initialValue);
    return prop;
  }


NS_END(CORE_VALUES_NAMESPACE)

