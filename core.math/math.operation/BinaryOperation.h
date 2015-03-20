#pragma once
#include <math.operation/Operation.h>

namespace nspace{
  namespace math{
    namespace operation{
      typedef OperationCode BinaryOperationCode;

      // the default implementation for a binary operation just prints an error message
      template<typename T, BinaryOperationCode code>
      class Operation<T, operation::Binary, code>{
      public:
        static inline void operation(T & c, const T & a, const T & b){
          //ERROR("UNIMPLEMENTED BINARY OPERATION");
        }
      };
    }
  }
}
