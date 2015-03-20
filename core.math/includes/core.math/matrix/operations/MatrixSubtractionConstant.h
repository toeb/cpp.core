#pragma once
#include <core.math/core.math.h>
NS_BEGIN(CORE_MATH_NAMESPACE)

template<typename MatrixResult, typename Matrix, typename Scalar>
class MatrixSubtractionConstant{
public:
  static inline void operation(MatrixResult & c, const Matrix & a, const Scalar & b){
    c.resize(a.rows(),a.cols());
    for(int i=0; i < a.rows(); i++){
      for(int j=0; j < a.cols(); j++){
        c(i,j)=a(i,j)-b;
      }
    }
  }
};
NS_END(CORE_MATH_NAMESPACE)