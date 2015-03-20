#pragma once
#include <core/core.h>
#include <core.reflection.h>
#include <core/PropertyChangingObject.h>
NS_BEGIN(CORE_NAMESPACE)
  class CompilerInfo: public PropertyChangingObject{
    //reflect_type(NS(CORE_NAMESPACE)::CompilerInfo);

    typedef std::string basic_property(CompilationDate);
    typedef std::string basic_property(CompilationTime);
    typedef std::string basic_property(TimeStamp);
  public:
    CompilerInfo(){}
    CompilerInfo(const std::string compileTime, const std::string &compileDate,const std::string & timestamp)
      :_CompilationDate(compileDate),_CompilationTime(compileTime),_TimeStamp(timestamp){}
  };

#define DS_COMPILER_INFO() NS(CORE_NAMESPACE)::CompilerInfo(__TIME__,__DATE__,__TIMESTAMP__)
#ifndef COMPILER_INFO
#define COMPILER_INFO DS_COMPILER_INFO()
#endif

  class SourceInfo : public PropertyChangingObject{
    //reflect_type(NS(CORE_NAMESPACE)::SourceInfo);
  public:
    SourceInfo(const std::string & file, int line, const std::string & func):_File(file),_Line(line),_Function(func){}
    void toString(std::ostream & out)const{
      out <<"Source: Line: "<< getLine()<< " File: "<<getFile()<<" Function: "<<getFunction();
    }
    typedef std::string basic_property(File);
    typedef int         basic_property(Line);
    typedef std::string basic_property(Function);

  };

#define DS_SOURCE_INFO() NS(CORE_NAMESPACE)::SourceInfo(__FILE__,__LINE__,__FUNCSIG__)
#define DS_SOURCE_INFO_PTR() new DS_SOURCE_INFO()

#ifndef SOURCE_INFO
#define SOURCE_INFO DS_SOURCE_INFO()
#endif
NS_END(CORE_NAMESPACE)
