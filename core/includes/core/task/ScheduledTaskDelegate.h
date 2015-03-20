#pragma once
#include <core/core.h>
#include <functional>
#include <core/task/ScheduledTask.h>
NS_BEGIN(CORE_NAMESPACE)
  template <typename T=std::function<void(Time ,Time)> >
  class ScheduledTaskDelegate : public virtual ScheduledTask{
    T & _callback;
  public :
    ScheduledTaskDelegate(T & callback):_callback(callback){
      setName("ScheduledTaskDelegate");
    }
    ScheduledTaskDelegate(T & callback, Time timeoutInterval, bool repeat):_callback(callback){
      setIsOneTimeTask(!repeat);
      setInterval(timeoutInterval);
    }
    virtual void timeout(Time dt, Time t){
      _callback(dt,t);
    }
  };

  template <>
  class ScheduledTaskDelegate<std::function<void(Time ,Time)> > : public virtual ScheduledTask{
    std::function<void(Time ,Time)> _callback;
  public :
    ScheduledTaskDelegate(std::function<void(Time ,Time)> callback):_callback(callback){
      setName("ScheduledTaskDelegate");
    }
    ScheduledTaskDelegate(std::function<void(Time ,Time)> callback, Time timeoutInterval, bool repeat):_callback(callback){
      setIsOneTimeTask(!repeat);
      setInterval(timeoutInterval);
    }
    virtual void timeout(Time dt, Time t){
      _callback(dt,t);
    }
  };
NS_END(CORE_NAMESPACE)
