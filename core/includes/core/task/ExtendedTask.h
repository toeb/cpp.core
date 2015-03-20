#pragma once
#include <core/core.h>

#include <core/task/Task.h>
#include <core/Time.h>
#include <functional>
NS_BEGIN(CORE_NAMESPACE)
  class ExtendedTask :public virtual Task, public virtual PropertyChangingObject{
    extensible_property_class;
    typedef long extensible_property(RunCount);
    typedef Time extensible_property(RunTime);
    typedef Time extensible_property(LastStartTime);
    typedef bool extensible_property(IsRunning);
  private :

  public:
    ExtendedTask();
    virtual void toString(std::ostream & o)const;
  protected:

    void onBeforeRun();
    void onAfterRun();
  };
NS_END(CORE_NAMESPACE)
