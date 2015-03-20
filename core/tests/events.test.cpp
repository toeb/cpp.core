#include <core.testing.h>
#include <core.events.h>
NS_USE(CORE_NAMESPACE)::events;
UNITTEST(EventTest){
  int res = 0;
  Event uut;
  auto handler = uut += [&](int arg){res = arg; };
  if (uut)uut(33);
  ASSERT(res == 33);
}

UNITTEST(ShouldAddEventListener){
  Event uut;
  auto handler = uut += [&](int arg){};
  ASSERT(handler);
  ASSERT(uut.handlers().size() == 1);
}

UNITTEST(ShouldRemoveEventHandler){
  Event uut;
  auto handler = uut += [](int arg){};
  uut.removeHandler(handler);
  ASSERT(uut.handlers().size() == 0);
}