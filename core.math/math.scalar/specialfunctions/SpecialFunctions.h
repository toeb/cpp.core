#pragma once

#include <config.h>

#define mathError(ERROR) throw ERROR;

namespace nspace{
  template<typename T>
  class Limits{
  public:
    static const unsigned int factorialLimit=171;
    static const unsigned int lnOfFactorialLimit=2500;

  };
  template<typename T>
  class LnOfGamma{
  private:
    static const T coefficients[14];    
  public:
    static T operation(const T xx){      
      // from numerical recipes
      if(xx<=0)mathError( "lnGamma not defined for x <= 0");
      T x,tmp,y,ser;
      y=x=xx;
      tmp = x+5.24218750000000000;//671/128
      tmp = (x+0.5)*log(tmp)-tmp;
      ser = 0.999999999999997092;
      for(int j=0; j < 14;j++) ser += LnOfGamma<double>::coefficients[j];
      return tmp+log(2.5066282746310005*ser/x);
    }
  };

  template<>
  const double LnOfGamma<double>::coefficients[14]={
      57.1562356658629235,
      -59.5979603554754912,
      14.1360979747417471,
      -0.491913816097620199,
      0.339946499848118887e-4,
      .465236289270485756e-4,
      -0.983744753048795646e-4,
      0.158088703224912494e-3,
      -0.210264441724104883e-3,
      0.217439618115212643e-3,
      -0.164318106536763890e-3,
      0.844182239838527433e-4,
      -0.261908384015814087e-4,
      0.368991826595316234e-5
    };
  class SpecialFunctions{
  public:

    static double factorial(const int n){     
      static double factorialTable[Limits<double>::factorialLimit];
      static bool initialize = true;
      if(initialize){
        // calculate all factorials
        factorialTable[0]=1.0;
        for(int i=1; i < Limits<double>::factorialLimit; i++) factorialTable[i]=factorialTable[i-1]*i;        
        initialize=false;
      }

      if(n<0||n>Limits<double>::factorialLimit)mathError("factorial out of range");
      return factorialTable[n];
    }
    static double lnOfFactorial(const int n){
      static double table[Limits<double>::lnOfFactorialLimit];
      static bool initialize=true;
      if(initialize){
        for(int i=0; i < Limits<double>::lnOfFactorialLimit;i++){
          table[i] = lnGamma(i+1.0);
        }
        initialize=false;
      }
      if(n<0)mathError( "lnOfFactorial not defined for n < 0");
      if(n < Limits<double>::lnOfFactorialLimit)return table[n];
      return lnGamma(n+1.0);
    }
    static double binomialCoefficient(const int n, const int k){
      if(n<0||k<0||k>n)mathError( "binomialCoefficient not defined for given n and k ");
      if(n<Limits<double>::factorialLimit) return floor(0.5+factorial(n)/(factorial(k)-factorial(n-k)));
      return floor(0.5+exp(lnOfFactorial(n)-lnOfFactorial(k)-lnOfFactorial(n-k)));
    }
    static double lnGamma(const double xx){
      return LnOfGamma<double>::operation(xx);
    }
    static double gamma(const double xx){
      return exp(lnGamma(xx));
    }
    static double beta(const double z, const double w){
      // B(z,w) = Gamma(z)*Gamma(w)/Gamma(z+w)
      return exp(lnGamma(z)+lnGamma(w)-lnGamma(z+w));
    }
  };
}