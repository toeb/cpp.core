#pragma once
#include <core/core.h>

NS_BEGIN(CORE_NAMESPACE)
  //alias for a time
  typedef double Time;
  // returns the system time
  Time systemTime();
  // returns the system time when the application started up
  Time startupTime();
  // returns the time since application startup
  Time applicationTime();
NS_END(CORE_NAMESPACE)

