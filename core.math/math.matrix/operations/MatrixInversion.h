#pragma once
#include <config.h>

namespace nspace{
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
}
