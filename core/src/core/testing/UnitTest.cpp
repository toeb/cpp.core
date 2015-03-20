#include <core/testing/UnitTest.h>
#include <core/testing/UnitTestRunner.h>
NS_USE(CORE_NAMESPACE);


UnitTest::UnitTest(const std::string & name){
  setTestName(name);
}


void UnitTest::RunTest(){run();}


void UnitTest::itemAdded(UnitTestResult*,Results){if(item->getFailed())setFailedTests(_FailedTests+1);}
void UnitTest::itemRemoved(UnitTestResult*,Results){if(item->getFailed())setFailedTests(_FailedTests-1);}




UnitTest::~UnitTest(){
  for(size_t i=0; i < Results(); i++){
    delete Results().at(i);
  }
  /* removed for backwards compatibility
  for(auto test : Results().elements()){
  delete test;
  }*/
  Results().clear();
}

void UnitTest::reset(){
  if(getIsInitialized())destroy();
  setIsInitialized(false);    
}

void UnitTest::initialize(){}
void UnitTest::destroy(){}

bool UnitTest::runTaskReturnSuccess(){
  reset();
  initialize();
  setIsInitialized(true);
  runTest();
  destroy();



  return true;
}

void UnitTest::toString(std::ostream & out)const{
  out << "Test '"<< getTestName()<<"' executed in "<< std::fixed<<getAccumulatedTime()<<"s (desciption:'"<< getTestDescription()<<"')";
  Results().foreachElement([&](UnitTestResult* result){
    out << std::endl<<"  "<<*result;
  });

}

void UnitTest::runTest(){     
  tick();
  bool finished = false;
  try{
    test();
    finished = true;
  }catch(const std::exception &){
    
  }catch(const std::string &){

  }catch(...){

  }
  if (!finished){
    UnitTestResult res;
    res.setFailed(true);
    res.setMessage("test failed with exception");
    res.setSourceInfo(new SourceInfo("",0,""));
    Results().add(new UnitTestResult(res));
  }
  
  tock();
}



