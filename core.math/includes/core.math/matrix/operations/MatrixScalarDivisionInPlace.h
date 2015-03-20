#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/operations/MatrixScalarMultiplication.h>
NS_BEGIN(CORE_MATH_NAMESPACE)
template<typename MatrixQuotient, typename MatrixDividend, typename ScalarDivisor>
class MatrixScalarDivisionInPlace{
public:
  static inline void operation(MatrixQuotient & quotient, const MatrixDividend & dividend, const ScalarDivisor & divisor){
    ScalarDivisor factor = math::shorthands::scalar::reciprocal(divisor);
    MatrixScalarMultiplication<MatrixQuotient, MatrixDividend, ScalarDivisor>::operation(quotient, dividend, factor);
  }
};
NS_END(CORE_MATH_NAMESPACE)