#pragma once
#include <core.math/core.math.h>
#include <math/operations/UnaryOperation.h>
#include <math/operations/OperationCodes.h>
#include <cmath>
NS_BEGIN(CORE_MATH_NAMESPACE)
    namespace scalar{
      template<T>
      class BinaryOperation<T, operation::Addition>{
      public:
        static inline T operation(const T a,const T b){
          return a+b;
        }
      };

      template<typename T>
      typedef BinaryOperation<T,operation::Addition> Addition;
    }
  NS_END(CORE_MATH_NAMESPACE)
