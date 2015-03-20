#pragma once
#include <core/core.h>


#include <core/Observable.h>
#include <core.property.h>
#include <core/reflection/type/TypeInfo.h>
#include <core/reflection/type/Argument.h>
#include <core/reflection/type/TypeInfo.implementation.template.h>

NS_BEGIN(CORE_NAMESPACE)
  class IReadableValue : public Observable{
    reflect_type_declaration(NS(CORE_NAMESPACE)::IReadableValue);    
    typedef const Type * basic_property(ValueType);
  protected:
    virtual Argument retrieveValue()const=0;
  public:
    IReadableValue();
    IReadableValue(const Type * valueType);
    template<typename T>
    operator T()const{return get();};
    operator Argument()const{return get();}
    Argument get()const;

  };
NS_END(CORE_NAMESPACE)

