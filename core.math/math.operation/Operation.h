#pragma once
#include <config.h>

namespace nspace{
  namespace math{
    namespace operation{
      //Operation Code.  an unsigned int which specifies which operation is to be executed
      typedef uint OperationCode;

      // the operation type specifies how many input arguments are used
      enum OperationType{
        Nullary = 0,
        Unary = 1,
        Binary = 2,
        Nary = 99
      };

      // the operation class is extendable by template specialization and can represent any type of operation
      template<typename T, operation::OperationType type, OperationCode code>
      class Operation{
      public:
      };
    }
  }
}