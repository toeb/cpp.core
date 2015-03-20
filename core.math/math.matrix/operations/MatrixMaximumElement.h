#pragma once
#include <config.h>
#include <math.matrix/operations/MatrixOperations.h>

  
namespace nspace{
  template<typename MatrixType, typename Functor, typename IndexA, typename IndexB>
  inline void indexOfMaximum(const MatrixType & matrix, IndexA & iMax, IndexB & jMax,const Functor & functor){
    CoefficientAliasForType(MatrixType);
    iMax=0; jMax=0;
    Coefficient currentMaxValue = functor(matrix,0,0);
    Coefficient currentValue;
   
      matrixForEach(matrix){
        currentValue = functor(matrix,i,j);
        if(currentValue > currentMaxValue){
          currentMaxValue = currentValue;
          iMax = i;
          jMax = j;
        }
      }
  }

  
  template<typename MatrixType, typename Functor>
  inline typename indexTypeOfType(MatrixType) indexOfColumnMaximum(const MatrixType & matrix, IndexArgument(MatrixType) j, const Functor & functor){
    CoefficientAndIndexAliasForType(MatrixType);
    Coefficient currentMaxValue=functor(matrix,0,j);
    Coefficient currentValue;
    Index currentMaxIndex=0;
    matrixForEachRow(matrix){
      currentValue = functor(matrix,i,j);
      if(currentValue > currentMaxValue){
        currentMaxIndex = i;
        currentMaxValue = currentValue;
      }
    }
    return currentMaxIndex;

  }

  


  template<typename MatrixType, typename Functor>
  inline typename indexTypeOfType(MatrixType) indexOfRowMaximum(const MatrixType & matrix, IndexArgument(MatrixType) i, const Functor & functor){
   CoefficientAndIndexAliasForType(MatrixType);
    Coefficient currentMaxValue=functor(matrix,i,0);
    Coefficient currentValue;
    Index currentMaxIndex=0;
    matrixForEachColumn(matrix){
      currentValue = functor(matrix,i,j);
      if(currentValue > currentMaxValue){
        currentMaxIndex = j;
        currentMaxValue = currentValue;
      }
    }
    return currentMaxIndex;
  }


  


  template<typename ScalarResult, typename MatrixInput>
  class MatrixMaximumElement{
  public:
    static inline void operation(ScalarResult & maximum, const MatrixInput & mat){
      maximum = mat(0,0);
      for(int i=0; i < mat.rows();i++){
        for(int j=0; j < mat.cols();j++){
          if(maximum < mat(i,j))maximum=mat(i,j);
        }
      }
    }
  };
}
