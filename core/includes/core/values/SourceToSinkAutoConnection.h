#pragma once

#include <core/values/SourceToSinkConnection.h>

NS_BEGIN(CORE_VALUES_NAMESPACE)


struct AutoSourceToSinkConnection : public SourceToSinkConnection{
  std::shared_ptr<::core::events::IEventHandler> listener;
  bool disconnect()override{

    return SourceToSinkConnection::disconnect();
  }
  bool connect(connectable_type from, connectable_type to) override{

    if (!SourceToSinkConnection::connect(from, to))return false;

    auto observable = std::dynamic_pointer_cast<IObservableSource>(from);
    if (!observable)throw std::exception();
    listener = observable->OnValueChanged() += [this](any a){
      this->sync();
    };
    return true;
  }

};
NS_END(CORE_VALUES_NAMESPACE)