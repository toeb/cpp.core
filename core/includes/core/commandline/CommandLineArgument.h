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

#include <core/commandline/CommandLineArgumentDefinition.h>
NS_BEGIN(CORE_NAMESPACE)
  namespace commandline {
    class CommandLineArgument {
    private:
      CommandLineArgumentDefinition & _ArgumentDefinition;
      REFERENCES(public, CommandLineArgumentDefinition,ArgumentDefinition);
      std::vector<std::string> _Tokens;
      REFERENCES(public, std::vector<std::string>,Tokens);

    public:
      CommandLineArgument(CommandLineArgumentDefinition & definition) ;

      template<typename T> std::unique_ptr<T> token(size_t i=0) const;



    };
  }
NS_END(CORE_NAMESPACE)



//template implementation
#include <core/utility/StringTools.h>

NS_BEGIN(CORE_NAMESPACE)
  namespace commandline {
    //implementation
    template<typename T>
    std::unique_ptr<T> CommandLineArgument::token(size_t i) const {
      if(_Tokens.size()<=i) return std::unique_ptr<T>();
      T result;
      if(!NS(CORE_NAMESPACE)::parse(result,_Tokens[i])) return std::unique_ptr<T>();
      return std::unique_ptr<T>(new T(result));
    }
  }
NS_END(CORE_NAMESPACE)
