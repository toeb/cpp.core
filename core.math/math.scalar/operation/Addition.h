#pragma once
#include <config.h>
#include <math/operations/UnaryOperation.h>
#include <math/operations/OperationCodes.h>
#include <cmath>
namespace nspace{
  namespace math{
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
  }
}
