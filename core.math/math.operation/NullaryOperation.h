#pragma once

#include <config.h>

#include <math.operation/Operation.h>

namespace nspace{
  namespace math{
    namespace operation{
      typedef OperationCode NullaryOperationCode;
      // the default implementation for a nullary operation just prints an error message
      template<typename T, NullaryOperationCode code>
      class Operation<T,operation::Nullary, code>{
      public:
        static inline void operation(T & a){
          //ERROR("UNIMPLEMENTED NULLARY FUNCTION");
        }
      };
    }
  }
}
