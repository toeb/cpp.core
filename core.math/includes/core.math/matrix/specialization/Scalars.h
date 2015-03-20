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

/**
 * \file  math.matrix\specialization\Scalars.h
 *
 * \brief Contains specializations for scalar matrices.
 */
#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/operations/MatrixOperationMacros.h>
#include <core.math/matrix/operations/MatrixTraits.h>
#include <core.math/matrix/operations/MatrixColumnTraits.h>
#include <core.math/matrix/operations/MatrixRowTraits.h>
#include <core.math/matrix/operations/MatrixColumnCount.h>
#include <core.math/matrix/operations/MatrixRowCount.h>
#include <core.math/matrix/operations/MatrixCoefficientType.h>


NS_BEGIN(CORE_MATH_NAMESPACE)
/**
 * \brief A convenience macro that calls OPERATION for all default scalar types. (double,float,int,unsigned int, short ....unsigned char)
 *
 * \param OPERATION The operation.
 */
#define FOR_ALL_DEFAULT_SCALAR_TYPES(OPERATION) \
  OPERATION(double); \
  OPERATION(float); \
  OPERATION(int); \
  OPERATION(unsigned int); \
  OPERATION(short); \
  OPERATION(unsigned short); \
  OPERATION(char); \
  OPERATION(unsigned char);

  
  //specializations for scalar types
  
#define DeclareScalarCoefficientType(SCALARTYPE) DeclareMatrixCoefficientType(SCALARTYPE,SCALARTYPE)
  FOR_ALL_DEFAULT_SCALAR_TYPES(DeclareScalarCoefficientType);

  /**
   * \brief Define Scalar Matrix Trait fro default scalars
   *
   */
  FOR_ALL_DEFAULT_SCALAR_TYPES(DefineScalarTrait);

  /**
   * \brief Define fixed size column for default scalars
   *
   */
  FOR_ALL_DEFAULT_SCALAR_TYPES(DefineMatrixFixedSizeColumns);

  /**
   * \brief Define Scalar Matrix Trait fro default scalars
   *
   */
  FOR_ALL_DEFAULT_SCALAR_TYPES(DefineMatrixFixedSizeRows);


#define Define1DColumnCount(TYPE) template<> SpecializeColumnCount(TYPE,1)
  FOR_ALL_DEFAULT_SCALAR_TYPES(Define1DColumnCount);
  
#define Define1DRowCount(TYPE) template<> SpecializeRowCount(TYPE,1)
  FOR_ALL_DEFAULT_SCALAR_TYPES(Define1DRowCount);

#define DefineScalarTypeSelectors(TYPE) \
template<typename MatrixType> SpecializeTypeSelectorPartially(MatrixType, TYPE, MatrixType);\
template<typename MatrixType> SpecializeTypeSelectorPartially(TYPE , MatrixType, MatrixType);\
SpecializeTypeSelector(TYPE , TYPE, TYPE);

  FOR_ALL_DEFAULT_SCALAR_TYPES(DefineScalarTypeSelectors);

#define DeclareScalarCoefficientAccess(SCALARTYPE) DefineCoefficientAccess(SCALARTYPE, return matrix)
  FOR_ALL_DEFAULT_SCALAR_TYPES(DeclareScalarCoefficientAccess);

#define DeclareScalarMatrixTransposedTypeTrait(SCALARTYPE) DeclareMatrixTraitTransposedType(SCALARTYPE,SCALARTYPE)
  FOR_ALL_DEFAULT_SCALAR_TYPES(DeclareScalarMatrixTransposedTypeTrait);

NS_END(CORE_MATH_NAMESPACE)