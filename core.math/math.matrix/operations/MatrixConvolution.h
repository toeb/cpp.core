#pragma once
#include <config.h>
#include <math.matrix/operations/MatrixSetConstant.h>
namespace nspace{
  template< typename OutputMatrix, typename InputMatrix, typename KernelMatrix,typename T>
  class MatrixConvolution{
  public:
    static inline void operation(OutputMatrix & r, const InputMatrix & g, const KernelMatrix & kernel  ){
      uint fx = kernel.cols();
      uint fy = kernel.rows();
      uint rx = g.cols()-fx+1;
      uint ry = g.rows()-fy+1;

      KernelMatrix window;
      window.resize(fy,fx);
      r.resize(ry,rx);
      for(int i=0; i < ry; i++){
        for(int j=0; j < rx; j++){
          T sum=0.0;
          for(int l = 0; l < fy; l++){
            for(int k =0; k < fx; k++){
              sum = sum + g(i+l,j+k)*kernel(l,k);
            }
          }
          r(i,j)=sum;
        }
      }
    }
  };
}
