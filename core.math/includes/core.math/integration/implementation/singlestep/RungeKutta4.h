#pragma once
#include <core.math/core.math.h>

#include <core.math/integration/SingleStepSolver.h>
NS_BEGIN(CORE_MATH_NAMESPACE, integration)
template<typename F>
struct RungeKutta4 :public SingleStepSolver < F> {
  RungeKutta4(F f) :SingleStepSolver<F>(f){}
  void doStep(){
    auto k1 = h()* f(x(), h(), t());
    auto k2 = h()* f(x() + 0.5*k1, h(), t() + 0.5*h());
    auto k3 = h()* f(x() + 0.5*k2, h(), t() + 0.5*h());
    auto k4 = h()*f(x() + k3, h(), t() + h());
    x() = x() + (1 / 6.0)*(k1 + 2.0*k2 + 2.0*k3 + k4);
  }
};

NS_END(CORE_MATH_NAMESPACE, integration)