#pragma once
#include <core/core.h>
#include <core/container/operations/OperationCollectionSize.h>
#include <core/container/operations/OperationCollectionItemAccess.h>
#include <vector>
#include <list>
NS_BEGIN(CORE_NAMESPACE)
  SpecializeCollectionItemType(std::vector<T>);
  SpecializeCollectionItemType(std::list<T>);
  template<typename T, typename IndexType> OperationCollectionSizeSpecialization(std::vector<T>,IndexType, size=collection.size(););
  template<typename T, typename IndexType> OperationCollectionSizeSpecialization(std::list<T>,IndexType, size=collection.size(););
  template<typename T, typename IndexType> CollectionItemAccessSpecialization(T,std::vector<T>,IndexType, item=collection[index]);
  template<typename T, typename IndexType> CollectionItemAccessSpecialization(T,std::list<T>,IndexType, item=collection[index]);

  template<typename T, typename IndexType> OPERATION_SPECIALIZATION(CollectionPointerAccess)<T,std::vector<T>,IndexType>{
    SPECIALIZATION(T ** ptr, std::vector<T>& collection, const IndexType & index){
      *ptr = &collection[index];
      return true;
    }
  };

  template<typename T, typename IndexType> OPERATION_SPECIALIZATION(CollectionSetItem)<T,std::vector<T>,IndexType>{
    SPECIALIZATION(std::vector<T>& vec, const T & it, const IndexType & index){
      vec[index]=it;
      return true;
    }
  };
  template<typename T, typename IndexType> OPERATION_SPECIALIZATION(CollectionSetItem)<T,std::list<T>,IndexType>{
    SPECIALIZATION(std::list<T>& lst, const T & it, const IndexType & index){
      lst[index]=it;
      return true;
    }
  };

  /*  template<typename T> CollectionItemAccessSpecialization(T , std::vector<T>, size_t,*item = &collection[index]);
  template<typename T> CollectionItemAccessSpecialization(T , std::list<T>, size_t,*item = &collection[index]);
  template<typename T> CollectionItemAccessSpecialization(const T , const std::vector<T>, size_t,*item = &collection[index]);
  template<typename T> CollectionItemAccessSpecialization(const T , const std::list<T>, size_t,*item = &collection[index]);*/
NS_END(CORE_NAMESPACE)

