#ifdef HI
#pragma once
#include <core/core.h>
#include <core/reflection/member/property/PropertyInfo.h>

NS_BEGIN(CORE_NAMESPACE)
  // describes a class property which is a set /collection
  class PropertySetInfo : public virtual PropertyInfo{
    //TYPED_OBJECT(PropertySetInfo);

    typedef const Type* basic_property(ElementType)

    // custom serializer
    typedef CustomSerializer* basic_property(CustomElementSerializer)
    // custom deserializer
    typedef CustomDeserializer* basic_property(CustomElementDeserializer)
    
    typedef bool basic_property(IsPointerCollection)


  public:
    PropertySetInfo():
      _ElementType(0),
      _CustomElementSerializer(0),
      _CustomElementDeserializer(0),
      _IsPointerCollection(false)
    {}
    // sets the value of the property set at i
    virtual bool setElement(void * object, size_t i, const void * value)const=0;
    // gets the value of the property set at i
    virtual bool getElement(const void * object, size_t i, void * value)const=0;
    
    virtual bool addElement(void * object, void*value)const=0;
    virtual bool removeElement(void * object, const void*value)const=0;

    virtual bool deserializeElement(void * object, size_t i,std::istream & in)const=0;
    virtual bool serializeElement(void * object, size_t i,std::ostream & out)const=0;

    virtual size_t getElementCount(void * object)const=0;

    template<typename ObjectType, typename T> bool get(T& value, size_t i, const ObjectType & object)const{ return getValue(&object,i,&value); }
    template<typename ObjectType, typename T> bool set(const T& value, size_t i, ObjectType & object)const{ return setValue(&object,i,&value); }
  };
  
NS_END(CORE_NAMESPACE)

#endif