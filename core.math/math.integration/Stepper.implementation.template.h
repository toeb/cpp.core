#pragma once

#include "Stepper.h"
namespace nspace{
namespace math{
namespace integration{

  template<typename F, typename X, typename H ,typename T> auto Stepper<F,X,H,T>::t()const->const TimeType & {return _t;}
  template<typename F, typename X, typename H ,typename T> auto Stepper<F,X,H,T>::t0()const->const TimeType & {return _t0;}
  template<typename F, typename X, typename H ,typename T> auto Stepper<F,X,H,T>::x()const->const StateType &  {return _x;}
  template<typename F, typename X, typename H ,typename T> auto Stepper<F,X,H,T>::x()->StateType & {return _x;}
  template<typename F, typename X, typename H ,typename T> auto Stepper<F,X,H,T>::x0()const->const StateType & {return _x0;}
  template<typename F, typename X, typename H ,typename T> auto Stepper<F,X,H,T>::h()const->const TimeStepType & {return _h;}
  template<typename F, typename X, typename H ,typename T> auto Stepper<F,X,H,T>::h()->TimeStepType & {return _h;}
  template<typename F, typename X, typename H ,typename T> auto Stepper<F,X,H,T>::h0()const->const TimeStepType & {return _h0;}

  template<typename F, typename X, typename H ,typename T> Stepper<F,X,H,T>::Stepper(
    F function,
    X x0,
    T t0,
    H h0
    ):_function(function),_x0(x0),_x(x0), _h0(h0),_h(h0),_t0(t0),_t(t0){}
  
   template<typename F, typename X, typename H ,typename T> void Stepper<F,X,H,T>::step(){
    IStepper::step();    
    _t=_t+_h;
  }
  
   template<typename F, typename X, typename H ,typename T> void Stepper<F,X,H,T>::stepUntil(const TimeType t_end){
    while(t()<=t_end){
      step();
    }
  }
   template<typename F, typename X, typename H ,typename T> auto Stepper<F,X,H,T>::f(StateType x, TimeStepType h, TimeType t)->StateType{
    return integrable_function_traits<FunctionType>::call(_function,x,h,t,i());
  }

    }
  }
}
