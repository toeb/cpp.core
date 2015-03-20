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

#include <core.math/matrix/operations/MatrixDimensionTraits.h>
NS_BEGIN(CORE_MATH_NAMESPACE)

/**
 * \brief Gets the column traits for the MatrixType.
 *
 * \tparam  typename MatrixType Type of the matrix.
 *
 * \return  the traits of the columns .
 */
 template<typename MatrixType> inline DimensionTraits columnTraits();

/**
 * \brief gets the Column traits for a matrix.
 *
 * \tparam  typename MatrixType Type of the matrix.
 * \param matrix  The matrix.
 *
 * \return  the traits of the columns.
 */
template<typename MatrixType> inline DimensionTraits columnTraits(const MatrixType & matrix);


/**
 * \brief Matrix column traits.
 *        the default implementation defines a matrix type's column trait as unknown
 *        this class should be specialized for Matrix types
 */
template<typename MatrixType>
class MatrixColumnTraits {
public:
  static const DimensionTraits Traits = Unknown;
};

/**
 * \brief A macro that specializes MatrixColumnTraits partially
 *        preprend with template<...>
 *
 * \param TRAIT The trait.(DimensionTraits type)
 * \param TYPE  The type.
 */
#define SpecializeMatrixColumnTraits(TRAIT,TYPE) class MatrixColumnTraits<TYPE>{public: static const DimensionTraits Traits = TRAIT; };

/**
 * \brief A macro that defines matrix column traits for a type (total specialization).
 *
 * \param TRAIT The trait.
 * \param TYPE  The type.
 */
#define DefineMatrixColumnTraits(TRAIT, TYPE) template<> SpecializeMatrixColumnTraits(TRAIT,TYPE)

/**
 * \brief A macro that specializes MatrixColumnTraits as fixed
 *
 * \param TYPE  The type.
 */
#define SpecializeMatrixFixedSizeColumns(TYPE)  SpecializeMatrixColumnTraits(Fixed,TYPE);

/**
 * \brief A macro that specializes MatrixColumnTraits as dynamic
 *
 * \param TYPE  The type.
 */
#define SpecializeMatrixDynamicSizeColumns(TYPE)  SpecializeMatrixColumnTraits(Dynamic,TYPE);

/**
 * \brief A macro that specializes MatrixColumnTraits as Infinite
 *
 * \param TYPE  The type.
 */
#define SpecializeMatrixInfiniteSizeColumns(TYPE)  SpecializeMatrixColumnTraits(Infinite,TYPE);

/**
 * \brief A macro that defines MatrixColumnTraits as Fixed
 *
 * \param TYPE  The type.
 */
#define DefineMatrixFixedSizeColumns(TYPE)  DefineMatrixColumnTraits(Fixed,TYPE);
/**
 * \brief A macro that defines MatrixColumnTraits as Dynamic
 *
 * \param TYPE  The type.
 */
#define DefineMatrixDynamicSizeColumns(TYPE)  DefineMatrixColumnTraits(Dynamic,TYPE);
/**
 * \brief A macro that defines MatrixColumnTraits as Infinite
 *
 * \param TYPE  The type.
 */
#define DefineMatrixInfiniteSizeColumns(TYPE)  DefineMatrixColumnTraits(Infinite,TYPE);

//implementation

template<typename MatrixType> inline DimensionTraits columnTraits(){
  return MatrixColumnTraits<MatrixType>::Traits;
}

template<typename MatrixType> inline DimensionTraits columnTraits(const MatrixType & matrix){
  return columnTraits<MatrixType>();
}
NS_END(CORE_MATH_NAMESPACE)