#pragma once
#include <config.h>
#include <core/template/function_traits.h>
/**
 * \brief an integrable function adheres to the following specification. ( it is not a struct or class etc)
 *        f is either a method/functor/function which 
 *          returns the derived state of a differential equation  the return type should always be of the same type as x
 *                
 *        f(x) where x is a state type (scalar, columnvector, matrix) x_i
 *        f(x,h) specification for x holds and h is the current timestep length h_i
 *        f(x,h,t) specification for x and h hold and t is the current time t_i
 *        f(x,h,t,i) specification for x,h and t hold and i is a unsigned integral value specifying the current step index
 *        
 *        if h is not given h will have the same type as a coefficient of x
 *        if t is not given it will be of the same time as h and if h is also not given it will the same type as a coefficient of x
 *        
 *        \example
 *                auto f = [](double x){return x;} is a integrable function typeof(x) == double, typeof(h) == double, typeof (t) ==double 
 *                double g(double x, float h) is a integrable function typeof(x) == double, typeof(h) == float, typeof(t) ==float
 *                double h(double x, double h, double double t) is a integrable function  typeof(x) ==double, typeof(h) == double, typeof(t) == double double
 *                double l(double x, double h, double t, long i) is a integrable function
 *                
 */
namespace nspace{
namespace math{
namespace integration{

  template<typename F, bool hasStepSize=nspace::function_traits<F>::arity==2||nspace::function_traits<F>::arity==3||nspace::function_traits<F>::arity==4 >
  struct step_size_type{
    typedef typename nspace::coefficientTypeOfType(typename nspace::function_traits<F>::result_type) type;
  };


  template<typename F>
  struct step_size_type<F,true>{
    typedef typename nspace::function_traits<F>::nested_template arg<1>::type type;

  };

  template<typename F, bool hasTime=nspace::function_traits<F>::arity==3||nspace::function_traits<F>::arity==4> 
  struct time_type{
    typedef typename step_size_type<F>::type type;
  };
  template<typename F>
  struct time_type<F,true>{
    typedef typename nspace::function_traits<F>::nested_template arg<2>::type type;
  };

  template<typename F>
  struct state_type{
    typedef typename nspace::function_traits<F>::result_type type;
  };

  template<typename F, int arity = nspace::function_traits<F>::arity>
  struct integrable_function_traits{
    typedef typename time_type<F>::type TimeType;
    typedef typename step_size_type<F>::type TimeStepType;
    typedef typename state_type<F>::type StateType;    
    typedef typename nspace::coefficientTypeOfType( StateType) CoefficientType;
    typedef size_t StepCountType;
    typedef F FunctionType;
    static StateType call(FunctionType f ,StateType x, TimeStepType h, TimeType t, StepCountType i);
  };
  template<typename F>
  struct integrable_function_traits<F,1>{
    typedef typename time_type<F>::type TimeType;
    typedef typename step_size_type<F>::type TimeStepType;
    typedef typename state_type<F>::type StateType;
    typedef size_t StepCountType;
    typedef F FunctionType;
    static StateType call(FunctionType f ,StateType x, TimeStepType h, TimeType t, StepCountType i){return f(x);}
  };

  template<typename F>
  struct integrable_function_traits<F,2>{
    typedef typename time_type<F>::type TimeType;
    typedef typename step_size_type<F>::type TimeStepType;
    typedef typename state_type<F>::type StateType;
    typedef size_t StepCountType;
    typedef F FunctionType;
    static StateType call(FunctionType f ,StateType x, TimeStepType h, TimeType t, StepCountType i){return f(x,h);}
  };

  template<typename F>
  struct integrable_function_traits<F,3>{
    typedef typename time_type<F>::type TimeType;
    typedef typename step_size_type<F>::type TimeStepType;
    typedef typename state_type<F>::type StateType;
    typedef size_t StepCountType;
    typedef F FunctionType;
    static StateType call(FunctionType f ,StateType x, TimeStepType h, TimeType t, StepCountType i){return f(x,h,t);}
  };
  template<typename F>
  struct integrable_function_traits<F,4>{
    typedef typename time_type<F>::type TimeType;
    typedef typename step_size_type<F>::type TimeStepType;
    typedef typename state_type<F>::type StateType;
    typedef size_t StepCountType;
    typedef F FunctionType;
    static StateType call(FunctionType f ,StateType x, TimeStepType h, TimeType t, StepCountType i){return f(x,h,t,i);}
  };





}
}
}
