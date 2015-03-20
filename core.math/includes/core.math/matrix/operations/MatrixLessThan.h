#pragma once
#include <core.math/core.math.h>
NS_BEGIN(CORE_MATH_NAMESPACE)
  template<typename MatrixTypeA, typename MatrixTypeB>
  class OperationMatrixLessThan{
  public:
    static inline bool operation(bool &result, const MatrixTypeA & matrixA, const MatrixTypeB & matrixB ){
      return false;
    }
  };
NS_END(CORE_MATH_NAMESPACE)