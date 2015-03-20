#pragma once
#include <core/core.h>
#include <core.operation.h>

// this macro helps specialize item access
// implementation example:
// CollectionItemAccessSpecialization(int, int*, int, *item = &collection[index])
#define CollectionItemAccessSpecialization(ITEMTYPE,COLLECTIONTYPE,INDEXTYPE, ACCESSITEMCODE)\
  OPERATION_SPECIALIZATION(CollectionItemAccess)<ITEMTYPE,COLLECTIONTYPE,INDEXTYPE>{\
  SPECIALIZATION(ITEMTYPE & item,COLLECTIONTYPE & collection ,const INDEXTYPE& index){if(item==0)return false; {ACCESSITEMCODE;} return true;}\
  };

NS_BEGIN(CORE_NAMESPACE)
  template<typename ItemType, typename CollectionType, typename IndexType>
  BINARY_OPERATION(CollectionItemAccess, ItemType & item,CollectionType & collection ,const IndexType& index,{return false;});

  template<typename ItemType, typename CollectionType, typename IndexType>
  BINARY_OPERATION(CollectionPointerAccess, ItemType ** item,CollectionType & collection ,const IndexType& index,{item=0; return false;});
NS_END(CORE_NAMESPACE)

