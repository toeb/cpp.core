#pragma once
#include <core/core.h>

#include <core/preprocessor/Basic.h>

#define DS_INITIALIZER_STATIC_INSTANCE_NAME(NAME) __ ## NAME ## StaticInitializer
#define DS_INITIALIZER_STATIC_CLASSNAME(NAME) __ ## NAME ## StaticInitializer ## Class
#define DS_INITIALIZER_STATIC_METHOD_NAME(NAME) DS_CONCAT(initializeStatic,NAME)
#define DS_INITIALIZER_STATIC_METHOD_WRAPPER_NAME(NAME) DS_CONCAT(initializeStaticWrapper,NAME)

/**
 * \brief A macro that defines a static initializer - it executes code once in the class it was defined
 *        it is executed the first time before a class is instanciated. /TODO: fix this somehow wihtout loosing flexibility
 *       \example DS_INITIALIZER_STATIC(SomeName){ cout << "static initialization";}.
 *
 * \param NAME  The name of the initializer (it must be unique for the class.
 */
#define DS_INITIALIZER_STATIC(NAME)                                                                                                               \
 struct DS_INITIALIZER_STATIC_CLASSNAME(NAME){                                                                                                    \
  DS_INITIALIZER_STATIC_CLASSNAME(NAME)(){                                                                                                        \
  static bool initialized = []()->bool{DS_INITIALIZER_STATIC_METHOD_NAME(NAME)(); return true;}();   /*This is called exactly once*/              \
  }                                                                                                                                               \
 }DS_INITIALIZER_STATIC_INSTANCE_NAME(NAME);                                                                                                      \
 private:                                                                                                                                         \
   static DS_INLINE void DS_INITIALIZER_STATIC_METHOD_NAME(NAME)()                                                                                                      



#define DS_EXECUTE_ONCE_IMPLEMENTATION(ID)\
  DS_INITIALIZER_STATIC_METHOD_NAME(ID)() 

#define DS_EXECUTE_ONCE(ID)\
  DS_INITIALIZER_STATIC(ID)



/**
 * \brief A macro that executes static code in a class once.
 */
#define DS_ONCE\
 DS_EXECUTE_ONCE(__LINE__)
