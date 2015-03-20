#pragma once
#include <core/core.h>
#include <core.reflection.h>
#include <core.logging.h>

NS_BEGIN(CORE_NAMESPACE)
  class Binding : public virtual PropertyChangingObject, public virtual Log, public virtual ObjectObserver{
    reflect_type(Binding);
    /*   

    OBJECTPOINTERPROPERTY(IModifiableValue,Source){
      if(oldvalue){
        oldvalue->removeObjectObserver(this);
      }
      if(newvalue){
        newvalue->addObjectObserver(this);
      }
      auto sink = getSink();
      if(!sink)return;
      if(newvalue && newvalue->getValueType()!=  sink->getValueType()){
        cancel = true;
        logWarning("trying to bind different value types!");
        return;
      }
    }
    void onChange(Observable * observable){
      //debugInfo("Source object changed");
      update();
    }
    OBJECTPOINTERPROPERTY(IModifiableValue,Sink){
      auto source = getSource();
      if(!source)return;
      if(newvalue->getValueType()!=  source->getValueType()){
        cancel = true;
        logWarning("trying to bind different value types!");
        return;
      }

      if(newvalue)setBindingType(newvalue->getValueType());
    }
    SIMPLE_PROPERTY(const Type*, BindingType){
      debugInfo("Binding type changed to "<<newvalue->getName());
    }

    PROPERTY(bool, IsUpdating){}

  public:
    virtual bool update(){
      if(getIsUpdating()){
        //debugWarning("already updating - wait for finish");
        return false;
      }
      setIsUpdating(true);
      auto source = getSource();
      auto sink = getSink();
      if(!(sink&&source))return false;
      auto type = getBindingType();
      auto instance = type->createInstance().get();
      if(!instance){
        logError("Type does not allow instanciation");
      }
      if(!source->getByPointer(instance)){
        logError("Source was not readable");
      }
      if(!sink->setByPointer(instance)){
        logError("Sink was not writable");
      }
      //type->deleteInstance(instance.get());
      //instance = 0;
      setIsUpdating(false);
      return true;
    }
    bool isValid(){
      if(!getSource())return false;
      if(!getSink())return false;
      return true;
    }
    static Binding * create(Object * a,  const std::string &  propertyNameA, Object * b, const std::string & propertyNameB){
      auto infoA = a->getType()->getProperty(propertyNameA);
      auto infoB = b->getType()->getProperty(propertyNameB);
      return create(a,infoA,b,infoB);
    }
    static Binding * create(Object * a, const PropertyInfo * infoA, Object * b, const PropertyInfo*infoB){
      auto valueA = new PropertyAdapter(a,infoA);
      auto valueB = new PropertyAdapter(b,infoB);
      return create(valueA,valueB);
    }
    static Binding * create(IModifiableValue * a, IModifiableValue * b){
      auto binding = new Binding();
      binding->setSource(a);
      binding->setSink(b);
      return binding;
    }
    //HACK: private default constructor causes errors for typed objects
    Binding():_Source(0),_Sink(0),_BindingType(0),_IsUpdating(false){
    }
  private:*/
    
  };
NS_END(CORE_NAMESPACE)

