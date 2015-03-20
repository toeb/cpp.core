#pragma once
#include <core/core.h> 
#include <core.property.h>
#include <core/reflection/type/Argument.h>
#include <core/reflection/callable/ArgumentInfo.h>
#include <core/reflection/callable/Callable.h>
#include <memory>
#include <vector>
NS_BEGIN(CORE_NAMESPACE)
  // callable info represents any callable 
  // a callabe is characterized as having the (...) call operator
  // known subclasses are MethodInfo, StaticMethodInfo, ...
  class CallableInfo : public Callable{
  public:
    static bool initializeType();

    bool isValid()const;

    typedef std::shared_ptr<ArgumentInfo> argument_ptr;
    typedef std::shared_ptr<const ArgumentInfo> const_argument_ptr;
    
    // contains the Argument info for all arguments
    propdef std::vector<argument_ptr> basic_property(Arguments);
    property_reference(Arguments);

    // returns a pointer to the argument at index i
    argument_ptr argument(unsigned int i);
    // returns a const pointer to the argument at index i
    const_argument_ptr argument (unsigned int i)const;

    // returns the returntype of the call
    propdef const Type * basic_property(ReturnType);

    // returns true if call is a const call (can only be true for class method)
    propdef bool basic_property(IsConst);

    // returns true if callable is static (free methods and static class members)
    propdef bool basic_property(IsStatic);

    // if callable is a function call to 3 ints the argument signature will be
    // (int,int,int)
    propdef std::string basic_property(ArgumentSignature);
    // if callable is a function call to 3 ints and a string the fully qualified argument signature will be
    // (::int,::int,::int,::std::string)    
    propdef std::string basic_property(FullyQualifiedArgumentSignature);
  };
NS_END(CORE_NAMESPACE)
