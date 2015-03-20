#pragma once
#include <core/core.h>

//#include <core/patterns/Singleton.h>
#include <core/reflection/preprocessor/type.h>
#include <sstream>
#include <core/reflection/type/Type.h>
NS_BEGIN(CORE_NAMESPACE)
  /*

  template<typename T>
  class TraitType : public Type{
  typedef T type;
  protected:
  TraitType(const std::string & name);
  private:
  void init();
  };
  template<typename T1=std::_Nil,typename T2=std::_Nil,typename T3=std::_Nil,typename T4=std::_Nil,typename T5=std::_Nil,typename T6=std::_Nil>
  struct TypeTemplateArguments{
  TypeTemplateArguments(Type * type){
  type->setIsTemplated(false);
  }
  };
  template<typename T1>
  struct TypeTemplateArguments<T1,std::_Nil,std::_Nil,std::_Nil,std::_Nil,std::_Nil>{
  TypeTemplateArguments(Type * type){
  type->setIsTemplated(true);
  type->TemplateArguments().push_back(type_of<T1>());
  }
  };
  template<typename T1,typename T2>
  struct TypeTemplateArguments<T1,T2,std::_Nil,std::_Nil,std::_Nil,std::_Nil>{
  TypeTemplateArguments(Type * type){
  type->setIsTemplated(true);
  type->TemplateArguments().push_back(type_of<T1>());
  type->TemplateArguments().push_back(type_of<T2>());
  }
  };
  template<typename T1,typename T2,typename T3>
  struct TypeTemplateArguments<T1,T2,T3,std::_Nil,std::_Nil,std::_Nil>{
  TypeTemplateArguments(Type * type){
  type->setIsTemplated(true);
  type->TemplateArguments().push_back(type_of<T1>());
  type->TemplateArguments().push_back(type_of<T2>());
  type->TemplateArguments().push_back(type_of<T3>());
  }
  };

  */

  template<typename T>
  class TypedTypeInfo : public Type{
  public:
    typedef T reflected_type;
    TypedTypeInfo(){

      auto name = typeid(T).name();

      setRttiName(name);
      setRttiHashCode(typeid(T).hash_code());
    }

  };


  template < typename T >
  struct initializer_exists
  {
    typedef char (&yes) [1];
    typedef char (&no)  [2];

    template < typename U >
    static yes check(decltype(U::initializeType()));

    template < typename U >
    static no check(...);

    enum { value = sizeof(check<T>(0)) == sizeof(yes) };



  };

  template<typename T, bool =  initializer_exists<T>::value>
  struct call_initializer{
    static void call(){}
  };

  template<typename T>
  struct call_initializer<T,true>{
    static void call(){T::initializeType();}
  };

  template<typename T>
  struct TypeInitializer{
    static void initialize(){call_initializer<T>::call();}
  };
  /**
  * \brief Information about the type.
  *        assumes T has method getTypeName which returns the fully qualified type name
  */
  
  template<typename T>
  class TypeInfo
  {
  public:
    static std::shared_ptr<TypedTypeInfo<T>> instance(){
      static std::shared_ptr<TypedTypeInfo<T>> _instance = std::make_shared<TypedTypeInfo<T>>();
      
      // initializer will only be executed once;
      static bool initialized = [&](){
      //  TypeInitializer<T>::initialize(); 
        //std::cout << typeid(T).name()<<" "<<_instance->getName()<<" "<<_instance->getId()<<""<<std::endl;


        return true;

        
      }();

      return _instance;
    };
  };

  template<typename T> const Type * type_of();
  template<typename T> const Type * type_of(const T & t);
  template<typename SuperType, typename TestType> bool subclassof();
  template<typename SuperType, typename TestType> bool subclassof(const TestType & b);
  template<typename SuperType, typename TestType> bool subclassof(const SuperType & a, const TestType & b);



NS_END(CORE_NAMESPACE)


// template implemetation

NS_BEGIN(CORE_NAMESPACE)

  template<typename T> const Type * type_of(){
    return NS(CORE_NAMESPACE)::TypeInfo<T>::instance().get();
  }

  template<typename T> const Type * type_of(const T & t){
    return type_of<T>();
  }

  template<typename SuperType, typename TestType> bool subclassof(){
    const Type * t1 = type_of<SuperType>();
    const Type * t2 = type_of<TestType>();
    return t2->isSubClassOf(t1);
  }



  template<typename SuperType, typename TestType> bool subclassof(const TestType & b){
    return subclassof<SuperType,TestType>();
  }
  template<typename SuperType, typename TestType> bool subclassof(const SuperType & a, const TestType & b){
    return subclassof<SuperType,TestType>();  
  }

NS_END(CORE_NAMESPACE)


/*
// specialization for NS(CORE_NAMESPACE)::Set
#include <core/container/containers/Set.h>
NS_BEGIN(CORE_NAMESPACE)
template<typename T>
class TypeInfo<Set<T> >: public TraitType<Set<T> >
{
TEMPLATEDSINGLETON(TypeInfo, Set<T>):TraitType(DS_INLINE_STRING("Set<"<< typeof(T)<<">"),0) {
}
};
}
*/