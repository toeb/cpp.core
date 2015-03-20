#pragma once

#include <core.math/core.math.h>

NS_BEGIN(CORE_MATH_NAMESPACE)
  template<typename Mat>
  class MatrixTransposeInPlace{
  public:
    static inline void operation(Mat & AT){
      Mat A = AT;
      AT.resize(A.cols(),A.rows());

      for(int i=0; i < A.rows(); i++){
        for(int j=0; j < A.cols(); j++){
          AT(j,i)=A(i,j);
        }
      }
    }
  };
NS_END(CORE_MATH_NAMESPACE)