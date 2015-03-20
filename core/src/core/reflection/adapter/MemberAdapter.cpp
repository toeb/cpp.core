#include <core/reflection/adapter/MemberAdapter.h>

NS_USE(CORE_NAMESPACE);

//#include <core.reflection.builder.h>

//reflect_type_default_definition(NS(CORE_NAMESPACE)::MemberAdapter);

MemberAdapter::MemberAdapter(){}
MemberAdapter::MemberAdapter(Argument owner):_Owner(owner){
  notify_after_set(Owner);
}


auto MemberAdapter::before_set(Owner){
  return BeforeSetAction::Accept;
}
auto MemberAdapter::after_set(Owner){

}
