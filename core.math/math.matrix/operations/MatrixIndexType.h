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

#include <config.h>
namespace nspace {
  
/**
 * \brief A macro that is replaced by the index typ of MATRIXTYPE
 *
 * \param MATRIXTYPE  The matrixtype.
 */
#define indexTypeOfType(MATRIXTYPE)  MatrixIndexType<MATRIXTYPE>::Type

/**
 * \brief A macro that is replaced by the index type of the MATRIXINSTANCE rvalue
 *
 * \param MATRIXINSTANCE  The matrixinstance.
 */
#define indexTypeOfInstance(MATRIXINSTANCE) indexTypeOfType( decltype(MATRIXINSTANCE))


/**
 * \brief Matrix index type.  has one typedef called Type which contains the type used for MatrixType's Indices
 *        the default Index type is unsigned int.  Matrix classes may specialize this template
 */
  template<typename MatrixType>
  class MatrixIndexType {
public:
    typedef unsigned int Type;
  };

/**
 * \brief A macro that defines partial matrix index type specialization
 *
 * \param MATRIXTYPE  The matrixtype.
 * \param INDEXTYPE   The indextype.
 */
#define SpecializeMatrixIndexType(MATRIXTYPE,INDEXTYPE) class MatrixIndexType<MATRIXTYPE>{public: typedef INDEXTYPE Type; };

/**
 * \brief A macro that defines full matrix index type specialization.
 *
 * \param MATRIXTYPE  The matrixtype.
 * \param INDEXTYPE   The indextype.
 */
#define DeclareMatrixIndexType(MATRIXTYPE,INDEXTYPE) template<> SpecializeMatrixIndexType(MATRIXTYPE,INDEXTYPE)

}