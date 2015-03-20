#pragma once
#include <core/core.h>

#include <core/task/ITaskRunner.h>

NS_BEGIN(CORE_NAMESPACE)
  class TaskRunnerBase : public virtual ITaskRunner,public virtual Log, public virtual NamedObject{
    extensible_property_class;
    //reflect_type(NS(CORE_NAMESPACE)::TaskRunnerBase);
    //reflect_superclasses(ITaskRunner,Log);

    typedef bool extensible_property(IsRunning);
    auto before_set(IsRunning){
      return BeforeSetAction::Cancel;
    }

    typedef unsigned int extensible_property(NumberOfRunningTasks)
    auto before_set(NumberOfRunningTasks){return BeforeSetAction::Cancel;}

    typedef bool extensible_property(IsHalting);
    auto after_set(IsHalting){
      debugInfo("IsHalting is set to"<<getIsHalting());
    }
  public:
    TaskRunnerBase();
    void halt();
    virtual void run();
    // returns true if a task was successfully started
    bool step();
  protected:
    bool doAddTask(ITask * task);
    bool doRemoveTask(ITask * task);
    virtual ITask * nextTask(){return 0;}
    virtual void onBeforeTaskRun(ITask * task){}
    virtual void onAfterTaskRun(ITask * task){}
    virtual bool accept(ITask * task){return false;}
    virtual bool hasTasks(){return false;}
    virtual void onTaskAccepted(ITask * task){}
    virtual void onTaskRejected(ITask * task){}
    virtual void onTaskRemoved(ITask* task){}
    virtual bool canStep(){return !getNumberOfRunningTasks();}
  };
NS_END(CORE_NAMESPACE)

