#pragma once
#include <core/core.h>

NS_BEGIN(CORE_NAMESPACE)
  namespace collection{
    template<typename T>
    class SimpleLinkedListEnumerator;
    template<typename T>
    class SimpleLinkedList{
    private:
      friend class SimpleLinkedListEnumerator<T>;
      T _item;
      SimpleLinkedList<T> * _tail;
    public:
      SimpleLinkedList():_tail(0){}
      inline SimpleLinkedList<T> * tail(){return _tail;}
      inline T & first(){return _item;}
      inline const T & first()const{return _item;}

      inline bool add(const T & item){
        if(_tail)return _tail->add(item);
        _item = item;
        _tail = new SimpleLinkedList();
        return true;
      }
      bool empty()const{return _tail==0;}
    };
  }
  SpecializeCollectionItemType(NS(CORE_NAMESPACE)::collection::SimpleLinkedList<T>);
NS_END(CORE_NAMESPACE)

