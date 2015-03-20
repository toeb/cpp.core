#pragma once
#include <core/core.h>
#include <core/reflection/member/MemberInfo.h>
NS_BEGIN(CORE_NAMESPACE)
  
  class FieldInfo : public MemberInfo{
  public:
    // gets/ sets the type of the field
    propdef std::shared_ptr<const Type> basic_property(FieldType);
    // returns the value of object's field
    Argument get(void * object)const;
    // sets the value of object's field
    void set(void * object, Argument value)const;
  };

NS_END(CORE_NAMESPACE)
