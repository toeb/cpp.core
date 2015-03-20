#pragma once
#include <core/core.h>

NS_BEGIN(CORE_NAMESPACE)
  /**
  * this class is a helper for the derivable pattern
  * it expects a pointer to it most derived version
  * and allows access to this typed pointer via 
  * derived()
  * This pattern is the template alternative to using virtual methods
  * and allows for base classes to returned fully derived instances of itself
  * 
  * example: 
  * - definition \snippet test.core.template/test.cpp derivable_pattern_definition
  * - usage \snippet test.core.template/test.cpp derivable_pattern_usage
  */
  template<typename Derived>
  class Derivable{
  public:
    typedef Derived derived_type;
    typedef derived_type* derived_ptr;
  private:
    // a field storing the pointer to self in its derived form
    derived_ptr _derived;
  public:
    Derivable(derived_ptr self):_derived(self){}
    /**
    * access to a mutable pointer of the derived type
    */
    inline derived_ptr derived(){return _derived;}
    /*
    * access to a const pointer to the derived type
    */
    inline const derived_ptr derived()const{return _derived;}
  };
NS_END(CORE_NAMESPACE)
