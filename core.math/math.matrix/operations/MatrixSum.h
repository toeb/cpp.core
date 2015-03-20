#pragma once

namespace nspace{

template<typename T,typename Mat>
class MatrixSum{
public:
  static inline void operation(T & result, const Mat & mat){
    result =0;
    for(int i=0; i < mat.rows(); i++){
      for(int j=0; j < mat.cols(); j++){
        result = result + mat(i,j);
      }
    }
  }
};
}