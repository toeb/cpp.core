#pragma once
#include <core/core.h>

#include <core/container/graph/DerivableDataNode.h>

NS_BEGIN(CORE_NAMESPACE)
  template<class T>
  class TypedNode :public virtual T, public DerivableDataNode<T*, TypedNode<T>> {
  };
NS_END(CORE_NAMESPACE)

