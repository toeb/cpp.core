#pragma once

#include <core/core.h>

NS_BEGIN(CORE_NAMESPACE)

// from https://gist.github.com/louisdx/1076849
template<typename T>
struct has_const_iterator
{
private:
  typedef char                      one;
  typedef struct { char array[2]; } two;

  template<typename C> static one test(typename C::const_iterator*);
  template<typename C> static two  test(...);
public:
  static const bool value = sizeof(test<T>(0)) == sizeof(one);
  typedef T type;
};



NS_END(CORE_NAMESPACE)