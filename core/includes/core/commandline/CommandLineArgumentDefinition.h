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
#include <core.reflection.h>

NS_BEGIN(CORE_NAMESPACE)
  namespace commandline {
    class CommandLineArgumentDefinition {

      Set<std::string> _Aliases;
      REFERENCES(public,Set<std::string>,Aliases);
      SIMPLE_PROPERTY(std::string, Description){}
      SIMPLE_PROPERTY(std::string, Name){}

public:
      CommandLineArgumentDefinition();
      CommandLineArgumentDefinition(const std::string & name,const std::string & description="", const std::string & alias="");

      bool isIdentifiedBy(const std::string & name) const;
    };
  }
NS_END(CORE_NAMESPACE)
