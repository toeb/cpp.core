#pragma once
#include <core/core.h>
#include <core/reflection/callable/TypedCallableInfoBase.h>
#include <core/reflection/callable/TypedArgumentInfo.h>
#include <memory>
#include <core/template/signature_discriminator.h>
#include <core/reflection/callable/TypedArgumentInfo.h>
NS_BEGIN(CORE_NAMESPACE)
  // a functor object which calls a function on overy type of a type tuple converting it to an argument info pointer
  struct ToArgumentInfo{
    ToArgumentInfo(std::function<void (std::shared_ptr<ArgumentInfo>)> callback):_callback(callback){}
    std::function<void (std::shared_ptr<ArgumentInfo>)> _callback;
    template<typename T,size_t i>
    void operator()(){
      _callback(std::make_shared<TypedArgumentInfo<T,i>>());
    };
  };


  template<typename TCallable>
  struct TypedCallableInfo : public virtual CallableInfo{
    TypedCallableInfo(TCallable callable):_callable(callable){

      /*setReturnType(type_of<typename callable_traits<TCallable>::return_type>());
      setIsConst(callable_traits<TCallable>::is_const);
      setIsStatic(!callable_traits<TCallable>::is_member);*/
    }

    Argument callImplementation(const ArgumentList & args)const{
        return Argument();
        // /return call_callable(_callable,args);
    }
  private:
    // info is stored as mutable because function pointers will cause errors else
    mutable TCallable _callable;    
  };

  // creates a TypedCallableInfo for the passed callable
  template<typename T>
  TypedCallableInfo<T> callable_info(T callable){
    return TypedCallableInfo<T>(callable);
  }

  // creates a TypedCallableInfo shared_ptr for the passed callable
  template<typename T>
  std::shared_ptr<TypedCallableInfo<T>> callable_info_shared(T callable){
    static auto info  = std::make_shared<TypedCallableInfo<T>>(callable);
    return info;
  }
NS_END(CORE_NAMESPACE)
  
