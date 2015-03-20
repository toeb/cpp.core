#pragma once
#include <core/core.h>
#include <core/container/graph/DerivableDataNode.h>
NS_BEGIN(CORE_NAMESPACE)
  template<typename T>
  class DataNode : public DerivableDataNode<T,DataNode<T> >{
  public:
    DataNode(){}
    DataNode(T data):DerivableDataNode<T,DataNode<T> >(data){}
    DataNode<T> & operator = (T data){
      this->data()=data;
      return *this->derived();
    }
  };
NS_END(CORE_NAMESPACE)