/**
 * Copyright (C) 2013 Tobias P. Becker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the  rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More information at: https://dslib.assembla.com/
 *
 */
#pragma once
#include <core/core.h>
/*
#include <core/reflection/Type.h>
#include <core/reflection/TypeInfo.h>


#include <core/reflection/PropertyInfo.h>
#include <core/reflection/MethodInfo.h>
#include <core/reflection/TypedMethodInfo.h>
#include <core/reflection/TypedProperty.h>
#include <core/reflection/TypedPropertySetInfo.h>
#include <core/reflection/PropertyAdapter.h>
#include <core/reflection/MethodAdapter.h>
#include <core/PropertyChangingObject.h>
#include <core/patterns/Singleton.h>
*/



/**
 * \brief A macro that defines memberclassname.
 *
 * \param NAME  The name.
 */
#define MEMBERCLASSNAME(NAME) NAME ## MemberClass

/**
 * \brief A macro that defines memberclassinstance.
 *
 * \param NAME  The name.
 */
#define MEMBERCLASSINSTANCE(NAME) ((MEMBERCLASSNAME(NAME)*)MEMBERCLASSNAME(NAME) ::instance().get())

/**
 * \brief A macro that defines propertyclass.
 *
 * \param NAME  The name.
 */
#define PROPERTYCLASS(NAME) MEMBERCLASSNAME(NAME) //NAME##PropertyClass

/**
 * \brief A macro that defines propertyclassinstance.
 *
 * \param NAME  The name.
 */
#define PROPERTYCLASSINSTANCE(NAME) MEMBERCLASSINSTANCE(NAME) //( (PROPERTYCLASS(NAME) * ) PROPERTYCLASS(NAME)::instance())
 

#define DS_REFLECT_PROPERTY(NAME, GETTER, SETTER)/*\
  DS_INITIALIZER_STATIC(NAME##Property){\
  auto type = const_cast<NS(CORE_NAMESPACE)::Type*>(typeof(CurrentClassType));\
  auto getter = type->getMethod(#GETTER);\
  auto setter = type->getMethod(#SETTER);\
  auto info = new NS(CORE_NAMESPACE)::TypedPropertyInfo<CurrentClassType>(#NAME,getter,setter);\
  type->Members()|=info;\
  }*/
  
#define DS_REFLECT_PROPERTY_DEFINITION(...) DS_EXPAND(DS_CONCAT(DS_REFLECT_PROPERTY_DEFINITION_,DS_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__))
  
#define DS_REFLECT_PROPERTY_DEFINITION_3(NAME,GETTER,SETTER) \
  DS_REFLECTION_METHOD(GETTER);\
  DS_REFLECTION_METHOD(SETTER);\
  DS_REFLECT_PROPERTY(NAME,GETTER,SETTER)

#define DS_REFLECT_PROPERTY_DEFINITION_2(NAME,PROPERTY_DEFINITION) PROPERTY_DEFINITION(NAME); \
  DS_REFLECT_PROPERTY_DEFINITION_3(NAME,DS_PROPERTY_GETTER_NAME(NAME),DS_PROPERTY_SETTER_NAME(NAME))

#define DS_REFLECT_PROPERTY_DEFINITION_1(NAME) DS_REFLECT_PROPERTY_DEFINITION_2(NAME, DS_PROPERTY_EXTENDED)

#define extensible_propertyreflect_property(...)  DS_REFLECT_PROPERTY_DEFINITION(__VA_ARGS__) 
#define reflect_method_property(GETTER,SETTER) DS_REFLECT_PROPERTY_DEFINITION_3(GETTER,GETTER,SETTER)




/**
 * \brief sets the propertydisplayname property of the property object created for the property
 *        specified by NAME (.... property)
 *
 * \param NAME  The name.
 * \param DNAME The dname.
 */
#define DISPLAYNAME(NAME, DNAME) \
  STATIC_INITIALIZER(NAME ## DisplayName, {MEMBERCLASSINSTANCE(NAME)->setDisplayName(DNAME); })

/**
 * \brief sets the description of property specified by name.
 *
 * \param NAME          The name.
 * \param DDESCRIPTION  The ddescription.
 */
#define DESCRIPTION(NAME, DDESCRIPTION) \
  STATIC_INITIALIZER(NAME ## Description, {MEMBERCLASSINSTANCE(NAME)->setDescription(DDESCRIPTION); })

/**
 * \brief sets the default value for the property specified by NAME  (make sure the type is
 *        correct) also add the set to default method.
 *
 * \param NAME          The name.
 * \param DEFAULTVALUE  The defaultvalue.
 */
#define DEFAULTVALUE(NAME,DEFAULTVALUE) \
public: \
  void set ## NAME ## ToDefault(){PROPERTYCLASSINSTANCE(NAME)->setToDefaultValue(this); } \
private: \
  STATIC_INITIALIZER(NAME ## DefaultValue, {static auto defaultvalue = DEFAULTVALUE; PROPERTYCLASSINSTANCE(NAME)->setDefaultValue(&defaultvalue); })

/**
 * \brief sets the groupname of the property specified by NAME.
 *
 * \param NAME  The name.
 * \param GROUP The group.
 */
#define GROUPNAME(NAME,GROUP) \
  STATIC_INITIALIZER(NAME ## GroupName,MEMBERCLASSINSTANCE(NAME)->setGroupName(GROUP); )


/**
 * \brief default property macro.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define PROPERTY(TYPE,NAME) typedef TYPE reflect_property(NAME)

/**
 * \brief creates a property for any nonpointer / nonreference field and addutionally allows access
 *        by reference.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define REF_PROP(TYPE,NAME) REFERENCE_PROPERTY(TYPE,NAME); PROPERTY(TYPE,NAME)

/**
 * \brief Defines a reflectable property collection.
 *
 * \param TYPE      The type.
 * \param NAME      The name.
 * \param ONADD     The onadd.
 * \param ONREMOVE  The onremove.
 */




#define DS_REFLECTION_METHOD(NAME)       /*                                                                   \
  DS_INITIALIZER_STATIC(NAME##Method){                                                                                                  \
  static NS(CORE_NAMESPACE)::TypedMethodInfo<decltype(&CurrentClassType::NAME)> info(&CurrentClassType::NAME);                                              \
  info.setName(#NAME);                                                                                      \
  auto type = const_cast<NS(CORE_NAMESPACE)::Type*>(static_cast<const NS(CORE_NAMESPACE)::Type*>(typeof(CurrentClassType)));        \
  type->Members()|=&info;                                                                                   \
  }*/

#ifndef reflect_method
#define reflect_method(NAME) DS_REFLECTION_METHOD(NAME)
#endif

/**
 * \brief creates a public method with the signature void <NAME>() and registers it at its typeinfo
 *        class only TYPED_OBJECT(<ClassName>) needs to be declared in the class were action is
 *        declared because ACTION needs access to Local ClassType function.
 *
 * \param NAME  The name.
 */
#define ACTION(NAME) DS_REFLECTION_METHOD(NAME); public: void NAME()
/*#define ACTION(NAME)                                                                                                  \
private:                                                                                                              \
  typedef CurrentClassType NAME ## ParentClassType;                                                                   \
  class MEMBERCLASSNAME(NAME) : public virtual NS(CORE_NAMESPACE)::MethodInfo {                                                   \
    SINGLETON(MEMBERCLASSNAME(NAME)){                                                                                 \
      setName(# NAME);                                                                                                \
      setOwningType(typeof(NAME ## ParentClassType));                                                                 \
    }                                                                                                                 \
public:                                                                                                               \
    bool unsafeCall(void * object, void * arguments=0, void** returnvalue=0)const{                                    \
      auto typedObject = static_cast<NAME ## ParentClassType*>(object);                                               \
      typedObject->NAME();                                                                                            \
      return true;                                                                                                    \
    }                                                                                                                 \
    bool call(NS(CORE_NAMESPACE)::Object * object, void * arguments=0, void ** returnvalue=0) const {                             \
      auto typedObject = dynamic_cast<NAME ## ParentClassType*>(object);                                              \
      if(!typedObject) return false;                                                                                  \
      typedObject->NAME();                                                                                            \
      return true;                                                                                                    \
    }                                                                                                                 \
  };                                                                                                                  \
  DS_ONCE                                                                                                             \
  {                                                                                                                   \
    auto typeInfo =  const_cast<NS(CORE_NAMESPACE)::Type*>(dynamic_cast<const NS(CORE_NAMESPACE)::Type * >(typeof(NAME ## ParentClassType))); \
    typeInfo->Members().add(MEMBERCLASSINSTANCE(NAME));                                                               \
  };                                                                                                                  \
public:                                                                                                               \
  void NAME()
  */
