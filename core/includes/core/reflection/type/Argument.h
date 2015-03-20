#pragma once
#include <core/core.h>

#include <memory>

NS_BEGIN(CORE_NAMESPACE)
  class Type;
  struct Void;

  template<typename T,bool is_rvalue=std::is_rvalue_reference<T>::value,bool is_ref = std::is_reference<T>::value>
  struct choose_reference{
    template<typename Arg>
    static T choose(Arg& arg){
      typedef T type;
        return  arg.template ref<type>();

    }
  };
  template<typename T>
  struct choose_reference<T,true,true>{
    template<typename Arg>
    static typename std::remove_reference<T>::type  choose(Arg &arg){
      typename std::remove_reference<T>::type val = arg;
      return val;
    }
  };
  template<typename T>
  struct choose_reference<T,false,true>{
    template<typename Arg>
    static typename std::remove_reference<T>::type choose(Arg& arg){
      typename std::remove_reference<T>::type val = arg;
      return val;
    }
  };

  //todo rename to ObjectHandle
  // a struct which stores data and dynamic type information for any value (similar to boost any but developed without knowledge of it)
  // shared_ptrs are not wrapped and the type will be the type of the shared ptr, else the assigned type is always used
  struct Argument{
    Argument(const NS(CORE_NAMESPACE)::Void & v);
    template<typename T> Argument(const T & data);
    template<typename T> Argument(std::shared_ptr<T> data);
    Argument(std::shared_ptr<void> data, const Type * type);
    Argument();
    ~Argument();

    // obsolete use Void() instead
    static const Argument & VoidArgument();    
    static const Argument & Void();    

    // checks to see if the Argument is valid (has a value)
    bool isValid()const;
    template<typename T> operator const T & ()const;
    template<typename T> operator T & ();    
    //template<typename T> operator T &&()const;

    template<typename T> const T& ref()const;
    template<typename T> T& ref();
    template<typename T> T rvalue()const;

    //returns a const pointer to the data
    template<typename T> const T* c_ptr()const;
    template<typename T> T* c_ptr();
    template<typename T> const std::shared_ptr<T> ptr()const;
    template<typename T> std::shared_ptr<T> ptr();
    template<typename T> const std::weak_ptr<T> w_ptr()const;
    template<typename T> std::weak_ptr<T> w_ptr();

    template<typename T> auto convert ()const->decltype(choose_reference<T>::choose(Argument()));


    template<typename T> operator std::shared_ptr<const T>()const;
    template<typename T> operator std::shared_ptr<T>();

    // same as ptr
    template<typename T> std::shared_ptr<T> cast();
    template<typename T> std::shared_ptr<const T> cast()const;

    // field containing the actual data.  It is void* so it can store anything
    std::shared_ptr<void> data;
    // type of the data useful for querying
    const Type * type;
  };


  inline std::ostream & operator<<(std::ostream & out, Argument val){ return out; }
NS_END(CORE_NAMESPACE)

