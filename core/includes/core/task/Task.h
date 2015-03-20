#pragma once
#include <core/core.h>



#include <core/task/ITask.h>
NS_BEGIN(CORE_NAMESPACE)
  class Task : public virtual ITask{
//    reflect_type(NS(CORE_NAMESPACE)::Task);
    extensible_property_class;
  protected:
    virtual void onBeforeRun();
    virtual void onAfterRun();
    virtual bool canRunTask();
  public:
    void run();
    virtual void runTask()=0;
  };
NS_END(CORE_NAMESPACE)

