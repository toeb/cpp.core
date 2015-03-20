#pragma once
#include <core/core.h>
#include <core/reflection/type/Argument.h>
#include <memory>
// template implementation
#include <core/reflection/type/TypeInfo.h>
#include <utility>
NS_BEGIN(CORE_NAMESPACE)

  

  template<typename T> const T& Argument::ref()const{return *cast<T>();}
  template<typename T> T& Argument::ref(){return *cast<T>();}
  template<typename T> T Argument::rvalue()const{
    T v = ref<T>();
    return v;
    //return std::move<T>(v);
  }

 /* template<typename T>
    auto
    Argument::convert ()const -> decltype(choose_reference<T>::template choose<const Argument>(Argument())){
    return choose_reference<T>::template choose<const Argument>(*this);
  }*/
  /*
  template<typename T> 
  Argument::operator T && ()const{    
    T result = *cast<T>();
    //return std::move<T>(result);
    return result;
  }*/
  template<typename T> 
  Argument::Argument(const T & data):
    data(std::static_pointer_cast<void>(std::shared_ptr<T>(new T(data)))),
    type(type_of<T>()){

  }
  template<typename T> 
  Argument::Argument(std::shared_ptr<T> data):
    data(std::static_pointer_cast<void>(data)),
    type(type_of<T>()){
  }
  template<typename T> 
  Argument::operator const T & ()const{
    if(!(bool)data){
      throw std::exception();//("dereferencing null pointer in Argument");
    }
    return *cast<T>(); 
  }
  template<typename T> 
  Argument::operator T & (){    
    if(!(bool)data){
      throw std::exception();//("dereferencing null pointer in Argument");
    }
    return *cast<T>(); 
  }

  template<typename T> 
  Argument::operator std::shared_ptr<const T>()const{
    return cast<const T>();    
  }
  template<typename T> 
  Argument::operator std::shared_ptr<T>(){
    return cast<T>();
  }
  template<typename T>  
  std::shared_ptr<T> Argument::cast(){
    return std::static_pointer_cast<T>(data);
  }
  template<typename T>  
  std::shared_ptr< const T> Argument::cast()const{
    return std::static_pointer_cast<T>(data);
  }


  template<typename T> const T* Argument::c_ptr()const{
    return std::static_pointer_cast<T>(data).get();
  }
  template<typename T> T* Argument::c_ptr(){
    return std::static_pointer_cast<T>(data).get();
  }
  template<typename T> const std::shared_ptr<T> Argument::ptr()const{
    return std::static_pointer_cast<T>(data);
  }
  template<typename T> std::shared_ptr<T> Argument::ptr(){
    return std::static_pointer_cast<T>(data);
  }
  template<typename T> const std::weak_ptr<T> Argument::w_ptr()const{
    return std::weak_ptr<T>(ptr<T>());
  }
  template<typename T> std::weak_ptr<T> Argument::w_ptr(){
    return std::weak_ptr<T>(ptr<T>());
  }
NS_END(CORE_NAMESPACE)

