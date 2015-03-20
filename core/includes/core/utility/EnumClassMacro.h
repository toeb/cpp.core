#pragma once

#include <core.preprocessor.h>

#define DS_ENUMCLASS_TOSTRING_ENTRY(ENTRY) if(value == enum_type::ENTRY){ out << DS_STRINGIFY(ENTRY); return; }
#define DS_ENUMCLASS_FROMSTRING_ENTRY(ENTRY) if(name==DS_STRINGIFY(ENTRY))return enum_type::ENTRY;

#define DS_ENUMCLASS(CLASS_NAME, ...) enum class CLASS_NAME { DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__) };\
  auto inline serialize(std::ostream & out, const CLASS_NAME& value)->void{\
    typedef CLASS_NAME enum_type;\
    DS_FOREACH(DS_ENUMCLASS_TOSTRING_ENTRY,__VA_ARGS__)\
    throw std::exception();\
    }\
    auto inline convertToString(const CLASS_NAME & value)->std::string{ std::stringstream ss; serialize(ss,value); return ss.str(); }\
  auto inline parse##CLASS_NAME(const std::string & name)->CLASS_NAME{\
    typedef CLASS_NAME enum_type;\
    DS_FOREACH(DS_ENUMCLASS_FROMSTRING_ENTRY,__VA_ARGS__)\
    throw std::exception();\
  }
