#pragma once
#include <core.math/core.math.h>

NS_BEGIN(CORE_MATH_NAMESPACE)
  enum MatrixProperty{
    Default = 0,
    PositiveDefinite=1,
    PositiveSemidefinite=2,
    Diagonal=3,
    Symmetric=4
  };

  template<typename InvertedMatrixType, typename OriginalMatrixType, MatrixProperty props=Default>
  class MatrixInversion{
  public:
    static void operation(InvertedMatrixType & inv, const OriginalMatrixType & orig){
    }
  };
NS_END(CORE_MATH_NAMESPACE)
