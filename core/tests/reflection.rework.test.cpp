#include <core.testing.h>
#include <map>
#include <core/any.h>
#include <core/template/type_traits.h>


#include <core.reflection.h>
NS_BEGIN(CORE_REFLECTION2_NAMESPACE)


template<typename TTuple, int ... S>
parameter_list create_parameters(CallableInfo & callableInfo, const sequence<S...> & s){
  return{
    create_parameter<
    typename std::tuple_element<S, TTuple>::type,
    S
    >(callableInfo)    ...
  };
}


template<typename TCallable>
MethodInfo & reflect_m(TCallable callable){
  typedef func_traits<TCallable> traits;
  ScopeInfo & scopeinfo = reflect<typename traits::class_type>();

  return *((MethodInfo*)0);// new MethodInfo();
}



/// implementation of static methods
const ScopeDeclaration & unknown(){
  class UnknownDeclaration : public ScopeDeclaration{
  public:
    UnknownDeclaration(){ initScopeDeclaration(); }
  protected:
    std::string get_id()const{ return "unknown"; }
    std::string get_name()const{ return "unknown"; }
  };
  static UnknownDeclaration _value;
  return _value;
}
NamespaceInfo & global(){
  static NamespaceInfo globalScope = [](){
    NamespaceInfo scope(0, "::");
    return scope;
  }();
  return globalScope;
}
NamespaceInfo & defaultNamespace(){
  static NamespaceInfo globalScope = [](){
    NamespaceInfo scope(0, "[default]");
    return scope;
  }();
  return globalScope;
}
/// ScopeDeclaration

ScopeDeclaration::ScopeDeclaration() : _id(""), _scope(0){}

ScopeDeclaration::ScopeDeclaration(ScopeInfo * parentScope) : _id(""), _scope(parentScope){}

const ScopeDeclaration & ScopeInfo::operator[](const std::string & id)const{
  if (_declarations.find(id) == std::end(_declarations))return unknown();
  return *_declarations.at(id);
}


const ScopeDeclaration & ScopeInfo::operator[](const std::string & id){
  if (_declarations.find(id) == std::end(_declarations))return unknown();
  return *_declarations.at(id);
}

void ScopeDeclaration::initScopeDeclaration(){
  _id = get_id();
  _name = get_name();
}

void ScopeDeclaration::setName(const std::string & name){
  _scope->_declarations.erase(_name);
  _name = name;
  if (name.size())_scope->_declarations[_name] = this;
}

const std::string & ScopeDeclaration::name()const{ return _name; }

void ScopeDeclaration::setScope(ScopeInfo & scope){
  if (_scope) _scope->_declarations.erase(_name);
  _scope = &scope;
  if (_name.size())_scope->_declarations[_name] = this;
}

const ScopeInfo & ScopeDeclaration::scope()const{
  if (!_scope)return defaultNamespace();
  return *_scope;
}
bool operator==(const ScopeDeclaration & lhs, const ScopeDeclaration & rhs){
  return &lhs == &rhs;
}

const std::string & ScopeDeclaration::id()const{ return _id; }

/// ScopeInfo Implementation



// returns the map of all declarations
auto  ScopeInfo::declarations()const->const declaration_map &{ return _declarations; }

bool operator==(const ScopeInfo & lhs, const ScopeInfo & rhs){
  return &lhs == &rhs;
}

ScopeDeclaration & ScopeInfo::resolveDeclaration(ScopeDeclaration & declaration){
  auto & id = declaration.id();
  auto found = _declarations.find(id);
  if (found == std::end(_declarations)){
    onDeclaration(declaration);
    _declarations[id] = &declaration;
    declaration.setScope(*this);
    return declaration;
  }
  else{
    return *(_declarations.at(id));
  }
}

/// template implementation for scopeinfo

template<typename T>
typename std::enable_if<std::is_base_of<ScopeDeclaration, T>::value, T>::type &
ScopeInfo::declare(T & declaration){
  return *dynamic_cast<T*> (&(resolveDeclaration(declaration)));
}

template<typename T, typename... TArgs>
typename std::enable_if<std::is_base_of<ScopeDeclaration, T>::value, T>::type &
ScopeInfo::declare(TArgs... args){
  auto declaration = new T(this, args...);
  auto decl = dynamic_cast<T*>(&(resolveDeclaration(*declaration)));
  if (decl != declaration)delete declaration;
  return *decl;
}

template<typename T>
typename std::enable_if<!std::is_base_of<ScopeDeclaration, T>::value && !std::is_function<T>::value, TypeInfo>::type &
ScopeInfo::declare()
{
  auto & typeInfo = reflect<T>();
  auto decl = dynamic_cast<TypeInfo*>(&(resolveDeclaration(typeInfo)));
  return *decl;
}


/// implementation for NamespaceInfo
NamespaceInfo::NamespaceInfo(ScopeInfo * scope, const std::string & fullName) :_fullName(fullName){
  initScopeDeclaration();
}

void NamespaceInfo::onDeclaration(const ScopeDeclaration & declaration){

}

std::string NamespaceInfo::get_id()const {
  return _fullName;
}

std::string NamespaceInfo::get_name()const {
  return _fullName;
}


bool operator==(const NamespaceInfo & lhs, const NamespaceInfo & rhs){
  auto a = &lhs;
  auto b = &rhs;
  return a == b;
}



/// implementation for TypeInfo
TypeInfo::TypeInfo(){}

void TypeInfo::initTypeInfo(){
  initScopeDeclaration();
  _rtti_hashcode = get_rttiHashCode();
  _rtti_name = get_rttiName();
  _fullName = _rtti_name;
  _rtti_rawName = get_rttiRawName();
}

std::string TypeInfo::get_id()const{ return get_rttiRawName(); }
std::string TypeInfo::get_name()const{ return get_rttiName(); }

auto TypeInfo::hash_code()const->type_id{ return _rtti_hashcode; }
bool TypeInfo::operator==(const TypeInfo & other)const{ return hash_code() == other.hash_code(); }
bool TypeInfo::isFundamental()const{ return get_isFundamental(); }
bool TypeInfo::isConst()const{ return get_isConst(); }
bool TypeInfo::isReference()const{ return get_isReference(); }
bool TypeInfo::isVolatile()const{ return get_isVolatile(); }
bool TypeInfo::isRValueReference()const{ return get_isRValueReference(); }

const TypeInfo & TypeInfo::pure_type()const{ return  get_pure_type(); }
const TypeInfo & TypeInfo::underlying_type()const{ return  get_underlying_type(); }

/// CallableInfo implementation


NS(CORE_NAMESPACE)::any CallableInfo::callImplementation(const argument_list & args)const{ return NS(CORE_NAMESPACE)::any(); };


/// ConstructorInfo

const std::string & ConstructorInfo::memberName()const  { static std::string name("~ctor"); return name; };
bool ConstructorInfo::isStatic()const { return true; };


template<typename ... TArgs> NS(CORE_NAMESPACE)::any ConstructorInfo::make(TArgs&&... args) {
  const argument_list argv{ args... };
  return this->make(argv);
}
template<typename ... TArgs> NS(CORE_NAMESPACE)::any ConstructorInfo::make_new(TArgs&&... args) {
  const argument_list argv{ args... };
  return this->make_new(argv);
}
template<typename ... TArgs> NS(CORE_NAMESPACE)::any ConstructorInfo::make_placement_new(void * place, TArgs&&... args) {
  const argument_list argv{ args... };
  return this->make_placement_new(place, argv);
}


bool ConstructorInfo::operator==(const ConstructorInfo & other)const{
  return definingType() == other.definingType();// && parameters are equal
}



/// TypeTypeInfo implementation and specialization

template<typename T>
class TypedTypeInfo : public TypeInfo{
public:
  TypedTypeInfo(){ initTypeInfo(); }
protected:
  const TypeInfo & get_pure_type()const{ return reflect<typename NS(CORE_NAMESPACE)::type_traits<T>::type>(); }
  const TypeInfo & get_underlying_type()const { return reflect<typename NS(CORE_NAMESPACE)::type_traits<T>::current_type>(); }
  std::string get_rttiName()const{ return typeid(T).name(); }
  std::string get_rttiRawName()const { return  std::string("not implemented"); }//return typeid(T).raw_name(); }
  size_t get_rttiHashCode()const { return typeid(T).hash_code(); }
  bool get_isConst()const{ return NS(CORE_NAMESPACE)::type_traits<T>::is_const; }
  bool get_isReference()const { return NS(CORE_NAMESPACE)::type_traits<T>::is_ref; }
  bool get_isVolatile()const { return NS(CORE_NAMESPACE)::type_traits<T>::is_volatile; }
  bool get_isFundamental()const { return NS(CORE_NAMESPACE)::type_traits<T>::is_fundamental; }
  bool get_isRValueReference()const { return NS(CORE_NAMESPACE)::type_traits<T>::is_rvalue_ref; }
  size_t get_sizeof()const { return 0; }
};


/// specialization for void
template<>
class TypedTypeInfo<void> : public TypeInfo{
public:
  TypedTypeInfo(){ initTypeInfo(); }
protected:
  const TypeInfo & get_pure_type()const{ return reflect<typename NS(CORE_NAMESPACE)::type_traits<void>::type>(); }
  const TypeInfo & get_underlying_type()const { return reflect<typename NS(CORE_NAMESPACE)::type_traits<void>::current_type>(); }
  std::string get_rttiName()const{ return typeid(void).name(); }
  std::string get_rttiRawName()const { return std::string("void"); }//return typeid(void).raw_name(); }
  size_t get_rttiHashCode()const { return typeid(void).hash_code(); }
  bool get_isConst()const{ return false; }
  bool get_isReference()const { return false; }
  bool get_isVolatile()const { return false; }
  bool get_isFundamental()const { return true; }
  bool get_isRValueReference()const { return false; }
  size_t get_sizeof()const { return 0; }
};



//// template implementation
template<typename T> TypeInfo & reflect(){
  static TypedTypeInfo<T> type;
  return type;
  //return *_types[typeid(T).hash_code()];
}

/// TypedParameterInfo
template<typename T, int pIdx>
class TypedParameterInfo : public ParameterInfo{
private:
  CallableInfo & _callableInfo;
public:
  TypedParameterInfo(CallableInfo & callable) :_callableInfo(callable){}

  const CallableInfo & callable()const{ return _callableInfo; }

  virtual const TypeInfo & parameterType()const {
    return reflect<T>();
  };

  virtual const std::string & parameterName()const {
    static std::string parameterName = DS_INLINE_STRING("a" << pIdx);
    return parameterName;
  };


  virtual int parameterIndex()const { return pIdx; };
};

template<typename T>
struct callable_traits{
  const static bool is_callable = false;
  const static bool is_const = false;
  const static bool is_member = false;
  const static bool is_volatile = false;
  typedef std::tuple<> args_tuple;
  const static int arity = 0;
  typedef void return_type;
  typedef void class_type;
};

template<typename TRet, typename ... TArgs>
struct callable_traits < TRet(*)(TArgs...) > {
  const static bool is_callable = true;
  const static bool is_const = false;
  const static bool is_member = false;
  const static bool is_volatile = false;
  typedef std::tuple<TArgs...> args_tuple;
  const static int arity = std::tuple_size<args_tuple>::value;
  typedef TRet return_type;
  typedef void class_type;
};

template<typename TRet, typename TClass, typename ... TArgs>
struct callable_traits < TRet(TClass::*)(TArgs...) > {
  const static bool is_callable = true;
  const static bool is_const = false;
  const static bool is_member = true;
  const static bool is_volatile = false;
  typedef std::tuple<TArgs...> args_tuple;
  const static int arity = std::tuple_size<args_tuple>::value;
  typedef TRet return_type;
  typedef TClass class_type;
};
template<typename TRet, typename TClass, typename ... TArgs>
struct callable_traits < TRet(TClass::*)(TArgs...)const > {
  const static bool is_callable = true;
  const static bool is_const = true;
  const static bool is_member = true;
  const static bool is_volatile = false;
  typedef std::tuple<TArgs...> args_tuple;
  const static int arity = std::tuple_size<args_tuple>::value;
  typedef TRet return_type;
  typedef TClass class_type;
};

template<typename TRet, typename TClass, typename ... TArgs>
struct callable_traits < TRet(TClass::*)(TArgs...)volatile > {
  const static bool is_callable = true;
  const static bool is_const = false;
  const static bool is_member = true;
  const static bool is_volatile = true;
  typedef std::tuple<TArgs...> args_tuple;
  const static int arity = std::tuple_size<args_tuple>::value;
  typedef TRet return_type;
  typedef TClass class_type;
};







/// TypedCallableInfo

template<typename TRet, bool isConst, bool isVolatile, typename ...TArgs>
class TypedCallableInfo : public virtual CallableInfo {
public:
  typedef typename
    NS(CORE_NAMESPACE)::generate_sequence <
    std::tuple_size<std::tuple<TArgs...>>::value
    > ::type sequence_type;

  TypedCallableInfo(){
    _parameterlist = create_parameters<std::tuple<TArgs...>>(*this, sequence_type());

  }
  virtual const parameter_list & parameters()const{
    return _parameterlist;
  }

  virtual const TypeInfo & returnType()const { return reflect<TRet>(); }
  virtual bool isConstCall()const { return isConst; }
  virtual bool isVolatileCall()const{ return isVolatile; }



private:
  parameter_list _parameterlist;
};

///TypedFieldInfo

template<typename TClass, typename T>
class TypedFieldInfo :public FieldInfo{

  const std::string & memberName()const override { static std::string name("~field"); return name; };
  bool isStatic()const override{ return true; };
  const TypeInfo & definingType()const override {
    return reflect<TClass>();
  };
  const TypeInfo & declaringType()const override {
    return reflect<TClass>();
  };


};

/// TypedMethodInfo


/// TypedConstructorInfo

template<typename TClass, typename ... TArgs>
class TypedConstructorInfo :
  public ConstructorInfo,
  public TypedCallableInfo < NS(CORE_NAMESPACE)::any, false, false, TArgs... > {
protected:
  std::string get_id()const{ return "~ctor"; }
  std::string get_name()const{ return "~ctor"; }
public:
  const TypeInfo & definingType()const override {
    return reflect<TClass>();
  };
  const TypeInfo & declaringType()const override {
    return reflect<TClass>();
  };

  static NS(CORE_NAMESPACE)::any construct(TArgs... args){
    return new TClass(args...);
  }

  virtual NS(CORE_NAMESPACE)::any make(const argument_list  & args){
    static auto construct = [](TArgs... args){
      std::cout << "asd" << std::endl;
      return TClass(args...);
    };
    return NS(CORE_NAMESPACE)::dynamic_call(construct, args);
  };
  virtual NS(CORE_NAMESPACE)::any make_new(const argument_list  & args) {
    static auto construct = [](TArgs... args){
      return new TClass(args...);
    };
    return NS(CORE_NAMESPACE)::dynamic_call(construct, args);
  };
  virtual NS(CORE_NAMESPACE)::any make_placement_new(void* place, const argument_list  & args) {
    static auto construct = [](void* location, TArgs... args){
      return new (location)TClass(args...);
    };


    argument_list copy;
    copy.push_back(place);
    for (auto arg : args){
      copy.push_back(arg);
    }

    return NS(CORE_NAMESPACE)::dynamic_call(construct, copy);
  };


};




template<typename T, int idx>
std::shared_ptr<ParameterInfo> create_parameter(CallableInfo & cinfo){
  auto info = std::make_shared<TypedParameterInfo<T, idx>>(cinfo);
  return info;
}


template< int argumentIndex, typename CallableType >
ParameterInfo & reflect_parameter(CallableType callable){
  auto  & callableInfo = reflect_callable(callable);
  static auto info = std::make_unique<TypedParameterInfo<CallableType, argumentIndex>>();
  static bool init = [](){

    return true;
  }();
  return *info;
}


template<typename TClass, typename ... TArgs>
ConstructorInfo & reflect_constructor(){
  static auto info = std::make_unique<TypedConstructorInfo<TClass, TArgs...>>();
  static bool init = [](){
    //      reflect<TClass>().registerConstructor<TArgs...>(info);
    return true; }();
    return *info;
};

/// Tests


UNITTEST(DeclareNamespaceInGlobal){
  NamespaceInfo global(0, "::");
  auto & decl = global.declare<NamespaceInfo>("subnamespace");
  ASSERT(global["subnamespace"].id() == "subnamespace");
}

class MyType{};
UNITTEST(DeclareTypeInGlobal){
  NamespaceInfo global(0, "::");
  auto & declaration = global.declare<MyType>();
  auto & id = declaration.id();
  auto & name = declaration.name();
  auto & scope = declaration.scope();
  ASSERT(scope == global);
  ASSERT(name == typeid(MyType).name());
}

UNITTEST(DeclareNestedNamespaces){
  NamespaceInfo global(0, "::");
  global.declare<NamespaceInfo>("ns1").declare<NamespaceInfo>("ns2");
  auto & ns1 = global["ns1"];
  const NamespaceInfo & ns1cast = *dynamic_cast<const NamespaceInfo*>(&ns1);

  ASSERT(ns1cast["ns2"].id() == "ns2");
}



UNITTEST(EqualityTest1){
  ASSERT(&reflect<int>() == &reflect<int>());
  ASSERT(reflect<int>() == reflect<int>());
  ASSERT(reflect<int>().hash_code() == typeid(int).hash_code());
}

UNITTEST(EqualityTest2){
  ASSERT(reflect<int>() == reflect<int&>().pure_type());
  ASSERT(reflect<int>() == reflect<int&>().underlying_type());
  ASSERT(&reflect<int*>() == &reflect<int**>().underlying_type());
}
UNITTEST(TestIsConst){
  ASSERT(reflect<const int>().isConst());
  ASSERT(!reflect<const int>().underlying_type().isConst());
}
UNITTEST(TestIsVolatile){
  ASSERT(reflect<volatile int>().isVolatile());
  ASSERT(!reflect<volatile int>().underlying_type().isVolatile());
}
UNITTEST(TestIsFundamental){
  ASSERT(reflect<int>().isFundamental());
  struct T2{};
  ASSERT(!reflect<T2>().isFundamental());
}



/*
UNITTEST(ReflectArgumentShouldHaveCorrectFields){
auto callable = [](int i, double j){return std::string("asd"); };

auto & arg1 = reflect_parameter<0>(callable);
ASSERT(arg1.parameterType() == reflect<int>());
ASSERT(arg1.parameterName() == "a0");
ASSERT(arg1.parameterIndex() == 0);
ASSERT(arg1.callableType() == reflect<decltype(callable)>());

auto & arg2 = reflect_parameter<1>(callable);
ASSERT(arg2.parameterType() == reflect<int>());
ASSERT(arg2.parameterName() == "a1");
ASSERT(arg2.parameterIndex() == 1);
ASSERT(arg2.callableType() == reflect<decltype(callable)>());

auto & r2 = reflect_parameter<1>(callable);
ASSERT(&arg2 == &r2);
}
*/




std::string method3(int i, double j){ return std::string("asd"); }
/*UNITTEST(ReflectCallableShouldHaveCorrectFields){
  auto callable1 = [](int i, double j){return std::string("asd"); };

  struct MyTest{
  static std::string method4(int i, double k){ return std::string("asd"); }
  std::string method(int i, double j){ return std::string("asd"); }
  std::string method2(int i, double j){ return std::string("asd"); }
  std::string method5(int i, double j)const{ return std::string("asd"); }
  };

  {
  auto & uut = reflect_callable(callable1);
  ASSERT(uut.parameters().size() == 2);
  //      ASSERT(!uut.isConstCall());
  ASSERT(!uut.isVolatileCall());
  ASSERT(uut.returnType() == reflect<std::string>());
  ASSERT(uut.parameters()[0]->parameterType() == reflect<int>());
  ASSERT(uut.parameters()[1]->parameterType() == reflect<double>());

  }
  {
  auto & uut = reflect_callable(&MyTest::method5);
  ASSERT(uut.parameters().size() == 2);
  ASSERT(uut.isConstCall());
  ASSERT(!uut.isVolatileCall());
  ASSERT(uut.returnType() == reflect<std::string>());
  ASSERT(uut.parameters()[0]->parameterType() == reflect<int>());
  ASSERT(uut.parameters()[1]->parameterType() == reflect<double>());
  }
  {
  auto & uut = reflect_callable(&MyTest::method);
  ASSERT(uut.parameters().size() == 2);
  ASSERT(!uut.isConstCall());
  ASSERT(!uut.isVolatileCall());
  ASSERT(uut.returnType() == reflect<std::string>());
  ASSERT(uut.parameters()[0]->parameterType() == reflect<int>());
  ASSERT(uut.parameters()[1]->parameterType() == reflect<double>());
  }
  {
  auto & uut = reflect_callable(&method3);
  ASSERT(uut.parameters().size() == 2);
  ASSERT(uut.isConstCall() == false);
  ASSERT(!uut.isVolatileCall());
  ASSERT(uut.returnType() == reflect<std::string>());
  ASSERT(uut.parameters()[0]->parameterType() == reflect<int>());
  ASSERT(uut.parameters()[1]->parameterType() == reflect<double>());
  }
  {
  auto & uut = reflect_callable(&MyTest::method4);
  ASSERT(uut.parameters().size() == 2);
  ASSERT(uut.isConstCall() == false);
  ASSERT(!uut.isVolatileCall());
  ASSERT(uut.returnType() == reflect<std::string>());
  ASSERT(uut.parameters()[0]->parameterType() == reflect<int>());
  ASSERT(uut.parameters()[1]->parameterType() == reflect<double>());
  }
  }
  */


void firstMethod(int i, int j){}

UNITTEST(ReflectStaticMethod){
  auto & uut = reflect_m(&firstMethod);
}




UNITTEST(ReflectConstructorFieldsShouldBeCorrect){
  struct MyTest{ int field; MyTest() :field(0){} };
  auto & uut = reflect_constructor<MyTest>();
  ASSERT(uut.definingType() == reflect<MyTest>());
  ASSERT(uut.declaringType() == reflect<MyTest>());
  ASSERT(uut.isConstCall() == false);
  ASSERT(uut.isStatic() == true);
  // should be true (constrcutors are static because the need no instance pointer)
  ASSERT(uut.parameters().size() == 0);
  ASSERT(uut == uut);
  ASSERT(&uut == &uut);
  //    ASSERT(reflect<MyTest>().constructor<>() == uut);
}

UNITTEST(ReflectDefaultConstructorMake){
  struct MyTest{ int field; MyTest() :field(0){} };
  // using default constructor (auto defined constructor) will not work...
  auto & uut = reflect_constructor<MyTest>();
  auto res = uut.make();
  auto cast = res.as<MyTest>();
  ASSERT(cast.field == 0);

}


UNITTEST(ReflectConstructorNoOverloadMake){
  struct MyTest{ int field; MyTest() :field(0){} MyTest(int i) :field(i){} };
  auto & uut = reflect_constructor<MyTest, int>();
  auto res = uut.make(2);
  auto cast = res.as<MyTest>();
  ASSERT(uut.parameters().size() == 1);
  ASSERT(cast.field == 2);
}

UNITTEST(ReflectConstructorWithOverloadsMake){
  struct MyTest{ int field; MyTest() :field(0){} MyTest(int i) :field(i){} MyTest(int i, int j) :field(i*j){} };
  auto & c1 = reflect_constructor<MyTest, int>();
  auto & c2 = reflect_constructor<MyTest, int, int>();

  auto res1 = c1.make(2).as<MyTest>();
  auto res2 = c2.make(2, 3).as<MyTest>();


  ASSERT(res1.field == 2);
  ASSERT(c1.parameters().size() == 1);
  ASSERT(res2.field == 6);
  ASSERT(c2.parameters().size() == 2);
}




UNITTEST(ReflectConstructor){

  struct MyTest{
    double res;
    MyTest() :res(0){}
    MyTest(int i) :res(i){}
    MyTest(int i, int j) :res(i*j){}
    MyTest(double d) :res(d){}
  };

  auto & ci1 = reflect_constructor<MyTest>();
  auto res1_make = ci1.make({}).as<MyTest>();
  auto res1_new = ci1.make_new({}).as<MyTest*>();
  MyTest mt(3);
  auto res1_placement_new = ci1.make_placement_new({ (void*)&mt }).as<MyTest*>();
  ASSERT(res1_make.res == 0.0);
  ASSERT(res1_new->res == 0.0);
  ASSERT(res1_placement_new->res == 0.0);

  auto & ci2 = reflect_constructor<MyTest, int>();
  auto res2 = ci2.make_new({ 1 }).as<MyTest*>();
  ASSERT(res2->res == 1.0);


  auto & ci3 = reflect_constructor<MyTest, int, int>();
  auto res3 = ci3.make_new({ 3, 4 }).as<MyTest*>();
  ASSERT(res3->res == 12.0);

  auto & ci4 = reflect_constructor<MyTest, double>();
  auto res4 = ci4.make_new({ 4.0 }).as<MyTest*>();
  ASSERT(res4->res == 4.0);


}



namespace ns1{
  namespace ns2{
    class ExampleType{
    public:
      ExampleType(){};
      ExampleType(const std::string & name) :_field1(name){}
      ExampleType(int accu) :_accu(accu){}

      static std::string staticField;
      std::string _field1;
      int _accu;

      int add(int i, int j)const{ return i + j; }
      int add(int i){ return _accu = _accu + i; }

      static std::string getName(){ return "hello"; }

      class SubType{

      };
    };
    std::string ExampleType::staticField = "asd";
  }
  int freeMethod(int i, int j){ return i + j; }
  int freeValue = 2;
}




template<typename T>
ScopeDeclaration & reflectMemberMethod(T what){


  static NamespaceInfo info(0, "");
  return info;
}


template<typename T>
ScopeDeclaration & reflectFreeField(T what){


  static NamespaceInfo info(0, "");
  return info;
}

template<typename T>
ScopeDeclaration & reflectMemberField(T what){


  static NamespaceInfo info(0, "");
  return info;
}

template<typename T>
ScopeDeclaration & reflectType(){

  static NamespaceInfo info(0, "");
  return info;
}


template<typename T, typename ... TArgs>
ScopeDeclaration & reflectConstructor(){

  static NamespaceInfo info(0, "");
  return info;
}






/// MethodInfo
class MethodInfo : public MemberInfo, public CallableInfo, public ScopeInfo{
public:
};


class FreeMethodInfo : public ScopeDeclaration, public ScopeInfo, public virtual CallableInfo{
public:

};

template<typename T>
class TCallableInfo : public virtual CallableInfo {
public:
  typedef callable_traits<T> traits;
  typedef typename NS(CORE_NAMESPACE)::generate_sequence<traits::arity>::type sequence_type;


  TCallableInfo(){
    _parameterlist = create_parameters<typename traits::args_tuple>(*this, sequence_type());
  }

  virtual const parameter_list & parameters()const{
    return _parameterlist;
  }

  virtual const TypeInfo & returnType()const { return reflect<typename traits::return_type>(); }
  virtual bool isConstCall()const { return traits::is_const; }
  virtual bool isVolatileCall()const{ return traits::is_volatile; }

private:
  parameter_list _parameterlist;
};
/*template<typename TRet, typename... TArgs>
class TCallableInfo : public virtual CallableInfo{
public:
typedef std::tuple<TArgs...> args_tuple;
const static int arity = std::tuple_size<args_tuple>::value;
typedef typename NS(CORE_NAMESPACE)::generate_sequence<arity>::type sequence_type;

};


template<typename T>
TCallableInfo<T> & ci(T){ return * new TCallableInfo<T>(); }
UNITTEST(Callab){
CallableInfo & res1 = ci(&ns1::freeMethod);
CallableInfo & res2 = ci(&ns1::ns2::ExampleType::getName);


}*/
/*
  template<typename T >
  class TypedFreeMethodInfo : public FreeMethodInfo{
  public:
  typedef T method_type;
  typedef std::pair<void*, TypeInfo*> method_id;
  TypedFreeMethodInfo(method_type methodPointer){

  }
  protected:
  std::string get_id()const{ return DS_INLINE_STRING("method_" << _method); }
  std::string get_name()const{ return ""; }
  const TypeInfo & returnType()const{ return reflect<typename NS(CORE_NAMESPACE)::func_traits<T>::return_type>(); }
  bool isConstCall()const{ NS(CORE_NAMESPACE)::func_traits<T>::is_const_call; }
  bool isVolatileCall()const{ NS(CORE_NAMESPACE)::func_traits<T>::is_volatile_call; }
  const refl::parameter_list & parameters()const{
  static parameter_list lst();
  return lst;
  }
  private:
  method_type _method;
  };*/


template<typename T>
ScopeDeclaration & reflectFreeMethod(T  what){
  typedef std::pair<void*, TypeInfo*> method_id;
  method_id id{ (void*)what, &reflect<T>() };

  static NamespaceInfo info(0, "");
  return info;
  //   return *new TypedFreeMethodInfo<T> info(what);
}




UNITTEST(ShouldReflectFreeMethod){

  auto & info = reflectFreeMethod(&ns1::freeMethod);
  auto infoptr = dynamic_cast<MethodInfo*>(&info);

}
UNITTEST(ShouldReflectMemberMethod){

}
UNITTEST(ShouldReflectFreeField){

}
UNITTEST(ShouldReflectMemberField){

}


UNITTEST(ShouldReflectConstructor){

}


UNITTEST(EndToEndReflectionTest){

  NamespaceInfo global(0, "global");
  auto & ns1 = global.declare<NamespaceInfo>("ns1");
  auto & ns2 = ns1.declare<NamespaceInfo>("ns2");
  auto & exampleType = ns2.declare<ns1::ns2::ExampleType>();
  using namespace ns1::ns2;
  using namespace ns1;



}







NS_END(CORE_REFLECTION2_NAMESPACE)

