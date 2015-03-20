#pragma once
#include <config.h>
#include <math.matrix/operations/MatrixInversion.h>
namespace nspace{
  template<typename InvertedMatrixType, typename InputMatrixType>
  class MatrixInversion<InvertedMatrixType,InputMatrixType,MatrixProperty::Symmetric>{
  public:
    static void operation(InvertedMatrixType & inv, const InputMatrixType & type){
      //assert(false);
    }
  };
}
