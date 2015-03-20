#pragma once

#include <math.matrix/operations/VectorCrossProduct.h>
#include <math.matrix.dslib/StaticMatrix.h>

namespace nspace{
  //specialization of crossproduct for statixmatrix31
  template<typename T>
  class VectorCrossProduct<nspace::matrix2::StaticMatrix<T,3,1>, nspace::matrix2::StaticMatrix<T,3,1> ,nspace::matrix2::StaticMatrix<T,3,1> >{
  public:
    inline static void operation(nspace::matrix2::StaticMatrix<T,3,1> & cv,const  nspace::matrix2::StaticMatrix<T,3,1> & av,const nspace::matrix2::StaticMatrix<T,3,1> & bv){
      // get data pointers
      const T * a = av.data();
      const T* b = bv.data();
      T * c = cv.data();
      // access elements directly
      c[0] = a[1]*b[2]-a[2]*b[1];
      c[1] = a[2]*b[0]-a[0]*b[2];
      c[2] = a[0]*b[1]-a[1]*b[0];
    }
  };
}