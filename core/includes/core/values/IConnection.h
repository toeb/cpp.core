#pragma once
#include <core/core.h>
#include <core/values/values.h>

NS_BEGIN(CORE_VALUES_NAMESPACE)


  class IConnectable;
  class IConnection{
  public:
    typedef std::shared_ptr<IConnectable> connectable_type;
    virtual bool connect(connectable_type lhs, connectable_type rhs) = 0;
    virtual bool disconnect() = 0;
    virtual bool sync() = 0;
  };

NS_END(CORE_VALUES_NAMESPACE)
