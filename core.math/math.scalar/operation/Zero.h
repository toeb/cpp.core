#pragma once
#include <config.h>
#include <math.operation/NullaryOperation.h>
#include <math.scalar/operationcodes.h>
namespace nspace{
  namespace math{
    namespace operation{
      template<typename T>
      class Operation<T, Nullary,scalar::opcodes::Zero >{
      public:
        static inline void operation(T & a){
          a = 0.0;
        }
      };
    }
  }
}
