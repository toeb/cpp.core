#pragma once
#include <core/core.h>

#include <core/reflection/dynamic/DynamicReflectedObjectImplementation.h>
#include <map>
NS_BEGIN(CORE_NAMESPACE)

  class DynamicMappedObjectImplementation :public DynamicReflectedObjectImplementation{
    std::map<std::string,Argument> _map;
  public:  
    DynamicMappedObjectImplementation();
    std::vector<std::string> __list_property_names()const;
    Argument __get_property(const std::string & name);
    bool __set_property(const std::string & name, Argument argument);
  };

NS_END(CORE_NAMESPACE)
