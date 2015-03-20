#pragma once

#include <config.h>
#include <core.serialization/Serialization.h>
namespace nspace{
  struct Interval{
    // set the interval to the invalid values (+inf, -inf)
    // which is useful for detrmining the max and min values
    void setInvalid(){
      b = -REAL_MAX;
      a = REAL_MAX;
    }

    /**
    * \brief Sets the interval to (-inf,inf) .
    */
    void setUnbounded(){
      a = -REAL_MAX;
      b = REAL_MAX;
    }

    /**
    * \brief Extends interval to contain value.
    *
    * \author Tobi
    * \date 30.05.2012
    *
    * \param value The value.
    */
    inline void extendTo(Real value){
      if(value < a)a = value;
      if(value > b)b  =value;
    }
    Interval(Real low, Real high):a(low), b(high){
    }
    Interval(){
      setUnbounded();
    }
    bool overlaps(const Interval & other){
      if(other.b < a)return false;
      if(other.a > b)return false;
      return true;
    }
    bool disjoint(const Interval & other){
      return !overlaps(other);
    }
    bool isSubsetOf(const Interval & other){
      if(other.a <= a && other.b >= b)return true;
      return false;
    }
    bool isBefore(Real value)const{
      if(b < value)return true;
      return false;
    }
    bool isAfter(Real value)const{
      if(value < a)return true;
      return false;
    }
    bool isElementOf(Real value)const{
      if(a <= value && value <= b)return true;
      return false;
    }

    inline Real length()const{
      return b-a;
    }
    friend bool operator == (const Interval & a, const Interval &  b){
      return a.a==b.a&&a.b==b.b;
    }
    Real a;
    Real b;
  };

  SERIALIZERS(Interval,{
    stream << "["<<value->a<<", "<<value->b<<"]";
  },{
    stream>>value->a; stream >> value->b;
  });
}