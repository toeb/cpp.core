#pragma once
#include <math.matrix/operations/MatrixOperations.h>
#include <math.matrix/operations/MatrixSwap.h>

namespace nspace{

  /**
   * \brief Swap rows.
   *
   * \tparam  typename MatrixType Type of the matrix.
   * \param [in,out]  matrix  The matrix.
   * \param i1                index of the 1. row to be swapped
   * \param i2                index of the 2. row to be swapped
   */
  template<typename MatrixType> void swapRows(MatrixType  & matrix, IndexArgument(MatrixType) i1, IndexArgument(MatrixType) i2);


  template<typename MatrixType>
  MatrixOperationClass(SwapRows){
    MatrixOperationMethod(MatrixType  & matrix, IndexArgument(MatrixType) i1, IndexArgument(MatrixType) i2){
      matrixForEachColumn(matrix){
        matrixSwap(coefficient(matrix,i1,j), coefficient(matrix,i2,j));
      }
    }
  };

  //implemenatation
  template<typename MatrixType>
  void swapRows(MatrixType  & matrix, IndexArgument(MatrixType) i1, IndexArgument(MatrixType) i2){MatrixOperation(SwapRows)<MatrixType>::operation(matrix,i1,i2);}

}