#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/operations/MatrixIndexType.h>
#include <core.math/matrix/operations/MatrixTypeSelector.h>
#include <core.math/matrix/operations/MatrixColumnTraits.h>
#include <core.math/matrix/operations/MatrixRowTraits.h>
#include <core.math/matrix/operations/MatrixTraits.h>
NS_BEGIN(CORE_MATH_NAMESPACE)
  
  template<typename T, size_t n> SpecializeMatrixIndexType(T[n],size_t);
  template<typename T, size_t n> SpecializeMatrixFixedSizeRows(T[n]);
  template<typename T, size_t n> SpecializeMatrixFixedSizeColumns(T[n]);
  template<typename T, size_t n> SpecializeMatrixCoefficientType(T[n],typename  std::remove_const<T>::type);
  
  
  template<typename T, size_t n,typename MatrixType> SpecializeTypeSelectorPartially(T[n],MatrixType,MatrixType);
  template<typename T, size_t n> class MatrixTypeSelector<T[n],T[n]>{public: typedef T Type[n];}; 

  
  template<typename T, size_t n,size_t m> SpecializeMatrixIndexType(T[n][m],size_t);
  template<typename T, size_t n,size_t m> SpecializeMatrixFixedSizeRows(T[n][m]);
  template<typename T, size_t n,size_t m> SpecializeMatrixFixedSizeColumns(T[n][m]);
  template<typename T, size_t n,size_t m> SpecializeMatrixCoefficientType(T[n][m],typename  std::remove_const<T>::type);
  template<typename T, size_t n,size_t m> class MatrixTraitTransposedType<T[n][m]>{public: typedef T Type[m][n];};
  template<typename T, size_t n,size_t m> class MatrixTypeSelector<T[n][m],T[n][m]>{public : typedef T Type[m][n];};
  template<typename T, size_t n,size_t m,typename MatrixType> SpecializeTypeSelectorPartially(T[n][m],MatrixType,MatrixType);


  template<typename T> SpecializeMatrixIndexType(T*, size_t);
  template<typename T> SpecializeMatrixCoefficientType(T*, typename std::remove_const<T>::type);
  template<typename T, typename MatrixType> SpecializeTypeSelectorPartially(T*,MatrixType,MatrixType);
  
  template<typename T> 
  class OperationMatrixCoefficientAccess<T*>{
  public:
    static inline T & operation(T*  matrix,size_t  i,size_t j){
      return matrix[i];
    }
    static inline T operation(const T* matrix,size_t i, size_t  j){
      return matrix[i];
    }
  };
  template<typename T> 
  class OperationMatrixCoefficientAccess<T**>{
  public:
    static inline T & operation(T**  matrix,size_t  i,size_t j){
      return matrix[i][j];
    }
    static inline T operation(const T** matrix,size_t i, size_t  j){
      return matrix[i][j];
    }
  };

  
  
  
  template<typename T> SpecializeMatrixIndexType(T**, size_t);
  template<typename T> SpecializeMatrixCoefficientType(T**, typename std::remove_const<T>::type);
  template<typename T, typename MatrixType> SpecializeTypeSelectorPartially(T**,MatrixType,MatrixType);
  
  
  // specialization for 2d array
  // specializeation for 1d array

  

  // specializations

  
  /**
   * \brief specialization for const size 2d array.
   *
   * \tparam  T[n][m] Type of the [n][m].
   */
  template<typename T, size_t n, size_t m>
  class OperationMatrixCoefficientAccess<T[n][m]>{
public:
    static inline typename coefficientTypeOfType(T[n][m]) & operation(T (&matrix)[n][m],const typename indexTypeOfType(T[n][m]) & i,const typename indexTypeOfType(T[n][m]) & j){
      return matrix[i][j];
    }

    static inline typename coefficientTypeOfType(T[n][m]) operation(const T (&matrix)[n][m],const typename indexTypeOfType(T[n][m]) &i, const typename indexTypeOfType(T[n][m]) & j){
      return matrix[i][j];
    }
  };
  template<typename T, size_t n, size_t m>
  class OperationMatrixCoefficientAccess<const T[n][m]>{
public:
    static inline typename coefficientTypeOfType(T[n][m]) & operation(T (&matrix)[n][m],const typename indexTypeOfType(T[n][m]) & i,const typename indexTypeOfType(T[n][m]) & j){
      return matrix[i][j];
    }

    static inline typename coefficientTypeOfType(T[n][m]) operation(const T (&matrix)[n][m],const typename indexTypeOfType(T[n][m]) &i, const typename indexTypeOfType(T[n][m]) & j){
      return matrix[i][j];
    }
  };


  /**
   * \brief specialization for 1d array which is understood as a column  vector ie 1 column.
   *        
   * \tparam  T Generic type parameter.
   * \tparam  n Type of the n.
   */
  template<typename T, size_t n>
  class OperationMatrixCoefficientAccess<T[n]>{
  public:
    static inline  T & operation(T (&matrix)[n],const typename indexTypeOfType(T[n]) & i,const typename indexTypeOfType(T[n]) & j){
      return matrix[i];
    }
    static inline T operation(const T (&matrix )[n],const typename indexTypeOfType(T[n]) &i, const typename indexTypeOfType(T[n]) & j){
      return matrix[i];
    }
  };

  
  template<typename T, size_t n>
  class OperationMatrixCoefficientAccess<const T[n]>{
  public:
    static inline T & operation(T (&matrix)[n],const typename indexTypeOfType(T[n]) & i,const typename indexTypeOfType(T[n]) & j){
      return matrix[i];
    }
    static inline  T operation(const T (&matrix )[n],const typename indexTypeOfType(T[n]) &i, const typename indexTypeOfType(T[n]) & j){
      return matrix[i];
    }
  };



NS_END(CORE_MATH_NAMESPACE)
