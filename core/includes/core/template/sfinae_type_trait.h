#pragma once


/// creates a struct to test a sfinae expression for type T
/// the struct's const value field will be true if the dependent type of T exists else it will be false
/// the type field always contains T
/// if you want to check for a specific typedef in T write sfinae_type_trait(has_value_type, typename T::value_type)
/// if T has the typedef valuetype has_value_type::value will be true else it will be false
// note: currently fails in VS2013
#define sfinae_type_trait(NAME, ...)\
  template<typename TT>\
  struct NAME{\
  private:\
    typedef char one;\
    typedef struct { char array[2]; } two;\
    template<typename T> static one test(__VA_ARGS__*);\
    template<typename T> static two  test(...);\
  public:\
    static const bool value = sizeof(test<TT>(0)) == sizeof(one);\
    typedef TT type;\
};
