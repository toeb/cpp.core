#pragma once
#include <core/core.h>

#include <core/task/ITask.h>

NS_BEGIN(CORE_NAMESPACE)
  template<typename T=std::function<void()> >
  class TaskDelegate : public virtual ITask{
    T & _callback;
  public:
    TaskDelegate(T & callback):_callback(callback){}
    void run(){_callback();}
  };

  template<>
  class TaskDelegate<std::function<void()> >{
    std::function<void()> _callback;
  public:
    TaskDelegate(std::function<void()> callback):_callback(callback){}
    void run(){_callback();}
  };
NS_END(CORE_NAMESPACE)
