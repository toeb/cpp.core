#pragma once
#include <core/core.h>


#include <core/reflection/type/TypeInfo.h>
#include <core/reflection/type/TypeInfo.implementation.template.h>
#include <string>
#include <iostream>
#include <fstream>
//#include <core/reflection.builder.h>
NS_BEGIN(CORE_NAMESPACE)



  /* template<> struct TypeInitializer<::std::ostream>{static void initialize();};
  template<> struct TypeInitializer<::std::istream>{static void initialize();};
  template<> struct TypeInitializer<::std::iostream>{static void initialize();};
  template<> struct TypeInitializer<::std::ifstream>{static void initialize();};
  template<> struct TypeInitializer<::std::ofstream>{static void initialize();};
  */
  template<> struct TypeInitializer< ::std::stringstream>{static void initialize();};

  template<> struct TypeInitializer< ::std::string>{
    static void initialize(){
      /*
      core::reflection::builder::reflect<std::string>()
        ->fullyQualifiedName("::std::string")
        ->method(&std::string::size)
        ->name("size")
        ->end()        
        ->publish()
        ->end();*/

    }
  };
  template<typename T> struct TypeInitializer< ::std::vector<T>>{
    static void initialize(){
      
      //auto builder = core::reflection::builder::reflect<std::vector<T>>();

      // builder->fullyQualifiedName(DS_INLINE_STRING("::std::vector<"<< type_of<T>()->getFullyQualifiedName() <<">")) ;
      // builder->constructor()->end();       
      // builder->method(signature<const typename std::vector<T>::value_type&>(&std::vector<T>::push_back))->name("push_back")->end();       
      // //builder->method(signature<std::vector<T>::value_type&&>(&std::vector<T>::push_back())->name("push_back")->end();
      // builder->method(&std::vector<T>::size)->name("size")->end();
      // builder->method(signature(&std::vector<T>::at))->name("at")->end();
      // builder->method(const_signature(&std::vector<T>::at))->name("at")->end();
      // builder->publishHierarchy();
      // builder->end();                                                                                               ;

    }
  };

  /*
  // meta information for std::types

  META(::std::string);
  //DS_DEFAULT_CONSTRUCTOR_ENABLE(std::string);


  META(::std::ostream);
  META(::std::istream);
  META(::std::iostream);
  META(::std::ifstream);
  META(::std::ofstream);
  }

  #include <functional>
NS_BEGIN(CORE_NAMESPACE)

  template<typename TResult>
  class TypeInfo<std::function<TResult(void)>> : public TraitType<std::function<TResult(void)>> {
  TEMPLATEDSINGLETON(TypeInfo, std::function<TResult(void)>):      
  TraitType(DS_INLINE_STRING("std::function<" << typeof(TResult)->getFullyQualifiedName()<<"(void)>"),0){     
  }
  };
  }

  #include <memory>


NS_BEGIN(CORE_NAMESPACE)



  //std::memory
  template<typename T> 
  class TypeInfo<std::shared_ptr<T>>: public TraitType< std::shared_ptr<T>>{ 
  TEMPLATEDSINGLETON(TypeInfo, std::shared_ptr<T>):      
  TraitType(DS_INLINE_STRING("std::shared_ptr<" << typeof(T)->getFullyQualifiedName()<<">")){ 
  TypeTemplateArguments<T> templateArgs(this);
  } 
  };

  template<typename T>
  class TypeInfo<std::unique_ptr<T>>: public TraitType< std::unique_ptr<T>>{ 
  TEMPLATEDSINGLETON(TypeInfo, std::unique_ptr<T>):
  TraitType(DS_INLINE_STRING("std::unique_ptr<" << typeof(T)->getFullyQualifiedName()<<">")){ 
  TypeTemplateArguments<T> templateArgs(this);
  } 
  };



  }

  // containers
  #include <set>
  #include <vector>
  #include <map>
  //#include <core/reflection/member/method/TypedMethodInfo.h>
NS_BEGIN(CORE_NAMESPACE)
  template<typename TKey,typename TValue>
  class TypeInfo<std::map<TKey,TValue>> : public TraitType<std::map<TKey,TValue>>{
  TEMPLATEDSINGLETON(TypeInfo,std::map<TKey,TValue>):TraitType(DS_INLINE_STRING("::std::std::map<"<<typeof(TKey)->getFullyQualifiedName()<<", "<<typeof(TValue)->getFullyQualifiedName()<<">"),0){
  TypeTemplateArguments<TKey,TValue> templateArgs(this);
  }
  };
  template<typename T>
  class TypeInfo<std::set<T>> :public TraitType<std::set<T>>{
  TEMPLATEDSINGLETON(TypeInfo,std::set<T> ):TraitType(DS_INLINE_STRING("::std::set<"<<typeof(T)->getFullyQualifiedName()<<">")){
  TypeTemplateArguments<T> templateArgs(this);
  }
  };
  template<typename T>
  class TypeInfo<std::vector<T>> :public TraitType<std::vector<T>>{
  TEMPLATEDSINGLETON(TypeInfo,std::vector<T>):TraitType(DS_INLINE_STRING("::std::vector<"<<typeof(T)->getFullyQualifiedName()<<">")){
  TypeTemplateArguments<T> templateArgs(this);

  static TypedMethodInfo<decltype(&std::vector<T>::size)> size(&std::vector<T>::size);
  size.setName("size");
  typedef std::vector<T>::reference (std::vector<T>::*typeofAt)(std::vector<T>::size_type);
  static TypedMethodInfo<typeofAt> at(&std::vector<T>::at);
  at.setName("at");
  Members()|=&size;
  Members()|=&at;

  } 
  };
  */
NS_END(CORE_NAMESPACE)
