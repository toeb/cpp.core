#pragma once
#include <core/core.h>
#include <core/values/values.h>
#include <memory>
#include <core/values/Connection.h>
#include <core/values/SourceToSinkConnection.h>
NS_BEGIN(CORE_VALUES_NAMESPACE)

  class TwoWayAutoConnection : public Connection{
  public:
    bool connect(connectable_type lhs, connectable_type rhs) override{
      auto lhs_sink = std::dynamic_pointer_cast<ISink>(lhs);
      auto lhs_source = std::dynamic_pointer_cast<ISource>(lhs);
      if (!lhs_sink)return false;
      if (!lhs_source)return false;
      auto rhs_sink = std::dynamic_pointer_cast<ISink>(rhs);
      auto rhs_source = std::dynamic_pointer_cast<ISource>(rhs);
      if (!rhs_sink)return false;
      if (!rhs_source)return false;

      if (!_ltr.connect(lhs_source, rhs_sink))return false;
      if (!_rtl.connect(rhs_source, lhs_sink))return false;
    }

    bool sync(){

      return _ltr.sync() && _rtl.sync();
    }
  private:
    SourceToSinkConnection _ltr;
    SourceToSinkConnection _rtl;
  };
NS_END(CORE_VALUES_NAMESPACE)
