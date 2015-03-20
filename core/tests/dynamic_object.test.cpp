#include <core.testing.h>
#include <core.dynamic.h>
#include <core/template/func_info.h>
#include <core.reflection.h>
#include <core/reflection/builder/builders.h>
#include <functional>
#include <regex>
NS_USE(CORE_NAMESPACE);
NS_USE(CORE_NAMESPACE)::dynamic;

DynamicObject expando(){
  return DynamicObject();
}

class MyType{
  int _accu;
public:
  int accu()const{ return _accu; }

  int add(int i){return  _accu = i + _accu; }
  int sub(int i){return  _accu =  _accu - i; }
  int mul(int i){ return _accu = i * _accu; }
  int div(int i){ return _accu = _accu / i; }
  void ce(){ _accu = 0; }
};



UNITTEST(Sample){
  DynamicObject obj = expando();
  obj["property1"] = 3;
  obj["property2"] = 4;
  obj["func1"] = [](int i, int j){return i + j; };
  obj["property3"] = expando();
  obj["property3"]["property4"] = obj["func1"](obj["property1"], 3);
  int res = obj["property3"]["property4"];


  DynamicObject obj2 = MyType();
  //obj2["ce"]();
}


UNITTEST(DynamicObjectSetValue){
  auto imp = std::make_shared<DynamicObjectExpandoImplementation>();

  DynamicObject uut(std::static_pointer_cast<IDynamicObjectImplementation>(imp));
  uut.set("myproperty", 3);
  auto val = imp->_members["myproperty"].as<int>();
  ASSERT(val == 3);
}
UNITTEST(DynamicObjectGetValue){
  auto imp = std::make_shared<DynamicObjectExpandoImplementation>();

  DynamicObject uut(std::static_pointer_cast<IDynamicObjectImplementation>(imp));
  imp->_members["myproperty"] = DynamicObject(4);
  auto val = uut.get("myproperty");
  int cast_val = val;
  ASSERT(cast_val == 4);
}

UNITTEST(DynamicObjectCallValue){
  auto imp = std::make_shared<DynamicObjectExpandoImplementation>();
  DynamicObject uut(std::static_pointer_cast<IDynamicObjectImplementation>(imp));
  imp->_members["myprop"] = DynamicObject([](){return 6; });
  auto val = uut.get("myprop")();
  int cast = val;
  ASSERT(cast == 6);
}

UNITTEST(DynamicObjectGetPropertyIndexer){

  auto imp = std::make_shared<DynamicObjectExpandoImplementation>();
  DynamicObject uut(std::static_pointer_cast<IDynamicObjectImplementation>(imp));
  imp->_members["propi"] = 4;

  DynamicProperty  prop = uut["propi"];
  int val = prop;
  ASSERT(val == 4);
}

UNITTEST(DynamicObjectGetPropertyIndexDirect){

  auto imp = std::make_shared<DynamicObjectExpandoImplementation>();
  DynamicObject uut(std::static_pointer_cast<IDynamicObjectImplementation>(imp));
  imp->_members["propi"] = 4;
  ASSERT(uut["propi"].as<int>() == 4)
}



UNITTEST(DynamicObjectSetpropertyIndexer){

  auto imp = std::make_shared<DynamicObjectExpandoImplementation>();
  DynamicObject uut(std::static_pointer_cast<IDynamicObjectImplementation>(imp));

  uut["myproperty"] = 33;


  auto val = imp->_members["myproperty"].as<int>();
  ASSERT(val == 33);
}

UNITTEST(DynamicObjectCallIndexer){

  auto imp = std::make_shared<DynamicObjectExpandoImplementation>();
  DynamicObject uut(std::static_pointer_cast<IDynamicObjectImplementation>(imp));
  imp->_members["propi"] = [](){return 44; };

  auto res = uut["propi"]().as<int>();
  ASSERT(res == 44);
}

UNITTEST(DynamicObjectConversionToAny){
  DynamicObject uut = 3;
  any a = uut;
  int cast = a;
  ASSERT(cast == 3);
}

UNITTEST(DynamicPropertyConversionToAny){
  DynamicObject uut;
  uut["test"] = 3;
  any res = uut["test"];
  int cast = res;
  ASSERT(cast == 3);
}




UNITTEST(DynamicPropertyConversionToDynamicObject){
  DynamicObject uut;
  uut["asd"] = 1;
  auto prop = uut["asd"];
  auto tn = typeid(decltype(prop)).name();
  DynamicObject res = prop;
  ASSERT(res.as<int>() == 1);
}

UNITTEST(ComplexDynamicObkectExample){
  DynamicObject uut;
  uut["test1"] = 3;
  uut["test2"] = 4;
  uut["add"] = [](int i, int j, int k){return i + k + j; };
  //    auto res = uut["add"](uut["test1"], uut["test2"]);
  auto res = uut["add"](uut["test1"], uut["test2"], 5);
  int cast = res;
  ASSERT(cast == 12);
}

UNITTEST(DynamicObjectInvoke){
  DynamicObject uut = [](){return 4; };
  auto res = uut();
  ASSERT(res.as<int>() == 4);
}

UNITTEST(RecursivePropertyAccess){
  DynamicObject uut;
  uut["a"]["b"]["c"] = 3;
  auto res = uut["a"]["b"]["c"];
  auto cast = res.as<int>();
  ASSERT(cast == 3);
}



UNITTEST(DynamicPropertyAssignment){
  DynamicObject uut;
  uut["3"] = 3;
  uut["2+1"] = uut["3"];
  ASSERT(uut["2+1"].as<int>() == 3);
}

UNITTEST(DynamicObjectReferenceDObjectAssign){
  /// checks to see if asigning a nested object correclty acts like a reference and not like a value type
  DynamicObject uut;
  uut["a"]["b"] = 3;
  uut["c"] = uut["a"];
  auto a = uut["c"]["b"].as<int>();
  ASSERT(a == 3);
  auto b = uut["a"]["b"].as<int>();
  ASSERT(b == 3);

  uut["c"]["b"] = 4;
  a = uut["a"]["b"].as<int>();
  ASSERT(a == 4);
}

template<typename T>
struct Ttest{

};

//NS_BEGIN(CORE_NAMESPACE)
//  //bool _Forced,
//  //class _Ret,
//  //class _Fun,
//  //  class... _Types
//  template<class TFunc, class TRet, bool b, class... TArgs>
//  struct is_callable<std::_Bind<b, TRet, TFunc, TArgs...>> :public std::true_type{
//    is_callable(){
//    }

//  };

//  template<class TFunc, class TRet, bool b, class... TArgs>
//  struct func_traits < std::_Bind<b, TRet, TFunc, TArgs...> > : public _func_traits<TRet(*)(TArgs...)>
//  {

//    typedef std::_Bind<b, TRet, TFunc, TArgs...> function_type;
//    typedef std::_Bind<b, TRet, TFunc, TArgs...> class_type;
//  };

//NS_END(CORE_NAMESPACE)
//


//UNITTEST(CallStdBoundFuntion){
//  using namespace std::placeholders;
//  auto fu = [](int i, int j){return i + j; };


//  //auto val = is_callable<decltype(std::bind(fu, 1, _1))>::value;
//  // this does nmot work since there is no iscallable traits available that detected multiple overloads for operator()
//  auto bound = std::bind(fu, 1, _1);
//auto val=   is_callable<decltype(bound)>().value;
//auto asta = is_callable<func_traits<decltype(bound)>::return_type>::value;

// // any uut;
// //uut= bound;
//  //auto res = uut(5);
//  // should be 6
//  //ASSERT
//}
UNITTEST(ReflectedDynamicObjectGetType){
  DynamicObject obj = 3;
  auto type = obj.getType();
  ASSERT(type == type_provider::typeOf<int>());
}
UNITTEST(ReflectedDynamicObjectIsConvertibleTo){
  DynamicObject uut = 3;
  auto result = uut.isConvertibleTo<int>();
  ASSERT(result);
// todo : is_assignable....
  ASSERT(!uut.isConvertibleTo<double>());
}
UNITTEST(ReflectedObjectShouldAllowBeStreamable){
  DynamicObject uut = 4;
  ASSERT("4" == uut.toString());
}

UNITTEST(anySHouldAllowToStringIfPossible){
  any uut = 3;
  std::stringstream ss;
  ss << uut;
  ASSERT(ss.str() == "3");
}

template<typename TContainer>
bool contains(const TContainer  & container,const typename TContainer::value_type & value){
  return std::find(std::begin(container), std::end(container), value)!=std::end(container);
}

UNITTEST(MemberListShouldOnlyContainObjectsFromCurrentLevel){
  DynamicObject uut;
  auto dp = uut["a"];
  dp["b"] = 1;


  auto memberList = uut.members();
  ASSERT(memberList.size() == 1);
  auto result = contains(memberList, "a");
  
  //contains(memberList, "a");

}