
#include <core/reflection/value/IReadableValue.h>
//#include "IReadableValue.h"
#include <core/reflection/type/TypeInfo.h>
//#include <core.reflection.builder.h>
NS_USE(CORE_NAMESPACE);

//reflect_type_default_definition(NS(CORE_NAMESPACE)::IReadableValue);



IReadableValue::IReadableValue():_ValueType(0){}


IReadableValue::IReadableValue(const Type * valueType):_ValueType(valueType){}

Argument IReadableValue::get()const {
  return retrieveValue();
}

