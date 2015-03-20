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
#include <core.math/matrix/operations/VectorNormSquared.h>

NS_BEGIN(CORE_MATH_NAMESPACE)

  /**
   * \brief calculates the length of the vector v
   *
   * \tparam  typename LengthType Type of the length .
   * \tparam  typename VectorType Type of the vector .
   * \param [out]  l length of vectro .
   * \param vector      The vector.
   */
  template<typename LengthType, typename VectorType> inline void length(LengthType & l, const VectorType & vector);
  template<typename LengthType, typename VectorType> inline LengthType length(const VectorType & vector){
    LengthType l; length(l,vector); return l;
  }
  template<typename VectorType> inline typename coefficientTypeOfType(VectorType)  length(const VectorType &vector){
    return length<typename coefficientTypeOfType(VectorType)>(vector);
  }


  template<typename LengthType, typename VectorType>
  VectorOperationClass(Length){
    VectorOperationMethod(LengthType & length, const VectorType &vector){
      auto l_sqr = lengthSquared(vector);
      elementWiseSquareRoot(length, l_sqr);
    }
  };

  template<typename LengthType, typename VectorType> inline void length(LengthType & l, const VectorType & vector){
    OperationVectorLength<LengthType,VectorType>::operation(l,vector);
  }



NS_END(CORE_MATH_NAMESPACE)