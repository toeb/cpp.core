#pragma once

#include <math.integration/SingleStepSolver.h>
namespace nspace{
  namespace math{
    namespace integration{
      template<
        typename F,
        typename X=typename nspace::function_traits<F>::result_type,
        typename H =typename step_size_type<F>::type,
        typename T = typename time_type<F>::type>
      struct RungeKutta4 :public SingleStepSolver<F,X,H,T>{
        RungeKutta4(F f):SingleStepSolver<F,X,H,T>(f){}
        void doStep(){
          auto k1 =h()* f(x(),h(),t());          
          auto k2 =h()* f(x()+0.5*k1,h(),t()+0.5*h());
          auto k3 =h()* f(x()+0.5*k2,h(),t()+0.5*h());
          auto k4 = h()*f(x()+k3,h(),t()+h());
          x() = x() + (1/6.0)*(k1+2.0*k2+2.0*k3+k4);
        }
      };
    }
  }
}