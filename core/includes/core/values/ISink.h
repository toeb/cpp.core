#pragma once
#include <core/core.h>
#include <core/values/values.h>

#include <core/values/IConnector.h>
NS_BEGIN(CORE_VALUES_NAMESPACE)



  // the sink is a connector which can consume data
  class ISink : public virtual IConnector{
  public:
    /// consumes the specified value
    virtual void consume(value_holder value) = 0;

    //template<typename T>    ISink & operator=(T rhs){      consume(rhs);      return *this;    }

  };

NS_END(CORE_VALUES_NAMESPACE)
