#pragma once
#include <core/core.h>

#include <core/reflection/dynamic/DynamicObject.h>
NS_BEGIN(CORE_NAMESPACE)  

  
struct DynamicObjectImplementation{
  typedef DynamicObject::MemberList MemberList;
  virtual std::shared_ptr<IModifiableValue> getMember(const std::string  & name)=0;
  virtual std::shared_ptr<const IModifiableValue> getMember(const std::string  & name)const=0;
  virtual MemberList getPropertyNames() const;
  virtual MemberList getMethodNames() const;
  virtual bool hasProperty(const std::string & name)const;
  virtual bool hasMethod(const std::string & name)const;
  virtual Argument asArgument();
};
NS_END(CORE_NAMESPACE)
