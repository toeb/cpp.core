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
#include <core/patterns/Singleton.h>
NS_BEGIN(CORE_NAMESPACE)

  /**
  * \brief Unit test runner.
  *
  */
  class UnitTestRunner : public StatefulTask, public ProgressReporter {
    //reflect_type(NS(CORE_NAMESPACE)::UnitTestRunner);
    //reflect_superclasses(StatefulTask,ProgressReporter)
    
    /**
    * \brief currently this runner is only available as a singleton
    *
    */
    SINGLETON(UnitTestRunner) : _FailedTestCount(0){
      setName("UnitTestRunner");
    }

    /**
    * \brief Contains all tests
    */
    typedef Set<UnitTest*> basic_property(RegisteredTests);
    REFERENCE_PROPERTY(Set<UnitTest*>, RegisteredTests)

    /**
    * \brief Number of Tests which failed during run.
    *
    */
    typedef int basic_property(FailedTestCount)


  public:
    Set<UnitTest*> Tests(const std::string & name);
    UnitTest* Test(const unsigned int index);
    static int runCommandLine(int argc=0, const char* const * argv=0);
    void toString(std::ostream & out) const;
  protected:
    bool runTaskReturnSuccess();
  };
NS_END(CORE_NAMESPACE)
