#pragma once
#include <core/core.h>

#include <core.operation.h>

// creates a specialization for CollectionItemType
#define SpecializeCollectionItemType(COLLECTIONTYPE)\
  template<typename T>\
class CollectionItemType<COLLECTIONTYPE>{\
public:\
  typedef T ItemType;\
};

NS_BEGIN(CORE_NAMESPACE)
  template<typename CollectionType>
  class CollectionItemType{
  public:
    typedef void ItemType;
  };
NS_END(CORE_NAMESPACE)
