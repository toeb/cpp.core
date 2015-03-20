#pragma once
#include <core/core.h>

#include <core.property.h>
#include <string>

NS_BEGIN(CORE_NAMESPACE)
  class Attribute{
    typedef std::string basic_property(AttributeName);
  public:
    virtual ~Attribute();
  };
NS_END(CORE_NAMESPACE)
