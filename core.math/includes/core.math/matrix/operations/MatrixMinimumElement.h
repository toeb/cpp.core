#pragma once

#include <core.math/core.math.h>

NS_BEGIN(CORE_MATH_NAMESPACE)
  template<typename ScalarResult, typename MatrixInput>
  class MatrixMinimumElement{
  public:
    static inline void operation(ScalarResult & minimum, const MatrixInput & mat){
      minimum = mat(0,0);
      for(int i=0; i < mat.rows();i++){
        for(int j=0; j < mat.cols();j++){
          if(minimum> mat(i,j))minimum=mat(i,j);
        }
      }
    }
  };
NS_END(CORE_MATH_NAMESPACE)