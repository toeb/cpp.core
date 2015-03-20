#pragma once
#include <core/core.h>

#include <core/any.h>
#include <core/events/events.h>
#include <iostream>
NS_BEGIN(CORE_EVENTS_NAMESPACE)

/// a simple data transfer object cotnaining the sender of the event as well a an arbitrary argument
  class EventArgs{
  public:
    typedef any sender_type;
    typedef any value_type;
    EventArgs(sender_type sender, value_type arg) :_sender(sender), _arg(arg){}
    sender_type event(){ return _sender; }
    value_type arg(){ return _arg; }
  private:
    sender_type _sender;
    value_type _arg;
  };

 inline std::ostream & operator << (std::ostream & out, const EventArgs &){ return out; }
 NS_END(CORE_EVENTS_NAMESPACE)
