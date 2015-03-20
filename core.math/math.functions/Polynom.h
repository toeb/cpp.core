#pragma once
#include <config.h>
#include <math/core.h>
#include <math.functions/Function.h>
namespace nspace{
  template<typename TY, typename TCoefficients,typename TXVector = VectorND>
  class Polynom : public Function<TY,Real> {
    TCoefficients _Coefficients;
  public:
    virtual inline bool evaluate(TY & result, const Real & x){
      int n = cols(_Coefficients); // order of the polynom
      int m = rows(_Coefficients); // dimension of the result
      if(!resize(result,m,1))return false;
      Real xi =1;
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

  // operators needed T a, T b;  a < b, a == b
  template<typename T>
  class TypedInterval{
  };

  template<typename TY, typename TX>
  class BoundedFunction : public Function<TY,TX>{
    BASIC_PROPERTY(Interval, Interval,public,,,);
  };

  template<typename TY, typename TCoefficients,typename TXVector = VectorND>
  class NormalizedPolynom : public Polynom<TY,TCoefficients, TXVector>{
    BASIC_PROPERTY(Interval, Interval,public,,,);
    virtual inline bool evaluate(TY & result, const Real & x){
      // normalizes the polyonom
      Real xTilde = (x - getInterval().a)/getInterval().length();
      return Polynom<TY,TCoefficients,TXVector>::evaluate(result,x);
    }
  };
}
