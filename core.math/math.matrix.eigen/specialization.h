/**
 * \file  src\math.matrix.eigen\specialization.h
 *
 * \brief Declares the specialization classes for Eigen::Matrix<...> .
 *        
 *        
 */
#pragma once

#include <math.matrix/MatrixOperations.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#define EigenMatrixTemplateDefinition template<typename T, int Rows, int Cols, int Options, int MaxRows, int MaxCols> 
#define EigenMatrixTemplateSpecialization Eigen::Matrix<T,Rows,Cols,Options,MaxRows,MaxCols>

namespace nspace{
  /**
   * \brief Specialization for MatrixIndexType of Eigen::Matrix<...>
   */ 
  EigenMatrixTemplateDefinition class MatrixIndexType<EigenMatrixTemplateSpecialization>{public: typedef int Type;};

  /**
   * \brief  Specialization for MatrixCoefficientType of Eigen::Matrix<...>
   *
   */
  EigenMatrixTemplateDefinition class MatrixCoefficientType< EigenMatrixTemplateSpecialization >{ public: typedef T Type; };


  EigenMatrixTemplateDefinition class MatrixRowTraits<EigenMatrixTemplateSpecialization >{ public: static const DimensionTraits Traits= Fixed; };
  EigenMatrixTemplateDefinition class MatrixColumnTraits<EigenMatrixTemplateSpecialization >{ public: static const DimensionTraits Traits= Fixed; };

  template<typename T, int Options, int MaxRows, int MaxCols> 
  class MatrixRowTraits<Eigen::Matrix<T,Eigen::Dynamic, Eigen::Dynamic, Options,MaxRows,MaxCols> >{ public :static const DimensionTraits Traits = Dynamic; };
  template<typename T, int Options, int MaxRows, int MaxCols> 
  class MatrixColumnTraits<Eigen::Matrix<T,Eigen::Dynamic, Eigen::Dynamic, Options,MaxRows,MaxCols> >{ public :static const DimensionTraits Traits = Dynamic; };

  template<typename T, int Cols, int Options, int MaxRows, int MaxCols> 
  class MatrixRowTraits<Eigen::Matrix<T,Eigen::Dynamic, Cols, Options,MaxRows,MaxCols> >{ public :static const DimensionTraits Traits = Dynamic; };

  template<typename T, int Rows, int Options, int MaxRows, int MaxCols>
  class MatrixColumnTraits<Eigen::Matrix<T,Rows, Eigen::Dynamic, Options,MaxRows,MaxCols> >{public: static const DimensionTraits Traits = Dynamic;};


  EigenMatrixTemplateDefinition class OperationRowCount<EigenMatrixTemplateSpecialization>{
  public:
    static inline int operation(const EigenMatrixTemplateSpecialization & m){ return m.rows(); }
 
  };
  EigenMatrixTemplateDefinition class OperationColumnCount<EigenMatrixTemplateSpecialization>{
  public:
    static inline int operation(const EigenMatrixTemplateSpecialization & m){ return m.cols(); }
  };

  EigenMatrixTemplateDefinition class OperationMatrixCoefficientAccess<EigenMatrixTemplateSpecialization>{
  public:
    static inline T & operation(EigenMatrixTemplateSpecialization & m, const int & i, const int & j){
      return m(i,j);
    }
    static inline T  operation(const EigenMatrixTemplateSpecialization & m, const int & i, const int & j){
      return m(i,j);
    }  
  };
}