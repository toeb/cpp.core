#pragma once
#include <core/core.h>
#include <core/values/values.h>

#include <core/values/ObservableSink.h>
#include <core/values/ObservableSource.h>
NS_BEGIN(CORE_VALUES_NAMESPACE)

class IObservableValue : public virtual IObservableSource, public virtual IObservableSink, public virtual IValue{
};
class ObservableValue :
  public virtual IObservableValue,
  public virtual ObservableSource,
  public virtual ObservableSink{
public:
protected:

private:

};
NS_END(CORE_VALUES_NAMESPACE)
