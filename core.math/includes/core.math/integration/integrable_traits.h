#pragma once

#include <core/template/func_traits.h>
#include <core/template/tuple_element_or_default.h>
#include <core.math/matrix/matrix_traits.h>
#include <core.math/core.math.h>
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
NS_BEGIN(CORE_MATH_NAMESPACE,integration)


/// specializable traits struct for defining integrable functions
template<typename TFunc>
struct integrable_traits{
  typedef TFunc function_type;
  typedef NS(CORE_NAMESPACE)::func_traits<function_type> function_traits;
  typedef typename function_traits::return_type state_type;
  typedef matrix::matrix_traits<state_type> state_traits;
  typedef typename state_traits::coefficient_type coefficient_type;
  
  /// step size_type typeof argument 2 of function or coefficient_type of return_type
  typedef typename NS(CORE_NAMESPACE)::tuple_element_or_default<1, typename function_traits::args_tuple, coefficient_type>::type
  step_size_type;
  /// time_type is the type of argument 3 or step_size_type
  typedef typename NS(CORE_NAMESPACE)::tuple_element_or_default<2, typename function_traits::args_tuple, step_size_type>::type
  time_type;

  
};

NS_END(CORE_MATH_NAMESPACE,integration)

