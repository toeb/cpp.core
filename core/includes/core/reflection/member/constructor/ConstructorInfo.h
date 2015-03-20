#pragma once
#include <core/core.h>

#include <core/reflection/member/MemberInfo.h>
#include <core/reflection/callable/CallableInfo.h>
NS_BEGIN(CORE_NAMESPACE)

  class ConstructorInfo : public MemberInfo, public Callable{
  public:
    ConstructorInfo();
    bool isValid()const;
    typedef std::shared_ptr<const CallableInfo> callable_ptr;
    Argument callImplementation(const ArgumentList & args)override;
    Argument callImplementation(const ArgumentList & args)const override;
    propdef callable_ptr basic_property(MakeShared);
    property_reference(MakeShared);
    propdef callable_ptr basic_property(MakeRaw);
    property_reference(MakeRaw);
    propdef callable_ptr basic_property(MakePlacement);
    property_reference(MakePlacement);
    const std::vector<std::shared_ptr<ArgumentInfo>> & Arguments()const;
  };
NS_END(CORE_NAMESPACE)
