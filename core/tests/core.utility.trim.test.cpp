#include <core.h>

NS_BEGIN(CORE_NAMESPACE)
  TEST(1, trimFront){
    using namespace stringtools;
    CHECK("1234   " == trimFront("   1234   "));

  }
  TEST(2, trimFront){
    using namespace stringtools;
    CHECK("1234   " == trimFront("1234   "));

  }
  TEST(3, trimFront){
    using namespace stringtools;
    CHECK("1234" == trimFront("1234"));

  }

  TEST(1, trimBack){
    using namespace stringtools;
    CHECK("   1234" == trimBack("   1234   "));

  }
  TEST(2, trimBack){
    using namespace stringtools;
    CHECK("   1234" == trimBack("   1234"));

  }
  TEST(3, trimBack){
    using namespace stringtools;
    CHECK("1234" == trimBack("1234"));

  }

  TEST(4, trimFront){
    using namespace stringtools;
    CHECK("" == trimFront(""));

  }

  TEST(4, trimBack){
    using namespace stringtools;
    CHECK("" == trimBack(""));

  }


  TEST(5, trimFront){
    using namespace stringtools;
    CHECK("" == trimFront("  "));

  }

  TEST(5, trimBack){
    using namespace stringtools;
    CHECK("" == trimBack("  "));

  }
NS_END(CORE_NAMESPACE)
