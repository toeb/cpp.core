#pragma once
#include <config.h>
namespace nspace{
  template<typename MatrixTypeA, typename MatrixTypeB>
  class OperationMatrixGreaterThan{
  public:
    static inline bool operation(bool &result, const MatrixTypeA & matrixA, const MatrixTypeB & matrixB ){
      return false;
    }
  };
}