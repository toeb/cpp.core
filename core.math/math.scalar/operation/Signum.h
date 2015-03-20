#pragma once
#include <config.h>
#include <math.operation/UnaryOperation.h>
#include <math.scalar/operationcodes.h>
namespace nspace{
  namespace math{
    namespace operation{
      template<typename T>
      class Operation<T,Unary, scalar::opcodes::Signum>{
      public:
        static inline void operation(T & b ,const T & a){
          if(a >=0.0){ b = 1.0 ; return;}
          if(a < 0.0){ b = -1.0 ;return;}
        }
      };
    }
  }
}
