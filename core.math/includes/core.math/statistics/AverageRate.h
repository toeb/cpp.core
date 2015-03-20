#pragma once
#include <core.math/core.math.h>
#include <core/Time.h>
#include <core.math/scalar/all.h>
#include <core.math/statistics/IAverage.h>
NS_BEGIN(CORE_MATH_NAMESPACE)
  namespace statistics{

    class AverageRate : public IAverage{
    public:
      typedef Time time_type;
    private:
      IAverage & _average;
      bool _initialized;
      time_type _lastSampleTime;
      value_type _lastSample;
    public:
      AverageRate(IAverage & average) :_average(average), _initialized(false){
      }
      void addSample(value_type sample){
        if (!_initialized){
          _lastSampleTime = systemTime();
          _lastSample = sample;
          _initialized = true;
          return;
        }

        value_type t_sys = systemTime();
        time_type dt = t_sys - _lastSampleTime;
        value_type delta = sample - _lastSample;
        value_type currentRate = delta / dt;

        _average.addSample(currentRate);

        _lastSample = sample;
        _lastSampleTime = t_sys;
      }

      value_type calculate(){
        return _average.calculate();
      }
    };
  }
NS_END(CORE_MATH_NAMESPACE)
