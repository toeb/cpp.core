#pragma once
#include <core/core.h>

#include <core/NamedObject.h>
#include <core/PropertyChangingObject.h>

NS_BEGIN(CORE_NAMESPACE)
  /**
  * represents a task.  The Run Method needs to be implemented
  */
  class ITaskRunner;

  class ITask: public virtual NamedObject, public virtual PropertyChangingObject{
    extensible_property_class;
    //reflect_type(NS(CORE_NAMESPACE)::ITask);
    typedef ITaskRunner* extensible_property(TaskRunner);
    typedef unsigned int extensible_property(NumberOfTimes);
  public:
    ITask():_TaskRunner(0),_NumberOfTimes(0){}
    // run may do anything.  if the task ongoing you need to make sure, that the implementation of run is fast
    // especially if the task is to be real time
    virtual void run()=0;
  };
NS_END(CORE_NAMESPACE)

