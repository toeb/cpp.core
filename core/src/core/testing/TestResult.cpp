#include <core/testing/TestResult.h>

NS_USE(CORE_NAMESPACE);

UnitTestResult::UnitTestResult():_Message("Result was not initialized"),_Failed(true){

}
UnitTestResult::UnitTestResult(bool failed,const std::string & message, SourceInfo * info):_Message(message),_Failed(failed),_SourceInfo(0){
  setSourceInfo(info);
}

void UnitTestResult::toString(std::ostream & out)const{      
  if(getFailed()){
    out << "Failure:  \""<<getMessage()<<"\" ";
  }else{
    out << "Success: \""<<getMessage()<<"\" ";
  }
  if(getSourceInfo()){
    out << "@"<<*getSourceInfo();
  }
}