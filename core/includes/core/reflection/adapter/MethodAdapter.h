#pragma once
#include <core/core.h>

#include <core/Object.h>
#include <core/reflection/member/method/MethodInfo.h>
#include <core/reflection/adapter/MemberAdapter.h>
#include <core/reflection/callable/Callable.h>

NS_BEGIN(CORE_NAMESPACE)
  class MethodAdapter : public Callable, public MemberAdapter{
    //reflect_type(NS(CORE_NAMESPACE)::MethodAdapter);
    //reflect_superclasses(Callable,MemberAdapter);

    typedef const MethodInfo * basic_property(MethodInfo);
  public:
    
    MethodAdapter();
    MethodAdapter(Argument object, const std::string & name);
    MethodAdapter(Argument object, const MethodInfo * method);    
  public:
    Argument callImplementation(const ArgumentList & args)override;
    bool isValid()const override;
  };
NS_END(CORE_NAMESPACE)
