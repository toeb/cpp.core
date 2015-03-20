#pragma once
namespace nspace{
  template<typename T, typename SourceType>
  class MatrixCopyToPointer{
  public:
    static inline void operation(T * data, const SourceType & source){
      //slow implementation copies every element
      for(uint i=0; i < source.size(); i++){
        data[i] = source(i);
      }
    }
  };
}