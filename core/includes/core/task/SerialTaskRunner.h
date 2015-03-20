#pragma once
#include <core/core.h>
#include <core/task/ITask.h>
#include <core/task/TaskRunnerBase.h>
#include <queue>
NS_BEGIN(CORE_NAMESPACE)
  class SerialTaskRunner : public virtual TaskRunnerBase{
    //reflect_type(NS(CORE_NAMESPACE)::SerialTaskRunner);
    //reflect_superclasses(TaskRunnerBase)
  private:
    std::queue<ITask*> _taskqueue;
  public:
    SerialTaskRunner(){setName("SerialTaskRunner");}
    virtual bool hasTasks(){
      return _taskqueue.size()!=0;
    }
    virtual ITask * nextTask(){
      if(!hasTasks())return 0;
      ITask * task = _taskqueue.front();
      _taskqueue.pop();
      return task;
    }
    virtual bool accept(ITask * task){
      _taskqueue.push(task);
      return true;
    }
  };
NS_END(CORE_NAMESPACE)
