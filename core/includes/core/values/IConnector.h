#pragma once
#include <core/core.h>
#include <core/values/values.h>
#include <core/values/IConnectable.h>
#include <core/values/IValueVersion.h>

#include <core/values/InvalidValueVersion.h>
NS_BEGIN(CORE_VALUES_NAMESPACE)


  // the connector is the basic interface for atomic data connection
  class IConnector : public virtual IConnectable{
  public:
  };

NS_END(CORE_VALUES_NAMESPACE)
