#pragma once
#include <config.h>

namespace nspace{
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
}