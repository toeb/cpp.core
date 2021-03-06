#pragma once
#include <config.h>
#include <math/operations/UnaryOperation.h>
#include <math/operations/OperationCodes.h>
#include <cmath>
namespace nspace{
  namespace math{
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
  }
}
