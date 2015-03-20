#include <core/PropertyChangingObject.h>


#include <core/reflection/type/TypeInfo.h>
NS_USE(CORE_NAMESPACE);


Set<PropertyChangedListener*> & PropertyChangingObject::listeners(){return _listeners;}

void PropertyChangingObject::onAfterPropertySet(const char * name){
  raisePropertyChanged(name); 
}

void PropertyChangingObject::raisePropertyChanged(const std::string & propertyname){
  onPropertyChanged(propertyname);
  _listeners.foreachElement([this, &propertyname](PropertyChangedListener* listener){
    listener->onPropertyChanged(this,propertyname);
  });
}
void PropertyChangingObject::onPropertyChanged(const std::string & propertyname){}