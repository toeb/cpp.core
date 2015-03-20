#pragma once
#include <core/core.h>

#include <core/reflection/type/TypeInfo.h>



NS_BEGIN(CORE_NAMESPACE)

  
#define DS_INTEGRAL_TYPES bool,char,/*char16_t,char32_t,*/wchar_t,/*signed char,*/ short int, int , long int , long long int, unsigned char, unsigned short int,unsigned int, unsigned long int, unsigned long long int
#define DS_FLOATING_POINT_TYPES float, double, long double
#define DS_VOID_TYPE void
#define DS_NULL_POINTER_TYPE std::nullptr_t
#define DS_FUNDEMENTAL_TYPES DS_INTEGRAL_TYPES,DS_FLOATING_POINT_TYPES/*,DS_VOID_TYPE/*,DS_NULL_POINTER_TYPE*/
#define DS_REFLECT_FUNDEMENTAL_TYPE(X) \
  template<> struct TypeInitializer<X>{static void initialize();};

DS_FOREACH(DS_REFLECT_FUNDEMENTAL_TYPE,DS_FUNDEMENTAL_TYPES);
  
template<> struct TypeInitializer<void>{static void initialize();};
  
NS_END(CORE_NAMESPACE)
