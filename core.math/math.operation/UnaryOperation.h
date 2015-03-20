#pragma once
#include <config.h>
#include <math.operation/Operation.h>

namespace nspace{
  namespace math{
    namespace operation{
      typedef OperationCode UnaryOperationCode;
      // the default implementation for a unary operation just prints an error message
      template<typename T, UnaryOperationCode code>
      class Operation<T,operation::Unary, code>{
      public:
        static inline void operation(T & b, const T & a){
          //ERROR("USING UNIMPLEMENTED UNARY FUNCTION ");
        }
      };
    }
  }
}
