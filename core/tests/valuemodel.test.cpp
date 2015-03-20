#include <core.testing.h>
#include <core.values.h>


using namespace std;


NS_USE(CORE_NAMESPACE);
NS_USE(CORE_VALUES_NAMESPACE);
NS_USE(CORE_EVENTS_NAMESPACE);




UNITTEST(Property_should_fire_correct_events){
  using namespace core::values;
  using namespace core::events;

  Property uut("myprop");

  std::vector<std::string> res;
  auto e1 = uut.OnBeforeConsumed() += [&res](core::any arg){
    res.push_back("bc");
  };
  auto e2 = uut.OnAfterConsumed() += [&res](core::any arg){
    res.push_back("ac");
  };
  auto e3 = uut.OnBeforeProduced() += [&res](core::any arg){
    res.push_back("bp");
  };
  auto e4 = uut.OnAfterProduced() += [&res](core::any arg){
    res.push_back("ap");
  };
  auto e5 = uut.OnValueChanged() += [&res](core::any arg){
    res.push_back("vc");
  };

  uut.consume(3);
  uut.produce();

  ASSERT(core::contains_partial_order_arguments(res, "bc", "vc", "ac", "bp", "ap"));
}


UNITTEST(GetSetAccessor){
  auto i = 1;
  
  auto accessor = make_accessor([&](){return i; }, [&i](int val){i = val; });

  ASSERT(i == 1);
  accessor = 3;
  ASSERT(i = 3);


}
UNITTEST(accessor){
  
  struct my{
    std::vector<int> _vals;

    accessor<int> operator()(int i){
      return accessor<int>(_vals[i]);
    }
  };

  my m;
  m._vals.push_back(2);
  m._vals.push_back(23);
  m._vals.push_back(24);
  m(1) = 2;

}


UNITTEST(SimpleValueTest){
  auto prop = make_property("myprop", 3);
  
  auto res = prop->as<int>();
  ASSERT(res == 3);
}


UNITTEST(DelegateValueTest){
  int getCount = 0;
  int setCount = 0;
  int value = 3;
  DelegateValue val(std::function<int()>([&]()->int{getCount++; return value; }), std::function<void(int)>([&](int val)->void{setCount++; value = val; }));

  int res = val.produce();
  ASSERT(res == 3);

  val.consume(5);
  ASSERT(value == 5);
}

UNITTEST(DelegateValueShouldAllowListening){
  int getCount = 0;
  int setCount = 0;
  int value = 3;
  DelegateValue val(std::function<int()>([&]()->int{getCount++; return value; }), std::function<void(int)>([&](int val)->void{setCount++; value = val; }));

  stringstream ss;

  auto handler1 = val.OnAfterProduced() += [&](EventArgs args){

    ss << "afterproduced" << args.arg().as<int>();
  };

  auto handler2 = val.OnBeforeProduced() += [&](EventArgs args){
    ss << "beforeproduced";
  };


  auto handler3 = val.OnBeforeConsumed() += [&](EventArgs args){
    ss << "beforeconsumed" << args.arg().as<int>();

  };
  auto handler5 = val.OnAfterConsumed() += [&](EventArgs args){
    ss << "afterconsumed" << args.arg().as<int>();

  };

  val.consume(4);
  int v = val.produce();
  ASSERT(v == 4);
  ASSERT(ss.str() == std::string("beforeconsumed4afterconsumed4beforeproducedafterproduced4"))

}


UNITTEST(PropertyTest){
  Property prop("myprop");
  int theValue = 0;
  prop = 3;
  prop.OnValueChanged() += [&](EventArgs args){theValue = args.arg(); };

  int i = prop.produce();

  ASSERT(i == 3);
}




// tests a manual one way connection between to value
UNITTEST(SourceToSinkConnection1){

  auto a = make_property("a", 3);
  auto b = make_property("b", 4);

  auto conn = connect(a, b);

  conn->sync();

  int res = b->produce();

  ASSERT(res == 3);
}

