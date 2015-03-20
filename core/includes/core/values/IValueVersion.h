#pragma once
#include <core/core.h>
#include <core/values/values.h>


NS_BEGIN(CORE_VALUES_NAMESPACE)


  class IConnectable;
  
  // represents the version of a value
  class IValueVersion{
  public:
    // is called to update the version for the specified connector
    virtual void update(IConnectable & connector) = 0;
    virtual int compare(const IValueVersion & other)const = 0;
  };
NS_END(CORE_VALUES_NAMESPACE)
