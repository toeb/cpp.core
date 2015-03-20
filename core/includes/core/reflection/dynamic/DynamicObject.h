#pragma once
#include <core/core.h>

#include <core/reflection/type/Argument.h>
#include <core/reflection/dynamic/DynamicCallable.h>
#include <core/reflection/value/IModifiableValue.h>

NS_BEGIN(CORE_NAMESPACE)
  struct DynamicObjectImplementation;
  class DynamicObject{
    //reflect_type_declaration(NS(CORE_NAMESPACE)::DynamicObject)
    std::shared_ptr<DynamicObjectImplementation> _implementation;
  public:
    Argument operator*();
    typedef std::vector<std::string> MemberList;  
    DynamicObject(std::shared_ptr<DynamicObjectImplementation> impl);
    // returns a reference to an modifiable value. this reference exists as long as this object exists
    // and will cause errors if accessed beyond the lifespan.  use getProperty / getMethod for a persistent reference
    // this operator will throw an exception if modifiable value can not be obtained.  use getProperty / getMethod for silent failures
    IModifiableValue & operator[](const std::string & name);
    std::shared_ptr<IModifiableValue> getProperty(const std::string & name);
    std::shared_ptr<const IModifiableValue> getProperty(const std::string & name)const;
    DynamicCallable getMethod(const std::string & name);
    MemberList getMemberNames()const;
    MemberList getPropertyNames()const;
    MemberList getMethodNames()const;
    bool hasMember(const std::string & name)const;
    bool hasProperty(const std::string & name)const;
    bool hasMethod(const std::string & name)const;
  };


  
  bool copy(DynamicObject & destination, const DynamicObject & source);

  DynamicObject make_dynamic(Argument argument);
  DynamicObject make_dynamic_mapped(Argument arg = Argument());

NS_END(CORE_NAMESPACE)
