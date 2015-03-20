#pragma once
#include <core/core.h>
#include <queue>
#include <map>

NS_BEGIN(CORE_NAMESPACE)
  template<typename T>
  class ArrayPool{
  private:
    static std::map<int,std::queue<T*>* > _arrays;
  public:
    static inline void createArray(T** arr, int dim){
      std::queue<T*> * item =  _arrays[dim];
      if(!item || item->empty()){
        *arr = new T[dim];
        return;
      }
      *arr = item->front();
      item->pop();
    }
    static inline void freeArray(T** arr, int dim){
      if(!*arr)return;
      std::queue<T*> * item =  _arrays[dim];
      if(!item){
        item = new std::queue<T*>();
        _arrays[dim]=item;
      }
      item->push(*arr);
      *arr =0;
    }
  };
  template<typename T>
  std::map<int,std::queue<T*> *> ArrayPool<T>::_arrays = *new std::map<int, std::queue<T*> *>();
NS_END(CORE_NAMESPACE)
