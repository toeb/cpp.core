#pragma once
#include <core.math/core.math.h>


NS_BEGIN(CORE_MATH_NAMESPACE, integration)

/// the basic interface for stepping through a function
/// keeps track of the current step count
/// subclasses need to implement the doStep method
struct IStepper{
  typedef size_t step_count_type;
  step_count_type _i;
  const step_count_type & i()const{ return _i; }
  void operator()(){ step(); }
  void operator()(const step_count_type n){
    nSteps(n);
  }

  virtual void step(){
    doStep();
    _i++;
  }
  void nSteps(const step_count_type n){
    for (step_count_type i = 0; i < n; i++){
      step();
    }
  }

  IStepper() :_i(0){}
  virtual ~IStepper(){}
protected:
  virtual void doStep() = 0;
};


NS_END(CORE_MATH_NAMESPACE, integration)