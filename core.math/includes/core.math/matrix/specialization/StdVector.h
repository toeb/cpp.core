#pragma once


//#include <map>
/*
#include <core.math/core.math.h>
NS_BEGIN(CORE_MATH_NAMESPACE)
template<typename T>
class MatrixCoefficientType<std::pair<T,T> >{public: typedef T Type;};

template<typename T>
class MatrixIndexType<std::pair<T,T> >{public: typedef size_t Type;};

template<typename T>
class OperationMatrixCoefficientAccess<std::pair<T,T> >{
public:
  typedef std::pair<T,T> MatrixType;
   static inline typename coefficientTypeOfType(typename MatrixType) & operation(MatrixType & matrix,IndexArgument(typename MatrixType)  i,IndexArgument(typename MatrixType)  j){
      if(i==0)return matrix.first();
      if(i==1)return matrix.second();
      throw "index out of bounds";
    }
    static inline typename coefficientTypeOfType(MatrixType) operation(const MatrixType &matrix,IndexArgument(MatrixType) i, IndexArgument(MatrixType)  j){
      if(i==0)return matrix.first();
      if(i==1)return matrix.second();
      throw "index out of bounds";
    }
NS_END(CORE_MATH_NAMESPACE)
*/