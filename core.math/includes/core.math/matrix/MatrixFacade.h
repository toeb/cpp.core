#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/Matrix.h>

NS_BEGIN(CORE_MATH_NAMESPACE, matrix)
template<typename T>
class IMatrixData{
public:
  typedef unsigned int Index;
  typedef T Coefficient;
  virtual Coefficient & operator()(const Index & i, const Index & j) = 0;
  virtual Coefficient operator()(const Index & i, const Index & j)const = 0;
  virtual Index rows()const = 0;
  virtual Index cols()const = 0;

};


template <typename T>
class IVectorData{
public:
  typedef unsigned int Index;
  typedef T Coefficient;
  virtual Coefficient & operator()(const unsigned int i) = 0;
  virtual Coefficient operator()(const Index & i)const = 0;
  virtual Index size()const = 0;
};


template<typename MatrixType>
class MatrixFacade : public Matrix < typename coefficientTypeOfType(MatrixType), typename indexTypeOfType(MatrixType), typename indexTypeOfType(MatrixType) > {
private:
  MatrixType & matrix;
public:
  inline MatrixFacade(MatrixType & matrix) :matrix(matrix){}
  typedef typename indexTypeOfType(MatrixType) Index;
  typedef typename coefficientTypeOfType(MatrixType) Coefficient;
  inline Coefficient & operator()(Index  i, Index  j){
    return coefficient(matrix, i, j);
  }
  inline const Coefficient & operator()(Index  i, Index  j)const{
    // /todo cconst casts are bad.
    return coefficient(const_cast<MatrixType&>(matrix), i, j);
  }

  inline Index rows()const{ return nspace::rows(matrix); }
  inline Index cols()const{ return nspace::cols(matrix); }
};

class ObservableMatrix{

};

template<typename VectorType>
class VectorFacade :public IVectorData < typename coefficientTypeOfType(VectorType) > {
private:
  VectorType & vector;
public:
  inline  VectorFacade(VectorType & vector) :vector(vector){}
  CoefficientAndIndexAliasForType(VectorType);
  inline  Coefficient & operator()(const Index & i){
    return coefficient(vector, i);
  }
  inline  Coefficient operator()(const Index & i)const{
    return coefficient(vector, i);
  }
  inline Coefficient & operator()(const Index & i, const Index & j){
    return coefficient(vector, i);
  }
  inline Coefficient operator()(const Index & i, const Index & j)const{
    return coefficient(vector, i);
  }
  inline Index size()const{ return rows(vector); }
  inline Index rows()const{ return nspace::rows(vector); }
  inline Index cols()const{ return nspace::cols(vector); }
};

class ObservableVector{

};



template<typename MatrixType>
auto wrapMatrix(MatrixType & mat)->MatrixFacade < MatrixType > { return MatrixFacade<MatrixType>(mat); }
template<typename VectorType>
auto wrapVector(VectorType & vector)->VectorFacade < VectorType > { return VectorFacade<VectorType>(vector); }


NS_END(CORE_MATH_NAMESPACE, matrix)