#pragma once

#include <core.math/core.math.h>

NS_BEGIN(CORE_MATH_NAMESPACE)
  template<typename MatCart,typename MatHom>
  class MatrixHomogenousToCartesianCoordinates{
  public:
    static inline void operation(MatCart & c, const MatHom & h){
      c.resize(h.rows()-1,h.cols,false);
      for(int i=0; i < c.rows(); i++){
        for(int j=0; j < c.cols(); j++){
          c(i,j) = h(i,j) / h(c.rows(),j);
        }
      }
    }
  };
NS_END(CORE_MATH_NAMESPACE)
