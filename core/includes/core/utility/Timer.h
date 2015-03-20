#pragma once
#include <core/core.h>
#include <core/PropertyChangingObject.h>
#include <core/Time.h>
NS_BEGIN(CORE_NAMESPACE)  
  class Timer/*:public virtual PropertyChangingObject*/{
//    reflect_type(NS(CORE_NAMESPACE)::Timer);
    //DS_PROPERTY_EXTENSION_METHODS;

    typedef Time basic_property(AccumulatedTime);
    typedef bool basic_property(IsRunning);

    Time _startTime;

  public:
    Timer():_AccumulatedTime(0){}
    inline void tick(){
      setIsRunning(true);
      _startTime=systemTime();
    };
    inline void tock(){
      Time endTime = systemTime();
      if(!getIsRunning())return;
      setIsRunning(false);

      _AccumulatedTime+= endTime-_startTime;
   //   notify_after_set(AccumulatedTime);
    }
    void resetTimer(){
      tock();
      setAccumulatedTime(0);
    }
  };
NS_END(CORE_NAMESPACE)
