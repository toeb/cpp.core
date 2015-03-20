#pragma once

#include <config.h>
namespace nspace{
  namespace math{
    namespace integration{
      struct IStepper{
        typedef size_t StepCount;
        StepCount _i;
        const StepCount & i()const{return _i;}
        void operator()(){step();}
        void operator()(const StepCount n){
          nSteps(n);
        }

        virtual void step(){
          doStep();
          _i++;
        }
        void nSteps(const StepCount n){
          for(StepCount i =0; i < n; i++){
            step();
          }
        }

        IStepper():_i(0){}
        virtual ~IStepper(){}
      protected:
        virtual void doStep()=0;
      };
    }
  }
}