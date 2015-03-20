#pragma once

#include <math.matrix.dslib/DynamicMatrix.h>

namespace nspace{
  namespace matrix2{
    template<typename T>
    inline DynamicMatrix<T>  operator * (const DynamicMatrix<T> & a, const DynamicMatrix<T> & b){
      DynamicMatrix<T> result;
      resize(result,a.rows(),b.cols());
      MatrixMultiplication<T,DynamicMatrix<T>,DynamicMatrix<T>,DynamicMatrix<T>>::operation(result,a,b);
      return result;
    }
    template<typename T>
    inline DynamicMatrix<T>  operator *= (DynamicMatrix<T> & a, const T & b){
      MatrixScalarMultiplication<DynamicMatrix<T>,DynamicMatrix<T>,T>::operation(a,a,b);
      return a;
    }
    template<typename T>
    inline DynamicMatrix<T>  operator * (const DynamicMatrix<T> & a, const T & b){
      DynamicMatrix<T> result;
      resize(result,a);
      MatrixScalarMultiplication<DynamicMatrix<T>,DynamicMatrix<T>,T>::operation(result,a,b);
      return result;
    }
    template<typename T>
    inline DynamicMatrix<T>  operator / (const DynamicMatrix<T> & a, const T & b){
      DynamicMatrix<T> result;
      resize(result,a);
      MatrixScalarDivisionInPlace<DynamicMatrix<T>,DynamicMatrix<T>, T>::operation(result,a,b);
      return result;
    }
    template<typename T>
    inline DynamicMatrix<T>  operator * (const T & b,const DynamicMatrix<T> & a){
      DynamicMatrix<T> result;
      resize(result,a);
      MatrixScalarMultiplication<DynamicMatrix<T>,DynamicMatrix<T>,T>::operation(result,a,b);
      return result;
    }
    template<typename T>
    inline DynamicMatrix<T> & operator += (DynamicMatrix<T> & a, const DynamicMatrix<T> & b){
      MatrixAddition<DynamicMatrix<T>,DynamicMatrix<T>, DynamicMatrix<T> >::operation(a,a,b);
      return a;
    }
    template<typename T>
    inline DynamicMatrix<T>  operator + (const DynamicMatrix<T> & a, const DynamicMatrix<T> & b){
      DynamicMatrix<T> result;
      resize(result,a);
      MatrixAddition<DynamicMatrix<T>,DynamicMatrix<T>, DynamicMatrix<T> >::operation(result,a,b);
      return result;
    }
    template<typename T>
    inline DynamicMatrix<T>  operator - (const DynamicMatrix<T> & a, const DynamicMatrix<T> & b){
      DynamicMatrix<T> result;
      resize(result,a);
      MatrixSubtraction<DynamicMatrix<T>,DynamicMatrix<T>,DynamicMatrix<T> >::operation(result,a,b);
      return result;
    }

    template<typename T>
    inline DynamicMatrix<T> & operator -= (DynamicMatrix<T> & a, const DynamicMatrix<T> & b){
      MatrixSubtraction<DynamicMatrix<T>,DynamicMatrix<T>,DynamicMatrix<T> >::operation(a,a,b);
    }

    template<typename T>
    inline DynamicMatrix<T> & operator += (DynamicMatrix<T> & a, const T& b){      
      MatrixAdditionConstant<DynamicMatrix<T>,DynamicMatrix<T>, T>::operation(a,a,b);
      return a;
    }
    template<typename T>
    inline DynamicMatrix<T> operator +(const DynamicMatrix<T> & a, const T & b){
      DynamicMatrix<T> result;
      resize(result,a);
      MatrixAdditionConstant<DynamicMatrix<T>,DynamicMatrix<T>, T>::operation(result,a,b);
      return result;
    }

    template<typename T>
    inline DynamicMatrix<T> & operator /= (DynamicMatrix<T> & a,const T & d){
      MatrixScalarDivisionInPlace<DynamicMatrix<T>, DynamicMatrix<T>,T>::operation(a,a,d);
      return a;
    }
    template<typename T>
    inline DynamicMatrix<T> & operator -=(DynamicMatrix<T> & a, const T & b){
      MatrixSubtractionConstant<DynamicMatrix<T>,DynamicMatrix<T>,T>::operation(a,a,b);
      return a;
    }

    template<typename T>
    inline DynamicMatrix<T>  operator -(const DynamicMatrix<T> & a, const T & b){
      DynamicMatrix<T> c;
      resize(c,a);
      MatrixSubtractionConstant<DynamicMatrix<T>,DynamicMatrix<T>,T>::operation(c,a,b);
      return c;
    }
  }
}