#pragma once
#include <core/core.h>
#include <core/any.h>
#include <core/values/values.h>
NS_BEGIN(CORE_VALUES_NAMESPACE)


// a reference accessor 
template<typename T>
struct accessor{
  T & val;
  //std::function<
    
  accessor(T & val) :val(val){}
  operator const T&()const{
    return val;
  }
  accessor<T> & operator=(const T && val){
    this->val = val;
    return *this;
  }

};

/// an accessor which maps property to a get and a set method
template <typename T, typename TGet, typename TSet >
struct get_set_accessor{
  typedef decltype(std::declval<TGet>()()) value_type;
  //typedef T value_type;
  
  inline core::any to_any()const{
    auto val = _getter();
    return any(val);
  }

  get_set_accessor(TGet getter, TSet setter) :_getter(getter), _setter(setter){}

  //get_set_accessor<T, TGet, TSet> & operator = (const T && val){
  //_setter(std::move(val));
  //return *this;
  //}



  // casting
  /// cast to class value type
  template<typename TX> typename std::enable_if<std::is_same<T, TX >::value, TX>::type
    as()const{ return _getter(); }
  operator T ()const{ return _getter(); }
  
  /// cast to any type
  template<typename TX> typename std::enable_if<!std::is_same<T, TX >::value, TX>::type 
  as()const{ return any(_getter()); }
  template<typename TX> operator TX ()const{ return any(_getter()); }


  get_set_accessor<T, TGet, TSet> & operator = (const T val){
    _setter(val);
    return *this;
  }

private:
  TGet _getter;
  TSet _setter;
};

template<typename TGet, typename TSet>
auto make_accessor(TGet getter, TSet setter)-> get_set_accessor < decltype(std::declval<TGet>()()), TGet, TSet > {
  return get_set_accessor<decltype(std::declval<TGet>()()), TGet, TSet>(getter, setter);
}

NS_END(CORE_VALUES_NAMESPACE)
