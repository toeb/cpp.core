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
 
#include <core.math/matrix/operations/MatrixRowCount.h>
#include <core.math/matrix/operations/MatrixColumnCount.h>
#include <core.math/matrix/operations/MatrixTraits.h>
#include <core.math/matrix/operations/MatrixBinaryOperation.h>
#include <core.math/scalar/operations.h>
#include <core.math/scalar/operationcodes.h>
NS_BEGIN(CORE_MATH_NAMESPACE)

  /**
   * \brief elementwise unary operation.
   *        \tparam A the matrix on which to perform the action
   *        \tparam B the operation to perform
   *
   */
  BinaryMatrixOperation(elementWiseUnary);

  /**
   * \brief Element wise unary.
   *
   * \tparam  typename OP Type of the operation OP::operation(b_ij&, (const)a_ij(&)) needs to be defined
   * \tparam  typename A  Type of the input matrix.
   * \tparam  typename B  Type of the output matrix.
   * \param [in,out]  b The output matrix.
   * \param a           The input matrix
   */
  template<typename OP,typename A,typename B> inline void elementWiseUnary(B & b, const A & a);
  template<typename OP,typename A,typename B> inline B elementWiseUnary(const A & a){
    B b; elementWiseUnary<OP>(b,a); return b;
  }
  template<typename OP,typename A> inline auto elementWiseUnary(const A & a)->A {
    return elementWiseUnary<OP,A,A>(a);
  }
  template<typename OP,typename A> inline void elementWiseUnaryInPlace(A & a){
    elementWiseUnary<OP>(a,a);
  }

  /**
   * \brief elementwise unary operation method for a scalar operation code
   *
   * \tparam  math::OperationCode OP  Operation Code.
   * \tparam  typename A              Input matrix type
   * \tparam  typename B              Output matrix type
   * \param [in,out]  b output matrix.
   * \param a           input matrix
   */
  template<typename TOperation,typename A,typename B> inline void elementWiseUnaryScalarOperation(B & b, const A & a){
    elementWiseUnary<TOperation>,A,B>(b,a);
  }
  template<typename TOperation, typename A, typename B> inline B elementWiseUnaryScalarOperation(const A & a){
    B b; elementWiseUnaryScalarOperation<OP>(b,a); return b;
  }
  template<typename TOperation, typename A> inline auto elementWiseUnaryScalarOperation(const A & a)->A {
    return elementWiseUnaryScalarOperation<OP,A,A>(a);
  }
  template<typename TOperation, typename A> inline void elementWiseUnaryScalarOperationInPlace(A & a){
    elementWiseUnary<OP>(a,a);
  }

/**
 * \brief A macro that defines unary element wise scalar matrix operations given the opcode.
 *@TODO: move somewhere else
 * \param OPCODE  The opcode.
 */
#define UnaryElementWiseMatrixOperation(OPCODE) \
  template<typename A,typename B> inline void elementWise ## OPCODE(B & b, const A &a){elementWiseUnaryScalarOperation<math::operation::scalar::opcodes::OPCODE, A, B>(b,a); } \
  template<typename A,typename B> inline B elementWise ## OPCODE(const A &a){B b; elementWise ## OPCODE(b,a); return b; } \
  template<typename A> inline A elementWise ## OPCODE(const A &a) {return elementWise ## OPCODE< A, A>(a); } \
  template<typename A> inline void elementWise ## OPCODE ## InPlace(A & a){elementWise ## OPCODE(a,a); }

  /**
   * \brief Definition of all unary scalar operations as elementwise matrix operations.
   *
   */
  //FOR_ALL_UNARY_SCALAR_OPERATIONCODES(UnaryElementWiseMatrixOperation);


/**
 * \brief Matrix element wise unary.
 */
  template<typename C,typename A,typename OP>
  class MatrixElementWiseUnary {
public:
    static inline void operation(C & c, const A &  a){
      typedef typename indexTypeOfType (C) Index;
      Index rowCount =  rows(c);
      Index colCount = cols(c);
      if(isScalarMatrix<C>()) {
        OP::operation(coefficient(c,0,0),coefficient(a,0,0));
        return;
      }
      for(Index i=0; i < rowCount; i++) {
        for(Index j=0; j <colCount; j++) {
          elementWiseUnary<OP>(coefficient(c,i,j), coefficient(a,i,j));
        }
      }
    }
  };

/**
 * \brief Matrix element wise unary runtime operation.
 */
  template<typename C,typename A,typename OP>
  class MatrixElementWiseUnaryRuntimeOperation {
public:
    static inline void operation(C & c, const A &  a,const OP & operation){
      typedef typename indexTypeOfType (C) Index;
      Index rowCount =  rows(c);
      Index colCount = cols(c);
      if(isScalarMatrix<C>()) {
        coefficient(c,0,0)=operation(coefficient(a,0,0));
        return;
      }
      for(Index i=0; i < rowCount; i++) {
        for(Index j=0; j <colCount; j++) {
          elementWiseUnary(coefficient(c,i,j), coefficient(a,i,j),operation);
        }
      }
    }
  };


//implementations

  template<typename OP,typename A,typename B> inline void elementWiseUnary(B & b, const A & a){
    MatrixElementWiseUnary<B,A,OP>::operation(b,a);
  }
  BinaryOperationImplementation(elementWiseUnary){
    MatrixElementWiseUnaryRuntimeOperation<C,A,B>::operation(c,a,b);
  }
NS_END(CORE_MATH_NAMESPACE)