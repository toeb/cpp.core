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
#include <core.math/core.math.h>


#include <core.math/matrix/operations/MatrixIndexType.h>
#include <core.math/matrix/operations/MatrixRowCount.h>
#include <core.math/matrix/operations/MatrixColumnCount.h>
#include <core.math/matrix/operations/MatrixDimensionCheck.h>
#include <core.math/matrix/operations/MatrixCoefficientAccess.h>

NS_BEGIN(CORE_MATH_NAMESPACE)
/**
 * \brief Matrix assign.
 *        the default implementation checks for dimension match and returns false if the dimensions do not match
 *        then every coefficient is copied in a boxed for loop
 */
 template<typename LHS, typename RHS>
class OperationMatrixAssign {
public:

  /**
   * \brief Operation  copies all coefficients from rhs to lhs.  disregards any dimension mismatch
   *        if the rowcount of rhs is 0 then operaiton tries to get the ros from the left hand side
   *        same for colcount.  the reasoning is as follows:  there are matrices where the dimensions are unknown
   *        for example lazy matrices were every element is calculated only when needed: f: N xN -> B.
   *        in such a case the left hand side's dimension is used for defining the dimension
   *        @TODO: Use Row and Columntraits for correct behaviour
   *
   * \param [in,out]  lhs The left hand side.
   * \param rhs           The right hand side.
   *
   * \return  true if it succeeds, false if it fails.
   */
  static inline bool operation(LHS &  lhs, const RHS & rhs){
    typename indexTypeOfType(RHS) rowCount = rows(rhs);
    if (!rowCount)rowCount = rows(lhs);
    typename indexTypeOfType(RHS) colCount = cols(rhs);
    if (!colCount)colCount = cols(lhs);
    for (typename indexTypeOfType(RHS) i = 0; i < rowCount; i++) {
      for (typename indexTypeOfType(RHS) j = 0; j < colCount; j++) {
        coefficient(lhs, i, j) = coefficient(rhs, i, j);
      }
    }
    return true;
  }
};

/**
 * \brief Blind assign matrix. assigns matrix lhs:=rhs.  disregards any dimension mismatches
 *
 * \tparam  typename LHS  Type of the  left hand side.
 * \tparam  typename RHS  Type of the  right hand side.
 * \param [in,out]  lhs The left hand side.
 * \param rhs           The right hand side.
 *
 * \return  true if it succeeds, false if it fails.
 */
template<typename LHS, typename RHS> inline bool assignMatrixBlindly(LHS & lhs, const RHS & rhs){
  return OperationMatrixAssign<LHS, RHS>::operation(lhs, rhs);
}

/**
 * \brief Assign matrix. operation for assigning matrices
 *
 * \tparam  typename LHS  Type of the left hand side.
 * \tparam  typename RHS  Type of the right hand side.
 * \param [in,out]  lhs The left hand side.
 * \param rhs           The right hand side.
 *
 * \return  true if it succeeds, false if it fails (e.g. The dimensions mismatch).
 */
template<typename LHS, typename RHS> inline bool assignMatrix(LHS & lhs, const RHS & rhs){
  if (!dimensionsMatch(lhs, rhs))return false;
  return assignMatrixBlindly(lhs, rhs);
}

/**
 * \brief Force assign matrix. assigns lhs := rhs
 *        if the left hand side matrix does not have the same dimensions as rhs it is resized.
 *        if anything fails along the way false is returned
 *
 * \tparam  typename LHS  Type of the typename left hand side.
 * \tparam  typename RHS  Type of the typename right hand side.
 * \param [in,out]  lhs The left hand side.
 * \param rhs           The right hand side.
 *
 * \return  true if it succeeds, false if it fails.
 */
template<typename LHS, typename RHS> inline bool assignMatrixForced(LHS & lhs, const RHS & rhs){
  if (!resize(lhs, rhs))return false;
  return assignMatrixBlindly(lhs, rhs);
}

/**
 * \brief Converts the given right hand side to a matrix of type LHS.
 *
 * \tparam  typename LHS  Type of the  left hand side.
 * \tparam  typename RHS  Type of the  right hand side.
 * \param rhs The right hand side.
 *
 * \return the converted matrix .
 */
template<typename LHS, typename RHS> inline LHS convert(const RHS & rhs){
  LHS lhs;
  assignMatrix(lhs, rhs);
  return lhs;
}


/**
 * \brief A macro that specializes the OperationMatrixAssign for LHS and RHS types.
 *        be sure to return true if the assignement was successfull . else false is returned by default
 *        this only works for types that do not contains commas
 *
 * \param LHS             The left hand side matrix.
 * \param RHS             The right hand side matrix.
 * \param ASSIGNMENTCODE  The assignmentcode.
 */
#define BeginSpecializeMatrixAssign(LHS,RHS) class OperationMatrixAssign<LHS,RHS>{public: static inline bool operation(LHS & lhs, const RHS &rhs)
#define EndSpecializeMatrixAssign };

NS_END(CORE_MATH_NAMESPACE)