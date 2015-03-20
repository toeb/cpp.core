#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/operations/MatrixOperations.h>


NS_BEGIN(CORE_MATH_NAMESPACE)

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

NS_END(CORE_MATH_NAMESPACE)
