#pragma once
#include <core/core.h>

#include <functional>
#include <core/events/events.h>
#include <core/events/IEventHandler.h>
NS_BEGIN(CORE_EVENTS_NAMESPACE)


/// a event handler implemented by a functor
class DelegateEventHandler : public  IEventHandler{
public:
  typedef std::function<any(any)> event_handler_type;
  DelegateEventHandler(event_handler_type handler) :_eventHandler(handler){}
  any onEvent(any arg)override{
    return _eventHandler(arg);
  }
  template<typename T>
  static std::shared_ptr<DelegateEventHandler> create(std::function<void(T)> handler){
    return std::make_shared<DelegateEventHandler>(handler);
  }
private:
  event_handler_type _eventHandler;
};


NS_END(CORE_EVENTS_NAMESPACE)
