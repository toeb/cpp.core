#pragma once
#include <core/core.h>

#include <core/reflection/type/Type.h>



NS_BEGIN(CORE_NAMESPACE)

  // for now r value references are treated as simple values.
  template<typename T>
  class TypeInfo<T&&>
  {
  public:
    static std::shared_ptr<Type> instance(){
      return TypeInfo<T>::instance();
    }
  };
  /*
  // specializations for qualifiers  
  template<typename T>
  struct  TypeInfo<T&>:public  TraitType<T&> {
  DS_SINGLETON_TEMPLATED(TypeInfo,T&):TraitType(DS_INLINE_STRING(type_of<T>()->getName()<<" &")){
  setUnderlyingType(type_of<T>()); 
  setIsReference(true);
  }
  };
  template<typename T>
  struct  TypeInfo<T*>:public  TraitType<T*> {
  DS_SINGLETON_TEMPLATED(TypeInfo,T*):TraitType(DS_INLINE_STRING(type_of<T>()->getName()<<" *")){
  setUnderlyingType(type_of<T>());      
  setIsPointer(true);
  }
  };
  template<typename T>
  struct TypeInfo<const T>:public  TraitType<const T> {
  DS_SINGLETON_TEMPLATED(TypeInfo,const T):TraitType(DS_INLINE_STRING(type_of<T>()->getName()<<" const")){       
  setUnderlyingType(type_of<T>());
  setIsConst(true);
  }
  };
  template<typename T>
  struct TypeInfo<volatile T>:public  TraitType<volatile T> {
  DS_SINGLETON_TEMPLATED(TypeInfo,volatile T):TraitType(DS_INLINE_STRING(type_of<T>()->getName()<<" volatile")){
  setUnderlyingType(type_of<T>());
  setIsVolatile(true);
  }
  };
  template<typename T>
  struct TypeInfo<const volatile T>:public  TraitType<const volatile T> {
  DS_SINGLETON_TEMPLATED(TypeInfo,const volatile T):TraitType(DS_INLINE_STRING(type_of<T>()->getName()<<" const volatile")){
  setUnderlyingType(type_of<T>());
  setIsVolatile(true);
  setIsConst(true);
  }
  };*/
NS_END(CORE_NAMESPACE)
