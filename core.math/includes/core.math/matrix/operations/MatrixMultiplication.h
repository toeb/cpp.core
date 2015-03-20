#pragma once
#include <core.math/core.math.h>

NS_BEGIN(CORE_MATH_NAMESPACE)
template<typename T, typename ProductType, typename FactorAType, typename FactorBType>
class MatrixMultiplication{
public:
  static inline void operation(ProductType & product, const FactorAType & a, const FactorBType & b){
    T sum;
    const int RowCount = product.rows();
    const int ColumnCount = product.cols();
    const int InnerDimension = a.cols();
    for (int i = 0; i < RowCount; i++){
      for (int j = 0; j < ColumnCount; j++){
        sum = 0.0;
        //ScalarOperations<T>::Zero(sum);#pragma once

        for (int k = 0; k < InnerDimension; k++){
          sum += a(i, k)*b(k, j);
          /*ScalarOperations<T>::multiply(scalarProduct,a(i,k),b(k,j));
          ScalarOperations<T>::add(sum,sum,scalarProduct);*/
        }
        product(i, j) = sum;
      }
    }
  }
};
NS_END(CORE_MATH_NAMESPACE)