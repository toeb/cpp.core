#pragma once
#include <config.h>
#include <math.matrix/operations/MatrixOperations.h>
#include <math.matrix/operations/MatrixAssignment.h>
namespace nspace{

  template<typename Matrix>
  class MatrixOperationSetConstant{
  public: 
    typedef typename coefficientTypeOfType(Matrix) Coefficient;
    static inline void operation(Matrix & matrix, const Coefficient & c){
      matrixForEach(matrix){
        coefficient(matrix,i,j)=c;
      }
    }
  };

  template<typename Matrix>
  void elementWiseSetConstant(Matrix & matrix, const typename coefficientTypeOfType(Matrix) & c){
    MatrixOperationSetConstant<Matrix>::operation(matrix,c);
  }

  template<typename Matrix>
  Matrix constant( const typename coefficientTypeOfType(Matrix) & c){
    Matrix m;
    //static_assert(RowType(Matrix)!=Dynamic&&ColType(Matrix!=Dynamic))
    elementWiseSetConstant(m,c);
    return m;
  }
  template<typename Matrix>
  Matrix constant(IndexArgument(Matrix) rows, IndexArgument(Matrix) cols, const typename coefficientTypeOfType(Matrix) & c){
    Matrix m;
    ensureMatrixDimension(m,rows,cols);
    return m;
  }





  template<typename T, typename Mat>
  class MatrixSetConstant{
  public:
    static inline void operation(Mat &  result, const T & val){
      for(int i=0; i < result.rows(); i++){
        for(int j=0; j < result.cols(); j++){
          result(i,j)=val;
        }
      }
    }
  };
}