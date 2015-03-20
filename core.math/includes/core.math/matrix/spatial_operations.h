#pragma once

#include <core.math/core.math.h>
#define CORE_MATH_MATRIX_SPATIAL_NAMESPACE CORE_MATH_NAMESPACE, spatial

NS_BEGIN(CORE_MATH_MATRIX_SPATIAL_NAMESPACE)

template<typename TMat, typename TRot>
void rot(TMat & rotE, const TRot & E){
  using namespace core::math;
  ensureMatrixDimension(rotE, 6, 6);
  matrixSetZero(rotE);
  matrix::setBlock(rotE, E, 0, 0);
  matrix::setBlock(rotE, E, 3, 3);
}
template<typename TMat, typename TRot>
TMat rot(const TRot & E){
  TMat res;
  rot(res, E);
  return res;
}


template<typename TMat>
void rotx(TMat & rotE, typename const core::math::coefficientTypeOfType(TMat) & theta){
  typedef typename core::math::coefficientTypeOfType(TMat) coeff;
  coeff E[3][3];
  matrix::rx(E, theta);
  rot(rotE, E);
}
template<typename TMat>
TMat rotx(typename const core::math::coefficientTypeOfType(TMat) & theta){
  TMat res;
  rotx(res, theta);
  return res;
}

template<typename TMat>
void roty(TMat & rotE, typename const core::math::coefficientTypeOfType(TMat) & theta){
  typedef typename core::math::coefficientTypeOfType(TMat) coeff;
  coeff E[3][3];
  matrix::ry(E, theta);
  rot(rotE, E);
}
template<typename TMat>
TMat roty(typename const core::math::coefficientTypeOfType(TMat) & theta){
  TMat res;
  roty(res, theta);
  return res;
}

template<typename TMat>
void rotz(TMat & rotE, typename const core::math::coefficientTypeOfType(TMat) & theta){
  typedef typename core::math::coefficientTypeOfType(TMat) coeff;
  coeff E[3][3];
  matrix::rz(E, theta);
  rot(rotE, E);
}
template<typename TMat>
TMat rotz(const typename core::math::coefficientTypeOfType(TMat) & theta){
  TMat res;
  rotz(res, theta);
  return res;
}

template<typename TMat, typename TPos>
void xlt(TMat & xltR, const TPos & r){
  using namespace core::math;
  CoefficientAliasForType(TPos);
  ensureMatrixDimension(xltR, 6, 6);
  matrixSetIdentity(xltR);
  Coefficient rx[3][3];
  Coefficient  minus_rx[3][3];
  matrix::crossProductMatrix(rx, r);
  transpose(minus_rx, rx);
  matrix::setBlock(xltR, minus_rx, 3, 0);
}
template < typename TMat, typename TPos >
TMat xlt(const TPos& r){
  TMat res;
  xlt(res, r);
  return res;
}

template < typename TMat, typename TRot, typename TPos >
void transform(TMat & X, const TRot & E, const TPos & r){
  core::math::multiply(X, rot<TMat>(E), xlt<TMat>(r));
}
template < typename TMat, typename TRot, typename TPos >
TMat transform(const TRot & E, const TPos & r){
  TMat res;
  transform(res, E, r);
  return res;
}

NS_END(CORE_MATH_MATRIX_SPATIAL_NAMESPACE)

