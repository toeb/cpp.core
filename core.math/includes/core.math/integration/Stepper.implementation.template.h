#pragma once

#include <core.math/integration/Stepper.h>
#include <core/template/sequence.h>
NS_BEGIN(CORE_MATH_NAMESPACE, integration)

template<typename F> auto Stepper<F>::t()const->const time_type &{ return _t; }
template<typename F> auto Stepper<F>::t0()const->const time_type &{ return _t0; }
template<typename F> auto Stepper<F>::x()const->const state_type &{ return _x; }
template<typename F> auto Stepper<F>::x()->state_type & { return _x; }
template<typename F> auto Stepper<F>::x0()const->const state_type &{ return _x0; }
template<typename F> auto Stepper<F>::h()const->const step_size_type &{ return _h; }
template<typename F> auto Stepper<F>::h()->step_size_type & { return _h; }
template<typename F> auto Stepper<F>::h0()const->const step_size_type &{ return _h0; }

template<typename F> Stepper<F>::Stepper(
function_type function,
state_type x0,
time_type t0,
step_size_type h0
) :_function(function), _x0(x0), _x(x0), _h0(h0), _h(h0), _t0(t0), _t(t0){}

template<typename F> void Stepper<F>::step(){
  IStepper::step();
  _t = _t + _h;
}

template<typename F> void Stepper<F>::stepUntil(const time_type t_end){
  while (t() <= t_end){
    step();
  }
}




NS_END(CORE_MATH_NAMESPACE, integration)