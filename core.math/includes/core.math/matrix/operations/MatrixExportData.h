#pragma once
#include <core.math/core.math.h>

NS_BEGIN(CORE_MATH_NAMESPACE)
  template<typename T, typename SourceType>
  class MatrixCopyToPointer{
  public:
    static inline void operation(T * data, const SourceType & source){
      //slow implementation copies every element
      for(uint i=0; i < source.size(); i++){
        data[i] = source(i);
      }
    }
  };
NS_END(CORE_MATH_NAMESPACE)