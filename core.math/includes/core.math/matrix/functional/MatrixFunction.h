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
#include <functional>
#include <core.math/core.math.h>

#include <core.math/matrix/MatrixOperations.h>
NS_BEGIN(CORE_MATH_NAMESPACE)

  /**
   * \brief Assign matrix function. this operation assigns a std::function to any matrix
   *        the indices i and j go from 0 to rows(lhs)-1 resp cols(lhs)-1
   *
   * \tparam  typename LHS  Type of the left hand side.
   * \param [in,out]  lhs The left hand side.
   * \param f             The matrix function f(i,j)->B
   *
   * \return  true if it succeeds, false if it fails.
   */
  template<typename LHS> bool assignMatrixFunction(LHS & lhs, const std::function<typename coefficientTypeOfType(LHS) (typename indexTypeOfType(LHS),typename indexTypeOfType(LHS))> & f){
    return assignMatrixBlindly(lhs,f);
  }
    template<typename LHS,typename Functor> bool assignMatrixFunction(LHS & lhs, const Functor & f){
    return assignMatrixBlindly(lhs,std::function<typename coefficientTypeOfType(LHS) (typename indexTypeOfType(LHS),typename indexTypeOfType(LHS))>(f));
    }


  // specializations for matrix framework
  template<typename T, typename Index> class MatrixIndexType<std::function<T(Index,Index)> >{
public:  typedef Index Type;
  };

  /**
   * \brief partial Specialization for columncount of a std::function.
   *
   * \tparam  T     Generic type parameter.
   * \tparam  Index Type of the index.
   */
  template<typename T, typename Index> class OperationColumnCount<std::function<T (Index,Index)> >{
public:

    /**
     * \brief returns 0 the given the matrix function.
     *
     * \param matrix  The matrix.
     *
     * \return  .
     */
    static inline size_t operation(std::function<T(Index,Index)>  matrix){
      return 0;
    }
  };
  template<typename T, typename Index>

  /**
   * \brief Functionpartial specialization for rowcount of a std::function
   *
   * \tparam  T (Index  Type of the ( index.
   * \tparam  Index)    Type of the index)
   */
  class OperationRowCount<std::function<T (Index,Index)> >{
public:
    static inline size_t operation(std::function<T(Index,Index)>  matrix){
      return 0;
    }
  };

  /**
   * \brief partial specialization for coefficienttype of a std::function
   *
   * \tparam  T     Generic type parameter.
   * \tparam  Index Type of the index.
   */
  template<typename T,typename Index> class MatrixCoefficientType<std::function<T(Index,Index)> >{public: typedef T Type;  };
  
  template<typename T, typename Index> class MatrixRowTraits<std::function<T(Index,Index)> >{public: static const DimensionTraits Traits=Infinite;  };
  template<typename T, typename Index> class MatrixColumnTraits<std::function<T(Index,Index)> >{public: static const DimensionTraits Traits=Infinite;  };



  
    template <typename T>
  T&& declval(); // vs2010 does not support std::declval - workaround http://stackoverflow.com/questions/11383722/adl-does-not-work-in-the-specific-situation

  

  template<typename BinaryFunction>
  class MatrixFunction{
    size_t _rows;
    size_t _cols;
    BinaryFunction  _function;

  public:

    ~MatrixFunction(){

    }
  inline auto operator()(size_t i, size_t j)-> decltype(nspace::declval<BinaryFunction>()(i,j)){
      return _function(i,j);
    }
    inline auto operator()(size_t i, size_t j)const->const decltype(nspace::declval<BinaryFunction>()(i,j)){
      return _function(i,j);
    }
    MatrixFunction(size_t rows, size_t cols, BinaryFunction   function):_rows(rows),_cols(cols),_function(function){

    }
    inline size_t rows()const{return _rows;}
    inline size_t cols()const{return _cols;}
  };
  // todo... double is wrong
  template<typename BinaryFunction> SpecializeMatrixCoefficientType(MatrixFunction<BinaryFunction>, double);

  template<typename BinaryFunction>
  auto lazyMatrix(size_t rows, size_t cols, BinaryFunction f)->MatrixFunction<BinaryFunction>{
    return MatrixFunction<BinaryFunction>(rows, cols,f);
  }
NS_END(CORE_MATH_NAMESPACE)
