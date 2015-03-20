#pragma once
#include <config.h>
namespace nspace{
  template<typename MatHom,typename MatCart>
  class MatrixCartesianToHomogenousCoordinates{
  public:
    static inline void operation(MatHom & h, const MatCart & c){
      h.resize(c.rows()+1,c.cols(),false);
      for(int i=0; i < c.rows(); i++){
        for(int j=0; j <c.cols();j++){
          h(i,j)=c(i,j);
        }
      }
      for(int j=0;j <h.cols(); j++){
        h(c.rows(),j)=1;
      }
    }
  };
}
