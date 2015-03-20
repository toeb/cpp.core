/**
* Copyright (C) 2013 Tobias P. Becker
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without restriction,
* including without limitation the  rights to use, copy, modify, merge, publish, distribute,
* sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* More information at: https://dslib.assembla.com/
*
*/
#pragma once
#include <core/core.h>

#include <core/testing/UnitTest.h>

NS_BEGIN(CORE_NAMESPACE)

  class PerformanceTest : public UnitTest {
//    reflect_type(NS(CORE_NAMESPACE)::PerformanceTest);
    extensible_property_class;
    typedef size_t extensible_property(PlannedRepititions);
    typedef size_t extensible_property(ExecutedRepititions);
    typedef size_t extensible_property(PrimerCount);
    typedef Time   extensible_property(ExecuteFor);
    typedef size_t extensible_propertyreflect_property(MaximumRepititions);
    
  protected:
    PerformanceTest(const std::string  &name);
    virtual void runTest();
  public:
    void test();
    void toString(std::ostream & out)const;
  };

  template<typename Derived>
  class TypedPerformanceTest :
    public PerformanceTest ,
    public Derivable<Derived>{
  public:
    TypedPerformanceTest(derived_ptr self, const std::string  &name) :
      PerformanceTest(name), Derivable<Derived>(self){}

    void runTest() override final{

      primeTest();
      planTest();
      iterateTests();
    }

  private:
    void primeTest(){
      // run once for any static initialization
      this->derived()->runPerformanceTest();

      // prime performance test.
      tick();
      for(size_t i=0; i < getPrimerCount();++i){
        this->derived()->runPerformanceTest();
      }
      tock();

    }
    void planTest(){
      setPlannedRepititions(1);
      if(getExecuteFor()!=0){
        // calculate the number of repetitions needed to run for <executeFor> seconds
        auto timePerRepetition = getAccumulatedTime()/getPrimerCount();
        if(timePerRepetition!=0.0){
          auto repeats = (size_t)(getExecuteFor()/timePerRepetition);
          setPlannedRepititions(repeats);
        }
      }
      if(getPlannedRepititions()>getMaximumRepititions()){
        setPlannedRepititions(getMaximumRepititions());
      }

      resetTimer();
    }
    void iterateTests(){
      size_t i;
      for(i=0; i < getPlannedRepititions(); ++i) {
        tick();
        this->derived()->runPerformanceTest();
        tock();
        if(getAccumulatedTime()>getExecuteFor()*2){
          logWarning("Test '"<< getTestName()<<"' is taking twice as long as anticipated.  Aborting after "<<i<<"/"<< getPlannedRepititions()<<" iterations");
          break;
        }
      }
      setExecutedRepititions(i);

    }

  };
NS_END(CORE_NAMESPACE)

