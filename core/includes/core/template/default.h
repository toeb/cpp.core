#pragma once
#include <core/core.h>

NS_BEGIN(CORE_NAMESPACE)
  /// can be used as the default value for any type of argument
    struct default_value{
      template<typename T> operator T(){ return T(); }
    };
NS_END(CORE_NAMESPACE)
