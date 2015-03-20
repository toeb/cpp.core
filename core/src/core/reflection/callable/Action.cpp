#include <core/reflection/callable/Action.h>


NS(CORE_NAMESPACE)::Argument NS(CORE_NAMESPACE)::Action::callImplementation(const ArgumentList & args){
  if(args.size()>0)return Argument();
  execute();
  return Argument::VoidArgument();
}
void NS(CORE_NAMESPACE)::Action::execute(){
  executeAction();
}