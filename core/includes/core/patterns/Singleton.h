#pragma once
#include <core/core.h>

#include <core/template/TemplateUtilities.h>

#include <memory>
NS_BEGIN(CORE_NAMESPACE)


#define DS_SINGLETON_TYPE(CLASSNAME,...) typedef CLASSNAME __VA_ARGS__ SingletonType;
  // todo remove if !_instance 
#define DS_SINGLETON_IMPL(CLASSNAME)                                              \
  static std::shared_ptr<SingletonType> instance(){                               \
  static std::shared_ptr<SingletonType> _instance;                                \
  if(!_instance)_instance = std::shared_ptr<SingletonType>(new SingletonType());  \
    return _instance;                                                             \
  }                                                                               \
  private:                                                                        \
  CLASSNAME()

#define DS_SINGLETON_TEMPLATED(CLASSNAME,...)\
  public:\
  DS_SINGLETON_TYPE(CLASSNAME,<__VA_ARGS__>);\
  DS_SINGLETON_IMPL(CLASSNAME)

#define DS_SINGLETON(CLASSNAME)\
  public:\
  DS_SINGLETON_TYPE(CLASSNAME,);\
  DS_SINGLETON_IMPL(CLASSNAME)



// obsolete use DS_SINGLETON_TEMPLATED and DS_SINGLETON instead
#define TEMPLATEDSINGLETON(CLASSNAME,...) DS_SINGLETON_TEMPLATED(CLASSNAME,__VA_ARGS__)

//defines a the class as a singleton (private constructor and public static instance() method returning a shared ptr
#define SINGLETON(CLASSNAME) DS_SINGLETON(CLASSNAME)





/*  Example of a class using the singleton macro

class TestClass{
SINGLETON(TestClass){
// constructor code here
}
};

*/

NS_END(CORE_NAMESPACE)
