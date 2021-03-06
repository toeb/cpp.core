#pragma once
#include <core.math/core.math.h>
#include <math/operations/UnaryOperation.h>
#include <math/operations/OperationCodes.h>
#include <cmath>
NS_BEGIN(CORE_MATH_NAMESPACE)
    namespace scalar{
      template<T>
      class UnaryOperation<T, operation::Tangens>{
      public:
        static inline T operation(const T a){
          return std::tan(a);
        }
      };

      template<typename T>
      typedef UnaryOperation<T,operation::Tangens> Tangens;
    }
NS_END(CORE_MATH_NAMESPACE)
