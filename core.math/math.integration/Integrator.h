#include <config.h>

#include <math.matrix.h>
namespace nspace{
  namespace math{
    namespace integration{
      
      namespace operators{
        template<typename LHS, typename RHS>
        auto operator +(const LHS &lhs, const RHS & rhs)->typename returnType(RHS,LHS){          
          return add(lhs,rhs);
        }
        template<typename LHS>
        auto operator *(const LHS & lhs, const typename coefficientTypeOfType(LHS) & rhs)->typename LHS{
          LHS result;
        }
      }

      template<typename X, typename F,typename H, unsigned int Algorithm=0>
      class IterationRule{
      public:
        inline X step(const F & f,X x,H h){
          return x;
        }
      };
#define EXPLICIT_EULER 0
      template<typename X, typename F,typename H>
      class IterationRule<X,F,H,EXPLICIT_EULER>{
      public:
        inline X step(const F & f, X x, H h){
          x = add(x,multiply(f(x),h));
        }
      };



      template<typename X, typename F,typename H, unsigned int Algorithm=0>
      class InitialValueProblem{
      public:
        InitialValueProblem(const F & f, x
      };



    }
  }
}