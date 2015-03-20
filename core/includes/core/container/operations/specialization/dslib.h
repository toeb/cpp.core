#pragma once
#include <core/core.h>

#include <core/container/operations/OperationCollectionSize.h>
#include <core/container/operations/OperationCollectionItemType.h>
#include <core/container/Set.h>
NS_BEGIN(CORE_NAMESPACE)
  SpecializeCollectionItemType(Set<T>);

  template<typename T, typename IndexType> OperationCollectionSizeSpecialization(Set<T>,IndexType, size=collection.size(););
  template<typename T, typename IndexType> CollectionItemAccessSpecialization(T,Set<T>,IndexType,item=collection.at(index));
  template<typename T, typename IndexType> CollectionItemAccessSpecialization(T,const Set<T>,IndexType,item=collection.at(index));

  //template<typename T, typename IndexType> CollectionSetItemSpecialization(Set<T>,T,IndexType,collection.set(index,item));
NS_END(CORE_NAMESPACE)
