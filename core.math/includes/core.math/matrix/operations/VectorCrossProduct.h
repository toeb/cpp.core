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

#include <core.math/matrix/operations/MatrixCoefficientAccess.h>
#include <core.math/matrix/operations/MatrixRowCount.h>
#include <core.math/matrix/operations/MatrixColumnCount.h>
#include <core.math/matrix/operations/MatrixDimensionCheck.h>
#include <core.math/matrix/operations/MatrixElementWiseMultiplication.h>
#include <core.math/matrix/operations/MatrixSubtraction.h>
#include <core.math/matrix/operations/MatrixTypeSelector.h>
#include <core.math/matrix/operations/MatrixBinaryOperation.h>


NS_BEGIN(CORE_MATH_NAMESPACE)

  /**
   * \brief  cross product operation for 3x1 vectors
   *
   */
  BinaryMatrixOperation(cross);

  /**
   * \brief performs the cross product .
   */
  template<typename VecC, typename VecA, typename VecB>
  class VectorCrossProduct {
public:
    static inline void operation(VecC &  c, const VecA & a, const VecB & b){
      typedef typename coefficientTypeOfType (VecA) CoeffA;
      typedef typename coefficientTypeOfType (VecB) CoeffB;
      typedef typename coefficientTypeOfType (VecC) CoeffC;

      typedef typename indexTypeOfType (VecC) Index;
      Index rowCount = rows(c);
      //assert(rowCount==3)
      Index i = 0;
      subtract(coefficient(c,0,i),multiply<CoeffC,CoeffA,CoeffB>(coefficient(a,1,i),coefficient(b,2,i)), multiply<CoeffC,CoeffA,CoeffB>(coefficient(a,2,i),coefficient(b,1,i)));
      subtract(coefficient(c,1,i),multiply<CoeffC,CoeffA,CoeffB>(coefficient(a,2,i),coefficient(b,0,i)), multiply<CoeffC,CoeffA,CoeffB>(coefficient(a,0,i),coefficient(b,2,i)));
      subtract(coefficient(c,2,i),multiply<CoeffC,CoeffA,CoeffB>(coefficient(a,0,i),coefficient(b,1,i)), multiply<CoeffC,CoeffA,CoeffB>(coefficient(a,1,i),coefficient(b,0,i)));

    }
  };

  //Implementation

  BinaryOperationImplementation(cross){
    VectorCrossProduct<C,A,B>::operation(c,a,b);
  }

NS_END(CORE_MATH_NAMESPACE)
