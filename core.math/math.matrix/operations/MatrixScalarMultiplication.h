#pragma once
#include <config.h>
#include <math.matrix/operations/MatrixOperations.h>
#include <math.matrix/operations/MatrixElementWiseMultiplication.h>

namespace nspace{

  template<typename Product,typename LHS,typename RHS>
  void matrixMultiplyScalar(Product & product, const LHS & lhs, const RHS & rhs);

  template<typename Product, typename LHS,typename RHS>
  MatrixOperationClass(ScalarMultiplication){
    MatrixOperationMethod(Product & product, const LHS &lhs,const RHS &rhs){
      matrixForEach(product){
        multiply(coefficient(product,i,j),coefficient(lhs,i,j),rhs);
      }
    }
    
  };
  
  template<typename Product,typename LHS,typename RHS>
  void matrixMultiplyScalar(Product & product, const LHS & lhs, const RHS & rhs){
    MatrixOperation(ScalarMultiplication)<Product,LHS,RHS>::operation(product,lhs,rhs);
  }

  template<typename LHS,typename RHS>
  LHS matrixMultiplyScalar(const LHS & lhs, const RHS &rhs){
    LHS result;
    matrixMultiplyScalar(result,lhs,rhs);
    return result;
  }
  
  template<typename Product, typename MatrixFactor, typename ScalarFactor>
  class MatrixScalarMultiplication{
  public:
    static inline void operation(Product & product, const MatrixFactor & a, const ScalarFactor & d){
      product.resize(a.rows(),a.cols());
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols(); j++){
          product(i,j)=a(i,j)*d;
        }
      }
    }
  };
}
