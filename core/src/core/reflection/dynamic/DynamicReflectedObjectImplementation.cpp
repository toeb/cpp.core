#include <core/reflection/dynamic/DynamicReflectedObjectImplementation.h>

#include <core/reflection/value/DelegateValue.h>
#include <core/reflection/adapter/PropertyAdapter.h>
#include <hash_set>

#include <core.utility.h>
//#include <core.reflection.builder.h>
NS_USE(CORE_NAMESPACE);

#define DS_OVERRIDE_PROPERTY_GET_METHOD_NAME __override_get_property
#define DS_OVERRIDE_PROPERTY_SET_METHOD_NAME __override_set_property
#define DS_PROPERTY_GET_METHOD_NAME __get_property
#define DS_PROPERTY_SET_METHOD_NAME __set_property
#define DS_PROPERTY_LIST_NAME __list_property_names


  //reflect_type_default_definition(NS(CORE_NAMESPACE)::DynamicReflectedObjectImplementation);

  DynamicReflectedObjectImplementation::DynamicReflectedObjectImplementation(Argument argument):data(argument){

  }
  
  Argument DynamicReflectedObjectImplementation::asArgument(){
    return data;
  }


  std::shared_ptr<DelegateModifiableValue> createValueDelegate(Argument data, const MethodInfo * getter, const MethodInfo* setter,const std::string & name){
    std::function<Argument()> getterFunction;
    std::function<void(Argument)> setterFunction;
    Argument objectHandleCopy = data;
    if(getter){
      getterFunction = [objectHandleCopy,getter,name](){
        std::vector<Argument> args;
        args.push_back(objectHandleCopy.data.get());
        args.push_back(name);          
        return getter->callImplementation(args);
      };
    }
    if(setter){
      setterFunction = [objectHandleCopy,setter,name](Argument arg){
        std::vector<Argument> args;
        args.push_back(objectHandleCopy.data.get());
        args.push_back(name);
        args.push_back(arg);
        setter->callImplementation(args);
      };
    }

    return std::make_shared<DelegateModifiableValue>(getterFunction,setterFunction);
  }



  std::shared_ptr<IModifiableValue> createValueHandle(Argument data, const std::string & name){
    // property was not yet found

    // 1) try to get "magic" __overide_get_property methods

    auto getterInfo = data.type->getMethod(DS_STRINGIFY(DS_OVERRIDE_PROPERTY_GET_METHOD_NAME));
    auto setterInfo = data.type->getMethod(DS_STRINGIFY(DS_OVERRIDE_PROPERTY_SET_METHOD_NAME));

    if(getterInfo||setterInfo){
      return createValueDelegate(data,getterInfo,setterInfo,name);
    }


    // 2) try to get property info 
    auto propertyInfo = data.type->getProperty(name);

    if(propertyInfo){
      return std::make_shared<PropertyAdapter>(data,propertyInfo);
    }


    // 3) try to get the "magic" __get_property, __set_property methods
    getterInfo = data.type->getMethod(DS_STRINGIFY(DS_PROPERTY_GET_METHOD_NAME));
    setterInfo = data.type->getMethod(DS_STRINGIFY(DS_PROPERTY_SET_METHOD_NAME));

    if(getterInfo||setterInfo){
      return createValueDelegate(data,getterInfo,setterInfo,name);
    }

    // nothing found return empty pointer
    return std::shared_ptr<IModifiableValue>();
  }

  std::shared_ptr<IModifiableValue> DynamicReflectedObjectImplementation::getMember(const std::string & name){      
    auto handleIterator = _valueMap.find(name);
    if(handleIterator!=std::end(_valueMap)){
      return handleIterator->second;
    }      
    auto handle = createValueHandle(data,name);
    _valueMap[name]=handle;
    return handle;
  }

  std::shared_ptr<const IModifiableValue> DynamicReflectedObjectImplementation::getMember(const std::string & name)const{      
    auto handleIterator = _valueMap.find(name);
    if(handleIterator!=std::end(_valueMap)){
      return handleIterator->second;
    }      
    auto handle = createValueHandle(data,name);

    _valueMap[name]=handle;
    return handle;
  }


  auto DynamicReflectedObjectImplementation::getPropertyNames()const->MemberList{
    std::vector<std::string> names;
    //1) add all reflected properties
    if(data.type){
      data.type->Properties().foreachElement([&names](const PropertyInfo * member){
        names.push_back(member->getName());
      });
    }

    //2) check if a __list_property_names exists and append those names
    auto listMethod = data.type->getMethod(DS_STRINGIFY(DS_PROPERTY_LIST_NAME));
    if(listMethod){
      std::vector<std::string> dynamicNames = (*listMethod)(data.data.get());
      names = concat(names,dynamicNames);
    }
    
    return names;
  }
  auto DynamicReflectedObjectImplementation::getMethodNames()const->MemberList{
    return MemberList();
  }

