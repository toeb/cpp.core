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
#include <config.h>
#include <math.matrix/operations/MatrixCoefficientType.h>
#include <math.matrix/operations/MatrixIndexType.h>
#include <math.matrix/operations/MatrixIndexMapping.h>
#include <math.matrix/operations/MatrixOperationMacros.h>
namespace nspace {

   /**
   * \brief coefficient mutable reference access to matrix' element at (i,j).
   *
   * \tparam  typename MatrixType Type of the typename matrix type.
   * \param [in,out]  matrix  The matrix.
   * \param i                 Zero-based index of the.
   * \param j                 The const typename indexTypeOfType(double[3]) &amp; to process.
   *
   * \return  .
   */
  template<typename MatrixType> inline auto coefficient(MatrixType & matrix, const typename indexTypeOfType(MatrixType) & i,const typename indexTypeOfType(MatrixType) & j)->typename coefficientTypeOfType(MatrixType)&;

  /**
   * \brief coefficient  value access to matrix' element at (i,j).
   *
   * \tparam  typename MatrixType Type of the typename matrix type.
   * \param matrix  The matrix.
   * \param i       Zero-based index of the.
   * \param j       The const typename indexTypeOfType(double[3]) &amp; to process.
   *
   * \return  .
   */
  template<typename MatrixType> inline auto coefficient(const MatrixType & matrix, IndexArgument(MatrixType) i,IndexArgument(MatrixType)  j)-> typename coefficientTypeOfType(MatrixType);

  /**
   * \brief reference to coefficient at i, given the row/column mapping (default is RowMajor)
   *
   * \tparam  typename MatrixType Type of the typename matrix type.
   * \param [in,out]  matrix  The matrix.
   * \param i                 Zero-based index of the.
   * \param mapping           (optional) the mapping.
   *
   * \return  .
   */
  template<typename MatrixType> inline auto coefficient(MatrixType & matrix, IndexArgument(MatrixType)  i, IndexMapping mapping=RowMajor)->typename coefficientTypeOfType(MatrixType)&;
  
  /**
   * \brief value of coefficient at i, given the row/column mapping (default is RowMajor)
   *
   * \tparam  typename MatrixType Type of the typename matrix type.
   * \param [in,out]  matrix  The matrix.
   * \param i                 Zero-based index of the.
   * \param mapping           (optional) the mapping.
   *
   * \return  .
   */
  template<typename MatrixType> inline auto coefficient(const MatrixType & matrix, IndexArgument(MatrixType)  i, IndexMapping mapping=RowMajor)-> typename coefficientTypeOfType(MatrixType);

 
  /**
   * \brief Operation matrix coefficient access.
   *        a template class which gives access to the coefficients of a  matrix by reference @todo --> maybe this should not be by reference!?
   *        matrix classes should specialize this class
   *        the default implementation access the elements by operator()(i,j)
   */
  template<typename MatrixType>
  class OperationMatrixCoefficientAccess {
public:
    /**
     * \brief reference access to a matrix coefficient
     *
     * \param matrix  The matrix.
     * \param i the row index.
     * \param j the column index.
     *
     * \return  the coefficient reference.
     */
    static inline typename coefficientTypeOfType(MatrixType) & operation(MatrixType & matrix,IndexArgument(MatrixType)  i,IndexArgument(MatrixType)  j){
      return matrix(i,j);
    }


    /**
     * \brief access to a matrix coefficient by value (matrix is const)
     *
     * \param matrix  The matrix.
     * \param i the row index.
     * \param j the column index.
     *
     * \return  the const coefficient reference.
     */
    static inline typename coefficientTypeOfType(MatrixType) operation(const MatrixType &matrix,IndexArgument(MatrixType) i, IndexArgument(MatrixType)  j){
      return matrix(i,j);
    }

  };


  /**
   * \brief Operation matrix coefficient access single index. uses the operation coefficientaccess for multiple 2d indices
   *        and the MatrixIndexMapping operations to give single index access to a matrix
   */
   template <typename MatrixType>
  class OperationMatrixCoefficientAccessSingleIndex{
  public:
    static inline typename coefficientTypeOfType(MatrixType) & operation(MatrixType  & matrix, IndexArgument(MatrixType)  i, IndexMapping mapping){
      return coefficient(matrix,mapRowIndex(matrix,i,mapping),mapColumnIndex(matrix,i,mapping));
    }
    static inline typename coefficientTypeOfType(MatrixType) operation(const MatrixType & matrix, IndexArgument(MatrixType)  i, IndexMapping mapping){
      return coefficient(matrix,mapRowIndex(matrix,i,mapping),mapColumnIndex(matrix,i,mapping));
    }
  };

/**
 * \brief A macro that is replaced by the full specialization for TYPE of the OperationMatrixCoefficientAccess class
 *
 * \param TYPE        The type to be specialized.
 * \param ACCESSCODE  The accesscode.
 */
#define DefineCoefficientAccess(TYPE,ACCESSCODE)template<> class OperationMatrixCoefficientAccess<TYPE>{ \
public: \
    static inline coefficientTypeOfType(TYPE) & operation(TYPE & matrix, const indexTypeOfType(TYPE) & i,const indexTypeOfType(TYPE) & j){ACCESSCODE;} \
    static inline coefficientTypeOfType(TYPE) operation(const TYPE &matrix, const indexTypeOfType(TYPE) & i,const indexTypeOfType(TYPE) & j){ACCESSCODE; } \
};

/**
 * \brief A macro is replaced by the partial specialization of OeprationMatrixCoefficientAccess
 *          remember to prepend template<...>  matrix is the variable name of matrix, i of the row index and j of the col index
 * \param TYPE        The type.
 * \param ACCESSCODE  The code which evaluates to a reference / resp const reference of the coefficient at i,j .
 */
#define SpecializeCoefficientAccess(TYPE,ACCESSCODE)class OperationMatrixCoefficientAccess<TYPE>{ \
public: \
    static inline typename coefficientTypeOfType(TYPE) & operation(TYPE & matrix, const typename indexTypeOfType(TYPE) & i,const typename indexTypeOfType(TYPE) & j){ACCESSCODE; } \
    static inline typename coefficientTypeOfType(TYPE)   operation(const TYPE &matrix, const typename indexTypeOfType(TYPE) & i,const typename indexTypeOfType(TYPE) & j){ACCESSCODE; } \
};
  

  // implementation 
  
  template<typename MatrixType> inline auto coefficient(MatrixType & matrix, const typename indexTypeOfType(MatrixType) & i,const typename indexTypeOfType(MatrixType) & j)->typename coefficientTypeOfType(MatrixType)&{
    return OperationMatrixCoefficientAccess<MatrixType>::operation(matrix,i,j);
  }

  template<typename MatrixType> inline auto coefficient(const MatrixType & matrix, const typename indexTypeOfType(MatrixType) & i,const typename indexTypeOfType(MatrixType) & j)-> typename coefficientTypeOfType(MatrixType){
    return OperationMatrixCoefficientAccess<MatrixType>::operation(matrix,i,j);
  }
  
  template<typename MatrixType> inline auto coefficient(MatrixType & matrix, const typename indexTypeOfType(MatrixType) & i, IndexMapping mapping)->typename coefficientTypeOfType(MatrixType)&{
    return OperationMatrixCoefficientAccessSingleIndex<MatrixType>::operation(matrix,i,mapping);
  }

  template<typename MatrixType> inline auto coefficient(const MatrixType & matrix, const typename indexTypeOfType(MatrixType) & i, IndexMapping mapping)-> typename coefficientTypeOfType(MatrixType){
    return OperationMatrixCoefficientAccessSingleIndex<MatrixType>::operation(matrix,i,mapping);
  }
}
