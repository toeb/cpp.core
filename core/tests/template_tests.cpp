#include <core.testing.h>

#include <core/template/tuple_element_or_default.h>

NS_USE(CORE_NAMESPACE);

UNITTEST(tuple_element_or_default_test){
  auto a = std::is_same <
    tuple_element_or_default < 0, std::tuple<int, bool>>::type,
    void > ::value;
  auto b = std::is_same <
    tuple_element_or_default < 4, std::tuple<int, bool>>::type,
    void > ::value;

    ASSERT(!a);
    ASSERT(b)

}