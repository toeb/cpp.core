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
#include <math.matrix/operations/VectorCrossProduct.h>
#include <math.matrix/operations/VectorNormalize.h>
namespace nspace {

  /**
   * \brief Calculate the Normal of the plane defined by vectors a and b
   *        n = a x b / ||a x b||_2
   *
   *
   * \tparam  typename N  Type of Normal.
   * \tparam  typename A  Type of Vector a.
   * \tparam  typename B  Type of Vector b.
   * \param n The resulting normal vector
   * \param a The first input vector
   * \param b The second input vector.
   */
  template<typename N, typename A, typename B> inline void normal(ARG_OUT(N)n, ARG_IN(A)a, ARG_IN(B)b);

  /**
   * \brief Calculate and return the Normal of the plane defined by vectors a and b.
   *
   * \tparam  typename VectorN  Type of vector n.
   * \tparam  typename VectorA  Type of vector a.
   * \tparam  typename VectorB  Type of vector b.
   * \param a vector a
   * \param b vector b
   *
   * \return  n the resulting normal vector.
   */
  template<typename N, typename A, typename B> inline N normal(ARG_IN(A)a, ARG_IN(B)b){
    N result;
    normal(result,a,b);
    return result;
  }

  /**
   * \brief Calculate and return the Normal of the plane defined by vectors a and b.
   *
   * \tparam  typename A  Type of a.
   * \tparam  typename B  Type of b.
   * \param a  vector a.
   * \param b  vector b.
   *
   * \return  the normal vector. (default return type)
   */
  template<typename A, typename B> inline typename returnType(A,B) normal(ARG_IN(A) a, ARG_IN(B) b){
    return normal<typename returnType(A,B),A,A>(a,b);
  }


  template<typename N, typename A, typename B>
  class OperationNormal {
public:
    static inline void operation(ARG_OUT(N)normal, ARG_IN(A)a, ARG_IN(B)b){
      cross(normal,a,b);
      normalize(normal);
    }
  };

  //implementation
  template<typename VectorN, typename VectorA, typename VectorB>
  inline void normal(ARG_OUT(VectorN)n, ARG_IN(VectorA)a, ARG_IN(VectorB)b){
    OperationNormal<VectorN,VectorA,VectorB>::operation(n,a,b);
  }


}
