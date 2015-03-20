#include <core.math/statistics/Average.h>

using namespace NS(CORE_MATH_NAMESPACE, statistics);

Average::Average(int samples) :_samples(samples){}

void Average::addSample(value_type sample){
  _queue.push(sample);
}

auto Average::calculate()->value_type{
  value_type result = 0;
  for (int i = 0; i < _samples; i++){
    value_type val = _queue.front();
    _queue.pop();
    result += val;
    _queue.push(val);
  }
  return result / _samples;
}

int & Average::numberOfSamples(){ return _samples; }
const int & Average::numberOfSamples()const{ return _samples; }
