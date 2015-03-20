#pragma once
#include <core/core.h>

#include <core/reflection/callable/ArgumentInfo.h>
NS_BEGIN(CORE_NAMESPACE)
  template<typename ArgumentType, unsigned int ArgumentIndex>
  class TypedArgumentInfo : public ArgumentInfo{
  public:
    TypedArgumentInfo();
  };
NS_END(CORE_NAMESPACE)

NS_BEGIN(CORE_NAMESPACE)
  template<typename ArgumentType, unsigned int ArgumentIndex>
  TypedArgumentInfo<ArgumentType,ArgumentIndex>::TypedArgumentInfo(){
    setIndex(ArgumentIndex);
    setArgumentType(TypeInfo<ArgumentType>::instance());
    setName(DS_INLINE_STRING("a"<<ArgumentIndex));
  }
NS_END(CORE_NAMESPACE)
