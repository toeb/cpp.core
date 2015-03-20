#pragma once
#include <config.h>
#include <math.operation/UnaryOperation.h>
#include <math.scalar/operationcodes.h>
#include <cmath>
namespace nspace{
  namespace math{
    namespace operation{
      template<typename T>
      class Operation<T, Unary, scalar::opcodes::Sinus>{
      public:
        static inline void operation(T & b, const T & a){
          b = std::sin(a);
        }
      };
    }
  }
}
