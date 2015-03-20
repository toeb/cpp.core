#pragma once
#include <core/core.h>

#include <core/template/function_traits.h>
#include <core.preprocessor.h>
#include <core.shim.h>
NS_BEGIN(CORE_NAMESPACE)

  template<typename T, int arity = NS(CORE_NAMESPACE)::function_traits<T>::arity, bool isConst=NS(CORE_NAMESPACE)::function_traits<T>::isConstCall>
  struct CallableFunctor{};
  
  template<typename F>
  auto make_callable(F f)->CallableFunctor<F>{
    return CallableFunctor<F>(f);
  }


#define DS_CALLABLE_FUNCTION_INVOKE_ARGS_I(X) args[X]
#define DS_CALLABLE_FUNCTION_INVOKE_N(N) _function(DS_REDUCE_COMMA(DS_CALLABLE_FUNCTION_INVOKE_ARGS_I, DS_SEQUENCE(DS_MINUS_ONE(N))))
#define DS_CALLABLE_FUNCTION_N(N)                                                                                                       \
  template<typename T>                                                                                                                    \
  struct CallableFunctor<T,N,true> : public Callable{                                                                                         \
  T _function;                                                                                                                          \
  typedef function_traits<T> traits;                                                                                                    \
  CallableFunctor(T function=T()):_function(function){}                                                                                    \
  bool isValid() const override final{                                                                                                  \
  return true ;                                                                                                                                 \
  }                                                                                                                                     \
  Argument callImplementation(const ArgumentList & args)override final{                                                                    \
  if(args.size() !=N)return Argument();                                                                                                 \
  return DS_CALLABLE_FUNCTION_INVOKE_N(N);                                                                                                  \
  }                                                                                                                                     \
  Argument callImplementation(const ArgumentList & args)const override final{                                                              \
  if(args.size() !=N)return Argument();                                                                                                 \
  return DS_CALLABLE_FUNCTION_INVOKE_N(N);                                                                                                   \
  }                                                                                                                                     \
  };\
  template<typename T>                                                                                                                    \
  struct CallableFunctor<T,N,false> : public Callable{                                                                                         \
  T _function;                                                                                                                          \
  typedef function_traits<T> traits;                                                                                                    \
  CallableFunctor(T function=T()):_function(function){}                                                                                    \
  bool isValid() const override final{                                                                                                  \
  return true ;                                                                                                                                 \
  }                                                                                                                                     \
  Argument callImplementation(const ArgumentList & args)override final{                                                                    \
  if(args.size() !=N)return Argument();                                                                                                 \
  return DS_CALLABLE_FUNCTION_INVOKE_N(N);                                                                                                  \
  }                 \
  };

  DS_FOREACH(DS_CALLABLE_FUNCTION_N, 1,2,3,4,5,6,7)
    


NS_END(CORE_NAMESPACE)

