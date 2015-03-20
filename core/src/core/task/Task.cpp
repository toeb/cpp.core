#include<core/task/Task.h>

NS_USE(CORE_NAMESPACE);
using namespace std;

void Task::onBeforeRun(){}
void Task::onAfterRun(){}
bool Task::canRunTask(){return true;}
void Task::run(){
  onBeforeRun();
  if(canRunTask())runTask();
  onAfterRun();
}