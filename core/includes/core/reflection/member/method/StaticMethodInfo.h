#pragma once
#include <core/core.h>
#include <core/reflection/callable/CallableInfo.h>
NS_BEGIN(CORE_NAMESPACE)

  class StaticMethodInfo : public CallableInfo{
  public:
    virtual const Type* getType()const override;
    static bool initializeType();
    

  };

  template<typename TMethod>
  class TypedStaticMethodInfo:public StaticMethodInfo{
  public:

  };

NS_END(CORE_NAMESPACE)
