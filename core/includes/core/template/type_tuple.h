#pragma once
#include <core/core.h>

#include <core/template/template_argument.h>
NS_BEGIN(CORE_NAMESPACE)
  template<typename T0=NS(CORE_NAMESPACE)::Nil, typename T1=NS(CORE_NAMESPACE)::Nil, typename T2=NS(CORE_NAMESPACE)::Nil, typename T3=NS(CORE_NAMESPACE)::Nil, typename T4=NS(CORE_NAMESPACE)::Nil, typename T5=NS(CORE_NAMESPACE)::Nil, typename T6=NS(CORE_NAMESPACE)::Nil, typename T7=NS(CORE_NAMESPACE)::Nil, typename T8=NS(CORE_NAMESPACE)::Nil, typename T9=NS(CORE_NAMESPACE)::Nil>
  struct type_tuple{
    static const size_t size =10;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.template operator()<T0, 0>();
      functor.template operator()<T1, 1>();
      functor.template operator()<T2, 2>();
      functor.template operator()<T3, 3>();
      functor.template operator()<T4, 4>();
      functor.template operator()<T5, 5>();
      functor.template operator()<T6, 6>();
      functor.template operator()<T7, 7>();
      functor.template operator()<T8, 8>();
      functor.template operator()<T9, 9>();
    }
  };

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  struct type_tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, NS(CORE_NAMESPACE)::Nil>{
    static const size_t size =9;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1, T2, T3, T4, T5, T6, T7, T8>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.template operator()<T0, 0>();
      functor.template operator()<T1, 1>();
      functor.template operator()<T2, 2>();
      functor.template operator()<T3, 3>();
      functor.template operator()<T4, 4>();
      functor.template operator()<T5, 5>();
      functor.template operator()<T6, 6>();
      functor.template operator()<T7, 7>();
      functor.template operator()<T8, 8>();
    }
  };

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  struct type_tuple<T0, T1, T2, T3, T4, T5, T6, T7, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil>{
    static const size_t size =8;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1, T2, T3, T4, T5, T6, T7>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.template operator()<T0, 0>();
      functor.template operator()<T1, 1>();
      functor.template operator()<T2, 2>();
      functor.template operator()<T3, 3>();
      functor.template operator()<T4, 4>();
      functor.template operator()<T5, 5>();
      functor.template operator()<T6, 6>();
      functor.template operator()<T7, 7>();
    }
  };

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  struct type_tuple<T0, T1, T2, T3, T4, T5, T6, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil>{
    static const size_t size =7;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1, T2, T3, T4, T5, T6>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.template operator()<T0, 0>();
      functor.template operator()<T1, 1>();
      functor.template operator()<T2, 2>();
      functor.template operator()<T3, 3>();
      functor.template operator()<T4, 4>();
      functor.template operator()<T5, 5>();
      functor.template operator()<T6, 6>();
    }
  };

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  struct type_tuple<T0, T1, T2, T3, T4, T5, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil>{
    static const size_t size =6;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1, T2, T3, T4, T5>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.template operator()<T0, 0>();
      functor.template operator()<T1, 1>();
      functor.template operator()<T2, 2>();
      functor.template operator()<T3, 3>();
      functor.template operator()<T4, 4>();
      functor.template operator()<T5, 5>();
    }
  };

  template<typename T0, typename T1, typename T2, typename T3, typename T4>
  struct type_tuple<T0, T1, T2, T3, T4, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil>{
    static const size_t size =5;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1, T2, T3, T4>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.template operator()<T0, 0>();
      functor.template operator()<T1, 1>();
      functor.template operator()<T2, 2>();
      functor.template operator()<T3, 3>();
      functor.template operator()<T4, 4>();
    }
  };

  template<typename T0, typename T1, typename T2, typename T3>
  struct type_tuple<T0, T1, T2, T3, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil>{
    static const size_t size =4;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1, T2, T3>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.template operator()<T0, 0>();
      functor.template operator()<T1, 1>();
      functor.template operator()<T2, 2>();
      functor.template operator()<T3, 3>();
    }
  };

  template<typename T0, typename T1, typename T2>
  struct type_tuple<T0, T1, T2, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil>{
    static const size_t size =3;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1, T2>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.template operator()<T0, 0>();
      functor.template operator()<T1, 1>();
      functor.template operator()<T2, 2>();
    }
  };

  template<typename T0, typename T1>
  struct type_tuple<T0, T1, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil>{
    static const size_t size =2;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.template operator()<T0, 0>();
      functor.template operator()<T1, 1>();
    }
  };

  template<typename T0>
  struct type_tuple<T0, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil>{
    static const size_t size =1;
    template<size_t i> 
    struct at:public template_argument<i, T0>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.template operator()<T0, 0>();
    }
  };

  template<>
  struct type_tuple<NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil, NS(CORE_NAMESPACE)::Nil>{
    static const size_t size =0;
    template<size_t i> 
    struct at:public template_argument<i>{};
    template<typename Functor>
    static void for_each(Functor & functor){
    }
  };


NS_END(CORE_NAMESPACE)

