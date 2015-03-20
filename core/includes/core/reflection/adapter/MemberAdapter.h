#pragma once
#include <core/core.h>

#include <core/reflection/member/MemberInfo.h>
#include <core/reflection/type/Argument.h>
NS_BEGIN(CORE_NAMESPACE)
  class MemberAdapter{
    reflect_type_declaration(NS(CORE_NAMESPACE)::MemberAdapter);    
    typedef Argument extensible_property(Owner);
  protected:
    MemberAdapter();
    MemberAdapter(Argument owner);
    virtual auto before_set(Owner);
    virtual auto after_set(Owner);

  };
NS_END(CORE_NAMESPACE)
