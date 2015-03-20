#pragma once
#include <core/core.h>


#include <core.operation.h>
#include <core/container/operations/OperationCollectionItemType.h>
#include <core/container/operations/OperationCollectionItemAccess.h>
#include <memory>
// is replaced by the item type that the ENUMERABLETYPE contains
#define ITEMTYPE(ENUMERABLETYPE) typename EnumerableItemType<ENUMERABLETYPE>::ItemType

NS_BEGIN(CORE_NAMESPACE)
  namespace collection{
    // forwad declarations
    template<typename T>
    class Enumerator;
    template<typename T>
    class Enumerable;
    template<typename T>

    // enumerator implementation
    class EnumeratorImplementation{
    protected:
      typedef T Item;
      virtual bool isValid()const=0;
      virtual T&currentItem()=0;
      virtual const T & currentItem()const=0;
      virtual void moveNext()=0;
      virtual std::shared_ptr<EnumeratorImplementation<T>> clone()=0;
      friend class Enumerator<T>;
    };

    // enumerator class wraps an enumerator implementation
    template<typename T>
    class Enumerator{
    public:
      Enumerator(std::shared_ptr<EnumeratorImplementation<T>> impl):_implementation(impl){}
      Enumerator(Enumerator<T> & other):_implementation(other._implementation){}
      // returns true if this enumerator is valid . ergo points to a valid item
      operator bool()const{return _implementation->isValid();};
      // returns a reference to the item
      const T& operator*()const{return _implementation->currentItem();}
      T& operator*(){return _implementation->currentItem(); }
      // increments this enumerator
      Enumerator<T> operator++(int){
        Enumerator<T> result = Enumerator<T>(_implementation->clone()) ;
        _implementation->moveNext();
        return result;
      }
      Enumerator<T> & operator++(){
        _implementation->moveNext();
        return * this;
      }
    private:
      std::shared_ptr<EnumeratorImplementation<T>> _implementation;
    };

    template<typename T>
    class EnumerableImplementation{
    protected:
      virtual Enumerator<T> getEnumerator()=0;
      friend class Enumerable<T>;
    };

    template<typename T>
    class Enumerable{
    public:
      Enumerable(EnumerableImplementation<T>* implemenation):_implementation(implemenation){}
      Enumerator<T> getEnumerator(){return _implementation->getEnumerator();};
    private:
      std::shared_ptr<EnumerableImplementation<T>> _implementation;
    };
  }
NS_END(CORE_NAMESPACE)


/*
template<typename ElementType, typename CollectionType, typename IndexType>
class CollectionConstAccess{
public:
static bool operation(ElementType& element, const CollectionType & collection, const IndexType & index){    
element = list[index];
return true;
}
};


template<typename ElementType, typename CollectionType, typename IndexType>
class CollectionInsert{
public:
static bool operation(CollectionType & collection, ElementType& element, const IndexType & index){
return false;
}
};
template<typename ElementType, typename CollectionType, typename IndexType>
class CollectionRemove{
public:
static bool operation(CollectionType & collection, const ElementType& element,const IndexType & index){
return false;
}
};
template<typename ElementType, typename CollectionType, typename IndexType>
class CollectionSwap{
public:
static bool operation(CollectionType & collection, const IndexType & indexOld,const IndexType & indexNew){
return false;  
}
};

template<typename ElementType, typename CollectionType, typename IndexType, typename Function>
class CollectionIterate{
public:
static bool operation(Function & function, CollectionType & collection){
for(IndexType i =0; i < size(collection); i++){
function(element(collection,i));
}
}
};
template<typename ElementType, typename CollectionType, typename IndexType, typename Function>
bool iterate(Function & function, CollectionType & container){
return CollectionIterate<ElementType,CollectionType,IndexType,Function>::operation(function,container);
}

template<typename ListIndex, typename IndexType=size_t, IndexType RowCount=0, IndexType ColumnCount=0>
class RowMajorIndex{
public:
static inline ListIndex operation(const IndexType & i, const IndexType& j){
return 
}
};

template<typename Coefficient, typename Mat, typename Index>
class MatrixCoefficentMutableAccess{
public:
static Coefficient & operation(Mat & mat, const Index &i, const Index & j){
return mat(i,j);
}  
};
template<typename Coefficient, typename Mat, typename Index>
class MatrixCoefficentConstAccess{
public:
static const Coefficient & operation(const Mat & mat, const Index &i, const Index & j){
return mat[Index(i,j)]
}  
};


template<typename T,typename Mat, typename Index>
T & coefficient(Mat & mat, const Index & i, const Index & j){
return MatrixCoefficentMutableAccess<T,Mat,Index>::operation(mat)
}
template<typename T,typename Mat, typename Index>
const T & coefficient(const Mat & mat, const Index & i, const Index & j){
return MatrixCoefficentConstAccess<T,Mat,Index>::operation(mat);
}



*/
