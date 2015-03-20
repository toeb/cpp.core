#pragma once

#include <math.matrix.dslib/StaticMatrix.h>
namespace nspace{
#define USE_SPECIALIZATION
#ifdef USE_SPECIALIZATION

  
  template<typename T,int N, int M> class MatrixColumnTraits<matrix2::StaticMatrix<T,N,M> >{public: static const DimensionTraits Traits = Fixed; };
  template<typename T,int N, int M> class MatrixRowTraits<matrix2::StaticMatrix<T,N,M> >{public: static const DimensionTraits Traits = Fixed; };
  template<typename T,int N, int M> class MatrixCoefficientType<matrix2::StaticMatrix<T,N,M> >{public: typedef T Type;};

  /**
  * \brief specialization for the 3x3 Matrix Product
  *
  * \return .
  */
  template<>
  inline void MatrixMultiplication<Real,matrix2::StaticMatrix<Real,3,3> ,matrix2::StaticMatrix<Real,3,3> ,matrix2::StaticMatrix<Real,3,3> >::operation(
    matrix2::StaticMatrix<Real,3,3> &mC,const matrix2::StaticMatrix<Real,3,3> &mA,const matrix2::StaticMatrix<Real,3,3> &mB
    ){
      const Real * a=mA.data();
      const Real * b=mB.data();
      Real * c=mC.data();
      c[0]= a[0]*b[0]+a[1]*b[3]+a[2]*b[6];
      c[1]= a[0]*b[1]+a[1]*b[4]+a[2]*b[7];
      c[2]= a[0]*b[2]+a[1]*b[5]+a[2]*b[8];
      c[3]= a[3]*b[0]+a[4]*b[3]+a[5]*b[6];
      c[4]= a[3]*b[1]+a[4]*b[4]+a[5]*b[7];
      c[5]= a[3]*b[2]+a[4]*b[5]+a[5]*b[8];
      c[6]= a[6]*b[0]+a[7]*b[3]+a[8]*b[6];
      c[7]= a[6]*b[1]+a[7]*b[4]+a[8]*b[7];
      c[8]= a[6]*b[2]+a[7]*b[5]+a[8]*b[8];
  }

  /**
  * \brief specialization for the 3D MatrixVector Product
  *
  * \return .
  */
  template<>
  inline void MatrixMultiplication<Real,matrix2::StaticMatrix<Real,3,1> ,matrix2::StaticMatrix<Real,3,3> ,matrix2::StaticMatrix<Real,3,1> >::operation(
    matrix2::StaticMatrix<Real,3,1> &mC,const matrix2::StaticMatrix<Real,3,3> &mA,const matrix2::StaticMatrix<Real,3,1> &mB
    ){
      const Real * a=mA.data();
      const Real * b=mB.data();
      Real * c=mC.data();
      c[0]= a[0]*b[0]+a[3]*b[1]+a[6]*b[2];
      c[1]= a[1]*b[0]+a[4]*b[1]+a[7]*b[2];
      c[2]= a[2]*b[0]+a[5]*b[1]+a[8]*b[2];
  };

  template<typename T, int n, int m>
  class MatrixScalarMultiplication<matrix2::StaticMatrix<T,n,m>,matrix2::StaticMatrix<T,n,m>, T >{
  public:
    static inline void operation(matrix2::StaticMatrix<T,n,m> & product, const matrix2::StaticMatrix<T,n,m>  & aMat, const T & d){
      const Real * a = aMat.data();
      Real * p = product.data();

      for(int i=0; i < n*m; i++){
        p[i] = a[i]*d;
      }
    }
  };

  template<typename T>
  class MatrixScalarMultiplication<matrix2::StaticMatrix<T,3,3>,matrix2::StaticMatrix<T,3,3>, T >{
  public:
    static inline void operation(matrix2::StaticMatrix<T,3,3> & product, const matrix2::StaticMatrix<T,3,3>  & aMat, const T & d){
      const Real * a = aMat.data();
      Real * p = product.data();
      p[0] = a[0]*d;
      p[1] = a[1]*d;
      p[2] = a[2]*d;
      p[3] = a[3]*d;
      p[4] = a[4]*d;
      p[5] = a[5]*d;
      p[6] = a[6]*d;
      p[7] = a[7]*d;
      p[8] = a[8]*d;
    }
  };

  template<typename T>
  class MatrixScalarMultiplication<matrix2::StaticMatrix<T,3,1>,matrix2::StaticMatrix<T,3,1>, T >{
  public:
    static inline void operation(matrix2::StaticMatrix<T,3,1> & product, const matrix2::StaticMatrix<T,3,1>  & aMat, const T & d){
      const Real * a = aMat.data();
      Real * p = product.data();
      p[0] = a[0]*d;
      p[1] = a[1]*d;
      p[2] = a[2]*d;
    }
  };

  template<typename T, int rows, int cols>
  class MatrixAddition<matrix2::StaticMatrix<T,rows,cols>, matrix2::StaticMatrix<T,rows,cols>,matrix2::StaticMatrix<T,rows,cols> >{
  public:
    static inline void operation(matrix2::StaticMatrix<T,rows,cols> & cMat, const matrix2::StaticMatrix<T,rows,cols> & aMat, const matrix2::StaticMatrix<T,rows,cols> & bMat){
      int size = rows*cols;
      const Real * a = aMat.data();
      const Real * b = bMat.data();
      Real * c = cMat.data();
      for(int i=0; i < size; i++){
        c[i]=a[i]+b[i];
      }
    }
  };

  template<typename T>
  class MatrixAddition<matrix2::StaticMatrix<T,3,3>, matrix2::StaticMatrix<T,3,3>,matrix2::StaticMatrix<T,3,3> >{
  public:
    static inline void operation(matrix2::StaticMatrix<T,3,3> & cMat, const matrix2::StaticMatrix<T,3,3> & aMat, const matrix2::StaticMatrix<T,3,3> & bMat){
      const Real * a = aMat.data();
      const Real * b = bMat.data();
      Real * c = cMat.data();
      c[0] = a[0]+b[0];
      c[1] = a[1]+b[1];
      c[2] = a[2]+b[2];
      c[3] = a[3]+b[3];
      c[4] = a[4]+b[4];
      c[5] = a[5]+b[5];
      c[6] = a[6]+b[6];
      c[7] = a[7]+b[7];
      c[8] = a[8]+b[8];
    }
  };
  template<typename T>
  class MatrixSubtraction<matrix2::StaticMatrix<T,3,3>, matrix2::StaticMatrix<T,3,3>,matrix2::StaticMatrix<T,3,3> >{
  public:
    static inline void operation(matrix2::StaticMatrix<T,3,3> & cMat, const matrix2::StaticMatrix<T,3,3> & aMat, const matrix2::StaticMatrix<T,3,3> & bMat){
      const Real * a = aMat.data();
      const Real * b = bMat.data();
      Real * c = cMat.data();
      c[0] = a[0]-b[0];
      c[1] = a[1]-b[1];
      c[2] = a[2]-b[2];
      c[3] = a[3]-b[3];
      c[4] = a[4]-b[4];
      c[5] = a[5]-b[5];
      c[6] = a[6]-b[6];
      c[7] = a[7]-b[7];
      c[8] = a[8]-b[8];
    }
  };

  template<typename T>
  class MatrixAddition<matrix2::StaticMatrix<T,3,1>, matrix2::StaticMatrix<T,3,1>,matrix2::StaticMatrix<T,3,1> >{
  public:
    static inline void operation(matrix2::StaticMatrix<T,3,1> & cMat, const matrix2::StaticMatrix<T,3,1> & aMat, const matrix2::StaticMatrix<T,3,1> & bMat){
      const Real * a = aMat.data();
      const Real * b = bMat.data();
      Real * c = cMat.data();
      c[0] = a[0]+b[0];
      c[1] = a[1]+b[1];
      c[2] = a[2]+b[2];
    }
  };
  template<typename T>
  class MatrixSubtraction<matrix2::StaticMatrix<T,3,1>, matrix2::StaticMatrix<T,3,1>,matrix2::StaticMatrix<T,3,1> >{
  public:
    static inline void operation(matrix2::StaticMatrix<T,3,1> & cMat, const matrix2::StaticMatrix<T,3,1> & aMat, const matrix2::StaticMatrix<T,3,1> & bMat){
      const Real * a = aMat.data();
      const Real * b = bMat.data();
      Real * c = cMat.data();
      c[0] = a[0]-b[0];
      c[1] = a[1]-b[1];
      c[2] = a[2]-b[2];
    }
  };
  
  
  template<typename T, int rows, int cols>  
  class OperationMatrixAssign<matrix2::StaticMatrix<T,rows,cols>,matrix2::StaticMatrix<T,rows,cols> >{
  public:    
    static inline bool operation(matrix2::StaticMatrix<T,rows,cols> &  lhs, const matrix2::StaticMatrix<T,rows,cols> & rhs){
      memcpy(lhs.data(),rhs.data(),lhs.dataByteSize());     
      return true;
    }
  };

  
  template<typename T>  
  class OperationMatrixAssign<matrix2::StaticMatrix<T,3,1> ,matrix2::StaticMatrix<T,3,1> >{
  public:    
    static inline bool operation(matrix2::StaticMatrix<T,3,1> &  lhs, const matrix2::StaticMatrix<T,3,1> & rhs){
      memcpy(lhs.data(),rhs.data(),lhs.dataByteSize());     
      return true;
    }
  };
  
  template<typename T>  
  class OperationMatrixAssign<matrix2::StaticMatrix<T,3,3> , matrix2::StaticMatrix<T,3,3>>{
  public:    
    static inline bool operation(matrix2::StaticMatrix<T,3,3> &  lhs, const matrix2::StaticMatrix<T,3,3> & rhs){      
      Real * a = lhs.data();
      const Real * b = rhs.data();
      a[0]=b[0];
      a[1]=b[1];
      a[2]=b[2];
      a[3]=b[3];
      a[4]=b[4];
      a[5]=b[5];
      a[6]=b[6];
      a[7]=b[7];
      a[8]=b[8];
      return true;
    }
  };

#endif
}
