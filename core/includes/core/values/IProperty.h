#pragma once
#include <core/core.h>
#include <core/values/values.h>
#include <core/values/IValue.h>
NS_BEGIN(CORE_VALUES_NAMESPACE)

  /// a property is a named value
  class IProperty : public IValue{
  public:
    typedef std::string key_type;
    virtual const key_type name()const = 0;
    virtual void setName(const key_type & name) = 0;
  
    virtual const key_type fullName()const = 0;
    virtual void setFullName(const key_type & name) = 0;

    virtual IValue & value() = 0;
    virtual const IValue & value()const = 0;
    template<typename T>
    auto operator=(T val)->IProperty &{
      value() = val;
      return *this;
    }
    template<typename T> T as(){
      return produce().as<T>();
    }
    operator any(){
      return value().produce();
    }
  };

NS_END(CORE_VALUES_NAMESPACE)
