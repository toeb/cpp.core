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
   * \brief Transposes.
   *
   * \tparam  typename AT Type of th resulting transposed matrix.
   * \tparam  typename A  Type of the input matrix a.
   * \param [out]  at  the resulting transposed matrix.
   * \param a             The matrix to transpose.
   */
  template<typename AT, typename A> inline void transpose(AT & at, const A & a);



  /**
   * \brief Transposes a matrix. The Matrix AT may not be the  same matrix as AT
   *        use MatrixTransposeInplace instead
   *        \todo implement transpose inplace, transpose squared in place
   *
   * \tparam  typename MatrixTypeAT Type of the typename matrix type a t.
   * \tparam  typename MatrixTypeA  Type of the typename matrix type a.
   * \param parameter1  The first parameter.
   */
  template<typename MatrixTypeAT, typename MatrixTypeA>
  MatrixOperationClass(Transpose){
    MatrixOperationMethod(MatrixTypeAT & AT, const MatrixTypeA &A){

      if(isScalarMatrix<MatrixTypeAT>()) {
        // scalars are already transposed
        assignMatrixBlindly(AT,A);
        return;
      }
      // if A is MxN then AT needs to be NxM
      if(!ensureMatrixDimension(AT,cols(A),rows(A))) {
        throw "Transpose: cannot ensure needed matrix dimensions";
      }
      // actually transpose the matrix
      matrixForEach(A){
        transpose(coefficient(AT,j,i),coefficient(A,i,j));
      }
    }
  };
  template<typename AT, typename A> inline void transpose(AT & at, const A & a){
    OperationMatrixTranspose<AT,A>::operation(at,a);
  }
}
