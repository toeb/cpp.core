#pragma once

#include <math.matrix/operations/MatrixColumnTraits.h>
#include <math.matrix/operations/MatrixRowTraits.h>
#include <math.matrix/operations/MatrixCoefficientAccess.h>
#include <math.matrix/operations/MatrixTypeSelector.h>
#include <math.matrix/operations/MatrixBinaryOperation.h>
namespace nspace{
  /**
   * \brief multiplies two matrices together element wise $\f \mathbf{c}_{ij} := \mathbf{a}_{ij}\dot \mathbf{b}_{ij} $\f
   *
   */
  BinaryMatrixOperation(multiply);

template<typename C,typename A, typename B>
class MatrixElementWiseMultiply{
public:
  static inline void operation(C & c, const A &  a, const B & b){
    typedef typename indexTypeOfType(C) Index;
    Index rowCount =rows(c);
    Index colCount =cols(c);

    // template recursion anchor 
    if(isScalarMatrix<C>()){   
      coefficient(c,0,0)=coefficient(a,0,0)*coefficient(b,0,0);
      return;
    }

    for(Index i=0; i < rowCount; i++){
      for(Index j=0; j < colCount; j++){
        multiply(coefficient(c,i,j),coefficient(a,i,j),coefficient(b,i,j));
      }
    }
  }
};

/**
 * \brief implements multiply(c,a,b) method.
 * 
 */
BinaryOperationImplementation(multiply){MatrixElementWiseMultiply<C,A,B>::operation(c,a,b);}

}
