#pragma once
#include <math.integration/IStepper.h>
#include <math.matrix/operations/MatrixSetConstant.h>

namespace nspace{
  namespace math{
    namespace integration{
      //typename nspace::function_traits<F>::arg<0>::type
      template<typename F, typename X=typename  state_type<F>::type, typename H =typename step_size_type<F>::type,typename T = typename  time_type<F>::type>
      struct Stepper : public IStepper{
      public:
        typedef F FunctionType;
        typedef X StateType;
        typedef H TimeStepType;
        typedef T TimeType;
        typedef typename nspace::coefficientTypeOfType(X) CoefficientType;

        const TimeType & t()const;
        const TimeType & t0()const;
        const StateType & x()const ;
        StateType & x() ;
        const StateType & x0()const;
        const TimeStepType & h()const;
        TimeStepType & h();
        const TimeStepType & h0()const;

        Stepper(FunctionType function,
          StateType x0=constant<StateType>(0),
          TimeType t0=constant<TimeType>(0),
          TimeStepType h0=constant<TimeStepType>(0.02)
          );
        virtual  void step()override;
        void stepUntil(const TimeType t_end);
        StateType f(StateType x, TimeStepType h, TimeType t);
      private:

        FunctionType _function;
        StateType _x0;
        StateType _x;
        TimeStepType _h0;
        TimeStepType _h;
        TimeType _t0;
        TimeType _t;
      };
    }
  }
}

#include "Stepper.implementation.template.h"