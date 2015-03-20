#pragma once
#include <core/dynamic/dynamic.h>
#include <core/dynamic/DynamicProperty.h>
NS_BEGIN(CORE_DYNAMIC_NAMESPACE)

any DynamicProperty::to_any()const{
  auto prop = _object.get(_name);
  return prop.to_any();
}
DynamicProperty::DynamicProperty(DynamicObject obj, const member_name_type & key) :_object(obj), _name(key){

}
template<typename T> DynamicProperty::operator T(){
  return as<T>();
}
inline DynamicProperty::operator DynamicObject() {
  return get();
}
template<typename T, typename TNext> DynamicProperty & DynamicProperty::operator=(T && val){
  set(val);
  return *this;
}
DynamicProperty & DynamicProperty::operator = (const DynamicProperty & other){
  set(other.get());
  return *this;
}


inline DynamicObject DynamicProperty::get()const{
  return _object.get(_name);
}

void DynamicProperty::set(DynamicObject  val){
  _object.set(_name, val);
}

template<typename T> T DynamicProperty::as(){
  return _object.get(_name).as<T>();
}

template<typename TArgumentList>
DynamicObject DynamicProperty::call(const TArgumentList & arguments){
  return call(container_to_vector(arguments));
}
DynamicObject DynamicProperty::call(const argument_list_type & arguments){
  return _object.callMember(_name, arguments);
}
template<typename ... TArgs>
DynamicObject DynamicProperty::operator()(TArgs && ... args){

  return call(std::vector < any > { static_cast<any>(args)... });
}


auto DynamicProperty::operator[](const member_name_type & key)->DynamicProperty{
  auto obj = _object.get(_name);
  return obj[key];

}

NS_END(CORE_DYNAMIC_NAMESPACE)

