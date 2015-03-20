#pragma once
#include <queue>
#include <core.math/core.math.h>

NS_BEGIN(CORE_MATH_NAMESPACE, statistics)
//interface for calulating an average.
class IAverage{
public:
  typedef double value_type;
  // addsample method should be called for adding a new value
  virtual void addSample(value_type value) = 0;
  // calculate method should return the average which is to be caluclated
  virtual value_type calculate() = 0;
};
NS_END(CORE_MATH_NAMESPACE, statistics)