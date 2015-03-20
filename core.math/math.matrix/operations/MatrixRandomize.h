#pragma once
#include <math.matrix/operations/MatrixOperations.h>
#include <cstdlib>
namespace nspace{
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
  
}