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
          assert(0);
        }
      };
      /* private:
      ///< The tolerance
      Real tolerance;
      /// <summary> alpha in (0,1] default 0.9 (reduction of new step size) </summary>
      Real alpha;
      /// <summary> beta in (0,1) default 0.5 lower bound of new step size h_new >= beta*h_old </summary>
      Real beta;
      ///< gamma in (1,infinity) default 1.5 upper bound of new step size h_new <= gamma * h_old
      Real gamma;
      Real maximumStepSize;
      Real minimumStepSize;
      Real currentErrorEstimate;
      StateMatrix k1,k2,k3,k4,k5,k6,y,z;
      public:

      /**
      * \brief Constructor.
      *
      * \param tolerance       (optional) the tolerance used by RKF45 .
      * \param initialStepSize (optional) size of the initial step.
      * \param alpha           (optional) alpha in (1,1] - stepsize reduction factor in every step default should be 0.9.
      * \param beta            (optional) beta in [0,1] - the maximum decrease factor from step h_i to h_{i+1}.
      * \param gamma           (optional) gamma in [1, inf) - the maximum increase factor from step h_i to h_{i+1}
      * \param maxStepSize     (optional) the maximum step size h_i <= maxStepSize for all i in N.
      * \param minStepSize     (optional) the minimum step size h_i >= minStepSize for all i in N.
      * /
      RungeKuttaFehlberg45(
      Real tolerance = 10e-5,
      Real h0=10e-3,
      Real alpha=0.9,
      Real beta=0.5,
      Real gamma=1.5,
      Real maxStepSize = 1,
      Real minStepSize = 10e-7
      );*/
    }
  }
}