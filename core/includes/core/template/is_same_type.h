#pragma once
#include <core/core.h>
#include <cstddef>
NS_BEGIN(CORE_NAMESPACE)
  
  template<typename T1, typename T2> inline bool isSameType(){
    return std::is_same<T1,T2>::value;
  }

  template<typename T1,typename T2> inline bool isSameType(const T1 & a, const T2 & b){
    return std::is_same<T1,T2>::value;
  }
NS_END(CORE_NAMESPACE)
