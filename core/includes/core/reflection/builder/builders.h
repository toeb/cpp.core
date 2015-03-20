#pragma once
#include <core/core.h>
#include <core/builder/Builder.h>

#include <core.reflection.h>
#define AUTO_REFLECT(...) auto DS_CONCAT(__auto_reflect_,__LINE__)= NS(CORE_NAMESPACE)::auto_reflect<__VA_ARGS__>()

NS_BEGIN(CORE_NAMESPACE)

  template<int Index>
  class TemplateArgument{};

  BUILDER(Attribute, void){
    typedef Builder<TDerived,TDerived,TParentBuilder> builder_type;
    builder_type name(const std::string & name){
      this->element().setAttributeName(name);
      return this->builder();
    }
  };

  BUILDER(AttributeTarget, void){      
    typedef Builder<TDerived,TDerived,TParentBuilder> builder_type;
    template<typename TAttribute, typename... TArgs>
    builder_type attribute(TArgs... args){
      // static_assert(std::is_assignable<NS(CORE_NAMESPACE)::Attribute*, TAttribute*>::value, "expected TAttribute to inherit from Attribute");
      auto attribute = new TAttribute(args...);
      this->element().addAttribute(attribute);
      return this->builder();
    }
  };

  BUILDER(MemberInfo, AttributeTarget){

    typedef Builder<TDerived,TDerived,TParentBuilder> builder_type;
    builder_type memberName(const std::string & memberName){
      MemberInfo & info = this->element();
      info.setName(memberName);
      return this->builder();
    }
    /**
    * \fn  builder_type accessModifier()
    *
    * \brief sets the access modifier for specified member
    *
    * \author  Tobias
    * \date  02.06.2014
    *
    * \return  A builder_type.
    */
    builder_type accessModifier(AccessModifierEnum modifier){
      MemberInfo & info = this->element();
      info.setAccessModifier(modifier);
      return this->builder();
    }
  };


  BUILDER(ArgumentInfo, AttributeTarget){

    typedef Builder<TDerived,TDerived,TParentBuilder> builder_type;
    builder_type argumentName(const std::string & name){
      this->element().setName(name);
      return this->builder();
    }

  };



  template<typename TDerived, typename TParentBuilder, typename TArg, unsigned int ArgIdx>
  struct Builder<TypedArgumentInfo<TArg, ArgIdx>, TDerived, TParentBuilder> : public Builder < MethodInfo, TDerived, TParentBuilder > {

  };



  template<typename TDerived, typename TParentBuilder, typename TMethod>
  struct Builder<TypedMethodInfo<TMethod>, TDerived, TParentBuilder> : public Builder < MethodInfo, TDerived, TParentBuilder > {



  };   



  BUILDER(ScopeInfo, AttributeTarget){

      typedef Builder<TDerived,TDerived,TParentBuilder> builder_type;
    typedef typename TDerived::reflected_type reflected_type;
    /// sets the fully qualified name of the scope
    builder_type name(const std::string & name){
      this->element().setFullyQualifiedName(name);
      return this->builder();
    }
  };
  BUILDER(ConstructorInfo, MemberInfo){

      typedef Builder<TDerived,TDerived,TParentBuilder> builder_type;
  };

  //template<typename TDerived, typename TParentBuilder, typename TClass, typename... TArgs>
  //struct Builder<TypedConstructorInfo<TClass, TArgs...>, TDerived, TParentBuilder> : public Builder < ConstructorInfo, TDerived, TParentBuilder > {
  //    typedef Builder<TDerived,TDerived,TParentBuilder> builder_type;


  //};




  BUILDER(Type, ScopeInfo){

      typedef Builder<TDerived,TDerived,TParentBuilder> builder_type;
    template<typename TMethod>
    Builder<NS(CORE_NAMESPACE)::TypedMethodInfo<TMethod>, TypedMethodInfo<TMethod>, builder_type> method(TMethod method){
      Builder<TypedMethodInfo<TMethod>, TypedMethodInfo<TMethod>, builder_type> builder;
      // save a reference that is deleted
      static auto info = std::shared_ptr<TypedMethodInfo<TMethod>>();
      
//      element().requireMethod(method);
      
      
      if (!info) {
        builder.construct(method);
        info = builder.ptr();
        this->element().Members().add(info.get());
      
        
      }

      builder._parent.value = this->builder();

      return builder;

    }

    builder_type rtti(){
     // name(typeid(reflected_type).name());
      return this->builder();
    }

    /*
    template<typename TClass, typename... TArgs>
    Builder<TypedConstructorInfo<TClass, TArgs...>, TypedConstructorInfo<TClass, TArgs...>, builder_type> constructor(){
      Builder<TypedConstructorInfo<TClass, TArgs...>, TypedConstructorInfo<TClass, TArgs...>, builder_type> builder;
      // save a reference that is deleted
      static auto info = std::shared_ptr<TypedConstructorInfo<TClass, TArgs...>>();
      if (!info) {
        builder.construct();
        info = builder.ptr();
        element().Members().add(info.get());
      }

      builder._parent.value = this->builder();

      return builder;

    }*/



  };

  template<typename TClass, typename ... TArgs>
  struct TypedConstructorInfo{

  };


  template<typename TDerived, typename TParentBuilder, typename TClass>
  struct Builder<TypedTypeInfo<TClass>, TDerived, TParentBuilder> : public Builder < Type, TDerived, TParentBuilder > {
      typedef Builder<TDerived,TDerived,TParentBuilder> builder_type;


    template< typename... TArgs>
    Builder< TypedConstructorInfo< TClass, TArgs...>,  TypedConstructorInfo< TClass, TArgs...>, builder_type> constructor(){
      Builder< TypedConstructorInfo<TClass, TArgs...>,  TypedConstructorInfo<TClass, TArgs...>, builder_type> builder;
      // save a reference that is deleted
      static auto info = std::shared_ptr<TypedConstructorInfo<TClass, TArgs...>>();
      if (!info) {
        builder.construct();
        info = builder.ptr();
        this->element().Members().add(info.get());
      }

      builder._parent.value = this->builder();

      return builder;

    }

  };




  BUILDER(MethodInfo, MemberInfo){

    typedef Builder<TDerived,TDerived,TParentBuilder> builder_type;

      builder_type methodName(const std::string & name){
      this->memberName(name);
      return this->builder();
    }
    Builder<ArgumentInfo, ArgumentInfo, builder_type> arg(int i){
      Builder<ArgumentInfo, ArgumentInfo, builder_type> builder;
      builder.setElement(this->element().argument(i));
      builder._parent.value = this->builder();
      return builder;
    }
    /*
    ArgumentInfo CHILD_BUILDER(arg){

    }*/
    builder_type arg(int i, const std::string & name){
      return this->builder();
    }


  };

  template<typename T>
  Builder<TypedTypeInfo<T>> reflect(){
    return NS(CORE_NAMESPACE)::build<TypedTypeInfo<T>>(TypeInfo<T>::instance());
  }

    template<typename T>
    Builder<TypedTypeInfo<T>> auto_reflect(){
      return reflect<T>().rtti();
    }
  

NS_END(CORE_NAMESPACE)
