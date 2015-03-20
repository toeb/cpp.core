#pragma once
#include <core.math/core.math.h>

#include <core.math/functions/Function.h>
NS_BEGIN(CORE_MATH_NAMESPACE)

  template<typename TY, typename TCoefficients,typename TXVector = VectorND, typename TX=double>
  class Polynom : public Function<TY,TX> {
    TCoefficients _Coefficients;
  public:
    virtual inline bool evaluate(y_type & result, const x_type & x){
      int n = cols(_Coefficients); // order of the polynom
      int m = rows(_Coefficients); // dimension of the result
      if(!resize(result,m,1))return false;
      x_type xi =1;
      TXVector xVec;
      if(!resize(xVec,n,1))return false;

      for(int i=0; i< n; i++){
        math::shorthands::matrix::assignElement(xVec,i,0,xi);
        xi *= x;
      }
      assignMatrix(result, _Coefficients*xVec);
      return true;
    }

    TCoefficients & Coefficients(){
      return _Coefficients;
    }
    const TCoefficients & Coefficients()const{
      return _Coefficients;
    }
    void setCoefficients(const TCoefficients & coeffs){
      _Coefficients = coeffs;
    }
    TCoefficients getCoefficients()const{
      return _Coefficients;
    }
  };


  template<typename TY, typename TX>
  class BoundedFunction : public Function<TY,TX>{
    BASIC_PROPERTY(Interval, Interval,public,,,);
  };

  template<typename TY, typename TCoefficients,typename TXVector = VectorND, typename TX = double>
  class NormalizedPolynom : public Polynom<TY,TCoefficients, TXVector,TX>{
    BASIC_PROPERTY(Interval, Interval,public,,,);
    virtual inline bool evaluate(y_type & result, const x_type & x){
      // normalizes the polyonom
      x_type xTilde = (x - getInterval().a)/getInterval().length();
      return Polynom<y_type,TCoefficients,TXVector>::evaluate(result,x);
    }
  };
NS_END(CORE_MATH_NAMESPACE)
