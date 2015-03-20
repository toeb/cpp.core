#include <functional>
#include <core.testing.h>


#include <core/any.h>
using namespace std;
NS_USE(CORE_NAMESPACE);

UNITTEST(AnyTest1){
  any a = 3;
  int res = any_cast<int>(a);
  ASSERT(res == 3);
}

UNITTEST(AnyTest2){
  //  any uut = std::function<int(int, int) >([](int a, int b){return a + b; });
  // auto res = any_cast<std::function<int(int, int)>>(uut);
  // auto val = res(1, 3);
  // ASSERT(val == 4);
}

UNITTEST(AnyTest3){
  any uut = std::make_shared<int>(3);
  auto res = *any_cast<std::shared_ptr<int>>(uut);
  ASSERT(res == 3);
}





UNITTEST(AnyCallValue){
  any uut = 3;
  int res = uut().as<int>();
  ASSERT(res == 3);
}
UNITTEST(AnyFunc){
  any uut = function<int(int, int)>([](int i, int k){ return i + k; });
  auto v = is_callable<function<int(int, int)>>::value;
  int res = uut(2, 4).as<int>();
  ASSERT(6 == res);
}
UNITTEST(AnyLambda){
  auto a = [](int i, int j){return i + j; };

  //std::cout << a;
  auto v = is_callable<decltype(a)>::value;
  any uut = a;
  int res = uut(3, 4).as<int>();
  ASSERT(7 == res);
}

int addSmthn(int i, int j){
  return i + j;
}
UNITTEST(AnyCFunc){
  any uut = &addSmthn;
  auto res = uut(4, 5);
  ASSERT(res.as<int>() == 9);
}

UNITTEST(AnyMemberMethod){
  struct test{
    int val;
    test(int val) :val(val){

    }
    int add(int i, int j){
      return i + j + val;

    }
  };
  any uut = &test::add;
  auto res = uut(test(1), 2, 3);
  ASSERT(res.as<int>() == 6);
}

