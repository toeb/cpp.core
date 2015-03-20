#pragma once
#include <core/core.h>

#include <core/Object.h>
#include <core.logging.h>
#include <core/task/ITask.h>
NS_BEGIN(CORE_NAMESPACE)
  /**
  * ITaskRunner is the base class for task runners.  It allows tasks to be added and removed
  */
  class ITaskRunner : public virtual ITask, public virtual Log{
    //reflect_type(NS(CORE_NAMESPACE)::ITaskRunner);
    extensible_property_class;
    typedef unsigned int extensible_property(NumberOfTasks);
  public:
    ITaskRunner();
    bool addTask(ITask * task);
    bool removeTask(ITask * task);
  protected:
    // subclasses may implement doRemoveTask
    virtual bool doRemoveTask(ITask*){return true;};
    // subclass must implement
    virtual bool doAddTask(ITask*)=0;
  };
NS_END(CORE_NAMESPACE)
