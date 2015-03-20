#pragma once
#include <core.math/core.math.h>

NS_BEGIN(CORE_MATH_NAMESPACE)
  namespace statistics{

    /*
    template<typename ScalarType = Real, typename VectorType=VectorND, std::iterator<forward_iterator_tag, VectorType*> SampleIterator = std::vector<VectorType*>::iterator>
    class Statistics{
    public:
    static inline void mean(SampleIterator begin, SampleIterator end, VectorType & x_mean){
    x_mean.setZero();
    int n=0;
    for(SampleIterator it =begin; i != end; it++){
    VectorOperations<VectorType>::sum(x_mean, **it,x_mean);
    ++n;
    }
    if(n==0)return x_mean;
    VectorOperations<VectorType>::multiply(x_mean, ScalarOperations<ScalarType>::reciprocal((ScalarType)i) );
    }
    static inline void covariance(const VectorType & x, MatrixType & covariance){
    assert(covariance.rows()==x.size() && covariance.cols()==x.size());
    VectorType x_mean;

    VectorOperations::outerProduct(x,x,covariance);
    }

    static inline void variance(const VectorType & x, const Vector)
    static inline void covariance(const std::vector<const VectorType*> & samples)
    };
    */
  }
NS_END(CORE_MATH_NAMESPACE)