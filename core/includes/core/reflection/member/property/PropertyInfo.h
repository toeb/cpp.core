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

#include <core/reflection/member/MemberInfo.h>
#include <core/reflection/member/method/MethodInfo.h>
NS_BEGIN(CORE_NAMESPACE)
  class PropertyInfo : public MemberInfo{
    typedef const MethodInfo * basic_property(GetMethod);
    typedef const MethodInfo * basic_property(SetMethod);
    typedef const Type * basic_property(PropertyType);
  protected:
    PropertyInfo(const std::string & name, const MethodInfo * getter, const MethodInfo * setter);
  public:
    
    bool isGettable()const;
    bool isSettable()const;

    Argument get(const void * ptr)const;
    Argument get(void * ptr)const;
    void set(void * ptr, Argument argument)const;
    void set(const void * ptr , Argument argument)const;
  };
NS_END(CORE_NAMESPACE)
