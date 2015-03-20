#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/operations/MatrixIndexType.h>
#include <core.math/matrix/operations/MatrixRowCount.h>
#include <core.math/matrix/operations/MatrixColumnCount.h>
NS_BEGIN(CORE_MATH_NAMESPACE)  

  /**
   * \brief Values that represent IndexMappings.
   */
  enum IndexMapping{
    RowMajor,
    ColumnMajor
  };

  /**
   * \brief Maps indices (i,j)in NxN to i, element of N.
   *
   * \tparam  typename MatrixType Type of the  matrix .
   * \param matrix  The matrix.
   * \param i       row index
   * \param j       the column index
   * \param mapping (optional) the mapping. (default = RowMajor)
   *
   * \return  the 1d index.
   */
  template<typename MatrixType> inline auto mapIndex(const MatrixType & matrix, const typename indexTypeOfType(MatrixType) & i, const typename indexTypeOfType(MatrixType) & j, IndexMapping mapping=RowMajor)->typename indexTypeOfType(MatrixType){
    if(mapping==ColumnMajor){
      auto rowCount = rows(matrix);
      return rowCount * j+i;
    }    
    auto columnCount = cols(matrix);
    return columnCount*i+j;
  }

  /**
   * \brief maps a 1d index to the rowindex of the matrix given the mapping.
   *        
   *
   * \tparam  typename MatrixType Type of the  matrix .
   * \param matrix the matrix.
   * \param i the 2d index
   * \param mapping(optional) the index mapping default is RowMajor
   *                          
   * \return the row index .
   */
  template<typename MatrixType> inline auto mapRowIndex(const MatrixType & matrix, const typename indexTypeOfType(MatrixType) & i, IndexMapping mapping=RowMajor)->typename indexTypeOfType(MatrixType){
    if(mapping == ColumnMajor){
      auto rowCount = rows(matrix);
      if(rowCount==1)return 0;
      return i / rowCount;
    }
    auto columnCount = cols(matrix);
    if(columnCount==1)return i;
    return i % columnCount;
  }
  /**
   * \brief maps a 1d index to the column index of the matrix given the mapping.
   *        
   *
   * \tparam  typename MatrixType Type of the  matrix .
   * \param matrix the matrix.
   * \param i the 2d index
   * \param mapping(optional) the index mapping default is RowMajor
   *
   * \return the column index .
   */
  template<typename MatrixType> auto mapColumnIndex(const MatrixType & matrix, const typename indexTypeOfType(MatrixType) & i, IndexMapping mapping=RowMajor)->typename indexTypeOfType(MatrixType){
     if(mapping == ColumnMajor){
      auto rowCount = rows(matrix);
      if(rowCount==1)return i;
      return i % rowCount;
    }
    auto columnCount = cols(matrix);
    if(columnCount==1)return 0;
    return i / columnCount;
  }
NS_END(CORE_MATH_NAMESPACE)