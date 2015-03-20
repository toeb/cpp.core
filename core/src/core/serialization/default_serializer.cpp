#include <core.serialization.h>

NS_BEGIN(CORE_SERIALIZATION_NAMESPACE)
default_serializer(std::string){
  context.stream << value;
}

template<typename T> custom_template_serializer_declaration(DefaultFormat, T);
template<typename T> custom_serializer_definition(DefaultFormat, T){
  context.stream << value;
}
NS_END(CORE_SERIALIZATION_NAMESPACE)
