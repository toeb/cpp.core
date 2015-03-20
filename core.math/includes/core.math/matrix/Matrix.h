#pragma once

#include <core.math/core.math.h>

#include <iostream>
#include <core.math/matrix/MatrixOperations.h>
NS_BEGIN(CORE_MATH_NAMESPACE,matrix)
// Matrix is a base class for all matrices.  it has a very slim interface
template<typename T, typename IndexType = int, typename SizeType = int>
class Matrix
{
public:
  typedef IndexType Index;
  typedef SizeType Size;
public:
  //default constructor
  Matrix();
  virtual ~Matrix(){}
  // converts this matrix to a matrix of MatrixType
  template<typename MatrixType> operator MatrixType()const;
  //  prints this matrix
  virtual void toStream(std::ostream & s)const;
  // resizes this matrix (returns false if matrix could not be resized to the requested dimension)
  virtual bool resize(Index r, Index c);
  // returns the number of elements of this matrix
  virtual inline Size size()const;

  // returns the number of rows
  virtual Size rows() const = 0;
  // returns the number of columns
  virtual Size cols() const = 0;
  // returns a reference to the element at i,j
  virtual T& operator () (Index i, Index j) = 0;
  // returns a const reference to the element at i,j
  virtual const T& operator () (Index i, Index j) const = 0;
};

template<typename T, typename IndexType, typename SizeType>
Matrix<T, IndexType, SizeType>::Matrix(){}

template<typename T, typename IndexType, typename SizeType>
template<typename MatrixType>
Matrix<T, IndexType, SizeType>::operator MatrixType()const{
  MatrixType result;
  assignMatrix(result, *this);
  return result;
}


template<typename T, typename IndexType, typename SizeType>
void Matrix<T, IndexType, SizeType>::toStream(std::ostream & s)const{
  for (Index i = 0; i < rows(); i++){
    for (Index j = 0; j < cols(); j++){
      s << (*this)(i, j) << ", ";
    }
    s << std::endl;
  }
}

template<typename T, typename IndexType, typename SizeType>
bool Matrix<T, IndexType, SizeType>::resize(Index r, Index c){
  if (r == rows() && c == cols())return true;
  return false;
}

template<typename T, typename IndexType, typename SizeType>
SizeType Matrix<T, IndexType, SizeType>::size()const{
  return rows()*cols();
}


template<typename T, typename IndexType, typename SizeType>
class MatrixCoefficientType < Matrix<T, IndexType, SizeType> > { public: typedef T Type; };

template<typename T, typename IndexType, typename SizeType>
class MatrixIndexType < Matrix<T, IndexType, SizeType> > { public: typedef IndexType Type; };

NS_END(CORE_MATH_NAMESPACE,matrix)
