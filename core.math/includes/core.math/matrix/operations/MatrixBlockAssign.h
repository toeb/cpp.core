#pragma once
#include <core.math/core.math.h>
NS_BEGIN(CORE_MATH_NAMESPACE)
template<typename BlockType, typename SourceType>
class MatrixBlockAssign{
public:
  static inline void operation(SourceType  & target, const BlockType & source, size_t rowOffset, size_t colOffset){
    IndexAliasForType(BlockType);
    if (rows(source) + rowOffset > rows(target)){
      //ERROR("range exceed matrix dimension");
      return;
    }
    if (cols(source) + colOffset > cols(target)){
      /*        ERROR("range exceed matrix dimension");*/
      return;
    }
    for (Index i = 0; i < rows(source); i++){
      for (Index j = 0; j < cols(source); j++){
        coefficient(target, i+rowOffset, j+colOffset) =
          coefficient(source, i, j);
      }
    }
  }
};
NS_END(CORE_MATH_NAMESPACE)