#pragma once
#include <core/core.h>


#include <vector>
#include <functional>

NS_BEGIN(CORE_NAMESPACE)

  // TODO REWORK OBSERVABLE OBJECTS for performance
  class Observable;
  class ObjectObserver{
  protected:
    virtual void onChange(Observable * sender)=0;
    friend class Observable;
  };

  template <typename T=std::function<void (Observable*)> >
  class DelegateObjectObserver:public ObjectObserver{
    T _callback;
  public:
    DelegateObjectObserver(T callback):_callback(callback){
    }
    void onChange(Observable * sender){
      _callback(sender);
    }
  };

  class Observable{
    typedef std::vector<ObjectObserver*>   ObserverList;
  private:
    ObserverList * _observers;
  public:
    Observable();
    virtual ~Observable();
    bool hasObservers()const;
  protected:
    ObserverList & observers();
    void raiseObjectChanged();
    virtual void onChange(){}
  public:
    void addObjectObserver(ObjectObserver* oo);
    void removeObjectObserver(ObjectObserver * oo);
  };
NS_END(CORE_NAMESPACE)

