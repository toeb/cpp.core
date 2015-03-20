#pragma once
#include <core.math/core.math.h>
#include <core.math/matrix/operations/VectorCrossProduct.h>
#include <core.math/matrix.dslib/StaticMatrix.h>

NS_BEGIN(CORE_MATH_NAMESPACE)

//specialization of crossproduct for statixmatrix31
template<typename T>
class VectorCrossProduct <
  matrix::dslib::StaticMatrix<T, 3, 1>,
  matrix::dslib::StaticMatrix<T, 3, 1>,
  matrix::dslib::StaticMatrix < T, 3, 1 >
> {
public:
  typedef matrix::dslib::StaticMatrix<T, 3, 1> matrix_type;
  inline static void operation(matrix_type & cv, const  matrix_type & av, const matrix_type & bv){
    // get data pointers
    const T * a = av.data();
    const T* b = bv.data();
    T * c = cv.data();
    // access elements directly
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
  }
};
NS_END(CORE_MATH_NAMESPACE)