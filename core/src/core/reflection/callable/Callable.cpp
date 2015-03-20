#include <core/reflection/callable/Callable.h>

#include <core/reflection/type/TypeInfo.h>
//#include <core/reflection.builder.h>
NS_USE(CORE_NAMESPACE);



const Type* Callable::getType()const{
  return type_of<Callable>();
}
bool Callable::initializeType(){
 /* core::reflection::builder::reflect<Callable>()
    ->fullyQualifiedName(DS_STRINGIFY(::NS(CORE_NAMESPACE)::Callable))
    ->publishHierarchy()
    ->end();
  */return true;
}

//reflect_type_default_definition(NS(CORE_NAMESPACE)::Callable);
/*
const Type * Callable::getType()const{
return ds::type_of<CurrentClassType>();
}
void ds::Callable::_reflectType(){
ds::core::reflection::builder::reflect<CurrentClassType>() 
->fullyQualifiedName((std::function<std::string ()>([&]()->std::string {std::ostringstream stream; stream << "::"<<"NS(CORE_NAMESPACE)::Callable"; return stream.str(); }) () )) 
->publishHierarchy() 
->end(); 
};
*/

Argument Callable::operator()(){
  return callImplementation(std::vector<Argument>());
}

Argument Callable::operator()()const{
  return callImplementation(std::vector<Argument>());
}


Argument Callable::call(){
  return callImplementation(std::vector<Argument>());
}

Argument Callable::call()const{
  return callImplementation(std::vector<Argument>());
}


Argument Callable::callImplementation(const ArgumentList & args){
  return ((const Callable*)this)->callImplementation(args);
};
Argument Callable::callImplementation(const ArgumentList & args)const{    
  return Argument();
}