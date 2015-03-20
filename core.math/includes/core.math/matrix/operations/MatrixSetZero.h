#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/operations/MatrixCoefficientAccess.h>
#include <core.math/matrix/operations/MatrixRowCount.h>
#include <core.math/matrix/operations/MatrixColumnCount.h>
#include <core.math/matrix/operations/MatrixTraits.h>
#include <core.math/matrix/operations/MatrixBinaryOperation.h>
NS_BEGIN(CORE_MATH_NAMESPACE)

  

  template<typename Matrix> void matrixSetZero(Matrix & matrix);

  template<typename Matrix>
  MatrixOperationClass(Zero){
    MatrixOperationMethod(Matrix & matrix){
      if(isScalarMatrix<Matrix>()){
        coefficient(matrix,0,0) = 0;
        return;
      }
      matrixForEach(matrix){
        matrixSetZero(coefficient(matrix,i,j));
      }
    }
  };
  
  template<typename Matrix> void matrixSetZero(Matrix & matrix){
    MatrixOperation(Zero)<Matrix>::operation(matrix);
  }
  template<typename Matrix> Matrix zero(){
    Matrix result;
    matrixSetZero(result);
    return result;
  }
  template<typename Matrix> Matrix zero(typename indexTypeOfType(Matrix) rows,typename indexTypeOfType(Matrix) cols){
    Matrix result;
    ensureMatrixDimension(result,rows,cols);
    matrixSetZero(result);
    return result;
  }

  NullaryMatrixOperation(zeros);


template<typename MatrixType>
class MatrixZero{
public:
  static inline void operation(MatrixType & matrix){
    CoefficientAndIndexAliasForType(MatrixType);
    if(isScalarMatrix<MatrixType>()){
      coefficient(matrix,0,0)=0;
      return;
    }
    
    Index rowCount = rows(matrix);
    Index colCount = cols(matrix);
    for(Index i = 0; i < rowCount; i++)
      for(Index j =0; j < colCount; j++)
        zeros(coefficient(matrix,i,j));
  }
};
NullaryOperationImplementation(zeros){
  MatrixZero<A>::operation(a);
}


NS_END(CORE_MATH_NAMESPACE)