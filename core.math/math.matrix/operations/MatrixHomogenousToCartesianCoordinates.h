#pragma once

#include <config.h>

namespace nspace{
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
}
