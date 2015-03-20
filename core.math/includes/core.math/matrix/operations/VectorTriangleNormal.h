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
#include <core.math/matrix/operations/VectorNormal.h>
#include <core.math/matrix/operations/MatrixSubtraction.h>

NS_BEGIN(CORE_MATH_NAMESPACE)

  /**
   * \brief calculates the normal of the triangle defined by a,b,c (CCW order)
   *
   * \tparam  typename N  Type of n. (a Vector)
   * \tparam  typename A  Type of a.(a Vector)
   * \tparam  typename B  Type of b.(a Vector)
   * \tparam  typename C  Type of c.(a Vector)
   * \param n The normal.
   * \param a point a of the triangle
   * \param b point b of the triangle
   * \param c point c of the triangle
   */
  template<typename N, typename A, typename B, typename C>  inline void triangleNormal(ARG_OUT(N)n, ARG_IN(A)a, ARG_IN(B)b, ARG_IN(C)c);

  template<typename VectorN, typename VectorA, typename VectorB, typename VectorC>
  inline VectorN triangleNormal(ARG_IN(VectorA)a, ARG_IN(VectorB)b, ARG_IN(VectorC)c){
    VectorN result;
    triangleNormal(result,a,b,c);
    return result;
  }
  template<typename VectorA,typename VectorB, typename VectorC>
  inline typename MatrixTypeSelector<VectorA, typename returnType(VectorB,VectorC)>::Type triangleNormal(ARG_IN(VectorA) a, ARG_IN(VectorB) b, ARG_IN(VectorC) c){
    return triangleNormal<typename MatrixTypeSelector<VectorA, typename returnType(VectorB,VectorC)>::Type,VectorA,VectorB,VectorC>(a,b,c);
  }

  template<typename VectorN, typename VectorA, typename VectorB, typename VectorC>
  class OperationTriangleNormal {
public:
    static inline void operation(ARG_OUT(VectorN)n, ARG_IN(VectorA)a, ARG_IN(VectorB)b, ARG_IN(VectorC)c){
      normal(n, subtract(b,a), subtract(c,a));
    }
  };

  //implementations
  template<typename VectorN, typename VectorA, typename VectorB, typename VectorC>
  inline void triangleNormal(ARG_OUT(VectorN)n, ARG_IN(VectorA)a, ARG_IN(VectorB)b, ARG_IN(VectorC)c){
    OperationTriangleNormal<VectorN,VectorA,VectorB,VectorC>::operation(n,a,b,c);
  }

NS_END(CORE_MATH_NAMESPACE)
