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

#include <core/reflection/callable/Callable.h>
#include <core/reflection/type/TypeInfo.h>

NS_BEGIN(CORE_NAMESPACE)
  class Action : public Callable{
    //reflect_type_declaration(NS(CORE_NAMESPACE)::Action);
  public:
    Argument callImplementation(const ArgumentList & args)override final;
    virtual bool isValid()const override{return true;}
    void execute();
  protected:
    virtual void executeAction()=0;
  };
NS_END(CORE_NAMESPACE)
