#pragma once
#include <core/core.h>
#include <core/reflection/member/property/PropertyInfo.h>

NS_BEGIN(CORE_NAMESPACE)
  template<typename ClassType>
  struct TypedPropertyInfo:public PropertyInfo{
    TypedPropertyInfo(const std::string & name, const MethodInfo * getter, const MethodInfo * setter):PropertyInfo(name,getter,setter){
      setOwningType(type_of<ClassType>());     
    }
  };
NS_END(CORE_NAMESPACE)
