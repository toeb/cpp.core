#pragma once
#include <core/core.h>

NS_BEGIN(CORE_NAMESPACE)
  
/*
  template<typename T>
  struct meta_type_construction{
    static const bool constructible = default_constructor<T>::isConstructible;
    static std::shared_ptr<void> construct(){
      return default_constructor<T>::construct();
       //return std::shared_ptr<void>();
    }
  };*/
NS_END(CORE_NAMESPACE)

