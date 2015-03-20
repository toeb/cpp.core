#pragma once

#include <math.matrix/operations/MatrixOperations.h>


namespace nspace{

  /**
   * \brief Swap matrices a and b.
   *
   * \tparam  typename MatrixTypeA  Type of   matrix  a.
   * \tparam  typename MatrixTypeB  Type of   matrix  b.
   * \param [in,out]  first matrix
   * \param [in,out]  second matrix
   */
  template<typename MatrixTypeA, typename MatrixTypeB> inline void matrixSwap(MatrixTypeA & a, MatrixTypeB & b);

  template<typename MatrixTypeA, typename MatrixTypeB>
  MatrixOperationClass(Swap){
    MatrixOperationMethod(MatrixTypeA & a, MatrixTypeB &b){
      if(!dimensionsMatch(a,b)){
        return;//false
      }
      
      if(isScalarMatrix<MatrixTypeA>()){
        //todo check if this is ok!
        std::swap(a,b);  
        return;
      }
      matrixForEach(a){
        
        matrixSwap(coefficient(a,i,j),coefficient(b,i,j));
      }
    }
  };


  //implementation
  template<typename MatrixTypeA, typename MatrixTypeB> inline void matrixSwap(MatrixTypeA & a, MatrixTypeB & b){
    OperationMatrixSwap<MatrixTypeA,MatrixTypeB>::operation(a,b);  
  }

}