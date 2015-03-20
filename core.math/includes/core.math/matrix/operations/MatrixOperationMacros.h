#pragma once

#define ARG_IN(TYPE) const TYPE &
#define ARG_OUT(TYPE) TYPE &

#define NamedCoefficientAliasForType(TYPE, ALIAS) typedef typename coefficientTypeOfType(TYPE) ALIAS;
#define NamedCoefficientAliasForInstance(INSTANCE,ALIAS) NamedCoefficientAliasForType( decltype(INSTANCE), ALIAS);
#define NamedIndexAliasForType(TYPE, ALIAS)  typedef typename indexTypeOfType(TYPE) ALIAS;
#define NamedIndexAliasForInstance(INSTANCE,ALIAS) NamedIndexAliasForType( decltype(INSTANCE),ALIAS);
#define IndexAliasForType(TYPE) NamedIndexAliasForType(TYPE, Index)
#define IndexAliasForInstance(INSTANCE) NamedIndexAliasForInstance(INSTANCE, Index)
#define CoefficientAliasForType(TYPE) NamedCoefficientAliasForType(TYPE,Coefficient)
#define CoefficientAliasForInstance(INSTANCE) NamedCoefficientAliasForInstance(INSTANCE,Coefficient)
#define CoefficientAndIndexAliasForType(TYPE) IndexAliasForType(TYPE) CoefficientAliasForType(TYPE)
#define CoefficientAndIndexAliasForInstance(INSTANCE) IndexAliasForInstance(TYPE) CoefficientAliasForInstance(TYPE)

// maybe this is wron. in parallel environments const refs to indices could have unexpected results.
#define IndexArgument(MATRIXTYPE) ARG_IN(typename indexTypeOfType(MATRIXTYPE))

#define matrixForEachRow(MATRIX)\
  NamedIndexAliasForInstance(MATRIX,RowIndex)\
  RowIndex rowCount = rows(MATRIX);\
  for(RowIndex i =0; i < rowCount; i++)

#define matrixForEachColumn(MATRIX)\
  NamedIndexAliasForInstance(MATRIX,ColIndex)\
  ColIndex colCount = cols(MATRIX);\
  for(ColIndex j = 0; j < colCount; j++)

#define matrixForEach(MATRIX)\
  IndexAliasForInstance(MATRIX);\
  Index rowCount= rows(MATRIX);\
  Index colCount= cols(MATRIX);\
  for(Index i = 0; i < rowCount; i++)\
    for(Index j =0; j < colCount; j++)




#define DefineMatrixRowCount(TYPE) template<> inline indexTypeOfType(TYPE) OperationRowCount<TYPE>::operation(const TYPE & matrix)
#define DefineMatrixColumnCount(TYPE) template<> inline indexTypeOfType(TYPE) OperationColumnCount<TYPE>::operation(const TYPE & matrix)
#define DefineMatrixCoefficientReferenceAccess(TYPE) template<> inline coefficientTypeOfType(TYPE) & OperationMatrixCoefficientAccess<TYPE>::operation(TYPE & matrix, IndexArgument(TYPE) i, IndexArgument(TYPE) j)
#define DefineMatrixCoefficientValueAccess(TYPE) template<> inline coefficientTypeOfType(TYPE) OperationMatrixCoefficientAccess<TYPE>::operation(const TYPE & matrix, IndexArgument(TYPE) i, IndexArgument(TYPE) j)
#define DefineMatrixCoefficientAccess(TYPE) \
  DefineMatrixCoefficientReferenceAccess(TYPE);\
  template<> inline coefficientTypeOfType(TYPE) OperationMatrixCoefficientAccess<TYPE>::operation(const TYPE & matrix, IndexArgument(TYPE) i , IndexArgument(TYPE) j){return OperationMatrixCoefficientAccess<TYPE>::operation(const_cast<TYPE & >(matrix),i,j);}\
  DefineMatrixCoefficientReferenceAccess(TYPE)

/**
 * \brief A macro that declares a matrix type's template sepcialization.
 *        with this the MATRIXTYPE is declared as a Matrix which Index is of type
 *        INDEXTYPE, the coefficients are of type COEFFICIENTTYPE.
 *        The ROWCOUNT and COLCOUNT codes should return the number of rows and columns are available
 *        Directly at the end the closure (matrix&, const i, const j )->COEFFICIENTTYPE{} for accessing a mutable reference to 
 *        matrix' coefficient at i,j needs to be added 
 *
 * \param MATRIXTYPE      The matrixtype.
 * \param INDEXTYPE       The indextype.
 * \param COEFFICIENTTYPE The coefficienttype.
 * \param ROWCOUNT(const MATRIXTYPE & matrix)   shall return the row count of matrix.
 * \param COLCOUNT(const MATRIXTYPE & matrix)   shall return the column count of matrix.
 */
#define DeclareMatrixType(MATRIXTYPE, INDEXTYPE, COEFFICIENTTYPE, ROWCOUNT, COLCOUNT)\
DeclareMatrixIndexType(MATRIXTYPE, INDEXTYPE);\
  DefineMatrixRowCount(MATRIXTYPE){ROWCOUNT;}\
  DefineMatrixColumnCount(MATRIXTYPE){COLCOUNT;}\
  DeclareMatrixCoefficientType(MATRIXTYPE, COEFFICIENTTYPE);\
  DefineMatrixRowTraits(Fixed,MATRIXTYPE)\
  DefineMatrixColumnTraits(Fixed,MATRIXTYPE)\
  DefineMatrixCoefficientAccess(MATRIXTYPE)
