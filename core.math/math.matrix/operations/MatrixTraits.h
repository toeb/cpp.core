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

namespace nspace {
  /**
   * \brief Matrix trait for defining that a type is a scalar matrix type
   *        default implementation defines matrix type as non-scalar
   */
  template<typename MatrixType>
  class MatrixTraitIsScalar {
public:
    static const bool isScalar = false;
  };

  template<typename MatrixType>
  class MatrixTraitTransposedType{
  public:
    typedef void Type;
  };
  
#define SpecializeMatrixTraitTransposedType(TYPE, TRANSPOSEDTYPE) class MatrixTraitTransposedType<TYPE>{public: typedef TRANSPOSEDTYPE Type;};
#define DeclareMatrixTraitTransposedType(TYPE, TRANSPOSEDTYPE) template<> class MatrixTraitTransposedType<TYPE>{public: typedef TRANSPOSEDTYPE Type;};


/**
 * \brief A macro that defines define matrix scalar trait for a type.
 *
 * \param ISSCALAR  whether or not type is scalar.
 * \param TYPE      the type.
 */
#define DefineMatrixScalarTraits(ISSCALAR,TYPE) template<> class MatrixTraitIsScalar<TYPE>{public: static const bool isScalar = ISSCALAR; };

/**
 * \brief A macro that defines defines scalar trait
 *
 * \param TYPE  The type.
 */
#define DefineScalarTrait(TYPE) DefineMatrixScalarTraits(true,TYPE)

/**
 * \brief A macro that defines defines is scalar trait to false for type.
 *
 * \param TYPE  The type.
 */
#define DefineMatrixTrait(TYPE) DefineMatrixScalarTraits(false,TYPE)

  /**
   * \brief Query if type is a scalar matrix.
   *
   * \tparam  typename MatrixType Type of the matrix .
   *
   * \return  true if scalar matrix, false if not.
   */
  template<typename MatrixType> inline bool isScalarMatrix(){
    return MatrixTraitIsScalar<MatrixType>::isScalar;
  }

  /**
   * \brief Query if 'matrix' is scalar a matrix.
   *
   * \tparam  typename MatrixType Type of the matrix.
   * \param matrix  The matrix.
   *
   * \return  true if matrix is scalar matrix, false if not.
   */
  template<typename MatrixType> inline bool isScalarMatrix(const MatrixType & ){
    return isScalarMatrix<MatrixType>();
  }


}
