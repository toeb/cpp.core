#pragma once
#include <core/core.h>

#include <functional>
#include <algorithm>
#include <vector>
NS_BEGIN(CORE_NAMESPACE)
  /**
  * \brief this class is a base class for the composite pattern.
  *
  * \author Tobi
  * \date 13.07.2012
  */
  template<class T>
  class IComposite{
  public:
    friend IComposite<T>& operator<< (IComposite<T> & composite, T* component){
      composite.addComponent(component);
      return composite;
    }
    virtual bool isEmpty()const=0;
    virtual const std::vector<T*> & components()const=0;
    virtual void foreachComponent(std::function<void(T*)> action)=0;
    virtual void foreachComponent(std::function<void(T*)> action) const=0;
    virtual bool addComponent(T* component)=0;
    virtual void removeComponent(T* component)=0;
  };
  template<class T>
  class Composite : public virtual IComposite<T>{
  private:
    std::vector<T*>  _components;

  public:
    Composite(){
    }
    ~Composite(){
    }

    bool isEmpty()const {return _components.empty();}

    inline const std::vector<T*> & components()const{return _components;}
    void foreachComponent(std::function<void(T*)> action){
      for_each(_components.begin(), _components.end(), action);
    }
    void foreachComponent(std::function<void(T*)> action) const{
      for_each(_components.begin(), _components.end(), action);
    }
    bool addComponent(T* component){
      if(reinterpret_cast<long>(component)== reinterpret_cast<long>(this))return false;
      if(!acceptsComponent(component)){
        onComponentRejected(component);
        return false;
      }
      onBeforeComponentAdded(component);
      _components.push_back(component);
      onAfterComponentAdded(component);
      return true;
    }
    void removeComponent(T* component){
      onBeforeComponentAdded(component);
      remove(_components.begin(), _components.end(),component);
      onAfterComponentAdded(component);
    }
  protected:
    //extension points;
    virtual bool acceptsComponent(T* component){return true;}
    virtual void onComponentRejected(T* component){}
    virtual void onBeforeComponentAdded(T* component){}
    virtual void onAfterComponentAdded(T* component){}
    virtual void onBeforeComponentRemoved(T* component){}
    virtual void onAfterComponentRemoved(T* component){}
  };
NS_END(CORE_NAMESPACE)
