#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/operations/MatrixDimensionTraits.h>

NS_BEGIN(CORE_MATH_NAMESPACE)

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


template<typename MatrixType> inline DimensionTraits rowTraits(){ return MatrixRowTraits<MatrixType>::Traits; }
template<typename MatrixType> inline DimensionTraits rowTraits(const MatrixType & matrix){ return rowTraits<MatrixType>(); }

NS_END(CORE_MATH_NAMESPACE)