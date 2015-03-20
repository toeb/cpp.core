#pragma once
#include <core/core.h>


NS_BEGIN(CORE_NAMESPACE)
  
  template<typename T>
  struct meta_type_tostring{
    static void toString(const void * object, std::ostream& stream){
      stream <<static_cast<const T*>(object);
    }
  };

NS_END(CORE_NAMESPACE)
