#include <core/task/ProgressReporter.h>


NS_USE(CORE_NAMESPACE);


auto ProgressReporter::after_set(NumberOfNotifications){
  if(getNumberOfNotifications())setNumberOfNotifications(1.0);
}

auto ProgressReporter::after_set(TotalProgress){  
  setNotificationInterval(getTotalProgress()/getNumberOfNotifications());
}



ProgressReporter::ProgressReporter():    
  _NumberOfNotifications(200.0),
  _TotalProgress(1),
  _Progress(0),
  _ProgressLogLevel(4),
  _NotificationInterval(0.01),
  _LogProgress(true){
    resetProgress();

};
double ProgressReporter::percent()const{
  return quotient()*100.0;
}
double ProgressReporter::quotient()const{
  return getProgress()/getTotalProgress();
}


void ProgressReporter::resetProgress(double totalProgress){
  resetProgress();
  setTotalProgress(totalProgress);
}
void ProgressReporter::resetProgress(){
  _lastNotification=0;
  setProgress(0.0);  
}
void ProgressReporter::incrementProgress(double value){
  reportProgress(getProgress()+value);
}
void ProgressReporter::reportProgress(double value){
  _Progress = value;
  if(getProgress()>_lastNotification+getNotificationInterval()){
    _lastNotification=getProgress();
    notify_after_set(Progress);
    if(getLogProgress()){

      logMessage("Progress: "<< percent() << "%",getProgressLogLevel());
    }
  }    
}