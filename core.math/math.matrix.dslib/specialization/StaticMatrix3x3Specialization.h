#pragma once
#include <math.matrix/MatrixOperations.h>
#include <math.matrix.dslib/StaticMatrix.h>
#include <math.scalar/operations.h>
namespace nspace{
  template<typename T>
  class MatrixCompare<matrix2::StaticMatrix<T,3,3>, matrix2::StaticMatrix<T,3,3>, Real>{
  public:
    static inline void operation(bool & result, const matrix2::StaticMatrix<T,3,3> & aMat, const matrix2::StaticMatrix<T,3,3> & bMat, const T eps){
      const T * a = aMat.data();
      const T * b = bMat.data();
      result = false;
      // compare every element
      {
        using namespace math::shorthands::scalar;
        if(absolute(a[0]-b[0]) >= eps)return;
        if(absolute(a[1]-b[1]) >= eps)return;
        if(absolute(a[2]-b[2]) >= eps)return;
        if(absolute(a[3]-b[3]) >= eps)return;
        if(absolute(a[4]-b[4]) >= eps)return;
        if(absolute(a[5]-b[5]) >= eps)return;
        if(absolute(a[6]-b[6]) >= eps)return;
        if(absolute(a[7]-b[7]) >= eps)return;
        if(absolute(a[8]-b[8]) >= eps)return;
      }
      result = true;
    }
  };

  template<typename T>
  class MatrixInversion<matrix2::StaticMatrix<T,3,3>, matrix2::StaticMatrix<T,3,3>, MatrixProperty::Symmetric >{
  public:
    static inline void operation(matrix2::StaticMatrix<T,3,3> & inv, const matrix2::StaticMatrix<T,3,3> & m){
      //original code from IBDS Jan Bender.  He mentioned were to find the algorithm used.... gotta update this sometime \todo
      // extract data and store it in registers (since matrix is symmetric m10 m20 and m21 are not needed)
      const T * mData = m.data();
      T m00 = mData[0];
      T m01 = mData[1];
      T m02 = mData[2];
      //T m10 = mData[3];
      T m11 = mData[4];
      T m12 = mData[5];
      //T m20 = mData[6];
      //T m21 = mData[7];
      T m22 = mData[8];

      //precalculate products
      T e2_df = m12*m12 - m11*m22;  // e^2 - d*f
      T bf = m01*m22;
      T ce = m02*m12;
      T c2 = m02*m02;
      T cd = m02*m11;
      T be = m01*m12;
      T af = m00*m22;
      T ae = m00*m12;
      T bc = m01*m02;
      T b2 = m01*m01;
      T ad = m00*m11;

      T Div = 1.0 / (c2*m11 + m01 * (bf - 2 * ce) +m00* e2_df  );

      T a = e2_df * Div;
      T b = (bf - ce) * Div;
      T c = (cd - be) * Div;
      T d = (c2 - af) * Div;
      T e = (ae - bc) * Div;
      T f = (b2 - ad) * Div;

      //set result
      T * data = inv.data();
      data[0] = a;
      data[1] = b;
      data[2] = c;

      data[3] = b;
      data[4] = d;
      data[5] = e;

      data[6] = c;
      data[7] = e;
      data[8] = f;
    }
    /*
    original code from ibds
    Real e2_df = m(1,2)*m(1,2) - m(1,1)*m(2,2);  // e^2 - d*f
    Real bf = m(0,1)*m(2,2);
    Real ce = m(0,2)*m(1,2);
    Real c2 = m(0,2)*m(0,2);
    Real cd = m(0,2)*m(1,1);
    Real be = m(0,1)*m(1,2);
    Real af = m(0,0)*m(2,2);
    Real ae = m(0,0)*m(1,2);
    Real bc = m(0,1)*m(0,2);
    Real b2 = m(0,1)*m(0,1);
    Real ad = m(0,0)*m(1,1);

    Real Div = 1.0 / (c2*m(1,1) + m(0,1) * (bf - 2 * ce) +m(0,0)* e2_df  );

    Real a = e2_df * Div;
    Real b = (bf - ce) * Div;
    Real c = (cd - be) * Div;
    Real d = (c2 - af) * Div;
    Real e = (ae - bc) * Div;
    Real f = (b2 - ad) * Div;
    m_inverted(0,0)=a;
    m_inverted(0,1)=b;
    m_inverted(0,2)=c;

    m_inverted(1,0)=b;
    m_inverted(1,1)=d;
    m_inverted(1,2)=e;

    m_inverted(2,0)=c;
    m_inverted(2,1)=e;
    m_inverted(2,2)=f;*/
  };
}
