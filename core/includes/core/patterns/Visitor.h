#pragma once
#include <core/core.h>

#include <core/Object.h>

NS_BEGIN(CORE_NAMESPACE)
  class Visitor{

  };
  template<typename T>
  class TypedVisitor : public virtual Visitor{
  public:
    virtual void visit(T & t)=0;
  };

  template<class DerivedVisitable>
  class Visitable{
  public:
    bool accept(Visitor & v){
      TypedVisitor<DerivedVisitable> * typedVisitor = dynamic_cast<  TypedVisitor<DerivedVisitable> *>(&v);
      if(!typedVisitor)return false;
      typedVisitor->visit(*static_cast<DerivedVisitable*>(this));
      return true;
    }
  };
NS_END(CORE_NAMESPACE)
