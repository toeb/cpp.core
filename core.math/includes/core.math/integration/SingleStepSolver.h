#pragma once
#include <core.math/core.math.h>

#include <core.math/integration/Stepper.h>


NS_BEGIN(CORE_MATH_NAMESPACE, integration)

template<typename F>
struct SingleStepSolver : public Stepper < F > {
  SingleStepSolver(F f) :Stepper(f){}
};


NS_END(CORE_MATH_NAMESPACE, integration)
