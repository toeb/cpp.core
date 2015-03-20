#pragma once
#include <core.math/core.math.h>
#include <core.math/integration/Stepper.h>

NS_BEGIN(CORE_MATH_NAMESPACE, integration)

template<typename F, typename TStep>
struct DelegateStepper : public Stepper < F > {
  DelegateStepper(F f, TStep s) :Stepper(f), _step(s){}
  void doStep()override{
    x() = _step([this](state_type x, step_size_type h, time_type t){
      return this->f(x,h,t);
    }, x(), h(), t(), i());
  }
private:
  TStep _step;
};
/// creates and returns a stepper for the specified system function f and the step algorithm s
template<typename F, typename S> DelegateStepper<F, S> stepper(F f, S s){ return DelegateStepper<F, S>(f, s); }
NS_END(CORE_MATH_NAMESPACE, integration)