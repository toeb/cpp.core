#pragma once

#include <core.math/core.math.h>
NS_BEGIN(CORE_MATH_NAMESPACE)
template<typename Mat33, typename Vec3>
class VectorToCrossProductMatrix{
public:
  static inline void operation(Mat33 &  r_star, const Vec3 & r){
    if (3 != rows(r_star)){
      throw std::exception();
      return;
    }
    if (3 != cols(r_star)){
      throw std::exception();
      return;
    }
    if (rows(r) != 3){
      throw std::exception();
      return;
    }
    if (cols(r) != 1){
      throw std::exception();
      return;
    }

    CoefficientAliasForType(Mat33);


    auto zero = scalar::zero<Coefficient>();

    coefficient(r_star, 0, 0) = zero;
    coefficient(r_star, 0, 1) = -coefficient(r, 2, 0);
    coefficient(r_star, 0, 2) = coefficient(r, 1, 0);
    coefficient(r_star, 1, 0) = coefficient(r, 2, 0);
    coefficient(r_star, 1, 1) = zero;
    coefficient(r_star, 1, 2) = -coefficient(r, 0, 0);
    coefficient(r_star, 2, 0) = -coefficient(r, 1, 0);
    coefficient(r_star, 2, 1) = coefficient(r, 0, 0);
    coefficient(r_star, 2, 2) = zero;
  }
};
NS_END(CORE_MATH_NAMESPACE)
