#pragma once
#include <core.math/core.math.h>

NS_BEGIN(CORE_MATH_NAMESPACE)
  template<typename Mat, typename Func>
  class MatrixSetFunction{
  public:
    static inline void operation(Mat &  result, Func f){
      for(int i=0; i < result.rows(); i++){
        for(int j=0; j < result.cols(); j++){
          result(i,j)=f(i,j);
        }
      }
    }
  };
NS_END(CORE_MATH_NAMESPACE)