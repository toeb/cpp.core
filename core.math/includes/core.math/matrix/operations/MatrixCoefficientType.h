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

NS_BEGIN(CORE_MATH_NAMESPACE)

/**
 * \brief A macro that is replaced by the  coefficient type of a matrix type.
 *
 * \param MATRIXTYPE  The matrixtype.
 */
#define coefficientTypeOfType(MATRIXTYPE)  MatrixCoefficientType<MATRIXTYPE>::Type

 /**
  * \brief A macro that is replaced by the coefficient type of a matrix rvalue
  *
  * \param MATRIXINSTANCE  The matrixinstance.
  */
#define coefficientTypeOfInstance(MATRIXINSTANCE)  coefficientTypeOfType( decltype(MATRIXINSTANCE))


  /**
   * \brief Matrix coefficient type. template class which has a typedef Type containing the coefficient type of a MatrixType
   *        The default is double.  MatrixTypes need to specialize this template
   * \todo :remove double
   */
   template<typename MatrixType>
class MatrixCoefficientType {
public:
  typedef double Type;
};

/**
 * \brief A macro that specializes the MatrixCoefficientType class.
 *
 * \param MATRIXTYPE      The matrixtype.
 * \param COEFFICIENTTYPE The coefficienttype.
 */
#define SpecializeMatrixCoefficientType(MATRIXTYPE,COEFFICIENTTYPE) class MatrixCoefficientType<MATRIXTYPE>{public: typedef COEFFICIENTTYPE Type; };

#define DeclareMatrixCoefficientType(MATRIXTYPE,COEFFICIENTTYPE) template<> SpecializeMatrixCoefficientType(MATRIXTYPE,COEFFICIENTTYPE)


NS_END(CORE_MATH_NAMESPACE)
