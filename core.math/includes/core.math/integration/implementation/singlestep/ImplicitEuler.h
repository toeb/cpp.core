#pragma once
#include <core.math/core.math.h>
#include <core.math/integration/SingleStepSolver.h>

NS_BEGIN(CORE_MATH_NAMESPACE, integration)
template<typename F>
struct ImplicitEuler :public SingleStepSolver < F > {
  ImplicitEuler(F f) :SingleStepSolver<F>(f), _maxIterations(100), _tolerance(0.001){}

  step_count_type _maxIterations;
  coefficient_type _tolerance;

  void doStep(){
    state_type tmp;
    coefficient_type diffSquared;
    //fix point iteration
    auto toleranceSquared = _tolerance*_tolerance;

    size_t iteration = 0;
    while (iteration < _maxIterations){
      iteration++;
      tmp = this->x() + this->h() * this->f(this->x(), this->h(), this->t());
      diffSquared = lengthSquared(subtract(tmp, this->x()));
      this->x() = tmp;
      if (diffSquared < toleranceSquared)break;
    }
  }
};
NS_END(CORE_MATH_NAMESPACE, integration)