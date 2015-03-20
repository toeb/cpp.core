#pragma once
#include <core.math/core.math.h>


NS_BEGIN(CORE_MATH_NAMESPACE)
  template<typename FilteredMatrix, typename InputMatrix, typename FilterFunction, typename FilterFunctionArgument>
  class MatrixFilter{
  public:
    static inline void operation(FilteredMatrix & result, const InputMatrix & g, FilterFunction f, size_t filterWidth, size_t filterHeight){
      uint gx = g.cols();
      uint gy = g.rows();
      uint fx2 = filterWidth/2;
      uint fy2 = filterHeight/2;
      uint rx = gx-filterWidth+1;
      uint ry = gy-filterHeight+1;
      FilterFunctionArgument current;
      result.resize(ry,rx,false);
      current.resize(filterHeight,filterWidth,false);
      for(int i= 0; i < ry; i++){
        for(int j=0; j < rx; j++){
          g.block(current,i,j);
          // MatrixExtractBlock<FilterFunctionArgument, InputMatrix>::operation(current,g,i,j,filterHeight,filterWidth);
          f(result(i,j),current);
        }
      }
    }
  };
NS_END(CORE_MATH_NAMESPACE)