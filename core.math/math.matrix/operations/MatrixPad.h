#pragma once
#include <config.h>
namespace nspace{
  template<typename OutputMat, typename InputMat>
  class MatrixPad{
  public:
    static inline void operation(OutputMat & out, const InputMat & input, uint rowsTop, uint rowsBottom, uint colsLeft, uint colsRight){
      out.resize(input.rows()+rowsTop+rowsBottom,input.cols()+colsLeft+colsRight);
      MatrixSetConstant<Real, OutputMat>::operation(out,0.0);
      for(int i=0; i< input.rows(); i++){
        for(int j=0; j < input.cols(); j++){
          out(i+rowsTop,j+colsLeft) = input(i,j);
        }
      }
    }
  };
}