#pragma once
#include <core/core.h>

#include <core/container/graph/Node.h>

NS_BEGIN(CORE_NAMESPACE)
  // a class holding all nodes of a graph
  template<typename NodeType>
  class Graph: private virtual Set<NodeType*>, public virtual ObservableCollection<NodeType*>::Observer{
  public:
    // returns all nodes of the graph
    Set<NodeType*> & nodes();
    // readonly access to all nodes in the graph
    const Set<NodeType*> & nodes()const;
    // gets a single node by comparison with id
    template<typename T> NodeType * operator()(const T id)const;
    // returns all nodes which have no predecessors
    Set<NodeType*> leaves()const;
  protected:
    virtual void onElementAdded(NodeType * element);
    virtual void onElementRemoved(NodeType * element);

    virtual void elementAdded(ObservableCollection<NodeType*> * sender, NodeType* element){
      nodes()|=element;
    }
    virtual void elementRemoved(ObservableCollection<NodeType*> * sender, NodeType* element){
    }
  };

  //implementation of templated methods

  template<typename NodeType>
  void Graph<NodeType>::onElementAdded(NodeType * element){
    element->addObserver(this);
    element->neighbors().foreachElement([this](NodeType * node){
      this->nodes()|=node;
    });
  }
  template<typename NodeType>
  void Graph<NodeType>::onElementRemoved(NodeType * element){
    element->removeObserver(this);
  }

  // gets a single node by comparison with id
  template<typename NodeType>
  template<typename T>
  NodeType * Graph<NodeType>::operator()(const T id)const{
    return *this(id);
  }

  // returns all nodes of the graph
  template<typename NodeType>
  Set<NodeType*> & Graph<NodeType>::nodes(){
    return *this;
  }
  // readonly access to all nodes in the graph
  template<typename NodeType>
  const Set<NodeType*> & Graph<NodeType>::nodes()const{
    return *this;
  }

  // returns all nodes which have no successors
  template<typename NodeType>
  Set<NodeType*> Graph<NodeType>::leaves()const{
    return nodes().subset([](NodeType * n){
      return (bool)!n->successors();
    });
  }
NS_END(CORE_NAMESPACE)
