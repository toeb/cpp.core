#pragma once
#include <core/core.h>

#include <core/reflection/type/Type.h>
NS_BEGIN(CORE_NAMESPACE)

  

  
    template<typename Container> const ConstructorInfo * Type::getConstructor(const Container & container)const{
      auto it = std::begin(container);
      auto end = std::end(container);
      std::vector<const Type*> types;
      for(;it!=end;it++){
        types.push_back(*it);
      }
      return getConstructorInfo(types);
    }

NS_END(CORE_NAMESPACE)
