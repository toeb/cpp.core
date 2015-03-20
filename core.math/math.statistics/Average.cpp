#include "Average.h"
using namespace nspace;

Average::Average(int samples):_samples(samples){}

void Average::addSample(Real sample){
  _queue.push(sample);
}

Real Average::calculate(){
  Real result = 0;
  for(int i =0; i < _samples;i++){
    Real val = _queue.front();
    _queue.pop();
    result+=val;
    _queue.push(val);
  }
  return result / _samples;
}

int & Average::numberOfSamples(){return _samples;}
const int & Average::numberOfSamples()const{return _samples;}