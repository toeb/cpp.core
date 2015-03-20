#pragma once
#include <core.math/core.math.h>
NS_BEGIN(CORE_MATH_NAMESPACE)
  namespace scalar{
    template<typename T>
    struct Signum {
      static inline void operation(T & b, const T & a){
        if (a >= 0.0){ b = 1.0; return; }
        if (a < 0.0){ b = -1.0; return; }
      }
    };
  }
NS_END(CORE_MATH_NAMESPACE)
