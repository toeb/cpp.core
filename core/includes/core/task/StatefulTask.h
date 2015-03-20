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

#include <core.property.h>
#include <core.logging.h>
#include <core/task/ExtendedTask.h>
#include <core/NamedObject.h>
NS_BEGIN(CORE_NAMESPACE)
  class StatefulTask : public virtual ExtendedTask{
  //  reflect_type(NS(CORE_NAMESPACE)::StatefulTask);
    //reflect_superclasses(ExtendedTask,Log);
    extensible_property_class;
  protected:
    // method to override
    virtual bool runTaskReturnSuccess()=0;
  public:
    enum State {
      Unknown,
      Running,
      Succeeded,
      Failed
    };
    static std::string stateToString(const State & state);
    typedef State extensible_property(State);
    auto before_set(State);

    void Reset();
    void Run();

  public:
    virtual void clearResult();

    bool runStatefulTask();

    StatefulTask();
  private:
    // overridden from extended task
    void runTask();
  };

NS_END(CORE_NAMESPACE)

