#pragma once
#include <core.math/core.math.h>
#include <cmath>

NS_BEGIN(CORE_MATH_NAMESPACE)
  namespace scalar{
    template<typename T>
    struct ArcusSinus{
      static inline void operation(T & b, const T & a){
        b = std::asin(a);
      }
    };
  }
NS_END(CORE_MATH_NAMESPACE)
