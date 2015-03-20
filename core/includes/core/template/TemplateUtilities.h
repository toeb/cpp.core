#pragma once
#include <core/core.h>


// from http://pfultz2.com/blog/2014/11/08/non-template-constraints/
#define REQUIRES(...) requires_enum<__LINE__>::type = requires_enum<__LINE__>::type::none, bool PrivateBool=true, typename std::enable_if<PrivateBool && (__VA_ARGS__), int>::type = 0

/// removes const from return value and this and returns the value
#define UNCONSTIFY_THIS(...) \
  const_cast<typename std::remove_const<decltype(this->__VA_ARGS__) >::type> (\
    const_cast<typename std::remove_const<decltype(this)>::type>(this)__VA_ARGS__);



NS_BEGIN(CORE_NAMESPACE)
  
  




NS_END(CORE_NAMESPACE)



/*
template< typename T >
struct result_of_ptmf {};

template< typename R, typename C, typename A1 >
struct result_of_ptmf< R (C::*)( A1 ) > {
typedef R type;
};
template< typename R, typename C, typename A1, typename A2 >
struct result_of_ptmf< R (C::*)( A1 ,A2) > {
typedef R type;
};
template< typename R, typename C, typename A1, typename A2,typename A3 >
struct result_of_ptmf< R (C::*)( A1 ,A2,A3) > {
typedef R type;
};

template<typename T>

class RemovePointer
{
public:
typedef T Type;
};
template<typename T>

class RemovePointer<T*>
{
public:
typedef T Type;
};

template<typename T>

struct IsPointer {
bool operator()() const {
return false;
}
};
template<typename T>


struct IsPointer<T*> {
bool operator()() const {
return true;
}
};

template<typename T>


struct IsConst {
bool operator()() const {
return false;
}
};
template<typename T>


struct IsConst<const T> {
bool operator()() const {
return true;
}
};

// this should remove const from a variable
// all kind of warnings apply to this kind of stuff :/
template<typename T> 
struct remove_const_from_instance_impl{
typedef T type;
static typename type value(T val){return val;}
};
template<typename T>
struct remove_const_from_instance_impl<const T >{
typedef T type;
static typename type  value(const T val){return const_cast<T>(val);}
};


template<typename T>
auto remove_const_from_instance(T  value)-> typename remove_const_from_instance_impl<T>::type {
return remove_const_from_instance_impl<T>::value(value); 
}
*/