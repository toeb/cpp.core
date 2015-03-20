#pragma once
#include <core/core.h>
#include <core/values/values.h>

NS_BEGIN(CORE_VALUES_NAMESPACE)

  class SourceToSinkUpdateConnection : public SourceToSinkConnection{
  protected:
    auto connect(connectable_type from, connectable_type to)->bool override{
      if (!std::dynamic_pointer_cast<IVersioned>(from))return false;
      if (!std::dynamic_pointer_cast<IVersioned>(to))return false;
      return true;
    }


    virtual bool isDirty(std::shared_ptr<ISource> source, std::shared_ptr<ISink> sink)override{
      auto versioned_source = std::dynamic_pointer_cast<IVersioned>(source);
      auto versioned_sink = std::dynamic_pointer_cast<IVersioned>(sink);

      auto & sink_version = versioned_sink->version();
      auto & source_version = versioned_source->version();
      auto result = sink_version.compare(source_version);
      if (result >= 0)return false;
      return true;
    }
  };
NS_END(CORE_VALUES_NAMESPACE)
