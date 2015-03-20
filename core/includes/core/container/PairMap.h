#pragma once
#include <core/core.h>


NS_BEGIN(CORE_NAMESPACE)
  // a pair map is a twoway map
  template< typename K1, typename K2 >
  class PairMap{
  private:
    std::map<K1,K2> m12;
    std::map<K2,K1> m21;
  public:
    bool mappingExists(K1 k);
    bool mappingExists(K2 k);
    K1 operator()(K2 k);
    K2 operator()(K1 k);
    void addMapping(K1 k1,K2 k2);
  };

  // implementation
  template< typename K1, typename K2 >
  bool PairMap<K1,K2>::mappingExists(K1 k){
    auto it = m12.find(k);
    if(it == m12.end())return false;
    return true;
  }
  template< typename K1, typename K2 >
  bool PairMap<K1,K2>::mappingExists(K2 k){
    auto it = m21.find(k);
    if(it == m21.end())return false;
    return true;
  }
  template< typename K1, typename K2 >
  K1 PairMap<K1,K2>::operator()(K2 k){
    return m21[k];
  }
  template< typename K1, typename K2 >
  K2 PairMap<K1,K2>::operator()(K1 k){
    return m12[k];
  }
  template< typename K1, typename K2 >
  void PairMap<K1,K2>::addMapping(K1 k1,K2 k2){
    m12[k1] = k2;
    m21[k2] = k1;
  }
NS_END(CORE_NAMESPACE)
