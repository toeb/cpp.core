#include <type_traits>
#include <core/template/is_callable.h>
NS_BEGIN(CORE_NAMESPACE)

  template<typename T>
  struct type_traits{
    static const bool is_ref = false;
    static const bool is_rvalue_ref = false;
    static const bool is_const = false;
    static const bool is_volatile = false;
    static const bool is_array = false;
    static const bool is_pointer = false;
    typedef void base;
    typedef T type;
    typedef T current_type;
    static const bool is_fundamental = std::is_fundamental<T>::value;
    static const bool is_callable = NS(CORE_NAMESPACE)::is_callable<T>::value;
  };
  template<typename T>
  struct type_traits<T*> : public type_traits < T > {
    static const bool is_pointer = true;
    typedef type_traits<T> base;
    typedef T current_type;
  };
  template<typename T>
  struct type_traits<T&> : public type_traits < T > {
    static const bool is_ref = true;
    typedef type_traits<T> base;
    typedef T current_type;
  };

  template<typename T>
  struct type_traits<T&&> : public type_traits < T > {
    static const bool is_rvalue_ref = true;
    typedef type_traits<T> base;
    typedef T current_type;
  };

  template<typename T>
  struct type_traits<const T> : public type_traits < T > {
    static const bool is_const = true;
    typedef type_traits<T> base;
    typedef T current_type;
  };

  template<typename T>
  struct type_traits<volatile T> : public type_traits < T > {
    static const bool is_volatile = true;
    typedef type_traits<T> base;
    typedef T current_type;
  };
  template<typename T, int idx>
  struct type_traits<T[idx]> : public type_traits < T > {
    static const bool is_array = true;
    typedef type_traits<T> base;
    typedef T current_type;
  };
NS_END(CORE_NAMESPACE)

