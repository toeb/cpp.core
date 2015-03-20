#pragma once
#include <core/core.h>
#include <core/values/values.h>

#include <core/values/IValueVersion.h>
NS_BEGIN(CORE_VALUES_NAMESPACE)


  class IntValueVersion : public IValueVersion{
  public:
    IntValueVersion() :_version(0){}
    virtual void update(IConnectable & connector)override{ _version++; }
    virtual int compare(const IValueVersion & rhs)const override{
      const IntValueVersion * rhs_ptr = dynamic_cast<const IntValueVersion*>(&rhs);
      if (!rhs_ptr)return std::numeric_limits<int>::min();
      return rhs_ptr->_version - _version;
    }

  private:
    int _version;
  };


NS_END(CORE_VALUES_NAMESPACE)
