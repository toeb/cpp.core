#pragma once
#include <core.math/core.math.h>

#include <core.math/matrix/operations/MatrixColumnTraits.h>
#include <core.math/matrix/operations/MatrixRowTraits.h>
#include <core.math/matrix/operations/MatrixCoefficientAccess.h>
#include <core.math/matrix/operations/MatrixTypeSelector.h>
#include <core.math/matrix/operations/MatrixBinaryOperation.h>
NS_BEGIN(CORE_MATH_NAMESPACE)
/**
 * \brief multiplies two matrices together element wise $\f \mathbf{c}_{ij} := \mathbf{a}_{ij}\dot \mathbf{b}_{ij} $\f
 *
 */
 BinaryMatrixOperation(multiply);

template<typename C, typename A, typename B>
class MatrixElementWiseMultiply{
public:
  static inline void operation(C & c, const A &  a, const B & b){
    typedef typename indexTypeOfType(C) Index;
    Index rowCount = rows(c);
    Index colCount = cols(c);

    // template recursion anchor 
    if (isScalarMatrix<C>()){
      coefficient(c, 0, 0) = coefficient(a, 0, 0)*coefficient(b, 0, 0);
      return;
    }

    for (Index i = 0; i < rowCount; i++){
      for (Index j = 0; j < colCount; j++){
        multiply(coefficient(c, i, j), coefficient(a, i, j), coefficient(b, i, j));
      }
    }
  }
};

/**
 * \brief implements multiply(c,a,b) method.
 *
 */
BinaryOperationImplementation(multiply){ MatrixElementWiseMultiply<C, A, B>::operation(c, a, b); }

NS_END(CORE_MATH_NAMESPACE)
