#pragma once
#include <core/core.h>

#include <core/container/operations/OperationCollectionItemType.h>
NS_BEGIN(CORE_NAMESPACE)


template <typename EnumerableType>
class EnumerableItemType{
public:
    typedef typename CollectionItemType<EnumerableType>::ItemType ItemType;
};
template<typename IndexableType>
class IndexableIndexType{
public:
    typedef size_t IndexType;
};

namespace collection{
// returns true if size of collection could be determined.  then n is set to the number if items in colleciton
template<typename SizeType,typename CollectionType>
bool size(SizeType & n, const CollectionType & collection);
// returns the size of the collection.  if the size cannot be determined the result is undefined
template<typename SizeType,typename CollectionType>
SizeType size(const CollectionType & collection);
// returns the size of the collection (size_t)
template<typename CollectionType> auto size(const CollectionType & collection)->typename IndexableIndexType<CollectionType>::IndexType;
// returns true if the item at index could be accessed. then the item is assigned th ith item
template<typename ItemType, typename CollectionType, typename IndexType>
inline bool item(ItemType & item, CollectionType & collection, const IndexType & i);
// returns th ith item of the collection
template<typename ItemType, typename CollectionType, typename IndexType>
inline ItemType item(CollectionType & collection, const IndexType & i);
// returns true if the collection supports returning pointers to the item. if it does ptr is assign the pointer to the ith item in the collection
template<typename ItemType, typename CollectionType, typename IndexType>
inline bool pointer(ItemType ** ptr, CollectionType & collection, const IndexType & i);
// return the pointer to the ith item in the collection (returns null if the colleciton is not capable of returning pointers)
template<typename CollectionType, typename IndexType>
inline auto pointer(CollectionType & collection, const IndexType & index)->typename CollectionItemType<CollectionType>::ItemType*;
// returns a reference to the ith item.  this method will cause a failure if the item is invalid or the collection does not support returning pointers
template<typename ItemType, typename CollectionType, typename IndexType>
inline ItemType & reference(CollectionType & collection, const IndexType & i);
// returns true if item i of the collection could be successfully set
template<typename ItemType, typename CollectionType, typename IndexType>
inline bool setItem(CollectionType & collection, const ItemType & item, const IndexType & i);
// copies elements from source[i...j-1] to target[k...k+(j-i)-1]
template<typename CollectionTypeA, typename CollectionTypeB, typename IndexType>
inline bool copyRange(CollectionTypeA & target, const CollectionTypeB & source, const IndexType & i, const IndexType & j, const IndexType & k);
// copies elements from source[0,n-1] to target[0,n-1]  you need to ensure that target has at least n slots
template<typename CollectionTypeA, typename CollectionTypeB>
inline bool copy(CollectionTypeA & target, const CollectionTypeB & source);
//returns the collections underyling array structure (if the collection has one) else nullptr is returned,
template<typename CollectionType>
inline typename CollectionItemType<CollectionType>::ItemType* underlyingArray(CollectionType & collection){
    return nullptr;
};
}
NS_END(CORE_NAMESPACE)



#include <core/container/operations/OperationCollectionSize.h>
#include <core/container/operations/OperationCollectionItemAccess.h>
#include <core/container/operations/OperationCollectionSetItem.h>
#include <core/container/operations/OperationCollectionCopyRange.h>

NS_BEGIN(CORE_NAMESPACE)
namespace collection{
//IMPLEMENTATION

template<typename SizeType,typename CollectionType>
bool size(SizeType & n, const CollectionType & collection){
    return OperationCollectionSize<CollectionType,SizeType>::operation(n,collection);
}
template<typename SizeType,typename CollectionType> SizeType size(const CollectionType & collection){
    SizeType n;
    if(!size(n,collection)){
        n=0; return n;
    }
    return n;
}

template<typename CollectionType> auto size(const CollectionType & collection)->typename IndexableIndexType<CollectionType>::IndexType{
    return size<typename IndexableIndexType<CollectionType>::IndexType,CollectionType>(collection);
}

template<typename ItemType, typename CollectionType, typename IndexType>
inline bool item(ItemType & item, CollectionType & collection, const IndexType & index){
    return OperationCollectionItemAccess<ItemType,CollectionType,IndexType>::operation(item,collection,index);
}
template<typename ItemType, typename CollectionType, typename IndexType>
inline ItemType item(CollectionType & collection, const IndexType & index){
    ItemType it;
    item(it,collection,index);
    return it;
}

template<typename ItemType, typename CollectionType, typename IndexType>
inline bool pointer(ItemType ** ptr, CollectionType & collection, const IndexType & index){
    return OperationCollectionPointerAccess<ItemType,CollectionType,IndexType>::operation(ptr,collection,index);
}
template<typename CollectionType, typename IndexType>
inline auto pointer(CollectionType & collection, const IndexType & index)->typename CollectionItemType<CollectionType>::ItemType*{
    typename CollectionItemType<CollectionType>::ItemType* ptr;
    pointer(&ptr,collection,index);
    return ptr;
}

template<typename CollectionType, typename IndexType>
inline auto  reference(CollectionType & collection, const IndexType & index)->typename CollectionItemType<CollectionType>::ItemType&{
    return *pointer(collection,index);
}

template<typename ItemType, typename CollectionType, typename IndexType>
inline bool setItem(CollectionType & collection, const ItemType & item, const IndexType & index){
    return OperationCollectionSetItem<ItemType,CollectionType,IndexType>::operation(collection,item,index);
}

// copies elements from sourceStart to sourceEnd-1 to target from index targetStart
template<typename CollectionTypeA, typename CollectionTypeB, typename IndexType>
inline bool copyRange(CollectionTypeA & destination, const CollectionTypeB & source, const IndexType & sourceStart, const IndexType & sourceEnd, const IndexType & destinationStart){
    bool result=false;
    OperationCollectionCopyRange<CollectionTypeA,CollectionTypeB,IndexType>::operation(result,destination,source,sourceStart,sourceEnd,destinationStart);
    return result;
}

template<typename CollectionTypeA, typename CollectionTypeB>
inline bool copy(CollectionTypeA & destination, const CollectionTypeB & source){
    return copyRange<CollectionTypeA,CollectionTypeB,size_t>(destination,source,0,size(source),0);
}
}
NS_END(CORE_NAMESPACE)

/*
template<typename TContainer>
struct SizeType{
  typedef void type;
};

template<typename TElement>
struct SizeType<std::vector<TElement>>{
  typedef typename std::vector<TElement>::size_type type;
};

template<typename TContainer>
struct ElementType{
  typedef void* type;
};
template<typename TElement>
struct ElementType<std::vector<TElement>>{
  typedef TElement type;
};

// for references
template<typename TContainer>
struct ElementType<TContainer&>{
  typedef typename ElementType<typename TContainer>::type type;
};
//for pointers
template<typename TContainer>
struct ElementType<TContainer*>{
  typedef typename ElementType<typename TContainer>::type type;
};

template<typename TContainer>
struct ElementType<const TContainer>{
  typedef typename ElementType<typename TContainer>::type type;
};

template<typename TContainer>
struct ElementCount{
  static inline auto count(const TContainer & container)->size_t{
    throw new exception("count is not implemented for type");
  }
};

template<typename TElement>
struct ElementCount<std::vector<TElement>>{
  static inline auto count(const std::vector<TElement> & container)->size_t{
    return container.size();
    
  }
};


template<typename TContainer>
size_t count(const TContainer & container){
  ElementCount<TContainer>::count(container);
}

template<typename TContainer>
struct ElementAt{
  typedef typename ElementType<TContainer>::type TElement;
public:
  static inline TElement & elementAt(TContainer & container, size_t i){
    throw new exception("elementAt is not implement for type");
  }
};

template<typename TContainer>
struct ElementAtConst{
  typedef typename ElementType<TContainer>::type TElement;
public:
  static inline const TElement & elementAt(const TContainer & container, size_t i){
    throw new exception("elementAt (const) is not implement for type");
  }
};

template<typename TElement>
struct ElementAt<std::vector<TElement>>{
public:
  static inline TElement & elementAt(std::vector<TElement> & container, size_t i){
    return container.at(i);
  }
};

template<typename TContainer>
struct Predicate{
  typedef typename std::function<bool (typename const ElementType<TContainer>::type & )> type;
};



template<typename TContainer>
struct OperationFirstOrDefault{
  static inline auto firstOrDefault(TContainer & container, typename Predicate<TContainer>::type predicate)->typename ElementType<TContainer>::type{
    throw new exception("firstOrDefault not implemented for type");
  }
};



template<typename TElement>
struct OperationFirstOrDefault<std::vector<TElement>>{
  static inline auto firstOrDefault(std::vector<TElement> & container,typename Predicate<std::vector<TElement>>::type predicate)->typename TElement &{
     for(int i=0; i < container.size(); i++){
       if(predicate(container[i]))return container[i];
     }
     return 0;
  }
};


template<typename TContainer>
auto firstOrDefault(TContainer & container, typename Predicate<TContainer>::type predicate)->typename ElementType<TContainer>::type{
  return OperationFirstOrDefault<TContainer>::firstOrDefault(container,predicate);
}*/