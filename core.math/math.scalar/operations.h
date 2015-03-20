#pragma once

#include <config.h>

#include <math.operation/NullaryOperation.h>
#include <math.operation/UnaryOperation.h>
#include <math.operation/BinaryOperation.h>

#include <math.scalar/constants.h>
// include all scalar operations
//#include <math.scalar/operation/Addition.h>
#include <math.scalar/operation/ArcusCosinus.h>
//#include <math.scalar/operation/ArcusTangens.h>
//#include <math.scalar/operation/ArcusTangens2.h>
//#include <math.scalar/operation/Division.h>
//#include <math.scalar/operation/Identity.h>
//#include <math.scalar/operation/Maximum.h>
//#include <math.scalar/operation/Minimum.h>
//#include <math.scalar/operation/Multiplication.h>
//#include <math.scalar/operation/Subtraction.h>
//#include <math.scalar/operation/Tangens.h>
#include <math.scalar/operation/Zero.h>
#include <math.scalar/operation/SquareRootOfTwo.h>
#include <math.scalar/operation/Pi.h>
#include <math.scalar/operation/EulersNumer.h>
#include <math.scalar/operation/Signum.h>
#include <math.scalar/operation/Cosinus.h>
#include <math.scalar/operation/ArcusSinus.h>
#include <math.scalar/operation/Absolute.h>
#include <math.scalar/operation/Reciprocal.h>
#include <math.scalar/operation/Sinus.h>
#include <math.scalar/operation/SquareRoot.h>




#define FOR_ALL_UNARY_SCALAR_OPERATIONCODES(DEFINITION) \
DEFINITION(Signum);\
DEFINITION(Cosinus);\
DEFINITION(Sinus);\
DEFINITION(ArcusSinus);\
DEFINITION(ArcusCosinus);\
DEFINITION(Absolute);\
DEFINITION(Reciprocal);\
DEFINITION(SquareRoot);


#define NULLARY_SHORTHAND(NAME , OP)  \
  template<typename T> void NAME(T & result){ math::operation::Operation<T,math::operation::Nullary,math::operation::scalar::opcodes::OP>::operation(result); }\
  template<typename T> T NAME(){ T result; NAME(result); return result; }\

#define UNARY_SHORTHAND(NAME , OP)   \
  template<typename T> void NAME(T & result, const T & a){math::operation::Operation<T,math::operation::Unary,math::operation::scalar::opcodes::OP>::operation(result, a);}\
  template<typename T> T NAME(const T & a){T result; NAME(result,a); return result;}

#define BINARY_SHORTHAND(NAME , OP)  \
  template<typename T> void NAME(T & result, const T & a,const T & b){T result; math::operation::Operation<T,math::operation::Binary,math::operation::scalar::opcodes::OP>::operation(result, a,b); }\
  template<typename T> T NAME(const T & a,const T & b){T result; NAME(result, a,b); return result; }

namespace nspace{
  
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
  if(value <min){
    value=min;
    return true;
  }
  if(value>max){
    value=max;
    return true;
  }
  return false;
}


  namespace math{
    namespace shorthands{
      namespace scalar{
        // define shorthand functions for all operations
        UNARY_SHORTHAND(signum,Signum);
        UNARY_SHORTHAND(cosine,Cosinus);
        UNARY_SHORTHAND(sine,Sinus);
        UNARY_SHORTHAND(absolute,Absolute);
        UNARY_SHORTHAND(arcusSinus,ArcusSinus);
        UNARY_SHORTHAND(arcusCosinus,ArcusCosinus);
        UNARY_SHORTHAND(squareRoot,SquareRoot);
        UNARY_SHORTHAND(reciprocal,Reciprocal);

        NULLARY_SHORTHAND(e,EulersNumber);
        NULLARY_SHORTHAND(pi,Pi);
        NULLARY_SHORTHAND(squareRootOfTwo,SquareRootOfTwo);
        NULLARY_SHORTHAND(zero,Zero);
      }
    }
  }
  //create shortcut for scalar operation
  namespace scalar = nspace::math::shorthands::scalar;
}
