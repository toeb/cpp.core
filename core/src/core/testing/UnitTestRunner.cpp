#include <core/testing/UnitTestRunner.h>

#include <core.commandline.h>
NS_USE(CORE_NAMESPACE);

bool UnitTestRunner::runTaskReturnSuccess(){
  setTotalProgress(RegisteredTests().size());
  setFailedTestCount(0);

  RegisteredTests().foreachElement([this](UnitTest* test){
    test->run();
    if(test->getFailedTests()>0) setFailedTestCount(getFailedTestCount()+1);
    incrementProgress(1);
    logMessage("Progress: " << percent()<<" % done",3);
  });      

  return true;
}

void UnitTestRunner::toString(std::ostream & out)const{

  out << "Testrunner executed test count: " <<RegisteredTests().size()<<std::endl;
  RegisteredTests().foreachElement([&](UnitTest* test){
    out << test<<std::endl;
  });
   out << "Summary: " << (RegisteredTests().size()-getFailedTestCount()) << "/"<<RegisteredTests().size() <<" passed ("<<getFailedTestCount()<<" failed)"<<std::endl;
}

Set<UnitTest*> UnitTestRunner::Tests(const std::string & name){
  return RegisteredTests().subset([&](UnitTest* test){return stringtools::startWithIgnoreCase(test->getTestName(), name);});
}
UnitTest* UnitTestRunner::Test(const unsigned int index){
  if(index < RegisteredTests().size())return RegisteredTests().at(index);
  return 0;
}
int UnitTestRunner::runCommandLine(int argc, const char* const* argv){      
NS_USE(CORE_NAMESPACE)::commandline;
  CommandLineParser parser(argc,argv);
  parser.DefineArgument("--test-count","prints the number of tests to std out", "-c");
  parser.DefineArgument("--test-name","--test-name <index> prints the name of test at index to std out", "-n");
  parser.DefineArgument("--run-test","-run-test <index|name|'all'> runs the test at index i or name", "-r" );
  parser.DefineArgument("--verbose", " shows the output", "-v");
  parser.DefineArgument("--list-all", " shows all tests", "-l");
  auto & runner = *instance();
  int logLevel=0;
  auto arg = parser.Argument("--verbose");
  if(arg){
    logLevel = 10;
  }

  runner.setLoggingLevel(logLevel);

  arg = parser.Argument("--test-count");
  if(arg){
    std::cout << runner.RegisteredTests().size();
    return 0;
  }
  arg = parser.Argument("--test-name");
  if(arg){
    auto val = arg->token<unsigned int>();
    if(val){
      auto test = runner.Test(*val);
      if(!test){
        std::cerr << " test not found";
        return 0;
      }

      std::cout << test->getTestName();;

      return 0;
    }else{
      std::cerr << "no index given";

      return 1;
    }
  }

  arg = parser.Argument("--list-all");
  if(arg){
    int i=0;
    runner.RegisteredTests().foreachElement([&i](UnitTest * test){
      std::cout << i<<": "<< test->getTestName()<<std::endl;
      i++;
    });

    return 0;
  }

  arg = parser.Argument("--run-test");
  if(arg){
    Set< UnitTest *> tests;
    auto index = arg->token<unsigned int>();
    /*if(!index){*/
    //  hack:because of bug in parse method that returns true even if string was unparsable...
    if(index&&*index==0&&*arg->token<std::string>()!="0"){

      auto name = arg->token<std::string>();
      if(!name){
        std::cerr << "could not find test";
        return 1;
      }
      tests|=runner.Tests(*name);
    }else{
      tests |= runner.Test(*index);
    }        
    if(tests.empty()){
      std::cerr<< "no test found"<<std::endl;
      return 1;
    }

    int failures =0;

    tests.foreachElement([&](UnitTest* test){
      test->setLoggingLevel(logLevel);
      test->run();
      if(parser.Argument("--verbose")){
        std::cout << *test<<std::endl;
      }
      failures+=test->getFailedTests();
    });

    return failures;
  }

  runner.run();

  arg = parser.Argument("--verbose");
  if(arg){
    std::cout << runner<<std::endl;
  }

  std::cout<<runner;
  return runner.getFailedTestCount();
}