#pragma once
#include <config.h>
#include <math.operation/NullaryOperation.h>
#include <math.scalar/operationcodes.h>
#include <math.scalar/constants.h>

namespace nspace{
  namespace math{
    namespace operation{
      template<typename T>
      class Operation<T, operation::Nullary,scalar::opcodes::Pi >{
      public:
        static inline void operation(T & a){
          a = M_PI;
        }
      };
    }}}
