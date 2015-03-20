#pragma once
#include <core/core.h>

#include <core/reflection/callable/Action.h>

NS_BEGIN(CORE_NAMESPACE)
  template<typename T=std::function<void()> >
  class DelegateAction : public virtual Action{
    reflect_type(DelegateAction)
  private:
    T _callback;
  public:
    DelegateAction(T callback):_callback(callback){}
  protected:
    void executeAction(){
      _callback();
    };
  };
NS_END(CORE_NAMESPACE)
