#pragma once

#include <config.h>

namespace nspace{
  template<typename BlockType, typename SourceType>
  class MatrixBlockAssign{
  public:
    static inline void operation(SourceType  & target, const BlockType & source, uint rowOffset, uint colOffset){
      if(source.rows()+rowOffset > target.rows()){
        //ERROR("range exceed matrix dimension");
        return;
      }
      if(source.cols()+colOffset > target.cols()){
        /*        ERROR("range exceed matrix dimension");*/
        return;
      }
      for(uint i=rowOffset; i < rowOffset+source.rows(); i++){
        for(uint j=colOffset; j < colOffset+source.cols(); j++){
          target(i,j) = source(i,j);
        }
      }
    }
  };
}