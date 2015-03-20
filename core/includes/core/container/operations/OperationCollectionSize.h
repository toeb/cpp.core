#pragma once
#include <core/core.h>

#include <core/operation/Operation.h>

// macro for easy specialization of operationcollectionsize
// needs to be called insideNS_BEGIN(CORE_NAMESPACE)}
// ASSIGNSIZECODE needs to set SizeType & size variable
#define OperationCollectionSizeSpecialization(COLLECTIONTYPE,SIZETYPE, ASSIGNSIZECODE) \
  OPERATION_SPECIALIZATION(CollectionSize)<COLLECTIONTYPE,SIZETYPE> {\
  SPECIALIZATION (SIZETYPE & size, const COLLECTIONTYPE & collection){{ASSIGNSIZECODE}return true;}\
  };

/*
class OperationCollectionSize<COLLECTIONTYPE, SIZETYPE>{\
public:\
static inline bool operation(SIZETYPE & size, const COLLECTIONTYPE & collection){{ASSIGNSIZECODE}return true;}\
};\
*/
NS_BEGIN(CORE_NAMESPACE)
  template<typename CollectionType, typename SizeType> UNARY_OPERATION(CollectionSize, SizeType & size, const CollectionType & collection, size=0;return false;)
NS_END(CORE_NAMESPACE)
