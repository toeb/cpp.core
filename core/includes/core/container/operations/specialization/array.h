#pragma once
#include <core/core.h>
#include <core/container/operations/OperationCollectionItemType.h>
#include <core/container/operations/OperationCollectionSize.h>
#include <core/container/operations/OperationCollectionItemAccess.h>
NS_BEGIN(CORE_NAMESPACE)
  // this class wraps an pointer into a structure with number of elements
  template<typename T>
  class Array{
  private:Array():data(0),size(0){}

  public:
    Array(T * data, size_t size):data(data),size(size){}
    Array(size_t size){}
    size_t size;
    T * data;
  };

  SpecializeCollectionItemType(T*);

  SpecializeCollectionItemType(Array<T>);

  template<typename T,size_t n>
  class CollectionItemType<T[n]>{
  public:
    typedef T ItemType;
  };
  // specialization for fixed size arrays -- need to be written out beca
  template<typename T, size_t n> OPERATION_SPECIALIZATION(CollectionSize)<T[n],size_t>{
    SPECIALIZATION(size_t & thesize, const T* arr){
      thesize=n;
      return true;
    }
  };

  template<typename T, typename SizeType> OPERATION_SPECIALIZATION(CollectionSize)<Array<T>,SizeType >{
    SPECIALIZATION(SizeType & thesize, const Array<T> & arr){
      thesize = arr.size;
      return true;
    }
  };

  template<typename T, typename IndexType, size_t n> OPERATION_SPECIALIZATION(CollectionSetItem)<T,T[n],IndexType>{
    SPECIALIZATION(T* arr, const T & it, const IndexType & index){
      arr[index]=it;
      return true;
    }
  };

  template<typename T, typename IndexType> OPERATION_SPECIALIZATION(CollectionSetItem)<T,T*,IndexType>{
    SPECIALIZATION(T* arr, const T & it, const IndexType & index){
      arr[index]=it;
      return true;
    }
  };

  template<typename T, typename IndexType> OPERATION_SPECIALIZATION(CollectionSetItem)<T,Array<T> &,IndexType>{
    SPECIALIZATION(Array<T> & arr, const T & it, const IndexType & index){
      OperationCollectionSetItem::operation(arr.data,it,index);
      return true;
    }
  };

  template<typename T,  typename IndexType, size_t n> OPERATION_SPECIALIZATION(CollectionItemAccess)<T,T[n],IndexType>{
    SPECIALIZATION(T & it, T* arr, const IndexType & index){
      it = arr[index];
      return true;
    }
  };
  template<typename T,  typename IndexType, size_t n> OPERATION_SPECIALIZATION(CollectionPointerAccess)<T,T[n],IndexType>{
    SPECIALIZATION(T ** it, T* arr, const IndexType & index){
      *it = &arr[index];
      return true;
    }
  };
  template<typename T,  typename IndexType> OPERATION_SPECIALIZATION(CollectionPointerAccess)<T,T*,IndexType>{
    SPECIALIZATION(T ** it, T* arr, const IndexType & index){
      *it = &arr[index];
      return true;
    }
  };

  template<typename T, typename IndexType> CollectionItemAccessSpecialization(T, T *, IndexType,item = collection[index])
    //template<typename T, typename IndexType> CollectionItemAccessSpecialization(T , T *, IndexType,*item = &collection[index])
    //template<typename T> CollectionItemAccessMutableSpecialization(T , T*, size_t,*item = &collection[index])
NS_END(CORE_NAMESPACE)

