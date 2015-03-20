#pragma once
#include <core/core.h>


/**
* \brief this macro returns the Type * instance for TYPENAME.
*
* \param TYPENAME  The typename.
*/
//#define typeof(TYPENAME) NS(CORE_NAMESPACE)::type_of<TYPENAME>()


#define DS_GET_TYPE public: virtual const NS(CORE_NAMESPACE)::Type * getType() const{return NS(CORE_NAMESPACE)::type_of<CurrentClassType>(); }
#define DS_GET_TYPE_DECLARATION public: virtual const NS(CORE_NAMESPACE)::Type * getType() const;
#define DS_GET_TYPE_DEFINITION(TYPE) const NS(CORE_NAMESPACE)::Type * TYPE::getType() const {return NS(CORE_NAMESPACE)::type_of<CurrentClassType>(); } 

#define DS_TYPE_INITIALIZER public: static bool initializeType(){_reflectType(); return true;}private: static void _reflectType()
#define DS_TYPE_INITIALIZER_DECLARATION DS_TYPE_INITIALIZER
#define DS_TYPE_INITIALIZER_DEFINITION(TYPE) void TYPE::_reflectType()

// expects type to be fully qualified 
// \param TYPE  The fully qualified type without leading "::". not specifying the fully qualfied type leads to compiler errors
#define DS_TYPE_HEADER(TYPE) private: typedef ::TYPE CurrentClassType;


/**
* \brief Macro for making an object a typed object. defines a static meta information structure
*        (TypeData) and virtual access methods
*/
#define DS_CLASS(TYPE)                                              \
  DS_TYPE_HEADER(TYPE)                                              \
  DS_GET_TYPE                                                       \
  DS_TYPE_INITIALIZER{                                              \
    NS(CORE_NAMESPACE)::core::reflection::builder::reflect<CurrentClassType>()  \
      ->fullyQualifiedName(DS_INLINE_STRING("::"<<#TYPE))           \
      ->publishHierarchy()                                          \
      ->end();                                                      \
  }                                                                 \
  private:


#define DS_CLASS_DECLARATION(TYPE) DS_TYPE_HEADER(TYPE); DS_GET_TYPE_DECLARATION; DS_TYPE_INITIALIZER_DECLARATION;
#define DS_CLASS_DEFINITION(TYPE) DS_GET_TYPE_DEFINITION(TYPE); DS_TYPE_INITIALIZER_DEFINITION(TYPE)


#ifndef reflect_type
#define reflect_type(NAME) DS_CLASS(NAME) DS_PROPERTY_EXTENSION_METHODS 
#define reflect_type_declaration(NAME) DS_CLASS_DECLARATION(NAME); DS_PROPERTY_EXTENSION_METHODS
#define reflect_type_definition(NAME) DS_CLASS_DEFINITION(NAME)
#define reflect_type_default_definition(NAME) DS_CLASS_DEFINITION(NAME){\
    NS(CORE_NAMESPACE)::core::reflection::builder::reflect<CurrentClassType>()  \
      ->fullyQualifiedName(DS_INLINE_STRING("::"<<#NAME))           \
      ->publishHierarchy()                                          \
      ->end();                                                      \
      }

#endif


#define reflect_superclasses(...) DS_FOREACH(SUBCLASSOF,__VA_ARGS__);



/**
* \brief sets up inheritance hierarchy.
*        Subclass specify SUBCLASSOF in the class declaration so that the hierarchy can be generated
*
* \param TYPE  The parent type.
*/
#define SUBCLASSOF(TYPE)                                                                                                \
private:                                                                                                                \
  STATIC_INITIALIZER(TYPE ## Subclass,{                                                                                 \
  auto unconstCurrentType = const_cast<NS(CORE_NAMESPACE)::Type*>(dynamic_cast<const NS(CORE_NAMESPACE)::Type*>(typeof(CurrentClassType)));   \
  auto unconstSuperType = const_cast<NS(CORE_NAMESPACE)::Type*>(dynamic_cast<const NS(CORE_NAMESPACE)::Type*>(typeof(TYPE)));                 \
  unconstSuperType->successors()|=unconstCurrentType;                                                                 \
})



//////////////////////////////external refelction
/*

#define reflect_begin(TYPE)     \
NS_BEGIN(CORE_NAMESPACE)               \
  META(TYPE);                   \
}                               \
  namespace{                      \
struct ReflectInstance{       \
  typedef TYPE CurrentClassType;\


#define reflect_end   }instance; }
#define _method(NAME) typedef decltype(CurrentClassType::NAME) NAME; reflect_method(NAME);
#define _property(NAME,GETTER,SETTER)                 \
  typedef decltype(CurrentClassType::GETTER) GETTER;    \
  typedef decltype(CurrentClassType::SETTER) SETTER;    \
  reflect_property(NAME,GETTER,SETTER)                  

#define _default_constructor(NAME) DS_CONSTRUCTOR_STRUCT_DEFAULT(NAME)
#define _constructor(NAME,...)  DS_CONSTRUCTOR_STRUCT(NAME,__VA_ARGS__)
  */


/**
* \brief META which set allows instancecreation of type by default constructor
*
* \param TYPE  The type.
*/
//#define META_DEFAULTCONSTRUCTOR(TYPE) META(TYPE)

