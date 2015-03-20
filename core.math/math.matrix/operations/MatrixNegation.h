#pragma once
#include <config.h>

namespace nspace{
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
}