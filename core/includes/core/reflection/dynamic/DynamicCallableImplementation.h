#include <core/reflection/dynamic/DynamicCallable.h>

NS_BEGIN(CORE_NAMESPACE)
  
  //
  struct DynamicCallableImplementation : public Callable{
    virtual bool isValid()const=0;
    virtual Argument callImplementation(const ArgumentList &args)=0;
  };
NS_END(CORE_NAMESPACE)
