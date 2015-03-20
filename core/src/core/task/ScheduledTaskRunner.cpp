#include <core/task/ScheduledTaskRunner.h>


NS_USE(CORE_NAMESPACE);

ScheduledTaskRunner::ScheduledTaskRunner(){
  setName("ScheduledTaskRunner");
}

ITask * ScheduledTaskRunner::nextTask(){
  auto task = _taskqueue.top();
  _taskqueue.pop();
  return task;
}
void ScheduledTaskRunner::onBeforeTaskRun(ITask * task){
}
void ScheduledTaskRunner::onAfterTaskRun(ITask * task){
  auto scheduledTask = dynamic_cast<ScheduledTask*>(task);
  if(!scheduledTask)return;
  if(scheduledTask->getIsOneTimeTask())return;
  scheduledTask->calculateNextTimeout(currentTime());
  _taskqueue.push(scheduledTask);
}
bool ScheduledTaskRunner::accept(ITask * task){
  auto scheduledTask = dynamic_cast<ScheduledTask*>(task);
  if(!scheduledTask)return false;
  scheduledTask->calculateNextTimeout(currentTime());
  _taskqueue.push(scheduledTask);
  return true;
}
bool ScheduledTaskRunner::hasTasks(){
  if(!_taskqueue.size())return false;
  ScheduledTask * front = _taskqueue.top();
  if(front->nextExecutionTime() <= currentTime())return true;
  return false;
}
Time ScheduledTaskRunner::currentTime()const{
  return systemTime();
}