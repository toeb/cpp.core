#include <core/task/TaskRunnerBase.h>

NS_USE(CORE_NAMESPACE);

TaskRunnerBase::TaskRunnerBase():
  _IsRunning(false),
  _NumberOfRunningTasks(0),
  _IsHalting(false){
    setName("TaskRunnerBase");
}

void TaskRunnerBase::halt(){
  setIsHalting(true);
}
bool TaskRunnerBase::doAddTask(ITask * task){
  bool accepted= accept(task);
  if(accepted){
    onTaskAccepted(task);
    debugMessage("Task Accepted: "<<*task,5);
  }
  else{
    onTaskRejected(task);
  }
  return accepted;
}

bool TaskRunnerBase::doRemoveTask(ITask * task){
  onTaskRemoved(task);
  return true;
}

void TaskRunnerBase::run(){
  debugInfo("run Taskrunner called");
  if(_IsRunning)return;
  setIsHalting(false);
  _IsRunning =true;
  notify_after_set(IsRunning);
  while(!_IsHalting){
    step();
    if(!hasTasks())halt();
  }
  _IsRunning = false;
  notify_after_set(IsRunning);
}
bool TaskRunnerBase::step(){
  if(!canStep()){
    debugWarning("Cannot perform step --> canstep() returned false");
    return false;
  }
  // todo lock taskqueue
  if(!hasTasks()){
    debugMessage("Cannot perform step --> no tasks available",5);
    return false;
  }
  ITask * task = nextTask();
  if(!task){
    debugWarning("Cannot perform step --> task was not available anymore");
    return false;
  }
  _NumberOfRunningTasks++;
  
  notify_after_set(NumberOfRunningTasks);

  onBeforeTaskRun(task);
  debugMessage("Task Starting: "<<*task,6);

  task->run();

  debugMessage("Task Ended: "<<*task,6);
  onAfterTaskRun(task);

  removeTask(task);

  _NumberOfRunningTasks--;
  notify_after_set(NumberOfRunningTasks);
  return true;
}