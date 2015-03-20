#pragma once
#include <core/core.h>

#include <vector>
#include <core/reflection/type/TypeInfo.h>
#include <core/template/func_traits.h>
NS_BEGIN(CORE_NAMESPACE)
  
  struct func_info{
    typedef const Type * type_ptr;
    template<typename T>
    static func_info create(){
      func_info info;
      typedef func_traits<T> traits;
      info.type = traits::type;
      info.class_type = type_of<traits::class_type>();
      info.return_type = type_of<traits::return_type>();
     // info.argument_types = get_tuple_types(traits::args_tuple());
      return info;
    }
    callable_type type;
    type_ptr class_type;
    type_ptr return_type;
    std::vector<type_ptr> argument_types;

  };
  template<typename T>
  func_info create_func_info(){
    return func_info::create<T>();
  }
  template<typename T>
  func_info create_func_info(T t){
    return create_func_info<T>();
  }

NS_END(CORE_NAMESPACE)
