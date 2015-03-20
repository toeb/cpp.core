#pragma once
#include <core/core.h>
#include <core.reflection.h>
#include <core/PropertyChangingObject.h>
#include <core.logging.h>
NS_BEGIN(CORE_NAMESPACE)
  
class ProgressReporter : public virtual PropertyChangingObject, public virtual Log{
  //reflect_type(NS(CORE_NAMESPACE)::ProgressReporter);
  extensible_property_class;

  typedef double extensible_property(NumberOfNotifications);
  auto after_set(NumberOfNotifications);
  typedef double extensible_property(TotalProgress);
  auto after_set(TotalProgress);  
  typedef double extensible_property(Progress);
  typedef int    extensible_property(ProgressLogLevel);
  typedef double extensible_property(NotificationInterval);
  typedef bool   extensible_property(LogProgress);
  
public:
  ProgressReporter();
  double percent()const;
  double quotient()const;
private:
  double _lastNotification;
protected:
  void resetProgress(double totalProgress);
  void resetProgress();
  void incrementProgress(double value);
  void reportProgress(double value);
  
};

NS_END(CORE_NAMESPACE)
