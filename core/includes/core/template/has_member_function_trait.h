#pragma once


#define _has_member_function_trait(NAME,SUFFIX,...)\
  namespace NAME ## SUFFIX ## _sfinae_check{\
    template<class T> struct sfinae_true : public std::true_type{ typedef T type; };\
    template<class T> struct sfinae_false : public std::false_type{ typedef T type; };\
    template<class T> static auto test(int)\
     ->sfinae_true<decltype(&T::NAME __VA_ARGS__ )>;/*add varargs here in parens*/\
    template<class T> static auto test(long)\
     ->sfinae_false<T>;\
    template<class T, class T2 = decltype(test<T>(0))>\
    struct has : public T2{};\
   }\
   template<class T>\
   struct has_##NAME##_method##SUFFIX : \
    public std::integral_constant<bool,\
      std::is_member_function_pointer<typename NAME ## _sfinae_check::has<T>::type>::value\
      &&\
      NAME ## SUFFIX ## _sfinae_check::has<T>::value\
    >{};

/// creates a sfinae trait to check if a specific member function exists for a type
#define has_member_function_trait(NAME) _has_member_function_trait(NAME, )