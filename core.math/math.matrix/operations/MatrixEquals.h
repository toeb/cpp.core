#pragma once
#include <config.h>
#include <math.scalar/operations.h>
namespace nspace{
  //implementation requires MatrixTypeA (rows() operator(int) cols() size() )
  template<typename MatrixTypeA, typename MatrixTypeB, typename ElementType>
  class OperationMatrixEquals{
  public:
    static inline bool operation(bool &result, const MatrixTypeA & matrixA, const MatrixTypeB & matrixB , const ElementType & epsilon){
      result = false;
      // if dimensions mismatch matrices are not equal
      if(matrixA.rows()!=matrixB.rows()){
        return true;
      }
      if(matrixA.cols()!=matrixB.cols()){
        return true;
      }
      // check if every element is (almost) equals
      for(int i=0; i < matrixA.size(); i++){
        if(math::shorthands::scalar::absolute(matrixA(i)-matrixB(i)) > epsilon){
          return true;
        }
      }
      result = true;
      return true;
    }
  };
}