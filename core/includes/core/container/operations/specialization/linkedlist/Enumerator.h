#pragma once
#include <core/core.h>
#include <core/container/Enumerable.h>
NS_BEGIN(CORE_NAMESPACE)
  namespace collection{
    template<typename T>
    class SimpleLinkedListEnumerator : public EnumeratorImplementation<T>{
      SimpleLinkedList<T> & _list;
    public:
      SimpleLinkedListEnumerator(SimpleLinkedList<T> & list):_list(list){
      }
      typedef T Item;
      bool isValid()const{
        return !_list.empty();
      }
      T&currentItem(){
        return _list._item;
      }
      const T & currentItem()const{
        return _list._item;
      }
      void moveNext(){
        if(!isValid())return;
        _list = *_list._tail;
      }
      std::shared_ptr<EnumeratorImplementation<T>> clone(){
        return std::shared_ptr<SimpleLinkedListEnumerator<T>>(new SimpleLinkedListEnumerator<T>(_list));
      }
    };
  }
NS_END(CORE_NAMESPACE)
