#pragma once
#include <core/core.h>
#include <core/values/values.h>

#include <core/values/ObservableValue.h>
#include <core/values/BaseConnector.h>
NS_BEGIN(CORE_VALUES_NAMESPACE)

class IVersioned{
public:
  typedef const IValueVersion& version_type;
  virtual auto version()const->version_type = 0;

};
class ITyped{
public:
  typedef ::core::type_provider type_provider;
  typedef type_provider::type_id type_type;
  virtual auto type()const->type_type = 0;
};

class TypedBase : public ITyped{
public:
  auto type()const->type_type{ return _type; }
protected:
  virtual auto setType(const type_type & type)->void{ _type = type; }
private:
  type_type _type;
};



class VersionedBase : public IVersioned{
public:
  auto version()const ->version_type override{ return _version; }
protected:
  auto updateVersion(IConnectable & c)->void{ _version.update(c); }
private:
  IntValueVersion _version;
};

class MemoryValue :
  public virtual ObservableValue,
  public virtual BaseConnector,
  public virtual VersionedBase,
  public virtual ITyped{
public:
  MemoryValue(){}
  auto type()const->type_type{ return _value.type(); }

protected:
  value_holder produceValue()override{ return _value; }
  void consumeValue(value_holder arg)override{ _value = arg;  updateVersion(*this); raiseOnValueChanged(arg); }
private:
  value_holder _value;
};

NS_END(CORE_VALUES_NAMESPACE)

