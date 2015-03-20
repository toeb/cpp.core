#pragma once
#include <config.h>
#include <math.matrix/operations/MatrixDimensionTraits.h>

namespace nspace{
  
  template<typename MatrixType>
  class MatrixRowTraits{
  public:
    static const DimensionTraits Traits = Unknown;
  };

#define SpecializeMatrixRowTraits(TRAIT,TYPE) class MatrixRowTraits<TYPE>{public: static const DimensionTraits Traits = TRAIT;};
#define DefineMatrixRowTraits(TRAIT, TYPE) template<> SpecializeMatrixRowTraits(TRAIT,TYPE)  
#define SpecializeMatrixFixedSizeRows(TYPE)  SpecializeMatrixRowTraits(Fixed,TYPE);
#define SpecializeMatrixDynamicSizeRows(TYPE)  SpecializeMatrixRowTraits(Dynamic,TYPE);
#define SpecializeMatrixInfiniteSizeRows(TYPE)  SpecializeMatrixRowTraits(Infinite,TYPE);
#define DefineMatrixFixedSizeRows(TYPE)  DefineMatrixRowTraits(Fixed,TYPE);
#define DefineMatrixDynamicSizeRows(TYPE)  DefineMatrixRowTraits(Dynamic,TYPE);
#define DefineMatrixInfiniteSizeRows(TYPE)  DefineMatrixRowTraits(Infinite,TYPE);


  template<typename MatrixType> inline DimensionTraits rowTraits(){return MatrixRowTraits<MatrixType>::Traits;}
  template<typename MatrixType> inline DimensionTraits rowTraits(const MatrixType & matrix){return rowTraits<MatrixType>();}

}