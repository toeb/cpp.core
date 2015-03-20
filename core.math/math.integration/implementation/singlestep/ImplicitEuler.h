#pragma once

#include <math.integration/SingleStepSolver.h>
namespace nspace{
  namespace math{
    namespace integration{
      template<typename F, typename X=typename nspace::function_traits<F>::result_type, typename H =typename step_size_type<F>::type, typename T =typename time_type<F>::type>
      struct ImplicitEuler :public SingleStepSolver<F,X,H,T>{
        ImplicitEuler(F f):SingleStepSolver<F,X,H,T>(f),_maxIterations(100),_tolerance(0.001){}

        typename SingleStepSolver<F,X,H,T>::StepCount _maxIterations;
        typename SingleStepSolver<F,X,H,T>::CoefficientType _tolerance;

        void doStep(){
          typename SingleStepSolver<F,X,H,T>::StateType tmp;
          typename SingleStepSolver<F,X,H,T>::CoefficientType diffSquared;
          //fix point iteration
          auto toleranceSquared = _tolerance*_tolerance;

          size_t iteration=0;
          while(iteration < _maxIterations){
            iteration++;
            tmp = this->x() + this->h() * this->f(this->x(),this->h(),this->t());
            diffSquared = nspace::lengthSquared(nspace::subtract(tmp,this->x()));
            this->x() = tmp;
            if(diffSquared < toleranceSquared)break;
          }
        }
      };
    }
  }
}
