#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/operations/MatrixOperations.h>
#include <cstdlib>
NS_BEGIN(CORE_MATH_NAMESPACE)
  template<typename Matrix> void matrixSetRandom(Matrix & matrix);

  template<typename Matrix>
  MatrixOperationClass(Random){
    MatrixOperationMethod(Matrix & matrix){
      if(isScalarMatrix<Matrix>()){
        coefficient(matrix,0,0)=(((double)rand())/(double)RAND_MAX);
        return;
      }
      matrixForEach(matrix){
        matrixSetRandom(coefficient(matrix,i,j));
      }
    }
  };
  template<typename Matrix> void matrixSetRandom(Matrix & matrix){
    MatrixOperation(Random)<Matrix>::operation(matrix);
  }
  template<typename Matrix> Matrix random(){
    Matrix result;
    matrixSetRandom(result);
    return result;
  }
  template<typename Matrix> Matrix random(typename indexTypeOfType(Matrix) rows,typename indexTypeOfType(Matrix) cols){
    Matrix result;
    ensureMatrixDimension(result,rows,cols);
    matrixSetRandom(result);
    return result;
  }
  
NS_END(CORE_MATH_NAMESPACE)