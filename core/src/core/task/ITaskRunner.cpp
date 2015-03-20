//#include "ITaskRunner.h"
#include <core/task/ITaskRunner.h>

NS_USE(CORE_NAMESPACE);
ITaskRunner::ITaskRunner():_NumberOfTasks(0){setLoggingLevel(2);}
bool  ITaskRunner::addTask(ITask * task){
  if(!task){
    debugWarning("Attempt was made to add null task to taskrunner");
    return false;
  }
  if(task==this){
    logWarning("Attempt was made to add this task runner as its own subtask");
    return false;
  }
  debugInfo("Adding task '"<<*task<<"' to task runner");
  task->setTaskRunner(this);
  if(!task->getNumberOfTimes())setNumberOfTasks(getNumberOfTasks()+1);
  task->setNumberOfTimes(task->getNumberOfTimes()+1);

  bool result = doAddTask(task);
  if(!result){
    task->setTaskRunner(0);
    std::string name = NS(CORE_NAMESPACE)::name(task);
    debugInfo("Failed to add task '"<<*task<<"' to task runner");
  }else{
    setNumberOfTasks(getNumberOfTasks()+1);
    task->setTaskRunner(this);
    debugInfo("Successfull added task '"<<*task<<"' to task runner");
  }
  return result;
}
bool  ITaskRunner::removeTask(ITask * task){
  if(!task){
    debugWarning("Attempt was made to remove null task from taskrunner");
    return false;
  }
  if(task->getTaskRunner()!=this){
    debugWarning("Attempt was made to remove extraneous task from taskrunner: "<<*task);
    return false;
  }
  bool result =doRemoveTask(task);
  if(!result){
    debugInfo("failed to remove "<<*task);
  }else{
    debugInfo("Successfully removed "<<*task );
    setNumberOfTasks(getNumberOfTasks()-1);
    if(!task->getNumberOfTimes())setNumberOfTasks(getNumberOfTasks()-1);
    if(!task->getNumberOfTimes())task->setTaskRunner(0);
  }
  return result;
}