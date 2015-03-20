#pragma once
#include <core/core.h>
#include <core/values/values.h>
#include <core/values/IConnector.h>
#include <core/values/IntValueVersion.h>
NS_BEGIN(CORE_VALUES_NAMESPACE)

  /*class BaseConnectable : public virtual IConnectable{
  public:

    BaseConnectable(value_type type) :_valueType(type){}
    

    virtual value_type getValueType()const override{
      return _valueType;
    }

    virtual const IValueVersion & getVersion()const override{ return _version; }

  protected:
    void updateVersion(){ _version.update(*this); }
  private:
    value_type _valueType;

    IntValueVersion _version;
  };*/
  // this class is used as a base for various implementation of cponnectors
  // it sports a fixed value type
  class BaseConnector :/* public BaseConnectable, */public virtual IConnector{
  public:
   // using BaseConnectable::getValueType;
    /*BaseConnector(value_type type) :BaseConnectable(type){}*/
  };
NS_END(CORE_VALUES_NAMESPACE)
