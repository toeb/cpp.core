#include <core/reflection/type/Argument.h>

NS_USE(CORE_NAMESPACE);

bool Argument::isValid()const{return (bool)data;}

const Argument & Argument::VoidArgument(){
  return Void();
}
const Argument & Argument::Void(){
  // create a unique instance for argument
  static std::unique_ptr<Argument> instance(new Argument(std::shared_ptr<void>((void*)new int),0));
  return *instance.get();
}
  Argument::Argument(std::shared_ptr<void> data, const Type * type):data(data),type(type){}
  Argument::Argument():type(0){}
  
  Argument::Argument(const NS(CORE_NAMESPACE)::Void & v){
    data =Void().data;
    type = Void().type;
  }
  Argument::~Argument(){}