#pragma once
#include <queue>
#include <config.h>
namespace nspace{
  //interface for calulating an average.
  class IAverage{
  public:
    // addsample method should be called for adding a new value
    virtual void addSample(Real value)=0;
    // calculate method should return the average which is to be caluclated
    virtual Real calculate()=0;
  };
}