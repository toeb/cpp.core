#include <core/task/ExtendedTask.h>

#include <core/NamedObject.h>
NS_USE(CORE_NAMESPACE);
ExtendedTask::ExtendedTask():_RunCount(0),_RunTime(0),_IsRunning(false){
}
void ExtendedTask::onBeforeRun(){
  setIsRunning(true);
  setLastStartTime(systemTime());
}
void ExtendedTask::onAfterRun(){
  setRunTime(systemTime()-getLastStartTime());
  setRunCount(getRunCount()+1);
  setIsRunning(false);
}

void ExtendedTask:: toString(std::ostream & o)const{
  auto named = dynamic_cast<const NamedObject*>(this);
  o << "<task ";
  if(named)  o << " name=\"" << named->name()  << "\"";
  else  o << "" ;
  o <<" runcount = "<<getRunCount()<< " runtime = "<<getRunTime()<<" />";
}