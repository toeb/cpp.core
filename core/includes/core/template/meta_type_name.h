#pragma once
#include <core/core.h>



NS_BEGIN(CORE_NAMESPACE)

  template<typename T>
  struct meta_type_name{
    static const std::string & value(){
      static std::string name = T::getTypeName();
      return name;
    }
  };
NS_END(CORE_NAMESPACE)
