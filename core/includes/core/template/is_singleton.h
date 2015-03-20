#pragma once
#include <core/core.h>


NS_BEGIN(CORE_NAMESPACE)

  // compile time check if type is singleton. 
  // (which is marked by SingletonType being typedef'd)
  // it is expected for T to also have a static instance() method which returns a std::shared_ptr<T>
  template <typename T>
  struct is_singleton{
  private:
    template <typename T1>
    static typename T1::SingletonType test(int);
    template <typename>
    static void test(...);
  public:
    enum { value = !std::is_void<decltype(test<T>(0))>::value };
  };

NS_END(CORE_NAMESPACE)
