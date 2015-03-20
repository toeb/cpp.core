#include <core/reflection/member/method/MethodInfo.h>
//#include "MethodInfo.h"
//#include <core.reflection.builder.h>
NS_USE(CORE_NAMESPACE);

/*

auto MethodInfo::argument(unsigned int index)->argument_ptr {
  if(Arguments().size()<=index)return argument_ptr();
  return Arguments()[index];
}
auto MethodInfo::argument(unsigned int index)const ->const_argument_ptr {
  if(Arguments().size()<=index)return argument_ptr();
  return Arguments()[index];
}

Argument MethodInfo::call(void * object)const{
  std::vector<Argument> args;
  return call(object,args);
}
Argument MethodInfo::call(const void * object)const{
  std::vector<Argument> args;
  return call(object,args);
}*/

bool MethodInfo::initializeType(){
 /* core::reflection::builder::reflect<MethodInfo>()
    ->fullyQualifiedName(DS_STRINGIFY("::"<<NS(CORE_NAMESPACE)<<"MethodInfo"))
    ->supertype<CallableInfo>()
    ->supertype<MemberInfo>()
    ->publishHierarchy();*/
  return true;
}
const Type * MethodInfo::getType()const{
  return type_of<MethodInfo>();
}

