#include <core/reflection/callable/CallableInfo.h>
//#include "CallableInfo.h"
//#include <core.reflection.builder.h>

NS_USE(CORE_NAMESPACE);

bool CallableInfo::isValid()const{
  return true;
}

auto CallableInfo::argument(unsigned int index)->argument_ptr {
  if(Arguments().size()<=index)return argument_ptr();
  return Arguments()[index];
}
auto CallableInfo::argument(unsigned int index)const ->const_argument_ptr {
  if(Arguments().size()<=index)return argument_ptr();
  return Arguments()[index];
}


bool CallableInfo::initializeType(){
  /*core::reflection::builder::reflect<MethodInfo>()
    ->fullyQualifiedName(DS_STRINGIFY("::"<<NS(CORE_NAMESPACE)<<"CallableInfo"))
    ->publishHierarchy();
 */ return true;
}
