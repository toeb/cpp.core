#pragma once

#include <config.h>

namespace nspace{
  /**
  * \brief Matrix compare. Compares every element of the two matrices for equality and
  * 				 assigns the result to true if every element aij is no more than epsilon apart from bij
  * 				 if dimensions mismatch then the matrix cannot be equal
  */
  template<typename MatA, typename MatB, typename TEpsilon=Real>
  class MatrixCompare{
  public:
    static inline void operation(bool & equal, const MatA & matA, const MatB & matB, const TEpsilon eps){
      equal = true;
      //check dimensions
      if(matA.rows() != matB.rows()){
        equal = false;
        return;
      }
      if(matA.cols() != matB.cols()){
        equal = false;
        return;
      }
      // check every element
      for(int i=0; i < matA.rows(); i++){
        for(int j=0; j < matA.cols(); j++){
          if(abs(matA(i,j)-matB(i,j)) >= eps){
            equal = false;
            return;
          }
        }
      }
    }
  };
}