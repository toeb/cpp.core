#pragma once
#include <core/core.h>
#include <core/values/values.h>

#include <core/values/ISink.h>
#include <core/events/Event.h>
#include <core/events/EventArgs.h>

NS_BEGIN(CORE_VALUES_NAMESPACE)

class IObservableSink : public virtual ISink, public virtual IObservableConnectable{
public:

  virtual event & OnAfterConsumed() = 0;
  virtual event & OnBeforeConsumed() = 0;
};
class ObservableSink : public virtual IObservableSink{
  private:
    NS(CORE_EVENTS_NAMESPACE)::Event _onConsumed;
    NS(CORE_EVENTS_NAMESPACE)::Event _beforeConsume;
  protected:
    virtual void consumeValue(value_holder arg) = 0;
  public:
    event & OnAfterConsumed()override{ return _onConsumed; }
    event & OnBeforeConsumed()override{ return _beforeConsume; }
    virtual void consume(value_holder arg)override{
      _beforeConsume(arg);
      consumeValue(arg);
      _onConsumed(arg);
    }


  };
NS_END(CORE_VALUES_NAMESPACE)
