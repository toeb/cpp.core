#pragma once
#include <core/core.h>

#include <core.reflection.h>

NS_BEGIN(CORE_NAMESPACE)
  class Converter{
    TYPED_OBJECT(Converter);
    SIMPLE_PROPERTY(const Type *, TypeFrom){}
    SIMPLE_PROPERTY(const Type *, TypeTo){}
  public:
    Converter():_TypeFrom(0),_TypeTo(0){}
    virtual bool convert(void * from, void* to)=0;
  };
  template<typename TFrom, typename TTo>
  class TypedConverter : public virtual Converter{
  public:

    bool convert(void * from, void * to){
        return false;
    }
  };
  class ValueConverter : public virtual IModifiableValue, private virtual ObjectObserver{
    TYPED_OBJECT(ValueConverter);
    SIMPLE_PROPERTY(IModifiableValue*, Source){
      if(oldvalue){
        oldvalue->removeObjectObserver(this);
      }
      if(newvalue){
        newvalue->addObjectObserver(this);
      }
    }
  protected:
    void onChange(Observable * value){
      raiseObjectChanged();
    }
    bool retrieveValue(void * ptr)const{
      auto source = getSource();
      if(!source)return false;
      auto sourceType = source->getValueType();
      void * value = sourceType->createInstance().get();
      if(!value)return false;

      return false;
    }
    bool storeValue(const void * ptr){
      auto source = getSource();
      if(!source)return false;

      return false;
    }
  };
NS_END(CORE_NAMESPACE)
