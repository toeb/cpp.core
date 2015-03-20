#pragma once
#include <core/core.h>

#include <core.operation.h>
#include <core/container/Operations.h>

NS_BEGIN(CORE_NAMESPACE)
  //will copy anything.  this will cause errors if th target type is a pointer for example because it will write without knowing the targets size
  template<typename DestinationCollectionType, typename SourceCollectionType, typename IndexType>
  OPERATION(CollectionCopyRange){
    OPERATION_IMPLEMENTATION(bool &result,
      DestinationCollectionType & target,
      const SourceCollectionType & source,
      const IndexType & startSource,
      const IndexType & endSource,
      const IndexType & startTarget){        
        IndexType j=startTarget;
        IndexType i =startSource;
        typename CollectionItemType<DestinationCollectionType>::ItemType it;
        while(i < endSource){
          NS(CORE_NAMESPACE)::collection::item(it,source,i);
          NS(CORE_NAMESPACE)::collection::setItem(target,it,j);
          i++;
          j++;
        }
        result = true;
        return true;
    }
  };
NS_END(CORE_NAMESPACE)
