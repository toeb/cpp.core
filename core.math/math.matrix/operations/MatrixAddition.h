/**
 * Copyright (C) 2013 Tobias P. Becker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the  rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More information at: https://dslib.assembla.com/
 *
 */
#pragma once

#include <math.matrix/operations/MatrixOperations.h>
namespace nspace {

  /**
   * \brief Adds. lhs1:= rhs1+rhs2.
   *
   * \param [in,out]  lhs The left hand side.
   * \param rhs1          The first right hand side.
   * \param rhs2          The second right hand side.
   */
  template<typename LHS, typename RHS1, typename RHS2> void add(LHS & lhs, const RHS1 & rhs1, const RHS2 & rhs2);

  /**
   * \brief Adds rhs1 + rhs2 and returns the resulting matrix
   *
   * \param rhs1  The first right hand side.
   * \param rhs2  The second right hand side.
   *
   * \return  the resulting matrix.
   */
  template<typename T>  T add(const T & rhs1, const T& rhs2);


  /**
   * \brief Matrix addition .
   */
  template<typename Sum, typename Summand1, typename Summand2>
  class MatrixAddition {
public:

    /**
     * \brief Operation adds the a and b into sum.  this is done recursively if need be until scalars are reached
     *
     * \param [in,out]  sum Number of.
     * \param a             The const Summand1 &amp; to process.
     * \param b             The const Summand2 &amp; to process.
     */
    static inline void operation(Sum & sum, const Summand1 & a, const Summand2 & b){
      CoefficientAliasForType(Sum);
      // recursion anchor. 
      if(isScalarMatrix<Sum>()) {
        coefficient(sum,0,0)=coefficient(a,0,0)+coefficient(b,0,0);
        return;
      }
      matrixForEach(sum){
        add(coefficient(sum,i,j),coefficient(a,i,j),coefficient(b,i,j));
      }
    }
  };

  //Implementation
  template<typename LHS, typename RHS1, typename RHS2>
  void add(LHS & lhs, const RHS1 & rhs1, const RHS2 & rhs2){
    MatrixAddition<LHS,RHS1,RHS2>::operation(lhs,rhs1,rhs2);
  }

 
 
  template<typename T>
  T add(const T & rhs1, const T& rhs2){
    T lhs;
    resize(lhs,rhs1);
    add(lhs,rhs1,rhs2);
    return lhs;
  }
  

}
