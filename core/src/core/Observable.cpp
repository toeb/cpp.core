
#include <core/Observable.h>
#include <exception>

//#include <core/container/Query.h>

NS_USE(CORE_NAMESPACE);

Observable::Observable():_observers(0){}
Observable::~Observable(){if(hasObservers())delete _observers; _observers=0;}
bool Observable::hasObservers()const{
  return _observers!=0;
}
Observable::ObserverList & Observable::observers(){
  if(!_observers)_observers= new ObserverList();
  return * _observers;
}
void Observable::raiseObjectChanged(){
  onChange();
  if(!hasObservers())return;
  for(std::size_t i=0; i < observers().size(); i++){
    observers().at(i)->onChange(this);
  }
  /*
  std::for_each(observers().begin(),observers().end(),[this](ObjectObserver * observer){
  observer->onChange(this);
  });*/
}
void Observable::addObjectObserver(ObjectObserver* oo){
  observers().push_back(oo);
}
void Observable::removeObjectObserver(ObjectObserver * oo){
  if(!hasObservers())return;
  throw std::exception();
  //Query<ObjectObserver*>::remove(observers(),oo);
}
