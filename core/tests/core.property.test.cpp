#include <core.testing.h>
#include <core.property.h>
NS_BEGIN(CORE_NAMESPACE)

namespace properties{

  TEST(1, propertyDefinition){
    struct A{
      typedef std::string DS_PROPERTY_DEFINITION(StringValue)
    public:

      typedef StringValuePropertyType PublicStringValuePropertyType;
    };

    auto result = std::is_same<A::PublicStringValuePropertyType, std::string>::value;
    CHECK(result);
  }

  UNITTEST(typedefPreceedingType){
    class TestType{
    public:
      std::string DS_PRECEEDING_TYPE_TYPEDEF mystring;
      std::map<std::string, std::string> DS_PRECEEDING_TYPE_TYPEDEF mymap;
    };
    auto result = std::is_same<std::string, TestType::mystring>::value;

    ASSERT(result);
    result = std::is_same<std::map<std::string, std::string>, TestType::mymap>::value;
    ASSERT(result);
  }



  TEST(1, propertyField){
    class A{
      typedef std::string DS_PROPERTY_DEFINITION(StringValue);
      DS_PROPERTY_STORAGE_FIELD(StringValue)
    private:
      friend class UnitTestClass;
    };

    auto result = std::is_same<A::StringValuePropertyType, std::string>::value;
    CHECK(result);
  }


  TEST(1, TemplatedPropertyField){
    class A{
      typedef std::map<std::string, std::string> DS_PROPERTY_DEFINITION(MapValue)
        DS_PROPERTY_STORAGE_FIELD(MapValue);
    private:
      friend class UnitTestClass;
    };
    auto result = std::is_same<A::MapValuePropertyType, std::map<std::string, std::string>>::value;
    CHECK(result);
  }



  TTEST_DEFAULT(PropertyField, PropertyType){
    class A{
    public:typedef PropertyType DS_PROPERTY_DEFINITION_TEMPLATED(Value);
    public: DS_PROPERTY_STORAGE_FIELD(Value);
    private:
      friend class UnitTestClass;
    };


    auto res = std::is_same<typename A::ValueStorageType, PropertyType>::value;
    if (!res){
      FAIL(" the property storage type is incorrect");
    }
    typedef decltype(A()._Value) TheType;
    res = std::is_same<typename A::ValueStorageType, TheType>::value;
    if (!res){
      FAIL(" the field type is incorrect");
    }
  }


  TTEST_DEFAULT(PropertyPointerStorage, PropertyType){
    class A{
      friend class UnitTestClass;
    public: typedef PropertyType DS_PROPERTY_DEFINITION_TEMPLATED(Value);
    public: DS_PROPERTY_STORAGE_POINTER(Value);
    };

    auto res = std::is_pointer<typename A::ValueStorageType>::value;
    if (!res) FAIL("the property storage type is incorrect (not a pointer");
    res = std::is_same< typename A::ValueStorageType, typename std::add_pointer<PropertyType>::type>::value;
    if (!res) FAIL("the type of the storage field is incorrect");
  }


  TTEST_DEFAULT(PropertyReferenceStorage, PropertyType){
    class A{
      friend class UnitTestClass;
    public: typedef  PropertyType DS_PROPERTY_DEFINITION_TEMPLATED(Value);
    public: DS_PROPERTY_STORAGE_REFERENCE(Value);
    };

    auto res = std::is_reference<typename A::ValueStorageType>::value;
    if (!res) FAIL("the property storage type is incorrect (not a pointer");
    res = std::is_same< typename A::ValueStorageType, PropertyType&>::value;
    if (!res) FAIL("the type of the storage field is incorrect");
  }



  UNITTEST(PropertyFieldSetter){
    class A{
      friend class UnitTestClass;
      typedef  int DS_PROPERTY_DEFINITION(Value);
    public:DS_PROPERTY_STORAGE_FIELD(Value);
    public: DS_PROPERTY_SETTER(Value){ DS_PROPERTY_STORAGE(Value) = value; }


    }a;
    a.setValue(4);
    auto val = a._Value;
    CHECK_EQUAL(4, val);
  }



  UNITTEST(PropertyFieldGetter){
    class A{
      typedef  int DS_PROPERTY_DEFINITION(Value);
    public: DS_PROPERTY_STORAGE_FIELD(Value);
    public: DS_PROPERTY_GETTER(Value){ return _Value; }
    }a;
    a._Value = 24;
    auto val = a.getValue();
    CHECK_TYPES(decltype(val), int);

    CHECK_EQUAL(24, val);

  }


  UNITTEST(PropertyFieldAutoSetter){
    class A{
      typedef   int DS_PROPERTY_DEFINITION(Value);
    public: DS_PROPERTY_STORAGE_FIELD(Value);
    public: DS_PROPERTY_AUTO_SETTER(Value)
    }a;

    a.setValue(42);
    CHECK_EQUAL(42, a._Value);
  }

  UNITTEST(PropertyFieldAutoGetter){
    class A{
      typedef   int DS_PROPERTY_DEFINITION(Value);
    public: DS_PROPERTY_STORAGE_FIELD(Value);
    public: DS_PROPERTY_AUTO_GETTER(Value)
    }a;

    a._Value = 312;
    CHECK_EQUAL(312, a.getValue());

  }


  UNITTEST(PropertyFieldVirtualSetter){
    class A{
      typedef  int DS_PROPERTY_DEFINITION(Value);
    public: DS_PROPERTY_STORAGE_FIELD(Value);
    public: virtual DS_PROPERTY_AUTO_SETTER(Value)

    };

    class B : public A{
    public: DS_PROPERTY_SETTER(Value){
      A::setValue(value + 1);
    }
    }b;
    b.setValue(44);

    CHECK_EQUAL(45, b._Value);

  }
  UNITTEST(PropertyFieldVirtualGetter){
    class A{
      typedef  int DS_PROPERTY_DEFINITION(Value);
    public: DS_PROPERTY_STORAGE_FIELD(Value);
    public: virtual DS_PROPERTY_AUTO_GETTER(Value)

    };

    class B : public A{
    public:
      DS_PROPERTY_GETTER(Value){
        static int v;
        v = A::getValue() + 1;// no temp references 
        return v;
      }
    }b;
    b._Value = 2;
    CHECK_EQUAL(3, b.getValue());
  }





  UNITTEST(ExtensiblePropertyDefintion){

    struct ExtendedPropertyTestStruct{
      extensible_property_class;

      ExtendedPropertyTestStruct() :_RedChannel(0), beforeSetCallCount(0), afterSetCallCount(0), beforeGetCallCount(0), cancelSetResult(false){}

      // counters for accessing callcount
      int beforeSetCallCount;
      int afterSetCallCount;
      mutable int beforeGetCallCount;
      bool cancelSetResult;


      // define a default extended property - a property which has extension points for setting and getting
      typedef  float extensible_property(RedChannel);


      auto before_set(RedChannel){
        beforeSetCallCount++;
        if (cancelSetResult){
          return Cancel;
        }
        return Accept;
      }

      auto after_set(RedChannel){
        afterSetCallCount++;
      }
      auto before_get(RedChannel){
        beforeGetCallCount++;
      }

    };
    ExtendedPropertyTestStruct uut;
    CHECK_EQUAL(0, uut.afterSetCallCount);
    CHECK_EQUAL(0, uut.beforeGetCallCount);
    CHECK_EQUAL(0, uut.beforeSetCallCount);

    uut.setRedChannel(42);

    CHECK_EQUAL(42, uut.getRedChannel());
    CHECK_EQUAL(1, uut.beforeGetCallCount);

    uut.setRedChannel(41);

    uut.cancelSetResult = true;
    uut.setRedChannel(1);

    auto val = uut.getRedChannel();

    CHECK_EQUAL(41, val);
    CHECK_EQUAL(2, uut.beforeGetCallCount);
    CHECK_EQUAL(2, uut.afterSetCallCount);
    CHECK_EQUAL(3, uut.beforeSetCallCount);

  }
  TEST(1, constPointerProperty){
    struct A{
    public:
      typedef const void **const ** const**  basic_property(TheProperty);

      typedef ThePropertyPropertyType PublicThePropertyType;
      // create a public PropPropertyType public
    };
    auto a = A::PublicThePropertyType();
    bool  same = std::is_same<A::PublicThePropertyType, const void **const ** const**>::value;


    CHECK(same);



  }



  TEST(1, notifyingProperties){

    struct A{
      mutable std::stringstream ss;
      extensible_property_class;

      virtual void onBeforePropertyGet(const char * name)const{ ss << 1; }
      virtual void onAfterPropertySet(const char * name){ ss << 2; }
      virtual void onBeforePropertySet(const char * name, const void * data){ ss << 3; }

      typedef int extensible_property(IntProperty);


      auto before_get(IntProperty){

      }

      auto before_set(IntProperty){
        continue_set();
      }
      auto after_set(IntProperty){
      }

    };

    A a;
    a.setIntProperty(4242);
    a.getIntProperty();

    CHECK_EQUAL("321", a.ss.str());
  }

  TEST(2, notifyingProperties){
    struct A : public PropertyChangingObject{
      notify_property_changed;
      typedef int extensible_property(IntProperty);
    };

    A a;
    bool called = false;
    a.listeners() |= new NS(CORE_NAMESPACE)::DelegatePropertyChangedListener([&](Object* sender, const std::string &  name){
      if (name == "IntProperty") called = true;
    });
    CHECK(!called);
    a.setIntProperty(4242);
    CHECK(called);

  }






  UNITTEST(ContainerPropertyAddNumbers){
    //arrange
    class A{
    public:
      std::vector<int> DS_PRECEEDING_TYPE_TYPEDEF DS_PROPERTY_BASIC_CONTAINER(MyNumbers);
    };
    A a;

    // act
    a.addToMyNumbers(1);
    a.addToMyNumbers(2);
    a.addToMyNumbers(3);

    // assert
    ASSERT(a.MyNumbers()[0] == 1);
    ASSERT(a.MyNumbers()[1] == 2);
    ASSERT(a.MyNumbers()[2] == 3);


  }
  UNITTEST(ContainerPropertyRemoveNumbers){
    //arrange
    class A{
    public:
      std::vector<int> DS_PRECEEDING_TYPE_TYPEDEF DS_PROPERTY_BASIC_CONTAINER(MyNumbers);
    };
    A a;
    a.addToMyNumbers(1);
    a.addToMyNumbers(2);
    a.addToMyNumbers(3);


    // act
    a.removeFromMyNumbers(1);

    //assert
    ASSERT(a.MyNumbers()[0] == 2);
    ASSERT(a.MyNumbers()[1] == 3);

  }
}

NS_END(CORE_NAMESPACE)
