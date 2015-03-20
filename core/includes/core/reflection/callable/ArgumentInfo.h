#pragma once
#include <core/core.h>

#include <core/reflection/attribute/AttributeTarget.h>
#include <memory>

NS_BEGIN(CORE_NAMESPACE)

  /// represents an argument of a method signature
  class ArgumentInfo : public AttributeTarget{
  public:
    propdef unsigned int basic_property(Index);
    propdef std::string basic_property(Name);
    propdef std::shared_ptr<const Type> basic_property(ArgumentType);
    propdef Argument basic_property(DefaultValue);
  };
 

NS_END(CORE_NAMESPACE)
