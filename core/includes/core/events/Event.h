#pragma once
#include <core/core.h>


#include <map>
#include <memory>

#include <core/events/events.h>
#include <core/events/IEvent.h>

NS_BEGIN(CORE_EVENTS_NAMESPACE)


// implementation of the IEvent interface, uses a map to store eventhandlers and has a raiseEvent method
// todo should use the callable interfaces from core::reflection to allow multicast events with multiple input args (signals,slots like)
class Event : public IEvent{
  typedef ::std::map<void *, listener_type> handler_container;
  ::std::map<void *, listener_type> _handlers;
public:
  /// adds an event handler to this event
  void addHandler(listener_type listener)override {
    _handlers[listener.lock().get()] = listener;
  }
  /// removes an event handler from this event
  bool removeHandler(listener_type listener)override{
    return  _handlers.erase(listener.lock().get()) != 0;
  }
  /// returns true if the event has at least one handler
  bool hasHandler() const override{
    return _handlers.size() != 0;
  }

  // raises the event
  any operator()(any arg){
    return raiseEvent(arg);
  }

  const handler_container & handlers()const{ return _handlers; }

  /// raises the event, returning the result of the last event handler called (may be an empty argument)
  any raiseEvent(any arg){
    //std::accumulate()
    any lastArg;
    for (auto listener : _handlers){
      auto l = listener.second.lock();
      if (l) lastArg = l->onEvent(arg); 
    }
    return lastArg;
  }
};

NS_END(CORE_EVENTS_NAMESPACE)
