#pragma once
#include <core.math/core.math.h>
#include <core.math/scalar/constants.h>
NS_BEGIN(CORE_MATH_NAMESPACE)
  namespace scalar{
    template<typename T>
    struct EulersNumber  {
      static inline void operation(T & a){
        a = M_E;
      }
    };
  }
NS_END(CORE_MATH_NAMESPACE)
