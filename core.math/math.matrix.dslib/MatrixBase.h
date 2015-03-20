#pragma once
#include <math/Matrix.h>
namespace nspace{
  namespace matrix2{
    template<typename T, typename MatrixSubclass>
    class MatrixBase : public Matrix{
    private:
      MatrixSubclass & _this;
    protected:
      T * _data;
    public:
      MatrixBase():_data(0),_this(*static_cast<MatrixSubclass>(this)){}

      inline T * data(){return _data;}
      inline const T* data()const{return _data;}
    };
  }
}