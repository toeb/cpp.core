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
#include <core.utility.h>
NS_BEGIN(CORE_NAMESPACE)

  /**
   * \brief Unit test result. a test may have many result this mainly contains the message, a flag indicating whether the test was successful and a SourceInfo
   *        object which is useful for identifying where tests failed
   *        @todo add inconclusive state
   */
  class UnitTestResult : public Object{
    //reflect_type(NS(CORE_NAMESPACE)::UnitTestResult);
    //reflect_superclasses(Object);

    typedef std::string basic_property(Message);
    typedef bool basic_property(Failed)
    typedef SourceInfo * basic_property(SourceInfo);
public:
    UnitTestResult();
    UnitTestResult(bool failed,const std::string & message, SourceInfo * info);
    void toString(std::ostream & out) const;
  };
NS_END(CORE_NAMESPACE)
