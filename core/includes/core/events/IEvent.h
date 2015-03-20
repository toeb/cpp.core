#pragma once
#include <core/core.h>
#include <memory>

NS_BEGIN(CORE_EVENTS_NAMESPACE)

class IEventHandler;

/// Event interface for adding and removing events
class IEvent{
public:
  typedef ::std::weak_ptr<IEventHandler> listener_type;
  virtual void addHandler(listener_type listener) = 0;
  virtual bool removeHandler(listener_type listener) = 0;
  virtual bool hasHandler()const = 0;
  operator bool()const{
    return this->hasHandler();
  }
};


/// adds the specified handler to the event
static ::std::shared_ptr<IEventHandler> operator+= (IEvent & ev, ::std::shared_ptr<IEventHandler> handler){
  ev.addHandler(handler);
  return handler;
}

/// removes the specified handler from the event
static bool operator-= (IEvent & ev, ::std::shared_ptr<IEventHandler> handler){
  return  ev.removeHandler(handler);
}


NS_END(CORE_EVENTS_NAMESPACE)





#include <core/events/DelegateEventHandler.h>

NS_BEGIN(CORE_EVENTS_NAMESPACE)


/// adds the specified functor as an event handler to the event, returns the shared ptr to the event handler (for removing)
template<typename T>
static std::shared_ptr<IEventHandler> operator+=(IEvent & ev, T handler){
  auto resHandler = std::make_shared<DelegateEventHandler>([handler](any arg){handler(arg); return any(); });
  ev.addHandler(resHandler);
  return resHandler;
}
NS_END(CORE_EVENTS_NAMESPACE)
