#pragma once
#include <core/core.h>
#include <core/reflection/callable/CallableInfo.h>

NS_BEGIN(CORE_NAMESPACE)

  template<typename TCallable,typename TReturnType>
  struct TypedCallableInfoBase : public virtual NS(CORE_NAMESPACE)::CallableInfo{
    typedef TCallable callable_type;
    typedef TReturnType return_type;
    propdef callable_type basic_property(Callable);
    property_reference(Callable);

  protected:
    TypedCallableInfoBase(callable_type callable):
      CallableInfo(),
      _Callable(callable)
    {
      setReturnType(type_of<return_type>());
    }
  };

NS_END(CORE_NAMESPACE)
