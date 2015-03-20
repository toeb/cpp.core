#pragma once
#include <core/core.h>
#include <core/Object.h>
NS_BEGIN(CORE_NAMESPACE)
  template<typename T>
  class Decorator : public  T{
    T & _base;
  protected:
    T & base(){
      return _base;
    }
    const T& base()const{
      return _base;
    }
    Decorator(T & base):_base(base){
    }
  };
NS_END(CORE_NAMESPACE)
