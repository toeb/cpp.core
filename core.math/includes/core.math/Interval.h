#pragma once
#include <core.math/core.math.h>

NS_BEGIN(CORE_MATH_NAMESPACE)

template<typename T = double>
struct Interval{
  typedef T value_type;
  typedef Interval interval_type;

  // set the interval to the invalid values (+inf, -inf)
  // which is useful for detrmining the max and min values
  void setInvalid(){
    b = -std::numeric_limits<value_type>::infinity();
    a = std::numeric_limits<value_type>::infinity();
  }

  /**
  * \brief Sets the interval to (-inf,inf) .
  */
  void setUnbounded(){
    a = -std::numeric_limits<value_type>::infinity();
    b = std::numeric_limits<value_type>::infinity();
  }

  /**
  * \brief Extends interval to contain value.
  *
  * \author Tobi
  * \date 30.05.2012
  *
  * \param value The value.
  */
  inline void extendTo(value_type value){
    if (value < a)a = value;
    if (value > b)b = value;
  }
  inline void extendTo(const interval_type & other){
    extendTo(other.a);
    extendTo(other.b);
  }
  Interval(value_type low, value_type high) :a(low), b(high){
  }
  Interval(){
    setUnbounded();
  }
  bool overlaps(const interval_type & other){
    if (other.b < a)return false;
    if (other.a > b)return false;
    return true;
  }
  bool disjoint(const interval_type & other){
    return !overlaps(other);
  }
  bool isSubsetOf(const interval_type & other){
    if (other.a <= a && other.b >= b)return true;
    return false;
  }
  bool isBefore(value_type value)const{
    if (b < value)return true;
    return false;
  }
  bool isAfter(value_type value)const{
    if (value < a)return true;
    return false;
  }
  bool isElementOf(value_type value)const{
    if (a <= value && value <= b)return true;
    return false;
  }

  bool isInvalid()const{
    return b < a;
  }
  inline value_type length()const{
    return b - a;
  }
  friend bool operator == (const interval_type & a, const interval_type &  b){
    return a.a == b.a&&a.b == b.b;
  }

  bool equals(const interval_type & other, value_type epsilon){
    //@todo
    return *this == other;
  }
  value_type a;
  value_type b;
};

template<typename T>
auto interval(T && lower, T&& upper)->core::math::Interval < T > {
  return core::math::Interval<T>(lower, upper);
}

template<typename T = double>
auto interval()->core::math::Interval < T > {
  return core::math::Interval<T>();
}


/*SERIALIZERS(Interval,{
  stream << "["<<value->a<<", "<<value->b<<"]";
  },{
  stream>>value->a; stream >> value->b;
  });*/
NS_END(CORE_MATH_NAMESPACE)