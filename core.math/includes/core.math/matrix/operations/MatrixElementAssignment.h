#pragma once
#include <core.math/core.math.h>

NS_BEGIN(CORE_MATH_NAMESPACE)

template<typename TAssignee, typename TValue>
class MatrixElementAssignment{
public:
  static inline bool operation(TAssignee & assignee, size_t i, size_t j, const TValue & value){
    assignee(i, j) = value;
    return true;
  }
};

//specialization
template<typename TValue>
class MatrixElementAssignment < float, TValue > {
public:
  static inline bool operation(float & assignee, size_t i, size_t j, const TValue & value){
    if (i != 0 && j != 0)return false;
    assignee = value;
    return true;
  }
};

template<typename TValue>
class MatrixElementAssignment < double, TValue > {
public:
  static inline bool operation(double & assignee, size_t i, size_t j, const TValue & value){
    if (i != 0 && j != 0)return false;
    assignee = value;
    return true;
  }
};
NS_END(CORE_MATH_NAMESPACE)