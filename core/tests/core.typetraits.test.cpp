#include <core.testing.h>
#include <core/template/has_member_function_trait.h>


has_member_function_trait(lol);


UNITTEST(has_member_function_trait_test){
  struct asd{
    int lol(){}
  };
  struct asd2{};
  auto r1 = has_lol_method<asd>::value;
  auto r2 = has_lol_method<asd2>::value;
  ASSERT(r1);
  ASSERT(!r2);

}

