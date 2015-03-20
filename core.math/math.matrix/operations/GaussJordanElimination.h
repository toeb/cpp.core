#pragma once

#include <math.matrix/operations/MatrixOperations.h>
#include <math.matrix/operations/MatrixMaximumElement.h>
#include <math.matrix/operations/MatrixSwapRows.h>

#include <math.scalar/core.h>
namespace nspace{
  
  /*
  class AlgorithmError{

  };

  class Algorithm{
  public:
    //virtual void operator()()=0;
    static inline void require(bool condition, const std::string & conditiontext){}
  };
  */

  /*
   for k = 1 ... m:
   Find pivot for column k:
   i_max := argmax (i = k ... m, abs(A[i, k]))
   if A[i_max, k] = 0
     error "Matrix is singular!"
   swap rows(k, i_max)
   Do for all rows below pivot:
   for i = k + 1 ... m:
     Do for all remaining elements in current row:
     for j = k + 1 ... n:
       A[i, j] := A[i, j] - A[k, j] * (A[i, k] / A[k, k])
     Fill lower triangular matrix with zeros:
     A[i, k] := 0


  */
  //=matrix2::DynamicMatrix<typename indexTypeOfType(AMatrix)>
  template<typename AMatrix, typename BMatrix>
  MatrixOperationClass(GaussJordan){
    MatrixOperationMethod(AMatrix & A, BMatrix & b){
      using namespace math::shorthands::scalar;
      IndexAliasForType(AMatrix);
      Index m = rows(A);
      Index n = cols(b);
      for(Index k =0; k < m; k++){
        // find pivot element
        Index i_max = indexOfRowMaximum(A,k,[](const AMatrix & matrix, Index i, Index j){return absolute(coefficient(matrix,i,j));} );
        if(coefficient(A,i_max,k)==0){
          throw("matrix is singular");
        }
        // swap rows so that largest element is at 0 position
        swapRows(A, k, i_max);
        swapRows(b, k, i_max);

        for(Index i = k; k < n;i++){
          //for(Index j = k; j < m; k++) 
        }
      }

    }
    /*static void gaussJordanEleminitation(AMatrix & A, BMatrix & b){
      using namespace math::shorthands::scalar;
      // typedefs for index and coefficient type
      CoefficentAndIndexDeclaration(AMatrix);
      // number of equations
      auto n = rows(A);
      // number of b vectors to solve
      auto m = cols(b);
      // vectors for index management
      IndexVector rowIndex,colIndex, iPivot;
      // preconditions
      require(rows(A)==rows(b), "row count of A and b need to be the same");  
      require(rows(A)==cols(A), "Matrix A needs to be a square Matrix");
      require(isScalarMatrix<typename coefficientTypeOfType(AMatrix)>(), "Matrix A's coefficients need to be scalar");
      require(isScalarMatrix<typename coefficientTypeOfType(BMatrix)>(), "Matrix b's coefficients need to be scalar");
      require(ensureVectorDimension(colIndex,n) && ensureVectorDimension(rowIndex,n) && ensureVectorDimension(iPivot,n), "The index vectors need to be of size n");
      // indices
      Index i,j,k,l,ll, iColumn,iRow;

      Coefficient big,dum,inversePivot;

      zeros(iPivot);

      for(i=0; i < n; i++){
        big = 0;
        for(j=0;j<n;j++){
          if(iPivot(j)!=1) 
            for(k=0;k<n;k++){
              // if the pivot element was not yet found for row j...
              if(iPivot(k)==0){
                //... and the pivot element was not found for column k
                // find the largest element
                Coefficient absAjk = absolute(A(j,k));
                if(absAjk >= big){ // \todo element wise inequality
                  big = absAjk;
                  iRow = j;
                  iColumn = k;
                }
              }
            }
        }
        iPivot(iColumn)=1; // pivot element found for icol
        //swap the elements
        if(iRow != iColumn){
          for(l=0;l<n;l++) swap(A(iRow,l),A(iColumn,l));// \todo elementwise swap later on
          for(l=0;l<m;l++) swap(b(iRow,l),b(iColumn,l));
        }
        rowIndex(i) = iRow;
        colIndex(i) = iColumn;
        if(A(iColumn,iColumn) == 0.0) throw("Singular Matrix");
        inversePivot = reciprocal(A(iColumn,iColumn));//\todo elementwise
        A(iColumn,iColumn)=1.0;
        for(l=0;l<n;l++) A(iColumn,l) *= inversePivot;//\todo elementwise
        for(l=0;l<m;l++) b(iColumn,l) *= inversePivot;//\todo elementwise
        for(ll=0;ll<n;ll++){
          if(ll!=iColumn){
            dum=A(ll,iColumn);
            A(ll,iColumn)=0.0;
            for(l=0;l<n;l++)A(ll,l) -= A(iColumn,l)*dum;
            for(l=0;l<m;l++)b(ll,l) -= b(iColumn,l)*dum;
          }
        }

      }
      //restore original ordering
      Index p;
      for(l=n;l>0;l--){// originally it would be easier to say l=2-1 l <=0 l-- however when using unsigned indices this will fail
        p=l-1;
        if(rowIndex(l)!=colIndex(l)){
          for(k=0;k<n;k++)swap(A(k,rowIndex(l)),A(k,colIndex(l)));
        }
      }
    }*/
  };
}