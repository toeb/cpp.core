#pragma once
#include <core.math/core.math.h>

#include <core.math/integration/SingleStepSolver.h>
NS_BEGIN(CORE_MATH_NAMESPACE)
namespace integration{
  template<typename F>
  struct RungeKutta2 :public SingleStepSolver < F > {
    RungeKutta2(F f) :SingleStepSolver<F>(f){}
    void doStep(){
      auto k1 = h()* f(x(), h(), t());
      auto k2 = h()* f(x() + 0.5*k1, h(), t() + 0.5*h());
      x() = x() + k2;
    }
  };
}
NS_END(CORE_MATH_NAMESPACE)