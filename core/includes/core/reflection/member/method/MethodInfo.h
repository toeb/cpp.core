#pragma once
#include <core/core.h>
#include <core/reflection/member/MemberInfo.h>
#include <core/reflection/type/Argument.h>
#include <core/reflection/callable/ArgumentInfo.h>
#include <core/reflection/callable/CallableInfo.h>
NS_BEGIN(CORE_NAMESPACE)


  class MethodInfo : public MemberInfo, public virtual CallableInfo{
  public:
    virtual const Type  * getType()const;
    static bool initializeType();

    propdef std::string basic_property(PureName);
  };
NS_END(CORE_NAMESPACE)




