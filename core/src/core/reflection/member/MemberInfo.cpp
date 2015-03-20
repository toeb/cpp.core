#include <core/reflection/member/MemberInfo.h>
//#include "MemberInfo.h"
//#include <core.reflection.builder.h>

NS_USE(CORE_NAMESPACE);

MemberInfo::MemberInfo() :
  _AccessModifier(Unknown),
  _OwningType(0)
{}

MemberInfo::MemberInfo(const std::string & name):_AccessModifier(Unknown),_OwningType(0),_Name(name){}
MemberInfo::~MemberInfo(){}



bool MemberInfo::initializeType(){
  /*core::reflection::builder::reflect<MemberInfo>()
    ->fullyQualifiedName(DS_STRINGIFY(::NS(CORE_NAMESPACE)::MemberInfo))
    ->publishHierarchy()
    ->end();*/
  return true;
}