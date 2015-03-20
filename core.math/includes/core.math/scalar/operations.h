#pragma once

#include <core.math/core.math.h>



#include <core.math/scalar/constants.h>
// include all scalar operations
//#include <core.math/scalar/operation/Addition.h>
#include <core.math/scalar/operation/ArcusCosinus.h>
//#include <core.math/scalar/operation/ArcusTangens.h>
//#include <core.math/scalar/operation/ArcusTangens2.h>
//#include <core.math/scalar/operation/Division.h>
//#include <core.math/scalar/operation/Identity.h>
//#include <core.math/scalar/operation/Maximum.h>
//#include <core.math/scalar/operation/Minimum.h>
//#include <core.math/scalar/operation/Multiplication.h>
//#include <core.math/scalar/operation/Subtraction.h>
//#include <core.math/scalar/operation/Tangens.h>
#include <core.math/scalar/operation/Zero.h>
#include <core.math/scalar/operation/SquareRootOfTwo.h>
#include <core.math/scalar/operation/Pi.h>
#include <core.math/scalar/operation/EulersNumer.h>
#include <core.math/scalar/operation/Signum.h>
#include <core.math/scalar/operation/Cosinus.h>
#include <core.math/scalar/operation/ArcusSinus.h>
#include <core.math/scalar/operation/Absolute.h>
#include <core.math/scalar/operation/Reciprocal.h>
#include <core.math/scalar/operation/Sinus.h>
#include <core.math/scalar/operation/SquareRoot.h>

#define NULLARY_SHORTHAND(NAME , OP)  \
  template<typename T> void NAME(T & result){ NS(CORE_MATH_NAMESPACE)::scalar::OP<T>::operation(result); }\
  template<typename T> T NAME(){ T result; NAME(result); return result; }\

#define UNARY_SHORTHAND(NAME , OP)   \
  template<typename T> void NAME(T & result, const T & a){ NS(CORE_MATH_NAMESPACE)::scalar::OP<T>::operation(result, a);}\
  template<typename T> T NAME(const T & a){T result; NAME(result,a); return result;}

#define BINARY_SHORTHAND(NAME , OP)  \
  template<typename T> void NAME(T & result, const T & a,const T & b){T result;  NS(CORE_MATH_NAMESPACE)::scalar::OP<T>::operation(result, a,b); }\
  template<typename T> T NAME(const T & a,const T & b){T result; NAME(result, a,b); return result; }

NS_BEGIN(CORE_MATH_NAMESPACE)
  namespace scalar{
    /**
     * \brief Clamps the given value to the specified interval.
     *
     * \tparam  typename T  Type of the value.
     * \param [in,out]  value The value.
     * \param max             The maximum.
     * \param min             The minimum.
     *
     * \return  true if value was clamped false if value was in range
     */
    template<typename T> inline bool clamp(T & value, T min, T max){
      if (value < min){
        value = min;
        return true;
      }
      if (value > max){
        value = max;
        return true;
      }
      return false;
    }

    // define shorthand functions for all operations
    UNARY_SHORTHAND(signum, Signum);
    UNARY_SHORTHAND(cosine, Cosinus);
    UNARY_SHORTHAND(sine, Sinus);
    UNARY_SHORTHAND(absolute, Absolute);
    UNARY_SHORTHAND(arcusSinus, ArcusSinus);
    UNARY_SHORTHAND(arcusCosinus, ArcusCosinus);
    UNARY_SHORTHAND(squareRoot, SquareRoot);
    UNARY_SHORTHAND(reciprocal, Reciprocal);

    NULLARY_SHORTHAND(e, EulersNumber);
    NULLARY_SHORTHAND(pi, Pi);
    NULLARY_SHORTHAND(squareRootOfTwo, SquareRootOfTwo);
    NULLARY_SHORTHAND(zero, Zero);
  }


NS_END(CORE_MATH_NAMESPACE)
