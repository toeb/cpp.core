#include <core.testing.h>
#include <core.reflection.h>
#include <core/builder/Builder.h>
#include <core/reflection/builder/builders.h>
NS_USE(CORE_NAMESPACE);
using namespace std;
namespace core_reflection_tests{
  



  class DisplayAttribute : public Attribute{
  public:
    DisplayAttribute(){
      setAttributeName("DisplayAttribute");
    }
    DisplayAttribute(const std::string & displayName, const std::string & description = "") :
      _DisplayName(displayName),
      _Description(description)
    {
      setAttributeName("DisplayAttribute");

    }
    typedef std::string basic_property(DisplayName);
    typedef std::string basic_property(Description);
  };









  class A{
  public:

     int methodAdd(int a, int b){
      return a + b;
    }
    int field;
    A(){ field = 84; }
    A(int i) :field(i){}
  };


  void printAttribute(std::ostream & out, const Attribute * attribute){

    out << "[" << attribute->getAttributeName() << "]";
  }
  void printAttributeTarget(std::ostream & out, const AttributeTarget * target, const std::string & separator = "\n"){

    for (auto attr : target->Attributes()){
      printAttribute(out, attr);
      out << separator;
    }
  }

  void printType(std::ostream &  out, const Type * type);
  void printArgument(std::ostream & out, const ArgumentInfo * arg){
    out << arg->getName() << arg->getType()->getFullyQualifiedName();
  }

  void printCallableSignature(std::ostream & out, const CallableInfo * callable){
    out << "(";

    for (auto arg : callable->Arguments()){
      printArgument(out, arg.get());
      out << ", ";
    }

    out << ") : " << callable->getReturnType()->getFullyQualifiedName();
  }
  void printMember(std::ostream & out, const MemberInfo * member){
    auto callable = dynamic_cast<const CallableInfo *>(member);
    printAttributeTarget(out, member, "");
    switch (member->getAccessModifier()){
    case AccessModifierEnum::Private:
      out << "-";
      break;
    case AccessModifierEnum::Public:
      out << "+";
      break;
    case AccessModifierEnum::Protected:
      out << "#";
      break;
    case AccessModifierEnum::Unknown:
      out << "?";
      break;
    }
    if (callable){
      printCallableSignature(out, callable);
    }
    out << ";";

  }
  void printType(std::ostream & out, const Type * type){
    printAttributeTarget(out, type);
    out << type->getFullyQualifiedName() << "{" << endl;


    for (auto member : type->Members().elements()){
      out << "  ";
      printMember(out, member);
      out << endl;
    }

    out << "}" << endl;
  }

  UNITTEST(ReflectType1){
    auto res = reflect<int>();
    auto tmp = std::is_same<Builder<TypedTypeInfo<int>>, decltype(res)>::value;
    ASSERT(tmp);
  }


  UNITTEST(ShouldReflectOnlySameTypeObject){

    auto elementA = &(reflect<int>().element());
    auto elementB = &(reflect<int>().element());

    ASSERT(elementA == elementB);

  }

  UNITTEST(ShouldReflectMethod){
    struct MyType{
      int result(){ return 0; } int result2(){ return 0; }
    };
    auto typeBuilder = reflect<MyType>();

    auto element1 = &(typeBuilder.method(&MyType::result).element());
    auto element2 = &(typeBuilder.method(&MyType::result2).element());
  }

  



  UNITTEST(Reflect1){
    reflect<int>()
      .name("::int")
      .end();

    auto type = reflect<A>()
      .name("::core_reflection_tests::A")
      .attribute<DisplayAttribute>("A class called 'A'")
      .end()
      ;


    auto & out = std::cout;

    reflect<A>()
      .method(&A::methodAdd)
      .attribute<DisplayAttribute>(" methodAdd adds two ints")
      .memberName("methodAdd")
      .accessModifier(AccessModifierEnum::Public)
      .arg(0).argumentName("a").end()
      .arg(1).argumentName("b").end()
      .end()
      //.constructor().end()
      //.constructor<int>().end()
      ;


    printType(out, type.get());



  }
}



UNITTEST(ArgumentShouldBeInvalidWhenNoValueIsAssigned){
  Argument arg;
  ASSERT(!arg.isValid());
}

UNITTEST(ArgumentShouldBeValidWhenAssigned){
  Argument arg = 3;
  ASSERT(arg.isValid());

}

UNITTEST(ArgumentShouldReturnAssignedValue){

  Argument arg = 3;
  auto res1 = (int)arg;
  ASSERT(res1 == 3);

  const int & res2 = arg;
  ASSERT(&res2 == arg.data.get());
}


// This test shows that an argument can take control of a shared pointer
UNITTEST(ArgumentShouldTakeOwnershipOfSharedPointer){
  auto in = std::make_shared<int>(3);
  Argument arg = in;

  ASSERT(in.get() == arg.data.get());
}


UNITTEST(ArgumentShouldBeConvertibleToSharedPointer){
  auto in = make_shared<int>(3);
  Argument arg = in;
  shared_ptr<int> in2 = arg;
  ASSERT(in2.get() == in.get());
  // in , in2 and arg owns the shared pointer
  ASSERT(in.use_count() == 3);
}

UNITTEST(ArgumentSHouldBeAccessibleByRef){
  Argument arg = 3;
  arg.ref<int>() = 4;
  int res = arg;
  ASSERT(res == 4);
}

UNITTEST(ArgumentShouldBeAccessibleViaWeakPtr){
  Argument arg = 3;
  ASSERT(arg.data.use_count() == 1);
  auto wptr = arg.w_ptr<int>();
  ASSERT(arg.data.use_count() == 1);
}
UNITTEST(ArgumentShouldBeAssignableToArgument){

  Argument arg = 3;
  Argument arg2 = arg;
  ASSERT(arg.data.use_count() == 2);
  ASSERT(arg.type == arg2.type);
  ASSERT(arg.type == type_of<int>());
  ASSERT(arg.data.get() == arg2.data.get())
}
UNITTEST(ArgumentShouldNotUseUpMemory){
  Argument arg = 3;
  {
    Argument arg2 = arg;
    ASSERT(arg.data.use_count() == 2);
  }
  ASSERT(arg.data.use_count() == 1);
}
