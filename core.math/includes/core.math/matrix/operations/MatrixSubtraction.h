#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/operations/MatrixRowCount.h>
#include <core.math/matrix/operations/MatrixColumnCount.h>
#include <core.math/matrix/operations/MatrixCoefficientAccess.h>
#include <core.math/matrix/operations/MatrixTypeSelector.h>

NS_BEGIN(CORE_MATH_NAMESPACE)

/**
 * \brief Subtracts. lhs := b-a
 *
 * \tparam  typename LHS  Type of the left hand side.
 * \tparam  typename A    Type of a.
 * \tparam  typename B    Type of b.
 * \param [in,out]  lhs The left hand side.
 * \param a             The const A &amp; to process.
 * \param b             The const B &amp; to process.
 */
template <typename LHS, typename A, typename B> inline void subtract(LHS & lhs, const A & a, const B & b);

/**
 * \brief Subtracts. c := b-a
 *
 * \tparam  typename C  Type of c.
 * \tparam  typename A  Type of a.
 * \tparam  typename B  Type of b.
 * \param a The const A &amp; to process.
 * \param b The const B &amp; to process.
 *
 * \return  the resulting matrix.
 */
template <typename C, typename A, typename B> inline C subtract(const A & a, const B & b);

/**
 * \brief Returns a type.
 *
 * \tparam  typename A  Type of a.
 * \tparam  typename B  Type of b.
 * \param a The first parameter.
 * \param b The second parameter.
 *
 * \return  the default return type for A,B ;
 */
template <typename A, typename B> inline typename returnType(A,B) subtract(const A & a, const B & b);

  /**
   * \brief Matrix subtraction.  
   */
  template<typename C, typename A, typename B>
  class MatrixSubtraction{
  public:
    static inline void operation(C & c, const A & a, const B & b){
      auto rowCount = rows(c);
      auto colCount = cols(c);
      typedef typename indexTypeOfType(C) Index;
      // insert logic for scalar recursion anchor here
      if(rowCount==1 && colCount==1) {
        coefficient(c,0,0)=coefficient(a,0,0)-coefficient(b,0,0);
        return;
      }
      for(Index i=0; i < rowCount; i++){
        for(Index j=0; j < colCount; j++){
          subtract(coefficient(c,i,j),coefficient(a,i,j),coefficient(b,i,j));
        }
      }
    }
  };

  //implementation 
  
  


template <typename LHS, typename A, typename B> inline void subtract(LHS & lhs, const A & a, const B & b){
  MatrixSubtraction<LHS,A,B>::operation(lhs,a,b);
}
template <typename C, typename A, typename B> inline C subtract(const A & a, const B & b){
  C result;
  subtract(result,a,b);
  return result;
}

template <typename A, typename B> inline typename returnType(A,B) subtract(const A & a, const B & b){
  return subtract<typename returnType(A,B),A,B>(a,b);
}
NS_END(CORE_MATH_NAMESPACE)