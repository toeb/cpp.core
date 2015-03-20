#pragma once
#include <core.math/core.math.h>

NS_BEGIN(CORE_MATH_NAMESPACE)
  template<typename MatA, typename MatB>
  class MatrixNegation{
  public:
    static inline void operation(MatA & result, const MatB & m){
      for(int i=0; i < result.rows(); i++){
        for(int j=0; j < result.cols(); j++){
          result(i,j)=-m(i,j);
        }
      }
    }
  };
NS_END(CORE_MATH_NAMESPACE)