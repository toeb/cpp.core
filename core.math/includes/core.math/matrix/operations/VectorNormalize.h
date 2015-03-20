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
#include <core.math/matrix/operations/VectorNorm.h>
#include <core.math/matrix/operations/MatrixElementWiseMultiplication.h>
NS_BEGIN(CORE_MATH_NAMESPACE)

  /**
   * \brief Normalizes the given vector.
   *
   * \tparam  typename VectorType Type of  vector .
   * \param [in, out]  vector  The vector which is to be normalized.
   */
  template<typename VectorType> inline void normalize(VectorType & vector);

  /**
   * \brief Normalizes the vector and stores the result in the result vector
   *
   * \tparam  typename ResultingType  Type of the  result .
   * \tparam  typename VectorType     Type of the  vector .
   * \param [out]  result  The result.
   * \param vector            The vector.
   */
  template<typename ResultingType,typename VectorType> inline void normalized(ResultingType & result, const VectorType & vector){
    assignMatrix(result,vector); normalize(result);
  }

  /**
   * \brief Normalizes the given vector without modifiying it an returns the result.
   *
   * \tparam  typename ResultingType  Type of the  resulting .
   * \tparam  typename VectorType     Type of the  vector .
   * \param vector  The vector.
   *
   * \return the normalized vector .
   */
  template<typename ResultingType,typename VectorType> inline ResultingType normalized(const VectorType & vector){
    ResultingType result; normalized(result,vector); return result;
  }

  /**
   * \brief Normalizes the given vector without modifying it and returns the result.
   *
   * \tparam  typename VectorType Type of the vector .
   * \param vector  The vector.
   *
   * \return  normalized vector.
   */
  template<typename VectorType> inline VectorType normalized(const VectorType & vector){
    return normalized<VectorType,VectorType>(vector);
  }


  template<typename VectorType>
  VectorOperationClass(Normalize){
    VectorOperationMethod( VectorType & vector){
      using namespace math::shorthands::scalar;
      auto l = length(vector);
      auto inverseLength =  reciprocal(l);
      multiply(vector,vector,inverseLength);
    }
  };



  // implemenetation
  template<typename VectorType> inline void normalize(VectorType & vector){
    OperationVectorNormalize<VectorType>::operation(vector);
  }

NS_END(CORE_MATH_NAMESPACE)