/**
 * Copyright (C) 2013 Tobias P. Becker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the  rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More information at: https://dslib.assembla.com/
 *
 */
#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/operations/MatrixSetConstant.h>
#include <core.math/matrix/operations/MatrixIndexType.h>
#include <core.math/matrix/operations/MatrixRowCount.h>
#include <core.math/matrix/operations/MatrixColumnCount.h>
NS_BEGIN(CORE_MATH_NAMESPACE)

  /**
   * \brief Operation matrix resize.  tries to resize the matrix
   *        template class may be specialized.
   *        the default operation checks if the matrix  already has the whished for dimensions and returns true if it does.
   *        if it does not it returns false
   *        Matrix types may want to specialize this operation
   */
  template<typename MatrixType>
  class OperationMatrixResize {
public:
    static inline bool operation(MatrixType  & matrix, typename indexTypeOfType(MatrixType)newRowCount, typename indexTypeOfType(MatrixType)newColCount){
      if(newRowCount==rows(matrix) && newColCount==cols(matrix)) {
        return true;
      }
      return false;
    }
  };

  /**
   * \brief Resizes the matrix specified.
   *
   * \tparam  typename MatrixType Type of the  matrix.
   * \param [in,out]  matrix  The matrix.
   * \param newRowCount       Number of new rows.
   * \param newColCount       Number of new cols.
   *
   * \return  true if matrix has new dimensions , false if it did not work. if false is returned the matrix' state is not determined (mostly it will remain the same)
   */
  template<typename MatrixType> inline bool resize(MatrixType & matrix, typename indexTypeOfType(MatrixType)newRowCount, typename indexTypeOfType(MatrixType)newColCount){
    return OperationMatrixResize<MatrixType>::operation(matrix,newRowCount,newColCount);
  }

  /**
   *
   * \brief Resizes the matrix specified to a rowvector of dimension newRowCount.
   *
   * \tparam  typename VectorType Type of the  vector .
   * \param [in,out]  vector  The vector.
   * \param newRowCount       Number of new rows.
   *
   * \return  true if it succeeds, false if it fails.
   */

  template<typename VectorType> inline bool resize(VectorType & vector, typename indexTypeOfType(VectorType) newRowCount){
    return resize(vector,newRowCount,1);
  }

  template<typename MatrixType> inline bool ensureMatrixDimension(MatrixType & matrix, typename indexTypeOfType(MatrixType) newRowCount, typename indexTypeOfType(MatrixType) newColCount){
    if(rows(matrix)==newRowCount&&cols(matrix)==newColCount)return true;
    return resize(matrix,newRowCount,newColCount);
  }

  template<typename VectorType> inline bool ensureVectorDimension(VectorType & vector, typename indexTypeOfType(VectorType) newRowCount){
    return ensureMatrixDimension(vector,newRowCount,1);
  }

  /**
   * \brief Resizes the matrix lhs to the same dimension as the matrix rhs.
   *
   * \tparam  typename MatrixTypeA  Type of the typename matrix type a.
   * \tparam  typename MatrixTypeB  Type of the typename matrix type b.
   * \param [in,out]  lhs The left hand side.
   * \param rhs           The right hand side.
   *
   * \return  true if it succeeds, false if it fails.
   */
  template<typename MatrixTypeA, typename MatrixTypeB> inline bool resize(MatrixTypeA & lhs, const MatrixTypeB & rhs){
    return resize(lhs,rows(rhs),cols(rhs));
  }

  template<typename MatrixType> MatrixType createMatrix(typename indexTypeOfType(MatrixType) rowCount, typename indexTypeOfType(MatrixType) colCount){
    MatrixType matrix;
    if(!ensureMatrixDimension(matrix,rowCount,colCount)){}
    return matrix;
  }
  template<typename VectorType> VectorType createVector(typename indexTypeOfType(VectorType) rowCount){
    return createMatrix<VectorType>(rowCount,1);
  }


/**
 * \brief A macro that defines begin specialize matrix resize. the code for resizeing the matrix "matrix"
 *        to have "rowcount" and "colcount" dimensions needs to be written directly afterwards
 *
 * \param TYPE  The type.
 */
#define BeginSpecializeMatrixResize(TYPE) class OperationMatrixResize<TYPE>{public: static inline bool operation(TYPE & matrix, size_t rowcount, size_t colcount){

/**
 * \brief A macro that defines end specialize matrix resize.
 */
#define EndSpecializeMatrixResize return false;}};

/**
 * \brief A macro that is replaced by the specialization of MatrixResize for type TYPE.
 *          the matrix is accessible via "matrix" the rows are accessible via rowcount and columns by colcount
 * \param TYPE        The type.
 * \param RESIZECODE  The resize code must return true if it is ensured that matrix has the wished for dimensions else false.
 */
#define SpecializeMatrixResize(TYPE,RESIZECODE) BeginSpecializeMatrixResize(TYPE) RESIZECODE EndSpecializeMatrixResize
  
NS_END(CORE_MATH_NAMESPACE)
