#include <core.testing.h>
#include <core.dynamic.h>
#include <core.serialization.h>

NS_USE(CORE_SERIALIZATION_NAMESPACE);
NS_USE(CORE_NAMESPACE)::dynamic;
NS_USE(CORE_NAMESPACE);



UNITTEST(JsonSerializeInt32){
  int32_t i = 3;
  auto res = json(3);
  ASSERT(res == "3");
}
UNITTEST(JsonSerializeConstCharPtr){
  ASSERT(json("\"") == "\"\\\"\"");
  {
    auto serialized = json("\\");
    auto is_equal = serialized == "\"\\\\\"";
    ASSERT(is_equal);
  }
  {
    auto serialized = json("/");
    auto is_equal = serialized == "\"\\/\"";
    ASSERT(is_equal);
  }
  {
    auto serialized = json("\b");
      auto is_equal = serialized == "\"\\b\"";
    ASSERT(is_equal);
  }
  {
    auto serialized = json("\f");
    auto is_equal = serialized == "\"\\f\"";
    ASSERT(is_equal);
  }
  {
    auto serialized = json("\n");
    auto is_equal = serialized == "\"\\n\"";
    ASSERT(is_equal);
  }
  {
    auto serialized = json("\r");
    auto is_equal = serialized == "\"\\r\"";
    ASSERT(is_equal);
  }
  {
    auto serialized = json("\t");
    auto is_equal = serialized == "\"\\t\"";
    ASSERT(is_equal);
  }

}
UNITTEST(JsonSerializeDouble){
  auto serialized = json(3.14151);
  auto is_equal = serialized == "3.14151";
  ASSERT(is_equal);
}

UNITTEST(JsonSerializeBoolTrue){
  auto serialized = json(true);
  auto is_equal = serialized == "true";
  ASSERT(is_equal);
}
UNITTEST(JsonSerializeBoolFalse){
  auto serialized = json(false);
  auto is_equal = serialized == "false";
  ASSERT(is_equal);
}
UNITTEST(JsonSerializeNullPtr){
  auto serialized = json(nullptr);
  auto is_equal = serialized == "null";
  ASSERT(is_equal);
}
UNITTEST(JsonSerializeVectorInt){
  auto serialized = json(std::vector < int > {1,2,3,4,5,6});
  auto is_equal = serialized == "[1,2,3,4,5,6]";
  ASSERT(is_equal);
}
UNITTEST(JsonSerializeVectorAny){
  auto serialized = json(std::vector < any > {1,"asd", true, false, nullptr});
  auto is_equal = serialized == "[1,\"asd\",true,false,null]";
  ASSERT(is_equal);
}

UNITTEST(JsonSerializeDynamicObject){
NS_USE(CORE_SERIALIZATION_NAMESPACE);
NS_USE(CORE_NAMESPACE)::dynamic;
NS_USE(CORE_NAMESPACE);
  
  DynamicObject uut;
  uut["prop1"] = 3;
  uut["prop2"] = "hello";
  uut["prop3"]["prop31"] = 4;
  uut["prop3"]["prop32"] = "world";
  uut["prop3"]["prop33"]["prop331"] = true;

  auto serialized = json(uut);
  auto is_equal = serialized == "{\"prop1\":3,\"prop2\":\"hello\",\"prop3\":{\"prop31\":4,\"prop32\":\"world\",\"prop33\":{\"prop331\":true}}}";
  ASSERT(is_equal);
}


