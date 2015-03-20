#include <core.serialization.h>
#include <core.dynamic.h>
#include <core/serialization/json_serializers.h>
#include <iomanip>
#include <limits>
NS_USE(CORE_NAMESPACE)::dynamic;




NS_BEGIN(CORE_SERIALIZATION_NAMESPACE)

composite_serializer & json_serializer(){
  static composite_serializer serializer;
  return serializer;
}




std::string json(::NS(CORE_NAMESPACE)::any value){
  static bool initialized = [](){
    json_serializer().add_formatter<int, JsonFormat>();
    json_serializer().add_formatter<double, JsonFormat>();
    json_serializer().add_formatter<bool, JsonFormat>();
    json_serializer().add_formatter<std::string, JsonFormat>();
    json_serializer().add_formatter<const char *, JsonFormat>();
    json_serializer().add_formatter<std::nullptr_t, JsonFormat>();
    json_serializer().add_formatter< ::NS(CORE_NAMESPACE)::dynamic::DynamicObject, JsonFormat>();
    json_serializer().add_formatter<std::vector<int>, JsonFormat>();
    json_serializer().add_formatter<std::vector<any>, JsonFormat>();
    
    return true;
  }();
  std::stringstream ss;
  serialization_context context(ss, json_serializer());
  json_serializer().serialize(context, value);
  return ss.str();
}
std::string json(DynamicObject obj){
  return json(any::explicit_any(obj));
}


custom_serializer_definition(JsonFormat, bool){
  
  context.stream << (value ? "true" : "false");
}
custom_serializer_definition(JsonFormat, int){
  context.stream << value;
}
custom_serializer_definition(JsonFormat, double){
  context.stream << std::setprecision(std::numeric_limits<double>::digits10) << value;
}

custom_serializer_definition(JsonFormat, std::vector<any>){
  context.stream << '[';
  bool first = true;
  for (auto val : value){
    if (first) first = false;
    else context.stream << ',';
    context.stream << context.serializer.serialize(val);
  }
  context.stream << ']';
}
custom_serializer_definition(JsonFormat, std::nullptr_t){
  context.stream << "null";
}
custom_serializer_definition(JsonFormat, const char *){
  int i = 0;
  char c;
  context.stream << "\"";
  while ((c = value[i++])){
    switch (c){
    case '"':
      context.stream << "\\\"";
      break;
    case '\\':
      context.stream << "\\\\";
      break;
    case '/':
      context.stream << "\\/";
      break;
    case '\b':
      context.stream << "\\b";
      break;
    case '\f':
      context.stream << "\\f";
      break;
    case '\n':
      context.stream << "\\n";
      break;
    case '\r':
      context.stream << "\\r";
      break;
    case '\t':
      context.stream << "\\t";
      break;
    default:
      context.stream << c;
      break;
    }
  }
  context.stream << "\"";
}
custom_serializer_definition(JsonFormat, std::string){
  typed_serializer<const char *, JsonFormat>::serialize(context, value.c_str());
}


custom_serializer_definition(JsonFormat, DynamicObject){

  auto members = value.members();
  if (!members.size()){
    any val = value;
    context.serializer.serialize(context, val);
  }
  context.stream << "{";
  auto first = true;
  for (auto member : members){
    if (first)first = false;
    else  context.stream << ",";
    typed_serializer<std::string, JsonFormat>::serialize(context, member);
    context.stream << ":";
    any val = value[member].to_any();
    context.serializer.serialize(context, val);
  }
  context.stream << "}";
}

NS_END(CORE_SERIALIZATION_NAMESPACE)
