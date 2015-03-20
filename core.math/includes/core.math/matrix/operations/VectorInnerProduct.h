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
#include <core.math/matrix/operations/MatrixCoefficientType.h>
#include <core.math/matrix/operations/MatrixIndexType.h>
#include <core.math/matrix/operations/MatrixTypeSelector.h>
#include <core.math/matrix/operations/MatrixAddition.h>
#include <core.math/matrix/operations/MatrixMultiplication.h>
#include <core.math/matrix/operations/MatrixBinaryOperation.h>
NS_BEGIN(CORE_MATH_NAMESPACE)

  /**
   * \brief performs the dot product on two vectors
   *        aka the inner product 
   *        aka c= aT*b (for column vectors).
   *
   * \param c the result
   * \param a the first vector
   * \param b The second vector.
   */
  BinaryMatrixOperationOtherReturnType(dot,coefficientTypeOfType(typename returnType(A,B)));


  template<typename T, typename VecA, typename VecB>
  class VectorInnerProduct {
public:
    static inline void operation(T & result, const VecA & a, const VecB & b){
      typedef typename coefficientTypeOfType (VecA) CoeffA;
      typedef typename coefficientTypeOfType (VecB) CoeffB;
      typedef typename indexTypeOfType (VecA) Index;
      Index rowCount = rows(a);
      Index colCount = cols(a);
      result = 0;
      for(Index i=0; i < rowCount; i++) {
        add(result,result, multiply<T,CoeffA,CoeffB>(coefficient(a,i,0), coefficient(b,i,0)));
      }
    }
  };
  //implementations
  BinaryOperationImplementation(dot){
    VectorInnerProduct<C,A,B>::operation(c,a,b);
  }

NS_END(CORE_MATH_NAMESPACE)
