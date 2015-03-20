#pragma once
#include <core/core.h>

NS_BEGIN(CORE_NAMESPACE)

// a conditional field which is defined when T is not void
  template<typename T>
  struct not_void{
    T value;
  };

  template<>
  struct not_void < void > {

  };



NS_END(CORE_NAMESPACE)
