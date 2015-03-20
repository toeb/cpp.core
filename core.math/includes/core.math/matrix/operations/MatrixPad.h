#pragma once
#include <core.math/core.math.h>
#include <core.math/core.math.h>
#include <core.math/core.math.h>
NS_BEGIN(CORE_MATH_NAMESPACE)
  template<typename OutputMat, typename InputMat>
  class MatrixPad{
  public:
    static inline void operation(OutputMat & out, const InputMat & input, size_t rowsTop, size_t rowsBottom, size_t colsLeft, size_t colsRight){
      out.resize(input.rows()+rowsTop+rowsBottom,input.cols()+colsLeft+colsRight);
      MatrixSetConstant<Real, OutputMat>::operation(out,0.0);
      for(int i=0; i< input.rows(); i++){
        for(int j=0; j < input.cols(); j++){
          out(i+rowsTop,j+colsLeft) = input(i,j);
        }
      }
    }
  };
NS_END(CORE_MATH_NAMESPACE)