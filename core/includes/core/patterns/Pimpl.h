#pragma once
#include <core/core.h>
#include <memory>
#include <core.shim.h>
NS_BEGIN(CORE_NAMESPACE)
/// defines the private implementation for the Pimpl pattern
#define PIMPL(...) template<> struct Pimpl<__VA_ARGS__>::Implementation

  /// Private Implementation template class
  /// classes wanting to use the private implementation pattern
  /// can protected inherit this class (using the classname itself as the template param)
  /// ie class A : protected Pimpl<A>{...}
  /// The implementation struct needs to be specialized for each classs
  /// you can use the PIMPL macro 
  template<typename T>
  class Pimpl {
  protected:
    struct Implementation{};
    Pimpl(){ self = std::make_unique<Implementation>(); };
    std::unique_ptr<Implementation> self;
  };

NS_END(CORE_NAMESPACE)

