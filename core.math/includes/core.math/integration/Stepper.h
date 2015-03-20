#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/matrix_traits.h>
#include <core.math/integration/integrable_traits.h>
#include <core.math/matrix/all.h>
#include <core.math/integration/IStepper.h>

NS_BEGIN(CORE_MATH_NAMESPACE, integration)

//typename nspace::function_traits<F>::arg<0>::type
template<typename F>
struct Stepper : public IStepper, public integrable_traits < F > {
public:

  auto t()const->const time_type &;
  auto t0()const -> const time_type &;
  auto x()const->const state_type &;
  auto x()->state_type &;
  auto x0()const->const state_type &;
  auto h()const->const step_size_type &;
  auto h()->step_size_type &;
  auto h0()const->const step_size_type &;

  Stepper(function_type function,
    state_type x0 = constant<state_type>(0),
    time_type t0 = constant<time_type>(0),
    step_size_type h0 = constant<step_size_type>(0.02)
    );

  virtual auto step()->void override;

  auto stepUntil(const time_type t_end)->void;

  template<typename TX = function_type>
  typename std::enable_if <NS(CORE_NAMESPACE)::func_traits<TX>::arity == 1, state_type>::type f(state_type  x, step_size_type   h, time_type   t) { return _function((x)); }
  template<typename TX = function_type>
  typename std::enable_if<NS(CORE_NAMESPACE)::func_traits<TX>::arity == 2, state_type>::type f(state_type   x, step_size_type   h, time_type   t){ return _function((x), (h)); }
  template<typename TX = function_type>
  typename std::enable_if<NS(CORE_NAMESPACE)::func_traits<TX>::arity == 3, state_type>::type f(state_type   x, step_size_type   h, time_type   t){ return _function((x), (h), (t)); }
  template<typename TX = function_type>
  typename std::enable_if<NS(CORE_NAMESPACE)::func_traits<TX>::arity == 4, state_type>::type f(state_type   x, step_size_type   h, time_type   t){ return _function((x), (h), (t), i()); }
private:
  /// fields
  function_type _function;
  state_type _x0;
  state_type _x;
  step_size_type _h0;
  step_size_type _h;
  time_type _t0;
  time_type     _t;
};

NS_END(CORE_MATH_NAMESPACE, integration)

/// include implementation of the methods
#include <core.math/integration/Stepper.implementation.template.h>