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
#include <core.math/matrix/operations/MatrixIndexType.h>
NS_BEGIN(CORE_MATH_NAMESPACE)

  /**
   * \brief returns number of Rows of the given matrix.
   *
   * \tparam  typename MatrixType Type of the  matrix .
   * \param matrix  The matrix.
   *
   * \return  number of rows.
   */
  template<typename MatrixType> auto rows(const MatrixType & matrix)->typename indexTypeOfType(MatrixType);

  /**
   * \brief Operation row count.  a template class returning the rowcount of a matrix of type MatrixType
   *        the default implementation returns MatrixType::rows();
   *        matrix types should specialize this class
   */
  template<typename MatrixType>
  class OperationRowCount {
public:

    /**
     * \brief operation for getting the rowcount of a matrix
     *
     * \param matrix  the matrix of which the rowcoutn is to be queried
     *
     * \return  the rowcount.
     */
    static inline typename indexTypeOfType(MatrixType) operation(const MatrixType &matrix){
      return matrix.rows();
    }
  };

  /**
   * \brief A macro that is replaced by the specialization class of OperationRowCount.
   *        Remeber to add template<> or template<...> before macros for complete or partial specialization
   *
   * \param TYPE          The type for which to specialize.
   * \param ROWCOUNTCODE  The rowcountcode.
   */
  #define SpecializeRowCount(TYPE, ROWCOUNTCODE) class OperationRowCount<TYPE>{public: static inline indexTypeOfType(TYPE) operation(const TYPE &matrix){return ROWCOUNTCODE; }};


  //specialization

  //2d array
  template<typename T, size_t n, size_t m>
  class OperationRowCount<T[n][m]>{
public:
    static inline typename indexTypeOfType(T[n][m]) operation(const T(&matrix)[n][m]){
      return n;
    }
  };
  //1d array  - a column vector 
  template<typename T, size_t n>
  class OperationRowCount<T[n]>{
public:
    static inline typename indexTypeOfType(T[n]) operation( const T(&matrix)[n]){
      return n;
    }
  };

  //2d array  - 
  template<typename T>
  class OperationRowCount<T**>{
public:
    static inline typename indexTypeOfType(T**) operation(const T **  matrix){
      return 0;
    }
  };

  //1d array  - 
  template<typename T>
  class OperationRowCount<T*>{
public:
    static inline typename indexTypeOfType(T*) operation(const T *  matrix){
      return 0;
    }
  };


  //implementation
   template<typename MatrixType> auto rows(const MatrixType & matrix)->typename indexTypeOfType(MatrixType){
    return OperationRowCount<MatrixType>::operation(matrix);
  }
NS_END(CORE_MATH_NAMESPACE)
