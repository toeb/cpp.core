#pragma once
#include <core/core.h>

#include <vector>
#include <algorithm>
#include <core/reflection/attribute/Attribute.h>

NS_BEGIN(CORE_NAMESPACE)
  class Type;
  class AttributeTarget {
  public:
    virtual const Type* getType()const;
    static bool initializeType();

    propdef std::vector<const Attribute*> basic_property(Attributes);
    property_reference(Attributes);    
    const Attribute * getAttribute(const std::string & name)const;
    void addAttribute(const Attribute * attribute);


    template<typename TAttribute> const TAttribute * getAttribute()const;
    template<typename Predicate> const Attribute * getAttribute(Predicate predicate)const;
  };
NS_END(CORE_NAMESPACE)



// template implementation
NS_BEGIN(CORE_NAMESPACE)
   template<typename TAttribute>
    const TAttribute * AttributeTarget::getAttribute()const{
      return static_cast<const TAttribute*>( getAttribute([](const Attribute * attribute){return dynamic_cast<const TAttribute*>(attribute);}));
    }

    template<typename Predicate>
    const Attribute * AttributeTarget::getAttribute(Predicate predicate)const{
      auto iterator = std::find_if(std::begin(Attributes()),std::end(Attributes()), predicate);
      if(iterator!=std::end(Attributes()))return *iterator;
      return 0;
    }
NS_END(CORE_NAMESPACE)


  

#define DS_REFLECTION_ATTRIBUTE_CLASS_NAME(LINE) DS_CONCAT(Attribute,LINE)

#define _DS_REFLECTION_ATTRIBUTE(ATTRIBUTE_TYPE,TARGET_ACCESS, LINE,INITIALIZATION)             \
typedef CurrentClassType DS_CONCAT(DS_REFLECTION_ATTRIBUTE_CLASS_NAME(LINE),OwningType);        \
class DS_REFLECTION_ATTRIBUTE_CLASS_NAME(LINE):public ATTRIBUTE_TYPE{                           \
public:                                                                                         \
  DS_REFLECTION_ATTRIBUTE_CLASS_NAME(LINE)(){                                                   \
    {INITIALIZATION;}                                                                           \
    auto type = typeof(DS_CONCAT(DS_REFLECTION_ATTRIBUTE_CLASS_NAME(LINE),OwningType));         \
    auto target = TARGET_ACCESS;                                                                \
    target->addAttribute(this);                                                                 \
  }                                                                                             \
}DS_CONCAT(__instance,DS_REFLECTION_ATTRIBUTE_CLASS_NAME(LINE));

#define DS_REFLECTION_ATTRIBUTE(ATTRIBUTE,TARGET_ACCESS,...) _DS_REFLECTION_ATTRIBUTE(ATTRIBUTE,TARGET_ACCESS,__LINE__,DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__))

#define DS_REFLECTION_MEMBER_ATTRIBUTE(TARGET,ATTRIBUTE_TYPE,...) DS_REFLECTION_ATTRIBUTE(ATTRIBUTE_TYPE, const_cast<NS(CORE_NAMESPACE)::MemberInfo*>(type->getMember(#TARGET));,__VA_ARGS__)
#define DS_REFLECTION_TYPE_ATTRIBUTE(ATTRIBUTE_TYPE, ...) DS_REFLECTION_ATTRIBUTE(ATTRIBUTE_TYPE, const_cast<NS(CORE_NAMESPACE)::Type*>(type),__VA_ARGS__);

#define reflect_member_attribute(TARGET,ATTRIBUTE_TYPE,...) DS_REFLECTION_MEMBER_ATTRIBUTE(TARGET,ATTRIBUTE_TYPE,__VA_ARGS__)
#define reflect_type_attribute(ATTRIBUTE_TYPE, ...) DS_REFLECTION_TYPE_ATTRIBUTE(ATTRIBUTE_TYPE,__VA_ARGS__)
