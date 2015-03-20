#include <core/testing/PerformanceTest.h>

NS_USE(CORE_NAMESPACE);




  void PerformanceTest::runTest(){}


  void PerformanceTest::test(){}
    void PerformanceTest::toString(std::ostream & out)const{
      auto singleTestLength = getAccumulatedTime()/getExecutedRepititions();
      out << "Performance test '"<< getTestName()<<"' duration: "<< singleTestLength<<"s; "<<getExecutedRepititions()<<" iterations executed in "<< std::fixed<<getAccumulatedTime()<<"s; # of primer iterations: "<<getPrimerCount();
      Results().foreachElement([&](UnitTestResult* result){
        out << std::endl<<"  "<<*result;
      });


    }
PerformanceTest::PerformanceTest(const std::string  &name):
  UnitTest(name),
  _PlannedRepititions(0),
  _ExecutedRepititions(0),
  _ExecuteFor(0.2),
  _PrimerCount(4),
  _MaximumRepititions(std::numeric_limits<size_t>::max())
{}

