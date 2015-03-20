#pragma once
#include <queue>

#include <core.math/core.math.h>

#include <core/Time.h>

#include <core.math/statistics/IAverage.h>

NS_BEGIN(CORE_MATH_NAMESPACE, statistics)

class AverageOverTime : public IAverage{
public:
  typedef NS(CORE_NAMESPACE)::Time time_type;
  struct AverageOverTimeValue{
    time_type t;
    value_type value;
  };
private:
  size_t _valueCount;
  value_type _valueSum;
  time_type _timeLength;
  std::queue<AverageOverTimeValue> _values;

public:
  AverageOverTime(time_type tl) :
    _valueCount(0),
    _valueSum(0),
    _timeLength(tl)
  {}

  time_type currentTime(){
    NS(CORE_NAMESPACE)::applicationTime();
  }
  void addSample(value_type value){
    AverageOverTimeValue av;
    av.t = currentTime();
    av.value = value;

    _valueSum += value;
    _valueCount++;
    _values.push(av);
  }

  void removeOldSamples(){
    time_type t = currentTime() - _timeLength;
    while (_valueCount){

      AverageOverTimeValue & current = _values.front();
      if (current.t > t)break;
      _values.pop();

      _valueSum -= current.value;
      _valueCount--;
    }
  }
  value_type calculate(){
    removeOldSamples();
    if (!_valueCount)return 0.0;
    return _valueSum / _valueCount;
  }
};

NS_END(CORE_MATH_NAMESPACE, statistics)
