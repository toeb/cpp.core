#pragma once

#include <core.math/core.math.h>

NS_BEGIN(CORE_MATH_NAMESPACE, matrix)

template<typename T>
struct matrix_traits{
  typedef double coefficient_type;
  typedef int index_type;
  typedef int size_type;
};

NS_END(CORE_MATH_NAMESPACE, matrix)
