#pragma once
#include <core/core.h>
/**
 This file contains shims which allow different compilers to work correclty for the whole source base
*/

#include <memory>


// MSVC does not have a __FUNCSIG__ macro 
// this defines it so that any compile can use __FUNCSIG__
#ifndef __FUNCSIG__
#define __FUNCSIG__ __PRETTY_FUNCTION__
#endif

#ifndef WIN32
#define __FUNCSIG__ __PRETTY_FUNCTION__
#endif

// allow use of strncpy without warnings
#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

#ifdef WIN32
#pragma warning(disable : 4250)
#define noexcept
#endif

#ifdef __GNUC__
// shims for gcc less than 4.7
#if __GNUC__ < 5 && __GNUC_MINOR__ < 7

    #define override
    #define final


namespace std{

template<typename T, typename ...TArgs> std::unique_ptr<T> make_unique(TArgs&&... args){
    return std::unique_ptr<T>(new T(args...));
}

template<typename T> struct is_default_constructible{ static const bool value = false;};
template<typename T, typename TTo> struct is_assignable{static const bool value=false;};
}

#endif
#endif
// nested_template is to be placed in within nested templates (MSVC 10) does not work if there is a superfluos template
// keyword and the later compilers do not work without it
// todo make conditional on the compiler and version
#define nested_template template

