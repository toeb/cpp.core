#pragma once
#include <config.h>
#include <queue>
#include <math.statistics/IAverage.h>
namespace nspace{
  // allows the calculation of the average for the last n samples (discards all older samples)
  class Average : IAverage{
    std::queue<Real> _queue;
    int _samples;
  public:
    // constructor. allows to specify how many samples should be averaged
    Average(int samples = 50);
    // access to the number of samples
    int & numberOfSamples();
    // readonly access to the number of samples
    const int & numberOfSamples()const;
    // add a sample
    void addSample(Real sample);
    // calculate the average
    Real calculate();
  };
}