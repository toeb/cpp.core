#pragma once
#include <stdio.h>
#include <iostream>
#include <functional>
#include <assert.h>
#include <core.math/core.math.h>

#include <core.math/scalar/all.h>
#include <core.math/matrix/operations/MatrixAdditionInPlace.h>
#include <core.math/matrix/operations/MatrixAddition.h>
#include <core.math/matrix/operations/MatrixAssignment.h>
#include <core.math/matrix/operations/MatrixConvolution.h>
#include <core.math/matrix/operations/MatrixFilter.h>
#include <core.math/matrix/operations/MatrixFrobeniusNorm.h>
#include <core.math/matrix/operations/MatrixInversion.h>
#include <core.math/matrix/operations/MatrixMinimumElement.h>
#include <core.math/matrix/operations/MatrixMaximumElement.h>
#include <core.math/matrix/operations/MatrixMultiplicationInPlace.h>
#include <core.math/matrix/operations/MatrixMultiplication.h>
#include <core.math/matrix/operations/MatrixNegationInPlace.h>
#include <core.math/matrix/operations/MatrixNegation.h>
#include <core.math/matrix/operations/MatrixNormalization.h>
#include <core.math/matrix/operations/MatrixMultiplication.h>
#include <core.math/matrix/operations/MatrixAllocate.h>
#include <core.math/matrix/operations/MatrixDeallocate.h>
#include <core.math/matrix/operations/MatrixCoefficientAccess.h>
#include <core.math/matrix/operations/MatrixScalarDivisionInPlace.h>
#include <core.math/matrix/operations/MatrixScalarDivision.h>
#include <core.math/matrix/operations/MatrixScalarMultiplicationInPlace.h>
#include <core.math/matrix/operations/MatrixScalarMultiplication.h>
#include <core.math/matrix/operations/MatrixSetConstant.h>
#include <core.math/matrix/operations/MatrixSetFunction.h>
#include <core.math/matrix/operations/MatrixSubtractionInPlace.h>
#include <core.math/matrix/operations/MatrixSubtraction.h>
#include <core.math/matrix/operations/MatrixInversionSymmetric.h>
#include <core.math/matrix/operations/MatrixTranspositionInPlace.h>
#include <core.math/matrix/operations/MatrixTransposition.h>
#include <core.math/matrix/operations/VectorCrossProduct.h>
#include <core.math/matrix/operations/VectorInnerProduct.h>
#include <core.math/matrix/operations/VectorOuterProduct.h>
#include <core.math/matrix/operations/VectorToCrossProductMatrix.h>
#include <core.math/matrix/operations/QuaternionMultiplication.h>
#include <core.math/matrix/operations/QuaternionConjugation.h>
#include <core.math/matrix/operations/QuaternionToRotationMatrix.h>
#include <core.math/matrix/operations/MatrixBlockAssign.h>
#include <core.math/matrix/operations/MatrixBlockExtract.h>
#include <core.math/matrix/operations/MatrixElementWiseMultiplication.h>
#include <core.math/matrix/operations/MatrixElementWiseDivision.h>
#include <core.math/matrix/operations/MatrixReduce.h>
#include <core.math/matrix/operations/MatrixReduceSum.h>
#include <core.math/matrix/operations/MatrixScalarAddition.h>
#include <core.math/matrix/operations/MatrixScalarSubtraction.h>
#include <core.math/matrix/operations/MatrixCompare.h>
#include <core.math/matrix/operations/MatrixInversion.h>
#include <core.math/matrix/operations/MatrixInversionSymmetric.h>
#include <core.math/matrix/operations/MatrixCartesianToHomogenousCoordinates.h>
#include <core.math/matrix/operations/MatrixHomogenousToCartesianCoordinates.h>
#include <core.math/matrix/operations/MatrixExportData.h>
#include <core.math/matrix/operations/MatrixImportData.h>
#include <core.math/matrix/operations/MatrixResize.h>
#include <core.math/matrix/operations/MatrixSubtractionConstant.h>
#include <core.math/matrix/operations/MatrixElementWiseUnary.h>
#include <core.math/matrix/operations/MatrixElementWiseBinary.h>
#include <core.math/matrix/operations/MatrixPad.h>

#include <core.math/matrix/operations/MatrixEquals.h>
#include <core.math/matrix/operations/MatrixLessThan.h>
#include <core.math/matrix/operations/MatrixGreaterThan.h>

#include <core.math/matrix/operations/MatrixColumnCount.h>
#include <core.math/matrix/operations/MatrixRowCount.h>
#include <core.math/matrix/operations/MatrixElementAssignment.h>

#include <core.math/matrix/operations/MatrixTypeSelector.h>
#include <core.math/matrix/operations/MatrixTraits.h>
#include <core.math/matrix/operations/MatrixRowTraits.h>
#include <core.math/matrix/operations/MatrixColumnTraits.h>

#include <core.math/matrix/operations/MatrixSetZero.h>

#include <core.math/matrix/operations/MatrixMaximumElement.h>
#include <core.math/matrix/operations/MatrixMinimumElement.h>
#include <core.math/matrix/operations/MatrixSwap.h>
#include <core.math/matrix/operations/MatrixSwapColumns.h>
#include <core.math/matrix/operations/MatrixSwapRows.h>
#include <core.math/matrix/operations/MatrixOperations.h>

#include <core.math/matrix/operations/GaussJordanElimination.h>
#include <core.math/matrix/operations/VectorNormalize.h>
#include <core.math/matrix/operations/VectorNorm.h>

#include <core.math/matrix/operations/VectorNormal.h>
#include <core.math/matrix/operations/VectorTriangleNormal.h>

#include <core.math/matrix/operations/MatrixRandomize.h>
#include <core.math/matrix/operations/MatrixSetZero.h>
#include <core.math/matrix/operations/MatrixIdentity.h>

#include <core.math/matrix/specialization/Scalars.h>
#include <core.math/matrix/specialization/Array1D.h>
#include <core.math/matrix/specialization/Array2D.h>
#include <core.math/matrix/specialization/StdVector.h>




NS_BEGIN(CORE_MATH_NAMESPACE, matrix)

/// sets the coefficients of the 3x3 matrix m to
/// the rotational matrix for theta
template<typename TMat>
void rx(TMat & m, 
  const  typename core::math::coefficientTypeOfType(TMat) &theta){
  using namespace core::math;
  using namespace core::math::scalar;

  auto c = cosine(theta);
  auto s = sine(theta);
  matrixSetIdentity(m);
  coefficient(m, 1, 1) = c;
  coefficient(m, 1, 2) = s;
  coefficient(m, 2, 1) = -s;
  coefficient(m, 2, 2) = c;
}
/// creates a rotational matrix around x-unit vector with angle tetha
template<typename TMat>
TMat rx(const  typename core::math::coefficientTypeOfType(TMat) & theta){
  TMat res;
  rx(res, theta);
  return res;
}


template<typename TMat>
void ry(TMat & m, const  typename core::math::coefficientTypeOfType(TMat) &theta){
  using namespace core::math;
  using namespace core::math::scalar;

  auto c = cosine(theta);
  auto s = sine(theta);
  matrixSetIdentity(m);
  coefficient(m, 0, 0) = c;
  coefficient(m, 0, 2) = -s;
  coefficient(m, 2, 0) = s;
  coefficient(m, 2, 2) = c;
}
template<typename TMat>
TMat ry(const  typename core::math::coefficientTypeOfType(TMat) & coeff){
  TMat res;
  ry(res, coeff);
  return res;
}

template<typename TMat>
void rz(TMat & m, const  typename core::math::coefficientTypeOfType(TMat) &theta){
  using namespace core::math;
  using namespace core::math::scalar;

  auto c = cosine(theta);
  auto s = sine(theta);
  matrixSetIdentity(m);
  coefficient(m, 0, 0) = c;
  coefficient(m, 0, 1) = s;
  coefficient(m, 1, 0) = -s;
  coefficient(m, 1, 1) = c;
}
template<typename TMat>
TMat rz(const  typename core::math::coefficientTypeOfType(TMat) & coeff){
  TMat res;
  rz(res, coeff);
  return res;
}


template<typename MatA, typename MatB, typename Elem>
inline bool matricesEqual(const MatA & a, const MatB & b, const Elem & eps){
  bool result = false;
  OperationMatrixEquals<MatA, MatB, Elem>::operation(result, a, b, eps);
  return result;
}

template<typename MatA, typename Vec>
inline void crossProductMatrix(MatA & a_star, const Vec& a){
  VectorToCrossProductMatrix<MatA, Vec>::operation(a_star, a);
}

template<typename MatA, typename Vec>
inline MatA crossProductMatrix(const Vec & a){
  MatA res;
  crossProductMatrix(res, a);
  return res;
}

template<typename MatA, typename MatB>
inline void negate(MatA & result, const MatB & orig){
  MatrixNegation<MatA, MatB>::operation(result, orig);
}

template<typename Vec3A, typename Vec3B, typename Vec3C>
inline void crossProduct(Vec3C & c, const Vec3A & a, const Vec3B & b){
  VectorCrossProduct<Vec3C, Vec3A, Vec3B>::operation(c, a, b);
}


template<typename MatType, typename BlockType>
inline void setBlock(MatType & target, const BlockType & source, size_t rowoffset, size_t coloffset){
  MatrixBlockAssign<BlockType, MatType>::operation(target, source, rowoffset, coloffset);
}

template<typename BlockType, typename MatType>
inline void getBlock(BlockType & block, const MatType & mat, size_t rowoffset, size_t coloffset){
  MatrixBlockExtract<BlockType, MatType>::operation(block, mat, rowoffset, coloffset);
}

template<typename T, typename TargetType>
inline void assign(TargetType & target, const T* source){
  MatrixAssignData<T, TargetType>::operation(target, source);
}

template<typename T, typename SourceType>
inline void copyTo(T * target, const SourceType & source){
  MatrixCopyToPointer<T, SourceType>::operation(target, source);
}
template<typename T, typename VectorTypeA, typename VectorTypeB>
inline void innerProduct(T & result, const VectorTypeA & a, const VectorTypeB & b){
  VectorInnerProduct<T, VectorTypeA, VectorTypeB>::operation(result, a, b);
}

template<typename Result, typename Mat>
inline void maximum(Result & result, const Mat & mat){
  MatrixMaximumElement<Result, Mat>::operation(result, mat);
}
template<typename Mat>
inline typename matrix_traits<Mat>::coefficient_type maximum(const Mat & mat){
  typename matrix_traits<Mat>::coefficient_type  result;
  maximum(result, mat);
  return result;
}

template<typename C, typename A, typename B>
inline void elementWiseMultiply(C & result, const A & a, const B& b){
  MatrixElementWiseMultiply<C, A, B>::operation(result, a, b);
}
template<typename C, typename A, typename B>
inline void elementWiseDivide(C & result, const A & a, const B& b){
  MatrixElementWiseDivide<C, A, B>::operation(result, a, b);
}
template<typename OutputMatrix, typename InputMatrix>
void padMatrix(OutputMatrix & out, const InputMatrix & inputMatrix, size_t rowsTop, size_t rowsBottom, size_t colsLeft, size_t colsRight){
  MatrixPad<OutputMatrix, InputMatrix>::operation(out, inputMatrix, rowsTop, rowsBottom, colsLeft, colsRight);
}

template<typename OutputMatrix, typename InputMatrix, typename KernelMatrix>
void convolve(OutputMatrix & result, const InputMatrix & original, const KernelMatrix & kernel){
  MatrixConvolution<OutputMatrix, InputMatrix, KernelMatrix, Real>::operation(result, original, kernel);
}

template<typename MatA, typename MatB, typename TCoeff = matrix_traits<MatA>::coefficient_type >
void compareMatrix(bool & result, const MatA & a, const MatB & b, TCoeff epsilon = EPSILON){
  MatrixCompare<MatA, MatB, TCoeff>::operation(result, a, b, epsilon);
}

template<typename OutputMatrix, typename InputMatrix, typename KernelMatrix>
void convolveSame(OutputMatrix & result, const InputMatrix & original, const KernelMatrix & kernel, int borderStrategy = 0){
  size_t rowsTop = kernel.rows() / 2 - 1 + kernel.rows() % 2;
  size_t rowsBottom = kernel.rows() / 2;
  size_t colsLeft = kernel.cols() / 2 - 1 + kernel.cols() % 2;
  size_t colsRight = kernel.cols() / 2;
  InputMatrix padded;
  padMatrix(padded, original, rowsTop, rowsBottom, colsLeft, colsRight);
  MatrixConvolution<OutputMatrix, InputMatrix, KernelMatrix, Real>::operation(result, padded, kernel);
}

template<typename OutputMatrix, typename InputMatrix, typename FilterFunction, typename FilterArgument>
void filter(OutputMatrix & result, const InputMatrix & original, FilterFunction filter, size_t width, size_t height){
  MatrixFilter<OutputMatrix, InputMatrix, FilterFunction, FilterArgument>::operation(result, original, filter, width, height);
}


template<typename C, typename A, typename B>
void subtract(C & c, const A& a, const B & b){
  MatrixSubtraction<C, A, B>::operation(c, a, b);
}
template<typename C, typename A, typename B>
void multiplyMatrix(C & c, const A& a, const B & b){
  MatrixMultiplication<Real, C, A, B>::operation(c, a, b);
}
template<typename C, typename A, typename B>
void multiplyScalar(C & c, const A& a, const B & s){
  MatrixScalarMultiplication<C, A, B>::operation(c, a, s);
}

template<typename A, typename B>
inline void cart2hom(A & hom, const B & car){
  MatrixCartesianToHomogenousCoordinates<A, B>::operation(hom, car);
}

template<typename A, typename B>
inline void hom2car(A & cart, const B & hom){
  MatrixHomogenousToCartesianCoordinates<A, B>::operation(cart, hom);
}

template<typename InvertedMatrixType, typename InputMatrixType>
void invertSymmetricMatrix(InvertedMatrixType & inv, const InputMatrixType & symmetricMatrix){
  MatrixInversion<InvertedMatrixType, InputMatrixType, MatrixProperty::Symmetric>::operation(inv, symmetricMatrix);
}
template<typename InvertedMatrixType, typename InputMatrixType>
void invertMatrix(InvertedMatrixType & inv, const InputMatrixType & matrix){
  MatrixInversion<InvertedMatrixType, InputMatrixType, MatrixProperty::Symmetric>::operation(inv, matrix);
}

template<typename TAssignee, typename TValue>
inline bool assignElement(TAssignee & assignee, size_t i, size_t j, const TValue & value){
  return MatrixElementAssignment<TAssignee, TValue>::operation(assignee, i, j, value);
}


/// axis needs to be a normalized unit vector
template<typename TEuler, typename TAxis>
void axisAngleToEulerParameters(TEuler & p, const TAxis & u, const typename matrix_traits<TAxis>::coefficient_type & theta){
  using namespace core::math;
  typedef typename matrix_traits<TAxis>::coefficient_type coeff;
  static const coeff half = 0.5;
  auto theta2 = theta * half;

  auto p0 = coefficient(p, 0, 0) = scalar::cosine(theta2);
  auto p1 = coefficient(p, 1, 0) = scalar::sine(theta2) * coefficient(u, 0, 0);
  auto p2 = coefficient(p, 2, 0) = scalar::sine(theta2) * coefficient(u, 1, 0);
  auto p3 = coefficient(p, 3, 0) = scalar::sine(theta2) * coefficient(u, 2, 0);

  assert(p0*p0 + p1*p1 + p2*p2 + p3 + p3 == 1);
}


/// returns unit x if theta is 0
template<typename TAxis, typename TEuler>
void eulerToAxisAngle(TAxis & u, typename matrix_traits<TAxis>::coefficient_type & theta, const TEuler & p){
  using namespace core::math;
  auto & p0 = coefficient(p, 0, 0);
  auto & p1 = coefficient(p, 1, 0);
  auto & p2 = coefficient(p, 2, 0);
  auto & p3 = coefficient(p, 3, 0);
  auto  theta = arcusSine(p0) * 2.0;

  if (theta == 0) {
    ux = 1.0;
    uy = 0.0;
    uz = 0.0;
  }
  auto s = sine(theta*0.5);

  auto invs = 1 / s;
  auto ux = p0 * invs;
  auto uy = p1 * invs;
  auto uz = p2 * invs;

}

template<typename TMat, typename TEuler>
void eulerRotation(TMat & E, const TEuler & p){

  using namespace core::math;
  typedef typename coefficientTypeOfType(E) coeff;

  assert(cols(p) == 1);
  assert(rows(p) == 4);
  assert(cols(E) == 3);
  assert(rows(E) == 3);
  assert(isScalarMatrix<coeff>());

  static const coeff _2 = 2.0;
  static const coeff _05 = 0.5;
  auto & p0 = coefficient(p, 0, 0);
  auto & p1 = coefficient(p, 1, 0);
  auto & p2 = coefficient(p, 2, 0);
  auto & p3 = coefficient(p, 3, 0);
  auto p0p0 = multiply(p0, p0);
  auto p0p1 = multiply(p0, p1);
  auto p0p2 = multiply(p0, p2);
  auto p1p1 = multiply(p1, p1);
  auto p1p2 = multiply(p1, p2);
  auto p2p2 = multiply(p2, p2);
  coefficient(E, 0, 0) = p0p0 + p1p1 - _05;
  coefficient(E, 0, 1) = p1p2 + p0p3;
  coefficient(E, 0, 2) = p1p3 - p0p2;
  coefficient(E, 1, 0) = p1p2 - p0p3;
  coefficient(E, 1, 1) = p0p0 + p2p2 - _05;
  coefficient(E, 1, 2) = p2p3 + p0p1;
  coefficient(E, 2, 0) = p1p3 + p0p2;
  coefficient(E, 2, 1) = p2p3 - p0p1;
  coefficient(E, 2, 2) = p0p0 + p3p3 - _05;
  matrix::elementWiseMultiply(E, E, _2);
}

template<typename TEulerDot, typename TEuler, typename TOmega>
void eulerAccelerations(TEulerDot & pDot, const TEuler & p, const TOmega & omega){
  /*static_assert(std::is_same<
  typename matrix_traits<TEulerDot>::coefficient_type,
  typename matrix_traits<TEuler>::coefficient_type
  >::value
  &&
  std::is_same<
  typename matrix_traits<TOmega>::coefficient_type,
  typename matrix_traits<TEuler>::coefficient_type
  >::value
  )*/
  using namespace core::math;
  typedef typename matrix_traits<TEuler>::coefficient_type coeff;

  auto & p0 = coefficient(p, 0, 0);
  auto & p1 = coefficient(p, 1, 0);
  auto & p2 = coefficient(p, 2, 0);
  auto & p3 = coefficient(p, 3, 0);
  static const coeff _05 = 0.5;
  coeff P[4][3] = { { -p0, -p2, -p3 }, { p0, -p3, p2 }, { p3, p0, -p1 }, { -p2, p1, p0 } };

  matrix::elementWiseMultiply(P, P, _05);
  multiply(pDot, P, omega);
}

template<typename TMat, typename... TArgs>
void setUpperTriangleMatrix(TMat & mat, TArgs &&...  args){
  using namespace core::math;
  const static size_t s = std::tuple_size<std::tuple<TArgs...>>::value;
  assert(cols(mat) == rows(mat));
  auto n = cols(mat);
  assert(s == (n*(n + 1) / 2));

  typedef typename matrix_traits<TMat>::coefficient_type coeff;
  coeff elements[s] = { args... };
  static const coeff zero = 0.0;
  size_t k = 0;
  for (size_t i = 0; i < n; i++){
    for (size_t j = 0; j < n; j++){
      if (j >= i) coefficient(mat, i, j) = elements[k++];
      else coefficient(mat, i, j) = zero;
    }
  }
}
template<typename TMat, typename... TArgs>
TMat upperTriangleMatrix(TArgs && ... args){
  TMat res;
  using namespace core::math;
  const static size_t s = std::tuple_size<std::tuple<TArgs...>>::value;

  auto n = (1 + (int)sqrt(2 + 4 * s)) / 2;
  auto s2 = (n*(n + 1) / 2);

  if (s2 != s) throw std::exception();


  ensureMatrixDimension(res, n, n);
  setUpperTriangleMatrix(res, args...);
  return res;
}

template<typename TMat, typename... TArgs>
void setSymmetricMatrix(TMat & mat, TArgs && ... args){
  using namespace core::math;
  const static size_t s = std::tuple_size<std::tuple<TArgs...>>::value;
  assert(cols(mat) == rows(mat));
  auto n = cols(mat);
  assert(s == (n*(n + 1) / 2));

  typedef typename matrix_traits<TMat>::coefficient_type coeff;
  coeff elements[s] = { args... };
  size_t k = 0;
  for (size_t i = 0; i < n; i++){
    for (size_t j = i; j < n; j++){
      coefficient(mat, i, j) = coefficient(mat, j, i) = elements[k++];
    }
  }
}
template<typename TMat, typename...TArgs>
TMat symmetricMatrix(TArgs && ...args){
  TMat res;
  using namespace core::math;
  const static size_t s = std::tuple_size<std::tuple<TArgs...>>::value;
  auto s3 = s;
  auto n = (1 + (int)sqrt(2 + 4 * s)) / 2;
  auto s2 = (n*(n + 1) / 2);

  if (s2 != s) throw std::exception();


  ensureMatrixDimension(res, n, n);
  setSymmetricMatrix(res, args...);
  return res;
}
template<typename TMat, typename... TArgs>
void setLowerTriangleMatrix(TMat & mat, TArgs &&...  args){
  using namespace core::math;
  const static size_t s = std::tuple_size<std::tuple<TArgs...>>::value;
  assert(cols(mat) == rows(mat));
  auto n = cols(mat);
  assert(s == (n*(n + 1) / 2));

  typedef typename matrix_traits<TMat>::coefficient_type coeff;
  coeff elements[s] = { args... };
  static const coeff zero = 0.0;
  size_t k = 0;
  for (size_t i = 0; i < n; i++){
    for (size_t j = 0; j < n; j++){
      if (j <= i)coefficient(mat, i, j) = elements[k++];
      else coefficient(mat, i, j) = zero;
    }
  }
}
template<typename TMat, typename... TArgs>
TMat lowerTriangleMatrix(TArgs && ... args){
  TMat res;
  using namespace core::math;
  const static size_t s = std::tuple_size<std::tuple<TArgs...>>::value;

  auto n = (1 + (int)sqrt(2 + 4 * s)) / 2;
  auto s2 = (n*(n + 1) / 2);

  if (s2 != s) throw std::exception();

  ensureMatrixDimension(res, n, n);
  setLowerTriangleMatrix(res, args...);
  return res;
}


NS_END(CORE_MATH_NAMESPACE, matrix)

