#pragma once
#include <core/core.h> 
#include <core/reflection/type/TypeInfo.h>

#include <core/reflection/member/method/TypedMethodInfo.h>
#include <core/reflection/member/constructor/ConstructorInfo.h>
NS_BEGIN(CORE_NAMESPACE)
 
  /*

  template<typename T, bool hasDefaultConstructor = 
    !std::is_const<T>::value&& (std::is_fundamental<T>::value || 
    std::is_trivially_default_constructible<T>::value && !std::is_abstract<T>::value)
  >
  struct add_default_constructor{
    static void add(Type * type){}
  };
  template<typename T>
  struct add_default_constructor<T,true> : public ConstructorInfo{
    add_default_constructor(Type * type):ConstructorInfo(type){}
    NS(CORE_NAMESPACE)::Argument callImplementation(const  Arguments &  args)const override final{
        return Argument(std::shared_ptr<T>(new T()));                                                                      
    }   
    
    static void add(Type * type){
       new add_default_constructor<T,true>(type);
    }
  };

#define DS_DEFAULT_CONSTRUCTOR_SPECIALIZE(TYPE,ENABLED)\
  template<> struct add_default_constructor<TYPE, !ENABLED> : public add_default_constructor<TYPE,ENABLED>{\
  static void add(Type * type){add_default_constructor<std::string,ENABLED>::add(type);}\
  };

#define DS_DEFAULT_CONSTRUCTOR_ENABLE(TYPE) DS_DEFAULT_CONSTRUCTOR_SPECIALIZE(TYPE,true)
#define DS_DEFAULT_CONSTRUCTOR_DISABLE(TYPE) DS_DEFAULT_CONSTRUCTOR_SPECIALIZE(TYPE,false)


  

  template<typename T>
  TraitType<T>::TraitType(const std::string & name):Type(name){
    init();
  }

  template<typename T>
  void TraitType<T>::init(){
    add_default_constructor<T>::add(this);
  }
  */
NS_END(CORE_NAMESPACE)

