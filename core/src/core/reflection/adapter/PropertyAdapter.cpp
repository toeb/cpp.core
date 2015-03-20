#include <core/reflection/adapter/PropertyAdapter.h>

NS_USE(CORE_NAMESPACE);

void PropertyAdapter::onBeforeOwnerChanged(){
}
void PropertyAdapter::onOwnerChanged(){
}
void PropertyAdapter::onPropertyInfoChanged(){
  if(!getPropertyInfo())return ;
  setValueType(getPropertyInfo()->getPropertyType());
}
void PropertyAdapter::onChange(Observable * observable){
  raiseObjectChanged();
}
void PropertyAdapter::onBeforePropertyInfoChanged(){
}
PropertyAdapter::~PropertyAdapter(){
}
PropertyAdapter:: PropertyAdapter():_PropertyInfo(0){
}
PropertyAdapter::PropertyAdapter(Argument object, const std::string & name):
  MemberAdapter(object),
  IModifiableValue(object.type->getProperty(name)->getPropertyType()),
  _PropertyInfo(object.type->getProperty(name))
{

}
PropertyAdapter::PropertyAdapter(Argument object, const PropertyInfo * info):
  MemberAdapter(object),
  IModifiableValue(info->getPropertyType()),_PropertyInfo(info)
{

}
Argument PropertyAdapter::retrieveValue()const{
 return getPropertyInfo()->get(getOwner().data.get());
}
bool PropertyAdapter::storeValue(Argument argument){
  getPropertyInfo()->set(getOwner().data.get(),argument);
  return true;
}
