#pragma once
#include <core.math/core.math.h>

#include <core.math/integration/SingleStepSolver.h>

#include <core.math/integration/integrable_traits.h>
NS_BEGIN(CORE_MATH_NAMESPACE, integration)

template<typename F>
struct ExplicitEuler :public SingleStepSolver < F > {
  ExplicitEuler(F f) :SingleStepSolver(f){}

  void doStep(){
    this->x() = this->x() + this->h()*this->f(this->x(), this->h(), this->t());
  }
};




NS_END(CORE_MATH_NAMESPACE, integration)

