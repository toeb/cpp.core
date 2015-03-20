#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/MatrixOperations.h>
#include <core.math/matrix/VectorOperations.h>
NS_BEGIN(CORE_MATH_NAMESPACE, matrix, dslib)
template<typename T, int rows, int cols>
inline std::ostream &  operator<<(std::ostream &  s, const StaticMatrix<T, rows, cols> & a){
  for (int i = 0; i < a.rows(); i++){
    for (int j = 0; j < a.cols(); j++){
      s << a(i, j) << ", ";
    }
    s << "\n";
  }
  return s;
}
template<typename T, int rows, int cols>
inline StaticMatrix<T, rows, cols> operator+(const StaticMatrix<T, rows, cols> & a, const StaticMatrix<T, rows, cols> & b){
  StaticMatrix<T, rows, cols> c;
  MatrixAddition<StaticMatrix<T, rows, cols>, StaticMatrix<T, rows, cols>, StaticMatrix<T, rows, cols> >::operation(c, a, b);
  return c;
}

template<typename T>
inline StaticMatrix<T, 3, 1> operator^(const StaticMatrix<T, 3, 1> & a, const StaticMatrix<T, 3, 1> & b){
  StaticMatrix<T, 3, 1> c;
  VectorCrossProduct<StaticMatrix<T, 3, 1>, StaticMatrix<T, 3, 1>, StaticMatrix<T, 3, 1>>::operation(c, a, b);
  //VectorOperations<T>::crossProduct(c,a,b);
  return c;
}

template<typename T, int dimension>
inline T operator*(const StaticMatrix<T, dimension, 1> & a, const StaticMatrix<T, dimension, 1> & b){
  T result;
  VectorInnerProduct<StaticMatrix<T, dimension, 1>, StaticMatrix<T, dimension, 1>, StaticMatrix<T, dimension, 1> >::operation(result, a, b);
  //VectorOperations<T>::innerProduct(result,a,b);
  return result;
}

template<typename T, int rows, int cols>
inline  StaticMatrix<T, rows, cols> operator-(const StaticMatrix<T, rows, cols> & a, const StaticMatrix<T, rows, cols> & b){
  StaticMatrix<T, rows, cols> c;
  MatrixSubtraction<StaticMatrix<T, rows, cols>, StaticMatrix<T, rows, cols>, StaticMatrix<T, rows, cols>>::operation(c, a, b);
  return c;
}
template<typename T, int rows, int cols>
inline  StaticMatrix<T, rows, cols> operator*(const StaticMatrix<T, rows, cols> & a, const T & d){
  StaticMatrix<T, rows, cols> c;
  MatrixScalarMultiplication<StaticMatrix<T, rows, cols>, StaticMatrix<T, rows, cols>, T>::operation(c, a, d);
  return c;
}
template<typename T, int rows, int cols>
inline  StaticMatrix<T, rows, cols> operator/(const StaticMatrix<T, rows, cols> & a, const T & d){
  StaticMatrix<T, rows, cols> c;

  //MatrixOperations<T>::divideScalar(c,a,d);
  return c;
}
template<typename T, int rows, int cols>
inline  StaticMatrix<T, rows, cols> operator*(const T & d, const StaticMatrix<T, rows, cols> & a){
  StaticMatrix<T, rows, cols> c;
  MatrixScalarMultiplication<StaticMatrix<T, rows, cols>, StaticMatrix<T, rows, cols>, T>::operation(c, a, d);
  return c;
}
template<typename T, int outerRows, int outerCols, int innerDimension>
inline StaticMatrix<T, outerRows, outerCols> operator * (const StaticMatrix<T, outerRows, innerDimension> & a, const StaticMatrix<T, innerDimension, outerCols> & b){
  StaticMatrix<T, outerRows, outerCols> c;
  MatrixMultiplication<T, StaticMatrix<T, outerRows, outerCols>, StaticMatrix<T, outerRows, innerDimension>, StaticMatrix<T, innerDimension, outerCols>>::operation(c, a, b);
  return c;
};

template<typename T, int rows, int cols>
inline StaticMatrix<T, rows, cols> & operator +=(StaticMatrix<T, rows, cols> & a, const StaticMatrix<T, rows, cols> & b){
  MatrixAddition<StaticMatrix<T, rows, cols>, StaticMatrix<T, rows, cols>, StaticMatrix<T, rows, cols> >::operation(a, a, b);
  return a;
}
template<typename T, int rows, int cols>
inline StaticMatrix<T, rows, cols> & operator -=(StaticMatrix<T, rows, cols> & a, const StaticMatrix<T, rows, cols> & b){
  MatrixSubtraction<StaticMatrix<T, rows, cols>, StaticMatrix<T, rows, cols>, StaticMatrix<T, rows, cols>>::operation(a, a, b);
  return a;
}
template<typename T, int rows, int cols>
inline StaticMatrix<T, rows, cols> & operator *=(StaticMatrix<T, rows, cols> & a, const T & d){
  MatrixScalarMultiplication<StaticMatrix<T, rows, cols>, StaticMatrix<T, rows, cols>, T>::operation(a, a, d);
  return a;
}
template<typename T, int rows, int cols>
inline StaticMatrix<T, rows, cols> & operator /=(StaticMatrix<T, rows, cols> & a, const T & d){
  MatrixScalarDivisionInPlace<StaticMatrix<T, rows, cols>, StaticMatrix<T, rows, cols>, T>::operation(a, a, d);
  return a;
}

template<typename T, int rows, int cols>
inline bool operator == (const StaticMatrix<T, rows, cols> & a, const StaticMatrix<T, rows, cols> & b){
  return matricesEqual<StaticMatrix<T, rows, cols>, StaticMatrix<T, rows, cols>, T>(a, b, T(0));
}
NS_END(CORE_MATH_NAMESPACE, matrix, dslib)
