#pragma once
#include <core/core.h>
#include <core/values/values.h>
#include <core/values/IConnector.h>
#include <core/any.h>
NS_BEGIN(CORE_VALUES_NAMESPACE)


  //the source is a connector which can produce data
  class ISource : public virtual IConnector{
  public:
    virtual value_holder produce() = 0;
    //operator typename std::enable_if<std::is_base_of<IConnectable, T>::value, T>::type(){
   
    // template<typename T> operator T(){  return produce().as<T>();}
    template<typename T> T produce(){ return produce().as<T>(); }

    //operator any(){return produce();}

    template<typename... TArgs>
    any operator()(TArgs && ... args){
      return produce()(::std::move(args)...);
    };
   
  };
NS_END(CORE_VALUES_NAMESPACE)
