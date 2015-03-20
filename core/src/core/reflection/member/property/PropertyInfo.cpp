#include <core/reflection/member/property/PropertyInfo.h>


#include <iostream>

using namespace std;
NS_USE(CORE_NAMESPACE);

PropertyInfo::PropertyInfo(const std::string & name, const MethodInfo * getter, const MethodInfo * setter):MemberInfo(name),_SetMethod(setter),_GetMethod(getter),_PropertyType(0){
  const Type *  propertyType=0;
  // get the getters return type set propertyType to it
  if(getter){
    if(getter->Arguments().size()!=0){
      std::cerr << "getter is not a parameterless method. ignoring"<<std::endl;
      _GetMethod=0;
    }else{
      auto type = getter->getReturnType()->removeConst()->removeReference();
      propertyType = type->removeConst()->removeReference();
    }
  }
  
  // get the setter's first argument and get the common root of it and the getters returntype.  
  if(setter){
    if(setter->Arguments().size()!=1){
      std::cerr<<"setter method is not a single parameter method"<<std::endl;          
    }else{
      auto type = setter->Arguments().at(0)->getArgumentType()->removeReference()->removeConst();
      if(propertyType){
        if(propertyType!=type){
          std::cerr<<"getter and setter raw types do not match"<<std::endl;

        }else{
          // find closest relation 

        }
      }else{
        propertyType = type;
      }

    }
  }
  if(propertyType==0){
    //throw exception?  better not because this is a constructor
    std::cerr << "could not determine property type from getter and setter methods"<<std::endl;    
  }
  setPropertyType(propertyType);
}


bool  PropertyInfo::isGettable()const{return getGetMethod()!=0;}
bool  PropertyInfo::isSettable()const{return getSetMethod()!=0;}

Argument  PropertyInfo::get(const void * ptr)const{
  if(!isGettable())return Argument();
  auto getter = getGetMethod();
  
  return (*getter)(ptr);
  //return getter->call(ptr);
}
Argument  PropertyInfo::get(void * ptr)const{
  if(!isGettable())return Argument();
  auto getter = getGetMethod();  
  return (*getter)(ptr);
}
void  PropertyInfo::set(void * ptr, Argument argument)const{
  if(!isSettable())return;
  auto setter = getSetMethod();
  Argument args[2]={ptr, argument};

  (*setter)(args);

}
void  PropertyInfo::set(const void * ptr , Argument argument)const{ 
  if(!isSettable())return;
  auto setter = getSetMethod();
  Argument args[2]={ptr, argument};
  (*setter)(args);
}


