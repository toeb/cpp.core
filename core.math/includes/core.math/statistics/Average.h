#pragma once
#include <queue>

#include <core.math/core.math.h>
#include <core.math/statistics/IAverage.h>

NS_BEGIN(CORE_MATH_NAMESPACE,statistics)
  


  // allows the calculation of the average for the last n samples (discards all older samples)
  class Average : IAverage{
  private:
    std::queue<value_type> _queue;
    int _samples;
  public:
    // constructor. allows to specify how many samples should be averaged
    Average(int samples = 50);
    // access to the number of samples
    int & numberOfSamples();
    // readonly access to the number of samples
    const int & numberOfSamples()const;
    // add a sample
    void addSample(value_type sample);
    // calculate the average
    value_type calculate();
  };

NS_END(CORE_MATH_NAMESPACE, statistics)