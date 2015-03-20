#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/operations/MatrixInversion.h>
NS_BEGIN(CORE_MATH_NAMESPACE)
  template<typename InvertedMatrixType, typename InputMatrixType>
  class MatrixInversion<InvertedMatrixType,InputMatrixType,MatrixProperty::Symmetric>{
  public:
    static void operation(InvertedMatrixType & inv, const InputMatrixType & type){
      //assert(false);
    }
  };
NS_END(CORE_MATH_NAMESPACE)
