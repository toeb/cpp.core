#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/operations/MatrixOperations.h>

NS_BEGIN(CORE_MATH_NAMESPACE)

  /**
   * \brief Swaps 2  columns of a matrix
   *
   * \tparam  typename MatrixType Type of the matrix.
   * \param [in,out]  matrix  The matrix.
   * \param j1                The first column index
   * \param j2                The second column index
   */
  template<typename MatrixType> void swapColumns(MatrixType & matrix, IndexArgument(MatrixType)   j1, IndexArgument(MatrixType)   j2);

  template<typename MatrixType>
  MatrixOperationClass(SwapColumns){
    MatrixOperationMethod(MatrixType & matrix, IndexArgument(MatrixType) j1, IndexArgument(MatrixType) j2){
      matrixForEachRow(matrix){
        matrixSwap(coefficient(matrix,i,j1),coefficient(matrix,i,j2));
      }
    }
  };

  
  template<typename MatrixType> void swapColumns(MatrixType & matrix, IndexArgument(MatrixType)   j1, IndexArgument(MatrixType)   j2){
    OperationMatrixSwapColumns<MatrixType>::operation(matrix,j1,j2);
  }
NS_END(CORE_MATH_NAMESPACE)