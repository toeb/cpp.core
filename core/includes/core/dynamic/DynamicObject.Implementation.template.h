#pragma once
#include <core/dynamic/dynamic.h>
#include <core/dynamic/DynamicObject.h>
#include <core/dynamic/IDynamicObjectImplementation.h>
#include <core/dynamic/DynamicProperty.h>
#include <core/dynamic/DynamicObjectExpandoImplementation.h>
#include <core/dynamic/DynamicObjectReflectionImplementation.h>
#include <core/template/default.h>

NS_BEGIN(CORE_DYNAMIC_NAMESPACE)
std::string DynamicObject::toString()const{
  std::stringstream ss;
  toStream(ss);
  return ss.str();
}
void DynamicObject::toStream(std::ostream & out)const{
  auto res = _implementation->tryToStream(out);
}


bool DynamicObject::isConvertibleTo(any::type_id typeId){
  bool result;
  if (!_implementation->tryCanConvert(typeId, result))return false;
  return result;
}
any::type_id DynamicObject::getType()const{
  any::type_id type;
  if (!_implementation->tryGetType(type))return type_provider::unknown_type;
  return type;
}
template<typename T> bool DynamicObject::isConvertibleTo(){
  return isConvertibleTo(type_provider::typeOf<T>());
}

any DynamicObject::to_any()const{
  any result;
  if (_implementation->tryConvert(default_value(), result))return result;
  return any::explicit_any((DynamicObject)*this);
}
DynamicObject::DynamicObject(implementation_ptr imp) :_implementation(imp){}



auto DynamicObject::members()const->member_list{
  member_list lst;
  _implementation->tryGetMemberList(lst);
  return lst;
}
template<typename TArgumentList>
DynamicObject DynamicObject::call(const TArgumentList & container){
  return call(std::move(container_to_vector(container)));
}
DynamicObject DynamicObject::call(const argument_list_type && arguments){
  DynamicObject result;
  auto success = _implementation->tryInvoke(IDynamicObjectImplementation::invoke_context(), result, std::move(arguments));
  return result;
}
template<typename TArgumentList>
DynamicObject DynamicObject::callMember(const member_name_type & member, const TArgumentList & container){
  return callMember(member, container_to_vector(container));
}
DynamicObject DynamicObject::callMember(const member_name_type & member, const argument_list_type && arguments){
  DynamicObject result;
  auto success = _implementation->tryMemberInvoke(member, result, std::move(arguments));
  return result;
}
DynamicObject & DynamicObject::operator =(const any & any){
  DynamicObject res(any);
  assign(res);
  return *this;
}
template<typename T> DynamicObject & DynamicObject::operator=(T && t){
  DynamicObject res(t);
  assign(res);
  return *this;
}
void DynamicObject::assign(const DynamicObject  & other){
  _implementation = other._implementation;
}
DynamicObject & DynamicObject::operator=(const DynamicObject & other){
  _implementation = other._implementation;
  return *this;
}

DynamicObject & DynamicObject::operator=(const DynamicObject && other){
  _implementation = other._implementation;
  return *this;
}

template<typename T> T DynamicObject::as(){
  any result;
  _implementation->tryConvert(default_value(), result);
  return result;

}
template<typename T> DynamicObject::operator T(){
  return as<T>();
}

DynamicObject::operator any(){
  any result;
  auto success = _implementation->tryConvert(default_value(), result);
  if (!success) {
    any(*this);
  }

  return result;
}

void DynamicObject::set(const member_name_type & name, DynamicObject  value){
  auto success = _implementation->tryMemberSet(name, value);
}
DynamicObject DynamicObject::get(const member_name_type & name)const{
  DynamicObject val;
  auto success = _implementation->tryMemberGet(name, val);
  return val;
  //any result;
  //_implementation->tryMemberGet(name, result)
}



template<typename... TArgs>
DynamicObject DynamicObject::operator()(TArgs && ... args){
  return call({ args... });
};

auto DynamicObject::operator[](const member_name_type & key)->DynamicProperty{
  DynamicProperty prop(*this, key);
  return prop;
}

auto DynamicObject::operator[](const member_name_type & key)const->const DynamicProperty{
  DynamicProperty prop(*this, key);
  return prop;
}


DynamicObject::DynamicObject() : _implementation(std::make_shared<DynamicObjectExpandoImplementation>()){}
template<typename T, typename TDecayed, bool concept>
DynamicObject::DynamicObject(T && value, typename std::enable_if<concept>::type*
  ) : _implementation(std::make_shared<DynamicObjectReflectionImplementation>(value)){
  auto c = concept;
  auto tn = typeid(T).name();
  auto isprop = std::is_same<typename std::decay<T>::type, DynamicProperty>::value;
}

DynamicObject::DynamicObject(any && value) : _implementation(std::make_shared<DynamicObjectReflectionImplementation>(value)){}
DynamicObject::DynamicObject(const any & value) : _implementation(std::make_shared<DynamicObjectReflectionImplementation>(value)){}
DynamicObject::DynamicObject(const DynamicProperty & prop) : _implementation(prop.get()._implementation){

}
DynamicObject::DynamicObject(const DynamicObject & other) : _implementation(other._implementation){}
NS_END(CORE_DYNAMIC_NAMESPACE)

