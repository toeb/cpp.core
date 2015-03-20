#include <core/reflection/dynamic/DynamicMappedObject.h>


#include <core/reflection/dynamic/DynamicReflectedObjectImplementation.h>
#include <core/reflection/type/Argument.h>
#include <vector>
NS_USE(CORE_NAMESPACE);

std::vector<std::string> DynamicMappedObjectImplementation::__list_property_names()const{
  std::vector<std::string> result;
  for(auto it = _map.begin(); it!=_map.end();it++){    
    result.push_back(it->first);
  }
  return result;
}

DynamicMappedObjectImplementation::DynamicMappedObjectImplementation():DynamicReflectedObjectImplementation(std::shared_ptr<DynamicMappedObjectImplementation>(this,[](DynamicMappedObjectImplementation* ){})){

  // creates a shared pointer from itself and passes it on to the Dynamic object class.  
  // custom deleter which does nothing was added so the object is not automatically deleted.
}

Argument DynamicMappedObjectImplementation::__get_property(const std::string & name){    
  if(_map.find(name)==std::end(_map))return Argument();
  return _map[name];
}
bool DynamicMappedObjectImplementation::__set_property(const std::string & name, Argument argument){
  _map[name] = argument;
  return true;
}
/*
reflect_begin(DynamicMappedObjectImplementation);
_method(__get_property);
_method(__set_property);
_method(__list_property_names);
reflect_end;

*/