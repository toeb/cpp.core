#pragma once
#include <core/core.h>

#include <iostream>

#include <core/container/graph/Node.h>
#include <core/utility/StringTools.h>
NS_BEGIN(CORE_NAMESPACE)
  template<typename T, typename Derived>
  class DerivableDataNode: public Node<Derived>{
    T _data;
  public:
    DerivableDataNode(){}
    DerivableDataNode(T data):_data(data){}
    T & data(){return _data;}
    const T & data()const{return _data;}

    Derived & operator = (T data){
      this->data()=data;
      return this->derived();
    }
    operator T&() {
      return _data;
    }
    operator const T & ()const{
      return _data;
    }

    virtual void toStream(std::ostream & out)const{
      out << "node{";
      this->toStream(out);
      out << "}";
      out << data();
    }

    void successorsToStream(std::ostream & out){
      this->dfsWithPath([](Derived* current, Set<Derived*> path){
        std::cout << stringtools::spaces(path.size());
        std::cout << *current<<"\n";
      });
    }
  };
NS_END(CORE_NAMESPACE)

