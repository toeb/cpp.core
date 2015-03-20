//#include "DynamicCallable.h"
#include <core/reflection/dynamic/DynamicCallable.h>

#include <core/reflection/dynamic/DynamicCallableImplementation.h>
//#include <core.reflection.builder.h>
NS_USE(CORE_NAMESPACE);


//reflect_type_default_definition(NS(CORE_NAMESPACE)::DynamicCallable);


struct DynamicCallableSmartPointer:public DynamicCallableImplementation{
  std::shared_ptr<Callable> callable;
  DynamicCallableSmartPointer(std::shared_ptr<Callable> callable):callable(callable){}
  bool isValid() const override final{
    return callable->isValid();
  }
  Argument callImplementation(const ArgumentList & args) override final{
    return callable->callImplementation(args);
  }
  Argument callImplementation(const ArgumentList & args) const override final{
    return callable->callImplementation(args);
  }
};

struct DynamicCallableRawPointer:public DynamicCallableImplementation{
  Callable * callable;
  DynamicCallableRawPointer(Callable * callable):callable(callable){}
  bool isValid() const override final{
    return callable->isValid();
  }
  Argument callImplementation(const ArgumentList & args) override final{
    return callable->callImplementation(args);
  }
  Argument callImplementation(const ArgumentList & args) const override final{
    return callable->callImplementation(args);
  }
};



DynamicCallable::DynamicCallable(std::shared_ptr<Callable> callable):implementation(new DynamicCallableSmartPointer(callable)){}
DynamicCallable::DynamicCallable(Callable * callable):implementation(new DynamicCallableRawPointer(callable)){}
DynamicCallable::DynamicCallable(Callable & callable):implementation(new DynamicCallableRawPointer(&callable)){}

DynamicCallable::DynamicCallable(std::shared_ptr<DynamicCallableImplementation> impl):implementation(impl){}
DynamicCallable::DynamicCallable(){}


bool DynamicCallable::isValid()const {return (bool)implementation&&implementation->isValid();}
Argument DynamicCallable::callImplementation(const ArgumentList &args){return implementation->callImplementation(args);}