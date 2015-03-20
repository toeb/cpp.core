#pragma once
#include <config.h>
namespace nspace{

  

  template<typename TAssignee, typename TValue>
  class MatrixElementAssignment{
  public:
    static inline bool operation(TAssignee & assignee, uint i, uint j, const TValue & value){
      assignee(i,j)=value;
      return true;
    }
  };

  //specialization
  template<typename TValue>
  class MatrixElementAssignment<float,TValue>{
  public:
    static inline bool operation(float & assignee, uint i, uint j, const TValue & value){
      if(i!=0&&j!=0)return false;
      assignee = value;
      return true;
    }
  };

  template<typename TValue>
  class MatrixElementAssignment<double,TValue>{
  public:
    static inline bool operation(double & assignee, uint i, uint j, const TValue & value){
      if(i!=0&&j!=0)return false;
      assignee = value;
      return true;
    }
  };
}