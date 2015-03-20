#include <core/logging/Log.h>

NS_USE(CORE_NAMESPACE);

void Log::itemAdded(LogEntry*,LogEntries){
  std::ostream * out=0;
  switch(item->getLogLevel()){
  case 1:
    out = getLogErrorStream();
    break;
  case 2:
    out = getLogWarningStream();
    break;
  default:
    out = getLogInfoStream();
    break;
  }
  if(!out)return;
  *out << *item << std::endl;
}
void Log::itemRemoved(LogEntry*,LogEntries){

}

Log::Log():
  _LogInfoStream(0),
  _LogWarningStream(0),
  _LogErrorStream(0),
  _LoggingEnabled(true),
  _LoggingLevel(3)
{
  setLogInfoStream(&std::cout);
  setLogErrorStream(&std::cerr);
  setLogWarningStream(&std::cout);
}
LogEntry::LogEntry():_LogLevel(100),_Owner(0){
  setSystemTimeStamp(systemTime());
}
void LogEntry::toString(std::ostream & out)const{
  switch(getLogLevel()){
  case 3:out<< "Info    : ";
    break;
  case 2:out << "Warning : ";
    break;
  case 1:out << "Error   : ";
    break;
  default: out << "Message(lvl "<<getLogLevel()<<"): ";
  }
  out << getSystemTimeStamp()<<"s : ";
  out << getMessage();
  out << " (in "<<getObjectName()<<")";
  //out <<" "<<getFunctionSignature();
}

Log & NS(CORE_NAMESPACE)::getLog(){
  static Log * log=0;
  if(!log){
    log = new Log();
  }
  return *log;
}



void Log::log(
  int level,
  const std::string & message,
  const std::string & functionsignature,
  const std::string & sourcefile,
  int sourcelinenumber){
    auto entry = new LogEntry();
    entry->setLogLevel(level);
    entry->setMessage(message);
    entry->setFunctionSignature(functionsignature);
    entry->setSourceFileName(sourcefile);
    entry->setSourceLineNumber(sourcelinenumber);
    addEntry(entry);
}
void Log::info(
  const std::string & message,
  const std::string & functionsignature,
  const std::string & sourcefile ,
  int sourcelinenumber){
    log(3,message,functionsignature,sourcefile,sourcelinenumber);
}

void Log::warn(
  const std::string & message,
  const std::string & functionsignature,
  const std::string & sourcefile ,
  int sourcelinenumber){
    log(2,message,functionsignature,sourcefile,sourcelinenumber);
}

void Log::error(
  const std::string & message,
  const std::string & functionsignature,
  const std::string & sourcefile,
  int sourcelinenumber){
    log(1,message,functionsignature,sourcefile,sourcelinenumber);
}

void Log::addEntry(LogEntry * entry){
  if(!getLoggingEnabled()){
    delete entry;
    entry = 0;
    return;
  }

  if(getLoggingLevel()<entry->getLogLevel()){
    delete entry;
    entry = 0;
    return;
  }
  entry->setOwner(this);
  /*const Type& td = getType();*/
 // if(entry->getClassName()=="")entry->setClassName(getType()->getName());
  if(entry->getObjectName()=="")entry->setObjectName("log");

  LogEntries()|=entry;
}