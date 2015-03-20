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
#include <core.math/matrix/operations/MatrixBinaryOperation.h>
#include <core.math/matrix/operations/VectorInnerProduct.h>
NS_BEGIN(CORE_MATH_NAMESPACE)

  /**
   * \brief calculates the squared length of a vector
   *
   * \tparam  typename LengthType Type of the  length .
   * \tparam  typename VectorType Type of the  vector .
   * \param [out]  length  The length.
   * \param vector            The vector.
   */
  template<typename LengthType, typename VectorType> inline void lengthSquared(LengthType & length, const VectorType & vector);

  /**
   * \brief calculates the squared length of a vector
   *
   * \tparam  typename LengthType Type of the  length .
   * \tparam  typename VectorType Type of the  vector .
   * \param vector  The vector.
   *
   * \return the legnth .
   */
  template<typename LengthType, typename VectorType> inline LengthType lengthSquared(const VectorType & vector){
    LengthType length; lengthSquared<LengthType,VectorType>(length,vector); return length;
  }

  /**
   * \brief calculates the squared length of the vector
   *
   * \tparam  typename VectorType Type of the  vector .
   * \param parameter1  The first parameter.
   *
   * \return the length squared (same type as vector's coefficients) .
   */
  template<typename VectorType> inline typename coefficientTypeOfType(VectorType) lengthSquared(const VectorType &vector){
    return lengthSquared<typename coefficientTypeOfType(VectorType),VectorType>(vector);
  }


  template<typename LengthType, typename VectorType>
  VectorOperationClass(LengthSquared){
    VectorOperationMethod(LengthType & length, const VectorType &vector){
      dot(length,vector,vector);
    }
  };
  //implementations
  template<typename LengthType, typename VectorType> void lengthSquared(LengthType & length, const VectorType & vector){
    OperationVectorLengthSquared<LengthType,VectorType>::operation(length,vector);
  }

NS_END(CORE_MATH_NAMESPACE)

