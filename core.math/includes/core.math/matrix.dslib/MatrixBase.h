#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/Matrix.h>
NS_BEGIN(CORE_MATH_NAMESPACE, matrix, dslib)

template<typename T, typename MatrixSubclass>
class MatrixBase : public Matrix<T>{
private:
  MatrixSubclass & _this;
protected:
  T * _data;
public:
  MatrixBase() :_data(0), _this(*static_cast<MatrixSubclass>(this)){}

  inline T * data(){ return _data; }
  inline const T* data()const{ return _data; }
};
NS_END(CORE_MATH_NAMESPACE, matrix, dslib)