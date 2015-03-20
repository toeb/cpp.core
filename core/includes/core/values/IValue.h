#pragma once
#include <core/core.h>
#include <core/values/values.h>


#include <core/values/ISink.h>
#include <core/values/ISource.h>
NS_BEGIN(CORE_VALUES_NAMESPACE)



  // the value is a sink and a source 
  // as it can be assigned a value as well as produce a value
  class IValue :
    public virtual ISink, 
    public virtual ISource{
  public:
    //template<typename T> inline auto operator=(T value)->IValue & { this->consume(value); return *this; }
  };
NS_END(CORE_VALUES_NAMESPACE)
