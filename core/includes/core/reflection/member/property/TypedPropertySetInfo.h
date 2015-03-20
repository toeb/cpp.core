#ifdef HI
#pragma once
#include <core/core.h>

#include <core/reflection/member/property/PropertySetInfo.h>
#include <core/reflection/member/property/TypedPropertyInfo.h>

NS_BEGIN(CORE_NAMESPACE)
  template<typename OwningClass, typename ValueType>
  class TypedPropertySetInfo:public virtual TypedProperty<OwningClass, Set<ValueType> >, public virtual PropertySetInfo{
    TYPED_OBJECT(TypedPropertySetInfo);
  public:
    virtual Set<ValueType> & getMutableSetReference( OwningClass * object )const=0;
    virtual const Set<ValueType> & getConstSetReference(const OwningClass * object )const=0;
    virtual size_t getElementCount(void * ptr)const;

    TypedPropertySetInfo();
    // TypedProperty Implementation
    void setTypedValue(OwningClass * object, Set<ValueType>  value)const;
    Set<ValueType> getTypedValue(const OwningClass * object)const;

    bool addObserver(void * ptr,ObjectObserver* observer)const;
    bool removeObserver(void * ptr,ObjectObserver* observer)const;
    const Set<ValueType> * getConstTypedPointer(const OwningClass * object)const;
    Set<ValueType> * getMutableTypedPointer(OwningClass * object)const;

    bool addTypedElement(OwningClass & object, ValueType & value)const;
    bool removeTypedElement(OwningClass & object, const ValueType & value)const;

    bool addElement(void * object, void*value)const;
    bool removeElement(void * object, const void*value)const;
    bool setTypedElement(OwningClass * object, size_t i, const ValueType * value )const;
    bool getTypedElement(const OwningClass * object, size_t i, ValueType * value )const;
    // sets the value of the property set at i
    bool setElement(void * object, size_t i, const void * value)const;
    // gets the value of the property set at i
    bool getElement(const void * object, size_t i, void * value)const;
    bool deserializeElement(void * ptr, size_t i, std::istream & in)const;
    bool serializeElement(void * ptr,size_t i,  std::ostream & out)const;
  };

  // Implementation

  template<typename OwningClass, typename ValueType>
  TypedPropertySetInfo<OwningClass,ValueType>::TypedPropertySetInfo(){
    setElementType(typeof(ValueType));
    setPropertyType(typeof(Set<ValueType>));
    setOwningType(typeof(OwningClass));
  }

  template<typename OwningClass, typename ValueType>
  void  TypedPropertySetInfo<OwningClass,ValueType>::setTypedValue(OwningClass * object, Set<ValueType>  value)const{
    getMutableSetReference(object)=value;
  }
  template<typename OwningClass, typename ValueType>
  Set<ValueType>  TypedPropertySetInfo<OwningClass,ValueType>::getTypedValue(const OwningClass * object)const{
    return getConstSetReference(object);
  }

  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::addObserver(void  * object,ObjectObserver* observer)const{
    auto typedObject = dynamic_cast<OwningClass*>(object);
    if(!typedObject)return false;
    Set<ValueType> &  theset = getMutableSetReference(typedObject);
    theset.addObjectObserver(observer);
    return true;
  }
  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::removeObserver(void  * ptr,ObjectObserver* observer)const{
    auto object = dynamic_cast<OwningClass*>(ptr);
    if(!object)return false;
    Set<ValueType> &  theset = getMutableSetReference(object);
    theset.removeObjectObserver(observer);
    return true;
  }
  template<typename OwningClass, typename ValueType>
  const Set<ValueType> *  TypedPropertySetInfo<OwningClass,ValueType>::getConstTypedPointer(const OwningClass * object)const{
    return &getConstSetReference(object);
  }
  template<typename OwningClass, typename ValueType>
  Set<ValueType> *  TypedPropertySetInfo<OwningClass,ValueType>::getMutableTypedPointer(OwningClass * object)const{
    return &getMutableSetReference(object);
  }

  template<typename OwningClass, typename ValueType>
  size_t  TypedPropertySetInfo<OwningClass,ValueType>::getElementCount(void  * ptr)const{
    auto object = dynamic_cast<OwningClass*>(reinterpret_cast<Object*>(ptr));
    if(!object)return false;
    return getConstSetReference(object).size();
  }

  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::addTypedElement(OwningClass & object, ValueType & value)const{
    return getMutableSetReference(&object).add(value);
  }
  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::removeTypedElement(OwningClass & object, const ValueType & value)const{
    return getMutableSetReference(&object).remove(value);
  }

  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::addElement(void * object, void*value)const{
    auto typedObject = static_cast<OwningClass*>(object);
    auto typedValue = reinterpret_cast<ValueType*>(value);
    return addTypedElement(*typedObject,*typedValue);
  }
  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::removeElement(void * object, const void*value)const{
    auto typedObject = static_cast<OwningClass*>(object);
    auto typedValue = reinterpret_cast<const ValueType*>(value);
    return removeTypedElement(*typedObject,*typedValue);
  }
  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::setTypedElement(OwningClass * object, size_t i, const ValueType * value )const{
    Set<ValueType> & propertyset = getMutableSetReference(object);
    if(i>=propertyset.size())return false;
    return propertyset.setValue(i,*value);
  }
  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::getTypedElement(const OwningClass * object, size_t i, ValueType * value )const{
    const Set<ValueType> & propertyset = getConstSetReference(object);
    if(i>=propertyset.size())return false;
    return propertyset.getValue(i,*value);
  }
  template<typename OwningClass, typename ValueType>
  // sets the value of the property set at i
  bool  TypedPropertySetInfo<OwningClass,ValueType>::setElement(void  * object, size_t i, const void * value)const{
    auto typedObject = static_cast<OwningClass*>(object);
    auto typedValue = reinterpret_cast<const ValueType*>(value);
    if(!typedObject)return false;
    return setTypedElement(typedObject,i,typedValue);
  }
  // gets the value of the property set at i
  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::getElement(const void * object, size_t i, void * value)const{
    auto typedObject = static_cast<const OwningClass*>(object);
    auto typedValue = reinterpret_cast<ValueType*>(value);
    if(!typedObject)return false;
    return getTypedElement(typedObject,i,typedValue);
  }
  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::deserializeElement(void  * object, size_t i, std::istream & in)const{
    OwningClass * owningClass = static_cast<OwningClass*>(object);
    if(!owningClass)return false;
    ValueType value;
    if(getCustomDeserializer()){
      if(!(getCustomDeserializer()->deserialize(&value,in)))return false;
    }else{
      if(!Deserializer<ValueType>::deserialize(&value,in))return false;
    }

    setTypedElement(owningClass,i,&value);
    return true;
  }
  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::serializeElement(void * object,size_t i,  std::ostream & out)const{
    OwningClass * owningClass = static_cast<OwningClass*>(object);
    if(!owningClass)return false;
    ValueType value;
    getTypedElement(owningClass,i,&value);
    if(getCustomSerializer()){
      if(!(getCustomSerializer()->serialize(out,&value)))return false;
    }else{
      if(!Serializer<ValueType>::serialize(out,&value))return false;
    }
    return true;
  }
NS_END(CORE_NAMESPACE)

#endif