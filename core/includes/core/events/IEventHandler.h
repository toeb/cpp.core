#pragma once
#include <core/core.h>

#include <core/any.h>
#include <core/events/events.h>


NS_BEGIN(CORE_EVENTS_NAMESPACE)


class IEventHandler{
public:
  virtual any onEvent(any arg) = 0;
};

NS_END(CORE_EVENTS_NAMESPACE)
