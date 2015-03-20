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
 * \brief gets the number of columns for the matrix
 *
 * \tparam  typename MatrixType Type of the  matrix .
 * \param matrix  The matrix.
 *
 * \return  number of columns.
 */
 template<typename MatrixType> auto cols(const MatrixType & matrix)->typename indexTypeOfType(MatrixType);



/**
 * \brief Operation column count. a template class that should be specialized by MatrixType classes.
 *        the default implementations calls MatrixType::cols()
 *        other types of access need to be specialized
 */
template<typename MatrixType>
class OperationColumnCount {
public:

  /**
   * \brief Operation
   *
   * \param [in,out]  columnCount Number of columns.
   * \param matrix                The matrix.
   *
   * \return  true if it succeeds, false if it fails.
   */
  static inline typename indexTypeOfType(MatrixType) operation(const MatrixType & matrix){
    return matrix.cols();
  }
};


/**
 * \brief A macro that defines the specialization for OperationColumnCount.
 *
 * \param TYPE          The type.
 * \param COLCOUNTCODE  The core that needs to evaluate to the columncount.
 */
#define SpecializeColumnCount(TYPE, COLCOUNTCODE) class OperationColumnCount<TYPE>{public: static inline  indexTypeOfType(TYPE) operation(const TYPE &matrix){return COLCOUNTCODE; }};




// specializations

//2d array
template<typename T, size_t n, size_t m>
class OperationColumnCount < T[n][m] > {
public:
  static inline typename indexTypeOfType(T[n][m]) operation(const T(&matrix)[n][m]){
    return m;
  }
};

//1d array - a column vector
template<typename T, size_t n>
class OperationColumnCount < T[n] > {
public:
  static inline typename indexTypeOfType(T[n]) operation(const T(&matrix)[n]){
    return 1;
  }
};

//2d array  - 
template<typename T>
class OperationColumnCount < T** > {
public:
  static inline typename indexTypeOfType(T**) operation(const T **  matrix){
    return 0;
  }
};

//1d array  - 
template<typename T>
class OperationColumnCount < T* > {
public:
  static inline typename indexTypeOfType(T*) operation(const T *  matrix){
    return 1;
  }
};


//implementation 
template<typename MatrixType> auto cols(const MatrixType & matrix)->typename indexTypeOfType(MatrixType){
  return OperationColumnCount<MatrixType>::operation(matrix);
}
NS_END(CORE_MATH_NAMESPACE)