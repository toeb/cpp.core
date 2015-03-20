//#include "ScheduledTask.h"
#include <core/task/ScheduledTask.h>

NS_USE(CORE_NAMESPACE);

bool ScheduledTask::CompareTaskPriority::operator ()(const ScheduledTask * a,const ScheduledTask * b){
  return a->_nextExecutionTime > b->_nextExecutionTime;
};

Time ScheduledTask::nextExecutionTime()const{
  return _nextExecutionTime;
}

void ScheduledTask::calculateNextTimeout(Time time){
  _lastTimeoutTime = time;
  _nextExecutionTime = time +_Interval;
}
void ScheduledTask::run(){
  Time now = systemTime();
  timeout(now - _lastTimeoutTime,now);
}

void ScheduledTask::timeout(Time dt, Time t){}

ScheduledTask::ScheduledTask() :_Interval(0.0), _IsOneTimeTask(true), _lastTimeoutTime(std::numeric_limits<double>::max()), _nextExecutionTime(std::numeric_limits<double>::max()){
  setName("ScheduledTask");
}

bool ScheduledTask::comp(const ScheduledTask * a, const ScheduledTask * b){
  return a->nextExecutionTime() < b->nextExecutionTime();
}