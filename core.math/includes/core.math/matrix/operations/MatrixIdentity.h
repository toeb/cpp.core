#pragma once
#include <core.math/core.math.h>
NS_BEGIN(CORE_MATH_NAMESPACE)

  template<typename Matrix> void matrixSetIdentity(Matrix & matrix);
  template<typename Matrix>
  MatrixOperationClass(Identity){
    MatrixOperationMethod(Matrix & matrix){
      if(isScalarMatrix<Matrix>()){
        coefficient(matrix,0,0)=1;
        return;
      }
      matrixForEach(matrix){
        if(i==j){
          matrixSetIdentity(coefficient(matrix,i,j));
        }else{
          matrixSetZero(coefficient(matrix,i,j));
        }
      }
    }
  };
  
  template<typename Matrix> void matrixSetIdentity(Matrix & matrix){
  MatrixOperation(Identity)<Matrix>::operation(matrix);
  }
  
  template<typename Matrix> Matrix identity(){
    Matrix result;
    matrixSetIdentity(result);
    return result;
  }
  template<typename Matrix> Matrix identity(typename indexTypeOfType(Matrix) rows,typename indexTypeOfType(Matrix) cols){
    Matrix result;
    ensureMatrixDimension(result,rows,cols);
    matrixSetIdentity(result);
    return result;
  }

NS_END(CORE_MATH_NAMESPACE)