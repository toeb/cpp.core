#pragma once
#include <core/core.h>
#include <limits>
#include <core/values/values.h>
#include <core/values/IValueVersion.h>

NS_BEGIN(CORE_VALUES_NAMESPACE)


  // represents an uncomparable invalid verison which is not updatable.
  class InvalidValueVersion :public IValueVersion{
    virtual void update(IConnectable & connector)override{}
    virtual int compare(const IValueVersion & other)const override{
      return std::numeric_limits<int>::min();
    }
  };
NS_END(CORE_VALUES_NAMESPACE)
