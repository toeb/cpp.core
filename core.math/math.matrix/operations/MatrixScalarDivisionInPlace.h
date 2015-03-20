#pragma once
#include <config.h>
#include <math.matrix/operations/MatrixScalarMultiplication.h>
namespace nspace{
  template<typename MatrixQuotient,typename MatrixDividend, typename ScalarDivisor>
  class MatrixScalarDivisionInPlace{
  public:
    static inline void operation(MatrixQuotient & quotient, const MatrixDividend & dividend, const ScalarDivisor & divisor){
      ScalarDivisor factor = math::shorthands::scalar::reciprocal(divisor);
      MatrixScalarMultiplication<MatrixQuotient,MatrixDividend,ScalarDivisor>::operation(quotient,dividend,factor);
    }
  };
}