#include <core/task/StatefulTask.h>



NS_USE(CORE_NAMESPACE);
using namespace std;

std::string StatefulTask::stateToString(const State & state){
  switch(state){
  case Unknown: return "Unknown";
  case Running: return "Running";
  case Succeeded: return "Succeeded";
  case Failed: return "Failed";
  default: return "";
  }
}

auto StatefulTask::before_set(State){
  logMessage("StatefulTask state Changed from: "<<stateToString(getState()) <<" to " << stateToString(*newvalue),5);
  return BeforeSetAction::Accept;
}
void StatefulTask::Reset(){
  logMessage("resetting task",5);
  clearResult();
  setState(Unknown);

}
void StatefulTask::Run(){
  runStatefulTask();
}
void StatefulTask::clearResult(){}
void StatefulTask::runTask(){
  logMessage("running task",5)
    if(getState()!=Unknown){
      Reset();
    }
    setState(Running);
    bool result=false;
    try{
      result =  runTaskReturnSuccess();
    }catch(std::exception){
      result = false;
    }

    if(result)
      setState(Succeeded);
    else
      setState(Failed);
    logMessage("finished task",5);
}

bool StatefulTask::runStatefulTask(){
  run();
  return getState()==Succeeded;
}
StatefulTask::StatefulTask():NamedObject("StatefulTask"),_State(Unknown){
}