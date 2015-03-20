#pragma once
#include <core/core.h>


NS_BEGIN(CORE_NAMESPACE)
  

  /*

  template<typename T>
  struct class_of_member_method{};
  template<typename C, typename R, typename A1>
  struct class_of_member_method<R (C::*)(A1)>{
  typedef C type;
  };
  template<typename C, typename R, typename A1, typename A2>
  struct class_of_member_method<R (C::*)(A1,A2)>{
  typedef C type;
  };
  template<typename C, typename R, typename A1, typename A2, typename A3>
  struct class_of_member_method<R (C::*)(A1,A2,A3)>{
  typedef C type;
  };
  */
  


  template< typename T >
  struct result_of_static_function {};

  template< typename R >
  struct result_of_static_function< R (*)() > {
    typedef R type;
  };

  template< typename R , typename Arg >
  struct result_of_static_function< R (*)(Arg) > {
    typedef R type;
  };

  template< typename R , typename Arg1, typename Arg2 >
  struct result_of_static_function< R (*)(Arg1,Arg2) > {
    typedef R type;
  };


NS_END(CORE_NAMESPACE)
