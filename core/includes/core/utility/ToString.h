#pragma once
#include <core/core.h>

#include <string>
NS_BEGIN(CORE_NAMESPACE)

  /*
  // generic tostring method

  template <typename T>
  struct has_toString{
  private:
    template <typename T1>
    static bool test(typename decltype(&T1::toString));
    template <typename>
    static void test(...);
  public:
    enum { value = !std::is_void<decltype(test<T>(0))>::value };
  };

  template<typename T, bool hasToString = has_toString<T>::value>
  struct stringifier{
    static bool toString(const T & object, std::ostream & stream){
      return false;
    }
  };

  template<typename T>
  struct stringifier<T,true>{
    static bool toString(const T & object, std::ostream & stream){
      object.toString(stream);
      return true;
    }
  };


  template<typename T>
  bool toString(const T & object, std::ostream & stream){
    return stringifier<T>::toString(object,stream);
  }

  template<typename T>
  std::string toString(const T & object){
    std::stringstream stream;
    toString(object,stream);
    return stream.str();
  }
  */
NS_END(CORE_NAMESPACE)
