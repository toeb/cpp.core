#pragma once

#include <math.integration/Stepper.h>

namespace nspace{
  namespace math{
    namespace integration{
      template<typename F, typename X=typename state_type<F>::type, typename H =typename step_size_type<F>::type,typename T = typename time_type<F>::type >
      struct SingleStepSolver : public Stepper<F,X,H,T>{
        SingleStepSolver(F f):Stepper<F,X,H,T>(f){}
      };
    }
  }
}
