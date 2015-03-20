#pragma once
#include <core/core.h>
#include <core/values/values.h>


#include <core/events/Event.h>
#include <core/events/EventArgs.h>

#include <core/values/ISource.h>

NS_BEGIN(CORE_VALUES_NAMESPACE)


class IObservableSource : public virtual ISource, public virtual IObservableConnectable{
public:
  virtual event & OnBeforeProduced() = 0;
  virtual event & OnAfterProduced() = 0;
  virtual  event  &OnValueChanged() = 0;

};

/// a source which has fires events
class ObservableSource : public virtual IObservableSource{
private:

  NS(CORE_EVENTS_NAMESPACE)::Event _beforeProduced;
  NS(CORE_EVENTS_NAMESPACE)::Event _onProduced;
  NS(CORE_EVENTS_NAMESPACE)::Event _onValueChanged;

protected:
  auto raiseOnValueChanged(::core::any v)->::core::any{ return _onValueChanged(v); };

  virtual value_holder produceValue() = 0;
public:

  event & OnValueChanged()override{ return _onValueChanged; };
  event & OnBeforeProduced()override{ return _beforeProduced; }
  event & OnAfterProduced()override{ return _onProduced; }

  virtual value_holder produce()override{
    _beforeProduced(NS(CORE_EVENTS_NAMESPACE)::EventArgs(this, value_holder()));
    auto val = produceValue();
    _onProduced(NS(CORE_EVENTS_NAMESPACE)::EventArgs(this, val));
    return val;
  }



};
NS_END(CORE_VALUES_NAMESPACE)
