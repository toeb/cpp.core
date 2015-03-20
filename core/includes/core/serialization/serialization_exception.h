#pragma once
#include <core/core.h>
#include <core/serialization/serialization_config.h>
#include <exception>
NS_BEGIN(CORE_SERIALIZATION_NAMESPACE)


struct serialization_exception : std::exception{
  virtual const char * what()const override{
    return "failed to serialize";
  }
};
NS_END(CORE_SERIALIZATION_NAMESPACE)
