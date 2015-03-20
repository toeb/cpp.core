#pragma once
#include <core.math/core.math.h>
NS_BEGIN(CORE_MATH_NAMESPACE)
  namespace scalar{
    template<typename T>
    struct Zero{
      static inline void operation(T & a){
        a = 0.0;
      }
    };
  }
NS_END(CORE_MATH_NAMESPACE)
