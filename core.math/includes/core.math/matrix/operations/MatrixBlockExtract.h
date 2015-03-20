#pragma once
#include <core.math/core.math.h>

#include <core.math/matrix/operations/MatrixOperations.h>
#include <core.math/matrix/operations/MatrixAssignment.h>

NS_BEGIN(CORE_MATH_NAMESPACE)




template<typename BlockMatrix, typename SourceMatrix>
MatrixOperationClass(BlockExtract){
  IndexAliasForType(SourceMatrix);
  MatrixOperationMethod(BlockMatrix & block, const SourceMatrix & matrix, const Index rowOffset, const Index colOffset){

    const Index sourceRows = rows(matrix);
    const Index sourceCols = cols(matrix);
    const Index blockRows = rows(block);
    const Index blockCols = cols(block);

    if (blockRows + rowOffset > sourceRows)return;//error
    if (blockCols + colOffset > sourceCols)return;//error

    for (Index i = 0; i < blockRows; ++i){
      for (Index j = 0; j < blockCols; ++j){
        assignMatrixBlindly(coefficient(block, i, j), coefficient(matrix, i + rowOffset, j + colOffset));
      }
    }

  }
};

template<typename BlockMatrix, typename SourceMatrix>
inline void matrixBlockExtract(BlockMatrix & block, const SourceMatrix & source, const typename indexTypeOfType(SourceMatrix) rowOffset, const typename indexTypeOfType(SourceMatrix) columnOffset){
  MatrixOperation(BlockExtract) < BlockMatrix, SourceMatrix > ::operation(block, source, rowOffset, columnOffset);
}

template<typename BlockMatrix, typename SourceMatrix>
inline void matrixBlockExtract(BlockMatrix & block, const SourceMatrix & source,
  const typename indexTypeOfType(SourceMatrix) rowOffset, const typename indexTypeOfType(SourceMatrix) columnOffset,
  const typename indexTypeOfType(BlockMatrix) rowCount, const typename indexTypeOfType(BlockMatrix) columnCount){
  if (!ensureMatrixDimension(block, rowOffset, columnCount))return;
  MatrixOperation(BlockExtract) < BlockMatrix, SourceMatrix > ::operation(block, source, rowOffset, columnOffset);
}





template<typename BlockType, typename SourceType>
class MatrixBlockExtract{
public:
  static inline void operation(BlockType  & target, const SourceType & source, size_t rowOffset, size_t colOffset){
    if (target.rows() + rowOffset > source.rows()){
      /*ERROR("range exceed matrix dimension");*/
      return;
    }
    if (target.cols() + colOffset > source.cols()){
      /*      ERROR("range exceed matrix dimension");*/
      return;
    }
    for (size_t i = 0; i < target.rows(); i++){
      for (size_t j = 0; j < target.cols(); j++){
        target(i, j) = source(i + rowOffset, j + colOffset);
      }
    }
  }
};

template<typename OutputMatrix, typename InputMatrix>
class MatrixExtractBlock{
public:
  static inline void operation(OutputMatrix & result, const InputMatrix & original, size_t startRow, size_t startCol, size_t rows, size_t cols){
    result.resize(rows, cols, false);
    if (original.rows() < rows + startRow)return;
    if (original.cols() < cols + startCol)return;
    for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
        result(i, j) = original(i + startRow, j + startCol);
      }
    }
  }
};
NS_END(CORE_MATH_NAMESPACE)
