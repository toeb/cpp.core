#pragma once
#include <core/core.h>

NS_BEGIN(CORE_NAMESPACE)


/// a directed graph
/// uses a double adjacency list to represent edges
/// can store data in edge and in node
template<typename TNode, typename TEdge>
struct directed_graph{
  //// TYPEDEFS
  typedef directed_graph graph_type;
  typedef const graph_type const_graph_type;
  typedef graph_type & graph_type_ref;
  typedef const_graph_type & const_graph_type_ref;

  typedef TNode node_data_type;
  typedef node_data_type & node_data_ref;
  typedef const node_data_type & const_node_data_ref;

  typedef TEdge edge_data_type;

  struct _node_view;
  struct _edge_view;
  struct _edge;


  typedef _node_view node_view_type;
  typedef const node_view_type const_node_view_type;

  typedef _edge_view edge_view_type;
  typedef const edge_view_type const_edge_view_type;

  typedef _edge edge_type;

  typedef int size_type;
  typedef int index_type;

  typedef std::vector<bool> node_list_type;
  typedef std::vector<node_data_type> node_data_list_type;
  typedef std::vector<const_node_view_type> const_node_view_list_type;
  typedef std::vector<node_view_type> node_view_list_type;
  typedef std::vector<const_edge_view_type> const_edge_list;
  typedef std::vector<edge_view_type> edge_view_list;


  typedef std::vector<edge_type> edge_list_type;
  typedef std::vector<edge_data_type> edge_data_list_type;
  typedef std::vector<index_type> index_list_type;
  typedef std::vector<index_list_type> successor_list_type;
  typedef std::vector<index_list_type> predecessor_list_type;

  /// constructor
  directed_graph(){}

  directed_graph(std::initializer_list<node_data_type> data){
    for (auto & n : data){
      add_node(n);
    }
  }





  /// OPERATIONs

  /// adds an edge and returns this graph (can be chained)
  auto edge(edge_view_type tail, edge_view_type head, edge_data_type data = edge_data_type())->graph_type & {
    add_edge(tail, head, data);
    return *this;
  }
  /// adds a node and returns this graph (can be chained)
  auto node(node_data_type data)->graph_type &{
    add_node(tail, head, data);
    return *this;
  }

  /// performs the union of lhs and rhs and stores the result in rhs
  static void graph_union_inplace(graph_type & lhs, const graph_type & rhs){
    auto nodes = rhs.nodes();

    for (const auto & n : nodes){
      bool result = lhs.add_node(n.data());
    }

    auto edges = rhs.edges();
    for (const auto & e : edges){
      bool result = lhs.add_edge(e.tail().data(), e.head().data(), e.data());
    }
  }

  /// removes all nodes and edges in rhs from lhs
  static void graph_difference_inplace(graph_type & lhs, const graph_type & rhs){
    auto nodes = rhs.nodes();
    for (auto & n : nodes){
      lhs.remove_node(n.data());
    }
  }

  /// inserts every node data element into output iterator
  template<typename OutputIterator> auto all_node_data(OutputIterator output)const -> void{
    auto n = nodes();
    for (const auto & node : n){
      *output = node.data();
    }
  }

  /// return a list of all node data elements
  auto all_node_data()const-> node_data_list_type{
    node_data_list_type result;
    all_node_data(std::back_inserter(result));
    return result;
  }


  /// removes all nodes from lhs that do not exist in rhs
  static void graph_intersect_inplace(graph_type & lhs, const graph_type & rhs){
    auto dataL = lhs.all_node_data();
    auto dataR = rhs.all_node_data();

    std::sort(std::begin(dataL), std::end(dataL));
    std::sort(std::begin(dataR), std::end(dataR));


    lhs |= rhs;

    node_data_list_type remove;
    std::set_symmetric_difference(std::begin(dataL), std::end(dataL), std::begin(dataR), std::end(dataR), std::back_inserter(remove));

    for (auto &n : remove){
      lhs.remove_node(n);
    }

  }

  /// union in place operator
  friend graph_type & operator |= (graph_type & lhs, const graph_type & rhs){
    graph_union_inplace(lhs, rhs);
    return lhs;
  }

  /// union operator - returns a new graph
  friend graph_type operator || (const graph_type & lhs, const graph_type & rhs){
    graph_type g;
    g |= lhs;
    g |= rhs;
    return g;
  }

  friend auto operator &= (graph_type & lhs, const graph_type & rhs)->graph_type &{
    graph_intersect_inplace(lhs, rhs);
    return lhs;
  }

  friend auto operator &&(const graph_type & lhs, const graph_type & rhs)->graph_type{
    graph_type res = lhs;
    res &= rhs;
    return res;
  }


  /// returns the edge between tail and head, creates it if it does not exist
  edge_view_type operator()(node_view_type tail, node_view_type head){
    auto result = resolve_edge(edge_view_type(tail, head));
    if (!result)result = add_edge(tail, head);
    return result;
  }
  /// returns the edge between tail and head if it exists;
  const_edge_view_type operator()(node_view_type tail, node_view_type head)const{
    return resolve_edge(edge_view_type(tail, head));
  }


  /// intersection in place operator

  /// intersection operator - returns a new graph


  /// adds a node to this graph
  friend auto operator <<(graph_type & lhs, node_data_type data)-> graph_type & {
    return lhs.node();
  }






  //// FIELDS




  /// stores the node's state
  node_list_type _node_list;
  /// stores the node's data
  node_data_list_type _node_data_list;



  /// contains the data associated with the an edge
  edge_data_list_type _edge_data_list;
  /// contains the edge structs
  edge_list_type _edge_list;
  /// the successor adjacency list
  successor_list_type _successor_list;
  /// the predecessor adjacency list
  predecessor_list_type _predecessor_list;

  ///// METHODS

  /// adds a node containing the specified data into the graph, returns a valid mutalbe node_view
  auto add_node(node_data_type node_data = node_data_type())->node_view_type;
  /// returns a mutable node_view_type for the first node which contains node_data else returns an invalid view
  auto find_node(const node_data_type & node_data)->node_view_type;
  /// returns a const node_view_type for the first node which contains node_data else returns an invalid view
  auto find_node(const node_data_type & node_data)const->const node_view_type;

  /// disconnects all edges pointing to node
  auto remove_incomming_edges(node_view_type node)->size_type;


  /// disconnects all edges originating from node
  auto remove_outgoing_edges(node_view_type node)->size_type;

  /// disconnects specified node and returns the number of edges that were severed. 
  auto disconnect_node(node_view_type node)->size_type;

  /// returns true if tail and head are connected from head to tail as well as tail to head
  auto is_undirected_edge(node_view_type tail, node_view_type head)const->bool;

  /// returns true if node is connected from head to tail or from tail to head
  auto are_adjacent(node_view_type tail, node_view_type head)const->size_type;
  ///returns 1 if node is connected from tail to head or -1 if head to tail 0 if not connected or connected in both directions
  auto is_connected_one_way(node_view_type tail, node_view_type head)->size_type;

  /// adds an undirected edge to the graph (two directed edges) returns the number of edges that were create (0,1,2)
  auto add_undirected_edge(node_view_type tail, node_view_type head, edge_data_type data = edge_data_type())->size_type;

  /// returns a const node_view for the first node that matches the predicate the predicate may accept a const_node_view_type & 
  template<typename Predicate>
  auto find_node_if(Predicate predicate)const->const node_view_type;

  /// returns a mutable node_view for the first node that matches the predicate the predicate may accept a const_node_view_type & 
  template<typename Predicate>
  auto find_node_if(Predicate predicate)->node_view_type;

  /// returns the data reference for the node identified by its index 
  auto node_data(index_type node)->node_data_type &;

  /// returns the const data reference for the ndoe identified by its index
  auto node_data(index_type node)const->const node_data_type &;

  /// removes the node and all connected edges by id/value or node_view
  auto remove_node(node_view_type node)->bool;

  /// checks if the node specified exists
  auto has_node(node_view_type node)const->bool;

  /// inserts every node of this graph into the output iterator as a const node_view and returns the number of nodes
  template<typename OutputIterator>
  auto nodes(OutputIterator output)const->size_type;

  /// inserts every node of this graph into the output iterator as a mutable node_view and returns the number of nodes
  template<typename OutputIterator>
  auto nodes(OutputIterator output)->size_type;


  /// returns the a list of const node views containing all nodes of this graph
  auto nodes()const->const_node_view_list_type;

  /// returns a list of mutable node views containing all nodes of this graph
  auto nodes()->node_view_list_type;

  template<typename OutputIterator, typename Predicate>
  auto filter_nodes(OutputIterator output, Predicate predicate)const->size_type;
  template<typename Predicate>
  auto filter_nodes(Predicate predicate)const->const_node_view_list_type;


  template<typename OutputIterator, typename Predicate>
  auto filter_nodes(OutputIterator output, Predicate predicate)->size_type;


  template<typename Predicate>
  auto filter_nodes(Predicate predicate)->node_view_list_type;



  /// returns the number of nodes that are in this graph
  auto node_count()const->size_type;

  /// const access to node via data or index
  auto operator[](node_view_type  n)const->const_node_view_type;
  ///mutable access to node via data or index
  auto operator[](node_view_type n)->node_view_type;


  /// resolves the specified node view
  /// ie completes missing information and returns a valid node if possible
  auto resolve(node_view_type node_view)->node_view_type;


  /// resolves the specified node view
  /// ie completes missing information 
  auto resolve(node_view_type node_view)const->const_node_view_type;



  //////////////////////// EDGE


  /// removes the edge that exists between tail and head from the graph
  auto remove_edge(node_view_type tail, node_view_type head)->bool;
  /// removes the edge with matching data
  auto remove_edge(const edge_data_type & data)->bool;

  /// inserts the const edge_views for all edges into the output iterator and returns the number of edges
  template<typename OutputIterator>
  auto edges(OutputIterator output) const->size_type;

  /// returns a list of const edge views, one for every edge in the graph
  auto edges()const->const_edge_list;

  /// accepts an edge_query and tries to resolve it returning a new edge_view
  /// which is valid if the edge exists
  auto resolve_edge(edge_view_type edge_view)->edge_view_type;

  /// accepts an edge_query and returns a const_edge_view to the edge described /or  an invalid edge
  auto resolve_edge(edge_view_type edge_view)const->const_edge_view_type;

  /// returns true if an edge exists from tail to head
  auto has_edge(node_view_type tail, node_view_type head)const->bool;
  /// returns true if an edge exist which matches the edge_query
  auto has_edge(edge_view_type edge_query)const->bool;

  /// inserts a const_node_view of all predecessors of specified node into output iterator and returns the number of nodes inserted
  template<typename OutputIterator>
  auto predecessors(node_view_type node, OutputIterator output)const->size_type;


  /// returns a list of const node_views of all predecessors of specified node
  auto predecessors(node_view_type node)const->const_node_view_list_type;
  /// inserts a node_view for every predecessor of the specifed node into ouput and returns the number of nodes inserted
  template<typename OutputIterator>
  auto successors(node_view_type node, OutputIterator output)const->size_type;

  /// returns a list of const node_viewsof all successors of specified node
  auto successors(node_view_type node)const->const_node_view_list_type;

  /// inserts the all outgoing edges of the specified node into the output iterator and returns the number of nodes inserted
  template<typename OutputIterator>
  auto outgoing_edges(node_view_type node, OutputIterator output)const->size_type;
  template<typename OutputIterator>
  auto outgoing_edges(node_view_type node, OutputIterator output)->size_type;


  /// returns the list of outgoiung edges for specified node
  auto  outgoing_edges(node_view_type node)const->const_edge_list;
  auto  outgoing_edges(node_view_type node)->edge_view_list;


  /// inserts all nodes adjacent to specified node into output and returns the number
  template<typename OutputIterator>
  auto neighbors(node_view_type node, OutputIterator output)const->size_type;

  /// inserts all nodes adjacent to specifed node into output and returns the number
  template<typename OutputIterator>
  auto neighbors(node_view_type node, OutputIterator output)->size_type;
  /// returns a list of all adjacent nodes
  auto neighbors(node_view_type node)const->const_node_view_list_type;
  /// returns a list of all adjacent nodes
  auto neighbors(node_view_type node)->node_list_type;

  /// inserts all incident edges of the specified node into output and returns thue number of edges inserted
  template<typename OutputIterator>
  auto incident_edges(node_view_type node, OutputIterator output)const->size_type;

  /// inserts all incident edges of the specified node into output and returns thue number of edges inserted
  template<typename OutputIterator>
  auto incident_edges(node_view_type node, OutputIterator output)->size_type;

  /// returns a list of edges incident to the specified node
  auto incident_edges(node_view_type node)const->const_edge_list;

  /// returns a list of edges incident to the specified node
  auto incident_edges(node_view_type node)->edge_list_type;

  /// inserts every edge that points to the specified node into output and returns the count
  template<typename OutputIterator>
  auto incoming_edges(node_view_type node, OutputIterator output)const->size_type;


  /// returns a list of every edge that point to node
  auto incoming_edges(node_view_type node)const->const_edge_list;


  /// returns an edge_view for the edge between tail and head
  auto find_edge(node_view_type tail, node_view_type head)const->const_edge_view_type;
  auto find_edge(node_view_type tail, node_view_type head)->edge_view_type;
  /// retursn an edgeview for the edge corresponing to edge_data
  auto find_edge(const edge_data_type & edge_data)const->const_edge_view_type;

  /// retusn the number of edges in this graph
  auto edge_count()const->size_type;

  /// adds an edge and returns a mutable edge_view to it returns an invalid view if tail or head are invalid
  auto add_edge(node_view_type tail, node_view_type head, edge_data_type data = edge_data_type())->edge_view_type;

  /// returns true if graph is null -> does not contain any edges
  auto is_null()const->bool{ return edge_count() == 0; }
  /// returns true iff graph does not contain any nodes/edges
  auto is_empty()const->bool{ return is_null() && node_count() == 0; }

private:
  /// adds an edge by edge_struct 
  auto add_edge(edge_type edge, edge_data_type  data)->edge_view_type;

  /// removes the specified edge struct from the graph
  auto remove_edge(const edge_type & edge)->bool;
};


//// structs



template<typename TNode, typename TEdge>
struct directed_graph<TNode, TEdge>::_edge{
  _edge(index_type index, index_type tail, index_type head) :index(index), tail(tail), head(head){}
  _edge() : index(-1), tail(-1), head(-1){}

  _edge(const edge_view_type & ev) :index(ev.index()), tail(ev.tail_index()), head(ev.head_index()){}

  operator bool()const{ return index > -1; }
  index_type index;
  index_type tail;
  index_type head;
};

template<typename TNode, typename TEdge>
struct directed_graph<TNode, TEdge>::_node_view{
  _node_view(const graph_type * graph, index_type index) :_index(index), _graph(graph), _graph_mutable(0){}
  _node_view(const graph_type * graph) :_index(-1), _graph(graph), _graph_mutable(0){}

  _node_view(graph_type * graph) :_index(-1), _graph(graph), _graph_mutable(graph){}
  _node_view(graph_type * graph, index_type index) :_index(index), _graph(graph), _graph_mutable(graph){}

  _node_view(const node_data_type & data) : _index(-1), _graph(0), _graph_mutable(0), _query_data(data){}
  _node_view(const index_type & idx) :_index(idx), _graph(0), _graph_mutable(0){}


  _node_view() :_index(-1), _graph(0), _graph_mutable(0){}

  /// returns true if this node_view is a node_query
  bool is_query()const{
    return !_graph;
  }
  _node_view & operator =(const _node_view & rhs){

    if (!rhs.is_query()) {
      this->_graph = rhs._graph;
      this->_graph_mutable = rhs._graph_mutable;
      this->_index = rhs._index;
      return *this;
    }
    if (is_query()){
      this->_index = rhs._index;
      this->_query_data = rhs._query_data;
      return *this;

    }
    data() = rhs.data_query();
    return *this;
  }


  template<typename T>
  _node_view(T data) : _index(-1), _graph(0), _graph_mutable(0), _query_data(data){}

  const index_type & index()const{ return _index; }
  index_type & index(){ return _index; }

  const node_data_type & data()const{
    return _graph->node_data(_index);
  }
  node_data_type & data(){
    return _graph_mutable->node_data(_index);

  }

  const node_data_type & data_query()const{ return _query_data; }

  operator node_data_ref(){ return data(); }
  operator const_node_data_ref()const{ return data(); }

  operator bool()const{ return _graph && _index > -1; }
  operator index_type()const{ return _index; }

  bool operator == (const _node_view & other)const{ return _index == other._index && _graph == other._graph; }
  bool operator != (const _node_view & other)const{ return !(other == *this); }

  // returns true if this node_view is readonly
  bool is_readonly()const{ return _graph && !_graph_mutable; }

  // mutable operations

  edge_view_type add_successor(node_data_type node, edge_data_type  edge = edge_data_type());
  edge_view_type add_predecessor(node_data_type node, edge_data_type  edge = edge_data_type());


  void set_graph(const graph_type * graph){ _graph = graph; _graph_mutable = 0; }
  void set_graph(graph_type * graph){ _graph = graph; _graph_mutable = graph; }
  const graph_type * graph()const{ return _graph; }
private:
  index_type _index;
  const graph_type * _graph;
  node_data_type _query_data;
  graph_type * _graph_mutable;
};



template<typename TNode, typename TEdge>
struct directed_graph<TNode, TEdge>::_edge_view{
  _edge_view() :_index(-1), _graph(0), _graph_mutable(0){}
  _edge_view(const graph_type * graph, index_type index) : _index(index), _graph(graph), _graph_mutable(0){}
  _edge_view(const graph_type * graph) : _index(-1), _graph(graph), _graph_mutable(0){}

  _edge_view(edge_data_type data) :_index(-1), _graph(0), _graph_mutable(0), _data_query(data){}
  _edge_view(node_view_type tail, node_view_type head) :_index(-1), _graph(0), _graph_mutable(0), _head_query(head), _tail_query(tail){}

  _edge_view(index_type index) :_index(index), _graph(0), _graph_mutable(0){}

  _edge_view(graph_type * graph, index_type index) : _index(index), _graph(graph), _graph_mutable(graph){}
  _edge_view(graph_type * graph) : _index(-1), _graph(graph), _graph_mutable(graph){}

  template<typename T>
  _edge_view(T edge_data) : _index(-1), _graph(0), _graph_mutable(0), _data_query(edge_data){}

  operator bool()const{ return _graph && _index > -1 && _graph->_edge_list[_index]; }
  operator std::pair<index_type, index_type>()const{ return std::make_pair(_tail, _head); }

  _edge_view& operator=(const _edge_view & new_data){
    if (new_data) {
      this->_graph = new_data._graph;
      this->_graph_mutable = new_data._graph_mutable;
      this->_index = new_data._index;
      return *this;
    }
    if (!*this)return *this;

    data() = new_data.data_query();
    return *this;
  }
  bool is_mutable()const{ return _graph_mutable; }
  bool is_const()const{ return _graph && !_graph_mutable; }
  bool operator == (const _edge_view & other)const{ return other._index == _index && other._graph == _graph; }
  bool operator != (const _edge_view & other)const{ return !(other == *this); }

  const edge_data_type & data()const{ return _graph->_edge_data_list[_index]; }
  edge_data_type & data(){ return _graph_mutable->_edge_data_list[_index]; }

  const_node_view_type head()const{
    if (_graph)return node_view_type(_graph, _graph->_edge_list[_index].head);
    return node_view_type();
  }
  node_view_type head(){
    if (_graph_mutable)return node_view_type(_graph_mutable, _graph->_edge_list[_index].head);
    if (_graph)return node_view_type(_graph, _graph->_edge_list[_index].head);
    return node_view_type();
  }
  index_type head_index()const{
    if (_graph) return _graph->_edge_list[_index].head;
    return -1;
  }

  const_node_view_type tail()const{
    if (_graph) return const_node_view_type(_graph, _graph->_edge_list[_index].tail);
    return node_view_type();
  }
  node_view_type tail(){
    if (_graph_mutable) return const_node_view_type(_graph_mutable, _graph->_edge_list[_index].tail);
    if (_graph) return const_node_view_type(_graph, _graph->_edge_list[_index].tail);
    return node_view_type();

  }
  index_type tail_index()const{
    if (_graph)return _graph->_edge_list[_index].tail;
    return -1;
  }
  index_type index()const{ return _index; }

  const graph_type * graph()const{ _graph; }
  graph_type * graph(){ return _graph_mutable; }

  void set_graph(const graph_type * graph){ _graph = graph; _graph_mutable = 0; }
  void set_graph(graph_type * graph){ _graph = graph; _graph_mutable = graph; }

  const_node_view_type & head_query()const{ return _head_query; }
  const_node_view_type &tail_query()const{ return _tail_query; }
  const edge_data_type & data_query()const{ return _data_query; }
private:
  index_type _index;
  node_data_type _data_query;
  node_view_type _head_query;
  node_view_type _tail_query;
  const graph_type * _graph;
  graph_type * _graph_mutable;
};


///// Methods
template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::add_node(node_data_type node_data = node_data_type())->node_view_type{
  auto result = _node_list.size();
  // no duplicates allowed
  if (has_node(node_data))return node_view_type(this);
  _node_list.push_back(true);
  _node_data_list.push_back(node_data);
  _predecessor_list.push_back(index_list_type());
  _successor_list.push_back(index_list_type());
  return node_view_type(this, result);

}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::find_node(const node_data_type & node_data)->node_view_type{
  using namespace std;
  auto b = begin(_node_data_list);
  auto e = end(_node_data_list);
  auto current_begin = b;
  while (true){
    auto it = find(current_begin, e, node_data);
    if (it == e)return node_view_type(this);
    index_type index = it - b;
    if (_node_list[index])return node_view_type(this, index);
    current_begin = it + 1;
  }

}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::find_node(const node_data_type & node_data)const->const node_view_type{
  using namespace std;
  auto b = begin(_node_data_list);
  auto e = end(_node_data_list);
  auto current_begin = b;
  while (true){
    auto it = find(current_begin, e, node_data);
    if (it == e)return node_view_type(this);
    index_type index = it - b;
    if (_node_list[index])return node_view_type(this, index);
    current_begin = it + 1;
  }
}



template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::remove_incomming_edges(node_view_type node)->size_type{
  auto edges = incoming_edges(node);
  for (auto & e : edges){
    remove_edge(e);
  }
  return edges.size();
}


template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::remove_outgoing_edges(node_view_type node)->size_type{

  auto edges = outgoing_edges(node);
  for (auto & e : edges){
    remove_edge(e);
  }
  return edges.size();
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::disconnect_node(node_view_type node)->size_type{
  return disconnect_incomming_edges(node) + disconnect_outgoing_edges(node);
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::is_undirected_edge(node_view_type tail, node_view_type head)const->bool{
  return has_edge(tail, head) && has_edge(head, tail);
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::are_adjacent(node_view_type tail, node_view_type head)const->size_type{
  auto a = has_edge(tail, head);
  auto b = has_edge(head, tail);

  if (a&&b)return 2;
  if (a^b)return 1;
  return 0;
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::is_connected_one_way(node_view_type tail, node_view_type head)->int{
  auto a = has_edge(tail, head);
  auto b = has_edge(head, tail);

  if (!(a ^ b))return 0;

  if (a)return 1;
  else return -1;

}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::add_undirected_edge(node_view_type tail, node_view_type head, edge_data_type data = edge_data_type())->size_type{
  auto a = add_edge(tail, head, data);
  auto b = add_edge(head, tail, data);

  if (a && b)return 2;
  if (a ^ b)return 1;
  return 0;
}

template<typename TNode, typename TEdge>
template<typename Predicate>
auto directed_graph<TNode, TEdge>::find_node_if(Predicate predicate)const->const node_view_type{
  using namespace std;
  for (size_t i = 0; i < _node_list.size(); i++){
    const_node_view_type view(this, i);
    if (view && predicate(view))return view;
  }
  return const_node_view_type(this);
}

template<typename TNode, typename TEdge>
template<typename Predicate>
auto directed_graph<TNode, TEdge>::find_node_if(Predicate predicate)-> node_view_type{
  using namespace std;
  for (size_t i = 0; i < _node_list.size(); i++){
    node_view_type view(this, i);
    if (view && predicate(view))return view;
  }
  return node_view_type(this);
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::node_data(index_type node)->node_data_type & {
  return _node_data_list[node];
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::node_data(index_type node)const->const node_data_type &{
  return _node_data_list[node];
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::remove_node(node_view_type node)->bool{
  node = this->resolve(node);
  if (!node)return false;
  if (!has_node(node.index()))return false;
  _node_list[node.index()] = false;

  // remove edges

  auto edges = incident_edges(node);

  for (auto & edge : edges){
    remove_edge(edge);
  }

  return true;
}





template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::has_node(node_view_type node)const->bool{
  return resolve(node);
}

template<typename TNode, typename TEdge>
template<typename OutputIterator>
auto directed_graph<TNode, TEdge>::nodes(OutputIterator output)const->size_type {
  size_type sum = 0;
  for (size_t i = 0; i < _node_list.size(); i++){
    if (_node_list[i]){
      *output = node_view_type(this, i);
      sum++;
    }

  }
  return sum;
}

template<typename TNode, typename TEdge>
template<typename OutputIterator>
auto directed_graph<TNode, TEdge>::nodes(OutputIterator output)->size_type {
  size_type sum = 0;
  for (size_t i = 0; i < _node_list.size(); i++){
    if (_node_list[i]){
      *output = node_view_type(this, i);
      sum++;
    }

  }
  return sum;
}


template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::nodes()const->const_node_view_list_type {
  const_node_view_list_type result;
  nodes(std::back_inserter(result));
  return result;
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::nodes()->node_view_list_type{
  node_view_list_type result;
  nodes(std::back_inserter(result));
  return result;
}

template<typename TNode, typename TEdge>
template<typename OutputIterator, typename Predicate>
auto directed_graph<TNode, TEdge>::filter_nodes(OutputIterator output, Predicate predicate)const->size_type{
  size_type sum = 0;
  for (size_type i = 0; i < _node_list.size(); i++){
    const_node_view_type view(this, i);
    if (view && predicate(view)){
      *output = view;
      sum++;
    }

  }
  return sum;
}

template<typename TNode, typename TEdge>
template<typename Predicate>
auto directed_graph<TNode, TEdge>::filter_nodes(Predicate predicate)const->const_node_view_list_type{
  const_node_view_list_type result;
  filter_nodes(std::back_inserter(result), predicate);
  return result;
}


template<typename TNode, typename TEdge>
template<typename OutputIterator, typename Predicate>
auto directed_graph<TNode, TEdge>::filter_nodes(OutputIterator output, Predicate predicate)->size_type {
  size_type sum = 0;
  for (size_type i = 0; i < _node_list.size(); i++){
    node_view_type view(this, i);
    if (view && predicate(view)){
      *output = view;
      sum++;
    }
  }
  return sum;
}


template<typename TNode, typename TEdge>
template<typename Predicate>
auto directed_graph<TNode, TEdge>::filter_nodes(Predicate predicate)->node_view_list_type{
  node_view_list_type result;
  filter_nodes(std::back_inserter(result), predicate);
  return result;
}



template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::node_count()const->size_type{
  return std::count_if(std::begin(_node_list), std::end(_node_list), [](bool b){return b; });
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::operator[](node_view_type  n)const->const_node_view_type{
  return resolve(n);
}
template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::operator[](node_view_type n)->node_view_type{
  return resolve(n);
}


template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::resolve(node_view_type node_view)->node_view_type{

  if (node_view.graph() == this){
    return node_view;
  }

  if (node_view.index() > -1){
    return node_view_type(this, node_view.index());
  }

  return find_node(node_view.data_query());
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::resolve(node_view_type node_view)const->const_node_view_type{

  if (node_view.graph() == this){
    return node_view;
  }

  if (node_view.index() > -1){
    return node_view_type(this, node_view.index());
  }

  return find_node(node_view.data_query());
}





template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::remove_edge(node_view_type tail, node_view_type head)->bool{
  auto edge = resolve_edge(edge_view_type(tail, head));
  if (!edge)return false;
  return remove_edge(edge_type(edge.index(), edge.tail_index(), edge.head_index()));

}
template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::remove_edge(const edge_data_type & data)->bool{
  auto edge = find_edge(data);
  return remove_edge(edge.tail_index(), edge.head_index());
}

template<typename TNode, typename TEdge>
template<typename OutputIterator>
auto directed_graph<TNode, TEdge>::edges(OutputIterator output) const->size_type{
  size_t sum = 0;
  for (auto &edge : _edge_list){
    if (edge) { *output = const_edge_view_type(this, edge.index); sum++; }
  }
  return sum;
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::edges()const->const_edge_list {
  const_edge_list result;
  edges(std::back_inserter(result));
  return result;
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::resolve_edge(edge_view_type edge_view)->edge_view_type {
  if (edge_view.graph() == this)return edge_view;

  if (edge_view.index() > -1){
    return edge_view_type(this, edge_view.index());
  }

  auto tail_query = resolve(edge_view.tail_query());
  auto head_query = resolve(edge_view.head_query());
  if (tail_query && head_query){
    return find_edge(tail_query, head_query);
  }
  return find_edge(edge_view.data_query());

}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::resolve_edge(edge_view_type edge_view)const->const_edge_view_type {

  if (edge_view.graph() == this)return edge_view;

  if (edge_view.index() > -1){
    return edge_view_type(this, edge_view.index());
  }

  auto tail_query = resolve(edge_view.tail_query());
  auto head_query = resolve(edge_view.head_query());
  if (head_query && tail_query){
    return find_edge(tail_query, head_query);
  }
  return find_edge(edge_view.data_query());
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::has_edge(node_view_type tail, node_view_type head)const->bool{
  return has_edge(edge_view_type(tail, head));
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::has_edge(edge_view_type edge_view)const->bool{
  return resolve_edge(edge_view);
}



template<typename TNode, typename TEdge>
template<typename OutputIterator>
auto directed_graph<TNode, TEdge>::predecessors(node_view_type node, OutputIterator output)const->size_type{
  size_type sum = 0;
  const index_list_type & it = _predecessor_list[node.index()];
  for (index_type i : it){
    const edge_type & predecessor = _edge_list[i];
    if (!predecessor)continue;
    *output = const_node_view_type(this, predecessor.tail);
    sum++;
  }
  return sum;
}


template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::predecessors(node_view_type node)const->const_node_view_list_type {
  const_node_view_list_type result;
  predecessors(node, std::back_inserter(result));
  return result;
}
template<typename TNode, typename TEdge>
template<typename OutputIterator>
auto directed_graph<TNode, TEdge>::successors(node_view_type node, OutputIterator output)const->size_type{

  size_type sum = 0;
  const index_list_type & it = _successor_list[node.index()];
  for (index_type i : it){
    const edge_type & successor = _edge_list[i];
    if (!successor)continue;
    *output = const_node_view_type(this, successor.head);
    sum++;
  }

  return sum;
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::successors(node_view_type node)const->const_node_view_list_type{
  const_node_view_list_type result;
  successors(node, std::back_inserter(result));
  return result;
}

template<typename TNode, typename TEdge>
template<typename OutputIterator>
auto directed_graph<TNode, TEdge>::outgoing_edges(node_view_type node, OutputIterator output)const->size_type{
  node = this->resolve(node);
  auto node_index = node.index();
  size_type sum = 0;
  if (node_index < 0)return 0;
  auto & successors = _successor_list[node_index];
  for (auto & successor_index : successors){
    auto edge = const_edge_view_type(this, successor_index);
    if (!edge)continue;
    *output = edge;
    sum++;
  }
  return sum;
}

template<typename TNode, typename TEdge>
template<typename OutputIterator>
auto directed_graph<TNode, TEdge>::outgoing_edges(node_view_type node, OutputIterator output)->size_type{
  node = this->resolve(node);
  auto node_index = node.index();
  size_type sum = 0;
  if (node_index < 0)return 0;
  auto & successors = _successor_list[node_index];
  for (auto & successor_index : successors){
    auto edge = edge_view_type(this, successor_index);
    if (!edge)continue;
    *output = edge;
    sum++;
  }
  return sum;
}

template<typename TNode, typename TEdge>
auto  directed_graph<TNode, TEdge>::outgoing_edges(node_view_type node)const->const_edge_list{
  const_edge_list result;
  outgoing_edges(node, std::back_inserter(result));
  return result;
}


template<typename TNode, typename TEdge>
auto  directed_graph<TNode, TEdge>::outgoing_edges(node_view_type node)->edge_view_list{
  edge_view_list result;
  outgoing_edges(node, std::back_inserter(result));
  return result;
}

template<typename TNode, typename TEdge>
template<typename OutputIterator>
auto directed_graph<TNode, TEdge>::neighbors(node_view_type node, OutputIterator output)const->size_type{
  return predecessors(node, output) + successors(node, output);
}


template<typename TNode, typename TEdge>
template<typename OutputIterator>
auto directed_graph<TNode, TEdge>::neighbors(node_view_type node, OutputIterator output)->size_type{
  return predecessors(node, output) + successors(node, output);
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::neighbors(node_view_type node)const->const_node_view_list_type{
  const_node_view_list_type result;
  neighbors(node, std::back_inserter(result));
  return result;
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::neighbors(node_view_type node)->node_list_type{
  node_list_type result;
  neighbors(node, std::back_inserter(result));
  return result;
}

template<typename TNode, typename TEdge>
template<typename OutputIterator>
auto directed_graph<TNode, TEdge>::incident_edges(node_view_type node, OutputIterator output)const->size_type{
  return outgoing_edges(node, output) + incoming_edges(node, output);
}

template<typename TNode, typename TEdge>
template<typename OutputIterator>
auto directed_graph<TNode, TEdge>::incident_edges(node_view_type node, OutputIterator output)->size_type{

  auto a = outgoing_edges(node, output);
  auto b = incoming_edges(node, output);
  return a + b;
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::incident_edges(node_view_type node)const->const_edge_list{
  const_edge_list result;
  incident_edges(node, std::back_inserter(result));
  return result;
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::incident_edges(node_view_type node)->edge_list_type{
  edge_list_type result;
  incident_edges(node, std::back_inserter(result));
  return result;
}

template<typename TNode, typename TEdge>
template<typename OutputIterator>
auto directed_graph<TNode, TEdge>::incoming_edges(node_view_type node, OutputIterator output)const->size_type{
  node = this->resolve(node);
  index_type i = node;
  size_type sum = 0;
  if (i < 0)return 0;
  auto & predecessors = _predecessor_list[i];
  for (auto & predecessor_index : predecessors){

    auto edge = const_edge_view_type(this, predecessor_index);
    if (!edge)continue;
    *output = edge;
    sum++;
  }
  return sum;
}


template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::incoming_edges(node_view_type node)const->const_edge_list{
  const_edge_list result;
  incoming_edges(node, std::back_inserter(result));
  return result;
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::find_edge(node_view_type tail, node_view_type head)const->const_edge_view_type{
  using namespace std;
  tail = resolve(tail);
  head = resolve(head);
  if (!tail)return const_edge_view_type(this);
  if (!head)return const_edge_view_type(this);

  // lookup in smaller list    
  auto outgoing_edges = this->outgoing_edges(tail);

  auto it = find_if(begin(outgoing_edges), end(outgoing_edges), [&head](const_edge_view_type & edge){
    return edge.head_index() == head.index();
  });
  if (it == end(outgoing_edges))return const_edge_view_type(this);
  return *it;
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::find_edge(node_view_type tail, node_view_type head)->edge_view_type{
  using namespace std;
  tail = resolve(tail);
  head = resolve(head);
  if (!tail)return const_edge_view_type(this);
  if (!head)return const_edge_view_type(this);

  // lookup in smaller list    
  auto outgoing_edges = this->outgoing_edges(tail);

  auto it = find_if(begin(outgoing_edges), end(outgoing_edges), [&head](const_edge_view_type & edge){
    return edge.head_index() == head.index();
  });
  if (it == end(outgoing_edges))return edge_view_type(this);
  return *it;
}


template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::find_edge(const edge_data_type & edge_data)const->const_edge_view_type{
  using namespace std;
  auto b = begin(_edge_data_list);
  auto e = end(_edge_data_list);
  auto c = b;
  while (true){
    auto it = find(c, e, edge_data);
    if (it == e)return const_edge_view_type(this);
    auto idx = it - b;
    auto & edge = _edge_list[idx];
    if (edge)return const_edge_view_type(this, idx);
    c = it + 1;
  }
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::edge_count()const->size_type{
  return
    std::count_if(
    std::begin(_edge_list),
    std::end(_edge_list),
    [](const edge_type & edge)->bool{return (bool)edge; }
  );
}


template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::add_edge(node_view_type tail, node_view_type head, edge_data_type data = edge_data_type())->edge_view_type{
  tail = resolve(tail);
  head = resolve(head);
  if (!tail)return edge_view_type(this);
  if (!head)return edge_view_type(this);
  return add_edge(edge_type(-1, tail.index(), head.index()), data);
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::add_edge(edge_type edge, edge_data_type  data)->edge_view_type{
  if (has_edge(edge.tail, edge.head))return edge_view_type(this);
  edge.index = _edge_list.size();
  _edge_list.push_back(edge);
  _edge_data_list.push_back(data);
  _successor_list[edge.tail].push_back(edge.index);
  _predecessor_list[edge.head].push_back(edge.index);
  return edge_view_type(this, edge.index);
}

template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::remove_edge(const edge_type & edge)->bool{
  auto & existing_edge = _edge_list[edge.index];
  if (!existing_edge)return false;
  existing_edge.index = -1;
  return true;
}



template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::_node_view::add_successor(node_data_type node, edge_data_type edge)->edge_view_type{
  auto n = _graph->find_node(node);
  if (!n) n = _graph_mutable->add_node(node);
  return _graph_mutable->add_edge(index(), n.index(), edge);

}
template<typename TNode, typename TEdge>
auto directed_graph<TNode, TEdge>::_node_view::add_predecessor(node_data_type  node, edge_data_type edge)->edge_view_type{
  auto n = _graph->find_node(node);
  if (!n) n = _graph_mutable->add_node(node);
  return _graph_mutable->add_edge(n.index(), index(), edge);

}

NS_END(CORE_NAMESPACE)