#pragma once
#include <core/core.h>
#include <tuple>

NS_BEGIN(CORE_NAMESPACE)

template<size_t Idx, typename TTuple, typename TDefault=void,
  bool use_default = Idx >= std::tuple_size<TTuple>::value >
struct tuple_element_or_default{
  typedef TDefault type;
};
template<size_t Idx, typename TTuple, typename TDefault>
struct tuple_element_or_default<Idx,TTuple,TDefault,false>{
  typedef typename std::tuple_element<Idx,TTuple>::type type;
};

NS_END(CORE_NAMESPACE)
