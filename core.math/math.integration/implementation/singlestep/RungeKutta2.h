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
      struct RungeKutta2 :public SingleStepSolver<F,X,H,T>{
        RungeKutta2(F f):SingleStepSolver<F,X,H,T>(f){}
        void doStep(){                    
          auto k1 =h()* f(x(),h(),t());
          auto k2 =h()* f(x()+0.5*k1,h(),t()+0.5*h());
          x() = x() + k2;
        }


      };
    }
  }
}