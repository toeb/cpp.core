#pragma once
NS_BEGIN(CORE_MATH_NAMESPACE)
template<typename T, typename TargetType>
class MatrixAssignData{
public:
  static inline void operation(TargetType  & target, const T * source){
    for(uint i=0; i < target.size(); i++){
      target(i) = source[i];
    }
  }
};
NS_END(CORE_MATH_NAMESPACE)