#include <core/reflection/dynamic/DynamicObject.h>
#include <core/reflection/dynamic/DynamicObjectImplementation.h>
#include <core/reflection/dynamic/DynamicReflectedObjectImplementation.h>
#include <core/reflection/dynamic/DynamicMappedObject.h>


#include <core.utility.h>
#include <core/reflection/type/Argument.implementation.template.h>
//#include <core.reflection.builder.h>
NS_USE(CORE_NAMESPACE);


//reflect_type_default_definition(NS(CORE_NAMESPACE)::DynamicObject)


DynamicObject::DynamicObject(std::shared_ptr<DynamicObjectImplementation> impl):_implementation(impl){}


IModifiableValue & DynamicObject::operator[](const std::string & name){
  return *getProperty(name);
}

DynamicCallable DynamicObject::getMethod(const std::string & name){
  Argument a = _implementation->getMember(name)->get();
  return a;
}


bool DynamicObject::hasMember(const std::string & name)const{ return hasProperty(name)||hasMethod(name);}
bool DynamicObject::hasProperty(const std::string & name)const{
  return _implementation->hasProperty(name);
}
bool DynamicObject::hasMethod(const std::string & name)const{
  return _implementation->hasMethod(name);
}

DynamicObject::MemberList DynamicObject::getMemberNames()const{
  return concat(getPropertyNames(),getMethodNames());
}

DynamicObject::MemberList DynamicObject::getMethodNames()const{
  return _implementation->getMethodNames();
}

DynamicObject::MemberList DynamicObject::getPropertyNames()const{
  return _implementation->getPropertyNames();
}

std::shared_ptr<IModifiableValue> DynamicObject::getProperty(const std::string & name){
  return _implementation->getMember(name);
}

std::shared_ptr<const IModifiableValue> DynamicObject::getProperty(const std::string & name)const{
  return _implementation->getMember(name);
}
Argument DynamicObject::operator*(){
  return _implementation->asArgument();
}

NS_BEGIN(CORE_NAMESPACE)
  DynamicObject make_dynamic_mapped(Argument arg){
    return DynamicObject(std::make_shared<DynamicMappedObjectImplementation>());
  }


  DynamicObject make_dynamic(Argument argument){
    DynamicObject result(std::make_shared<DynamicReflectedObjectImplementation>(argument));
    return result;
  }
  
  
  bool copy(DynamicObject & destination, const DynamicObject & source){
    auto names = concat(source.getPropertyNames(),destination.getPropertyNames());
    std::sort(std::begin(names),std::end(names));
    names.erase(std::unique(std::begin(names),std::end(names)),std::end(names));

    
    for(auto it = std::begin(names); it != std::end(names); it++){
      auto d = destination.getProperty(*it);
      auto s = source.getProperty(*it);
      auto value = s->get();
      if(!value.isValid())continue;
      d->set(value);
    }

    return true;
  }
NS_END(CORE_NAMESPACE)
