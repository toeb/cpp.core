#pragma once
#include <core.math/core.math.h>
NS_BEGIN(CORE_MATH_NAMESPACE)

template<typename T,typename Mat>
class MatrixSum{
public:
  static inline void operation(T & result, const Mat & mat){
    result =0;
    for(int i=0; i < mat.rows(); i++){
      for(int j=0; j < mat.cols(); j++){
        result = result + mat(i,j);
      }
    }
  }
};
NS_END(CORE_MATH_NAMESPACE)