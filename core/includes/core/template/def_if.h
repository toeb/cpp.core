#pragma once
#include <core/core.h>

NS_BEGIN(CORE_NAMESPACE)
  // a conditional field
  // defines the field if enable is true at compile time
  template<typename T, bool enable = false>
  struct def_if{

  };
  template<typename T>
  struct def_if < T, true > {
    T value;
  };
NS_END(CORE_NAMESPACE)
