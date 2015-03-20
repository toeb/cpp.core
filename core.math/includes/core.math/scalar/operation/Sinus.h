#pragma once
#include <core.math/core.math.h>
#include <cmath>
NS_BEGIN(CORE_MATH_NAMESPACE)
  namespace scalar{
    template<typename T>
    struct Sinus  {
      static inline void operation(T & b, const T & a){
        b = std::sin(a);
      }
    };
  }
NS_END(CORE_MATH_NAMESPACE)
