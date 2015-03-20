#include <core.testing.h>
#include <algorithm>
#include <core/graph/directed_graph.h>
using namespace std;

using namespace core;

typedef directed_graph<std::string, std::string> g;
typedef g::_node_view nv;
typedef g::_edge_view ev;


UNITTEST(graph_intersect){
  g a{ "A", "B"}, b{ "B", "C" };
  a("A", "B") = "AB";
  b("B", "C") = "BC";
  a("A", "A") = "AA";
  a("B", "B") = "BB";
  b("B", "B") = "BB";
  b("C", "C") = "BB";

  auto res = a && b;

  ASSERT(res.has_node("B"));
  ASSERT(res.has_edge("BB"));
  
  ASSERT(res.node_count() == 1);
  ASSERT(res.edge_count() == 1);

}


UNITTEST(null_graph_intersect){
  g a{ "A", "B", "C" }, b{ "B", "C", "D" };
  auto res = a && b;
  ASSERT(res.node_count() == 2);
  ASSERT(res["B"]);
  ASSERT(res["C"]);
  ASSERT(!res["A"]);
  ASSERT(!res["B"]);
}



UNITTEST(null_graph_intersect_disjoint){
  g a{ "A", "B", "C" }, b{ "1", "2", "3" };

  auto res = a && b;

  ASSERT(res.is_empty());
}




UNITTEST(graph_node_assign_data){

  g uut{ "A" };

  uut["A"] = "Z";


  ASSERT(!uut["A"]);
  ASSERT(uut["Z"]);

}

UNITTEST(graph_copy){
  g b;
  {
    g a{ "A", "B", "C" };

    a("A", "B") = "a-b";
    a("B", "C") = "b-c";
    b = a;
  }

  ASSERT(b["A"]);
  ASSERT(b["B"]);
  ASSERT(b["C"]);
  ASSERT(b.has_edge("a-b"));
  ASSERT(b.has_edge("b-c"));
}





UNITTEST(graph_union_same_edge){

  g uut1{ "A", "B", "C" };
  g uut2{ "B", "C", "D" };

  uut1("A", "B") = "A->B";
  uut1("C", "B") = "C->B";

  uut2("B", "D") = "B->D";
  uut2("C", "B") = "C->B";

  auto res = uut1 || uut2;

  ASSERT(res.has_node("A"));
  ASSERT(res.has_node("B"));
  ASSERT(res.has_node("C"));
  ASSERT(res.has_node("D"));

  ASSERT(res.node_count() == 4);

  ASSERT(res.has_edge("A->B"));
  ASSERT(res.has_edge("C->B"));
  ASSERT(res.has_edge("B->D"));

  ASSERT(res.edge_count() == 3);
}
UNITTEST(graph_union_disjoint){
  g uut1{ "A", "B", "C" };
  g uut2{ "1", "2", "3" };

  uut1("A", "B") = "A->B";
  uut1("C", "A") = "C->A";

  uut2("1", "2") = "1->2";

  auto res = uut1 || uut2;


  ASSERT(res.has_node("A"));
  ASSERT(res.has_node("B"));
  ASSERT(res.has_node("C"));
  ASSERT(res.has_node("1"));
  ASSERT(res.has_node("2"));
  ASSERT(res.has_node("3"));

  ASSERT(res.has_edge("1->2"));
  ASSERT(res.has_edge("A->B"));
  ASSERT(res.has_edge("C->A"));
}


UNITTEST(Ease_of_use_graph_create_sample){
  g uut{ "A", "B", "C" };

  uut("A", "B") = "edge1";
  uut("A", "C") = "edge2";
  uut("A", "C") = "edge2b";

  ASSERT(uut.edge_count() == 2);
  ASSERT(uut.has_edge("edge1"));
  ASSERT(uut.has_edge("edge2b"));
  ASSERT(!uut.has_edge("edge2"));

}

UNITTEST(edge_operator_creates_edge){
  g uut{ "A", "B", "C" };
  uut("A", "B");
  ASSERT(uut.edge_count() == 1);
  ASSERT(uut.has_edge("A", "B"));
}
UNITTEST(find_edge_mutable){

  g uut{ "A", "B", "C" };

  uut.add_edge("A", "B", "A->B");


  ASSERT(uut.find_edge("A", "B").is_mutable());

}
UNITTEST(edge_view_assign){


  g uut{ "A", "B", "C" };
  uut.add_edge("A", "B", "A->B");
  auto res = uut("A", "B");

  res = "lalala";


  ASSERT(uut.has_edge("lalala"));
  ASSERT(uut.edge_count() == 1);




}
UNITTEST(edge_operator){

  g uut{ "A", "B", "C" };
  uut.add_edge("A", "B", "A->B");
  auto res = uut("A", "B");
  ASSERT(res);
  ASSERT(uut.edge_count() == 1);
  ASSERT(uut.has_edge("A->B"));
}

UNITTEST(construct_graph_with_initializer_list){
  g uut{ "A", "B", "C" };

  ASSERT(uut.node_count() == 3);
  ASSERT(uut.has_node("A"));
  ASSERT(uut.has_node("B"));
  ASSERT(uut.has_node("C"));

}
UNITTEST(graph_union_with_only_nodes){

  g uut1;
  uut1.add_node("A");

  g uut2;
  uut2.add_node("B");


  auto res = uut1 || uut2;

  ASSERT(res.node_count() == 2);
  ASSERT(res.has_node("A"));
  ASSERT(res.has_node("B"));

}

UNITTEST(graph_union_with_empty_graphs){
  g uut1;
  g uut2;
  auto res = uut1 || uut2;
  ASSERT(res.is_empty());
}





UNITTEST(has_edge_by_data){

  g uut;
  uut.add_node("A");
  uut.add_edge("A", "A", "dd");
  ASSERT(uut.has_edge("dd"));
  ASSERT(!uut.has_edge("ff"));

}

UNITTEST(has_edge_by_tail_head){
  g uut;
  uut.add_node("A");
  uut.add_node("B");


  ASSERT(!uut.has_edge("A", "B"));
  uut.add_edge("A", "B");

  ASSERT(uut.has_edge("A", "B"));
}




UNITTEST(graph_only_allows_unique_nodes){
  g uut;

  auto res = uut.add_node("A");
  ASSERT(res);
  res = uut.add_node("A");
  ASSERT(!res);
}

UNITTEST(graph_is_empty){
  g uut;
  ASSERT(uut.is_empty());
  uut.add_node("A");
  ASSERT(!uut.is_empty());
}

UNITTEST(graph_is_null){
  g uut;
  ASSERT(uut.is_null());
  uut.add_node("A");
  ASSERT(uut.is_null());
  uut.add_edge("A", "A");
  ASSERT(!uut.is_null());
}

UNITTEST(auto_convert_node_view){
  auto a = 2 + 2;


  auto fu = [](nv view){return view; };

  auto res = fu("asd");
}

UNITTEST(add_undirected_edge){
  g uut;
  uut.add_node("A");
  uut.add_node("B");
  ASSERT(uut.add_undirected_edge("A", "B") == 2);

  ASSERT(uut.edge_count() == 2);
  ASSERT(uut.find_edge("A", "B"));
  ASSERT(uut.find_edge("B", "A"));

}

UNITTEST(create_edge_view_by_data_query){
  ev uut = "ABC";
  ASSERT(uut.index() == -1);
  ASSERT(!uut);
  ASSERT(uut.data_query() == "ABC");
  ASSERT(!uut.head());
  ASSERT(!uut.tail());
  ASSERT(!uut.head_query());
  ASSERT(!uut.tail_query());

  ASSERT(uut.tail_index() == -1);
  ASSERT(uut.head_index() == -1);
  ASSERT(!uut.graph());

}
UNITTEST(create_edge_view_by_index){
  ev uut = 3;
  ASSERT(uut.index() == 3);
  ASSERT(!uut);
  ASSERT(!uut.head());
  ASSERT(!uut.tail());
  ASSERT(!uut.head_query());
  ASSERT(!uut.tail_query());

  ASSERT(uut.tail_index() == -1);
  ASSERT(uut.head_index() == -1);
  ASSERT(!uut.graph())
}
UNITTEST(create_edge_view_default){
  ev uut;
  ASSERT(uut.index() == -1);
  ASSERT(!uut);
  ASSERT(!uut.head());
  ASSERT(!uut.tail());
  ASSERT(uut.tail_index() == -1);
  ASSERT(uut.head_index() == -1);
  ASSERT(!uut.head_query());
  ASSERT(!uut.tail_query());
  ASSERT(!uut.graph());
}
UNITTEST(create_edge_view_by_tail_head){
  ev uut(nv("A"), nv("B"));
  ASSERT(!uut);
  ASSERT(uut.tail_query().data_query() == "A");
  ASSERT(uut.head_query().data_query() == "B");
  ASSERT(!uut.head());
  ASSERT(!uut.tail());
  ASSERT(uut.tail_index() == -1);
  ASSERT(uut.head_index() == -1);
  ASSERT(!uut.graph());
}

UNITTEST(resolve_edge_by_data){
  g uut;

  uut.add_node("A");
  uut.add_node("B");
  uut.add_node("C");

  auto e1 = uut.add_edge("A", "B", "A->B");
  auto e2 = uut.add_edge("B", "C", "B->C");
  auto e3 = uut.add_edge("A", "C", "A->C");

  auto res = uut.resolve_edge(std::string("A->C"));
  ASSERT(res);
}
UNITTEST(resolve_edge_by_idx){

  g uut;

  uut.add_node("A");
  uut.add_node("B");
  uut.add_node("C");

  auto e1 = uut.add_edge("A", "B", "A->B");
  auto e2 = uut.add_edge("B", "C", "B->C");
  auto e3 = uut.add_edge("A", "C", "A->C");

  auto res = uut.resolve_edge(1);
  ASSERT(res);
  ASSERT(res.tail().data() == "B");
  ASSERT(res.head().data() == "C");
}


UNITTEST(filter_nodes_const){
  g uut;
  auto a = uut.add_node("A");
  uut.add_node("B");
  auto c = uut.add_node("C");

  const g & uut2 = uut;

  auto result = uut2.filter_nodes([](const std::string & str){return str == "A" || str == "C"; });

  ASSERT(result[0] == a);
  ASSERT(result[1] == c);

}

UNITTEST(filter_nodes_mutable){
  g uut;
  auto a = uut.add_node("A");
  uut.add_node("B");
  auto c = uut.add_node("C");

  auto result = uut.filter_nodes([](const std::string & str){return str == "A" || str == "C"; });

  ASSERT(result[0] == a);
  ASSERT(result[1] == c);

}

UNITTEST(remove_node_with_edges){

  g uut;

  uut.add_node("A").add_successor("B").head().add_successor("C");

  ASSERT(uut.remove_node(std::string("B")));
  ASSERT(uut.node_count() == 2);
  ASSERT(uut.find_node("A"));
  ASSERT(!uut.find_node("B"));
  ASSERT(uut.find_node("C"));

  ASSERT(uut.edge_count() == 0);

}

UNITTEST(remove_node_with_edges_left_over){
  g uut;
  uut.add_node("A").add_successor("B").head().add_successor("C");
}
UNITTEST(const_get_incident_edges){

  g uut_;
  const g& uut = uut_;
  uut_.add_node("A");
  uut_.add_node("B");
  uut_.add_node("C");

  uut_.add_edge("A", "B", "AB");
  uut_.add_edge("A", "C", "AC");
  uut_.add_edge("C", "A", "CA");
  uut_.add_edge("C", "B", "CB");

  auto incident_edges = uut.incident_edges(std::string("A"));

  ASSERT(incident_edges.size() == 3);

}
UNITTEST(get_incident_edges){
  g uut;
  uut.add_node("A");
  uut.add_node("B");
  uut.add_node("C");

  uut.add_edge("A", "B", "AB");
  uut.add_edge("A", "C", "AC");
  uut.add_edge("C", "A", "CA");
  uut.add_edge("C", "B", "CB");

  auto incident_edges = uut.incident_edges(std::string("A"));

  ASSERT(incident_edges.size() == 3);


}
UNITTEST(get_outgoing_edges_by_data){
  g uut;
  uut.add_node("A");
  uut.add_node("B");
  uut.add_node("C");

  uut.add_edge("A", "B", "AB");
  uut.add_edge("A", "C", "AC");
  uut.add_edge("C", "A", "CA");
  uut.add_edge("C", "B", "CB");

  auto res = uut.outgoing_edges(std::string("A"));

  ASSERT(res.size() == 2);
}

UNITTEST(get_incoming_edges_by_data){
  g uut;
  uut.add_node("A");
  uut.add_node("B");
  uut.add_node("C");

  uut.add_edge("A", "B", "AB");
  uut.add_edge("A", "C", "AC");
  uut.add_edge("C", "A", "CA");
  uut.add_edge("C", "B", "CB");

  auto res = uut.incoming_edges(std::string("A"));

  ASSERT(res.size() == 1);
}


UNITTEST(node_view_create1){
  nv uut = "asd";
  ASSERT(uut.data_query() == "asd");
  ASSERT(uut.index() < 0);
  ASSERT(!uut);
}

UNITTEST(node_view_create2){
  nv uut = std::string("dad");
  ASSERT(uut.data_query() == "dad");
  ASSERT(uut.index() < 0);
  ASSERT(!uut);
}


UNITTEST(node_view_create3){
  nv uut = 1;
  ASSERT(uut.index() == 1);
  ASSERT(!uut);
}



UNITTEST(resolve_node_by_id){
  g uut;
  auto a = uut.add_node("A");
  ASSERT(uut.resolve(0) == a);
  ASSERT(uut.resolve(std::string("A")) == a);
  ASSERT(uut.resolve(a) == a);
  //ASSERT(uut.resolve("A"));
}


UNITTEST(index_operation){
  g uut;
  auto n = uut.add_node("A");

  auto r = uut[std::string("A")];
  ASSERT(r);
  ASSERT(r == n);

}
UNITTEST(const_index_operation){
  g uut;
  auto n = uut.add_node("A");

  const g& uut2 = uut;
  auto r = uut2[std::string("A")];

  ASSERT(r);
  ASSERT(r == n);
}


UNITTEST(node_view_equality){

  g G;
  G.add_node("A");

  auto uut = G.find_node("A");

  //ASSERT(uut == g::index_type(0));
  //ASSERT(uut == "A");

  //ASSERT(uut != "B");
  //ASSERT(uut != g::index_type(1));



}
UNITTEST(refresh_node_view_data){
  g G;
  G.add_node("A");
  auto n = G.add_node("B");
  G.add_node("C");
  nv uut = "B";

  uut = G.resolve(uut);

  ASSERT(uut);
  ASSERT(n == uut);
}
UNITTEST(refresh_node_view_id){
  g G;
  G.add_node("A");
  auto n = G.add_node("B");
  G.add_node("C");

  nv uut = n.index();
  ASSERT(!uut);
  uut = G.resolve(uut);

  ASSERT(uut);
  ASSERT(uut == n);
  ASSERT(uut.data() == "B");

}



UNITTEST(node_view_create_index){
  nv uut = g::index_type(2);
  ASSERT(uut.index() == 2);
  ASSERT(!uut);
}



UNITTEST(find_node_if_by_data){
  g uut;
  uut.add_node("A");
  auto e = uut.add_node("B");
  uut.add_node("C");

  auto n = uut.find_node_if([](const std::string & data){
    return data == "B";
  });



  ASSERT(n);
  ASSERT(n == e)
}
UNITTEST(find_node_if_by_view){
  g uut;
  uut.add_node("A");
  auto e = uut.add_node("B");
  uut.add_node("C");


  auto n = uut.find_node_if([](const g::node_view_type & data){
    return data.data() == "B";
  });

  ASSERT(n);
  ASSERT(n == e)
}
UNITTEST(add_successor_by_node_view){
  g uut;

  uut.add_node("A");
  auto n = uut.find_node("A");
  n.add_successor("B");
  ASSERT(uut.node_count() == 2);
  ASSERT(uut.edge_count() == 1);

  ASSERT(uut.find_node("B"));
  ASSERT(uut.find_edge("A", "B"));
}
UNITTEST(add_predecessor_by_node_view){
  g uut;
  uut.add_node("B");
  auto n = uut.find_node("B");
  n.add_predecessor("A");
  ASSERT(uut.node_count() == 2);
  ASSERT(uut.edge_count() == 1);

  ASSERT(uut.find_node("B"));
  ASSERT(uut.find_edge("A", "B"));

}
UNITTEST(remove_last_edge){
  g uut;
  uut.add_node("A");
  uut.add_node("B");

  uut.add_edge("A", "B", "A->B");

  ASSERT(uut.remove_edge("A", "B"));
  ASSERT(uut.node_count() == 2);
  ASSERT(uut.edge_count() == 0);
  ASSERT(uut.edges().size() == 0);
  ASSERT(!uut.find_edge("A", "B"));

}

UNITTEST(get_outgoing_edges_after_remove){
  g uut;
  uut
    .add_node("A")
    .add_successor("B", "A->B")
    .head()
    .add_successor("C", "B->C");

  uut.remove_edge("A->B");

  auto edges = uut.outgoing_edges(std::string("A"));
  ASSERT(edges.size() == 0);

}
UNITTEST(get_incomming_edges_after_remove){

  g uut;
  uut
    .add_node("A")
    .add_successor("B", "A->B")
    .head()
    .add_successor("C", "B->C");

  uut.remove_edge("A->B");

  auto edges = uut.incoming_edges(std::string("B"));
  ASSERT(edges.size() == 0);
}
UNITTEST(get_incoming_edges){

  g uut;

  uut.add_node("A");
  uut.add_node("B");
  uut.add_node("C");

  auto e1 = uut.add_edge("A", "B", "A->B");
  auto e2 = uut.add_edge("B", "C", "B->C");
  auto e3 = uut.add_edge("A", "C", "A->C");


  auto edges1 = uut.incoming_edges(uut.find_node("A"));
  auto edges2 = uut.incoming_edges(uut.find_node("B"));
  auto edges3 = uut.incoming_edges(uut.find_node("C"));


  ASSERT(edges1.size() == 0);
  ASSERT(edges2.size() == 1);
  ASSERT(edges3.size() == 2);

  ASSERT(edges2[0] == e1);

  ASSERT(edges3[1] == e3);
  ASSERT(edges3[0] == e2);
}

UNITTEST(get_edge_by_index_after_delete){

  g uut;

  uut.add_node("A");
  uut.add_node("B");
  uut.add_node("C");

  auto e1 = uut.add_edge("A", "B", "A->B");
  auto e2 = uut.add_edge("B", "C", "B->C");
  auto e3 = uut.add_edge("A", "C", "A->C");


  uut.remove_edge("A->C");

}
UNITTEST(get_outgoing_edges){// also incomming edges
  g uut;

  uut.add_node("A");
  uut.add_node("B");
  uut.add_node("C");

  auto e1 = uut.add_edge("A", "B", "A->B");
  auto e2 = uut.add_edge("B", "C", "B->C");
  auto e3 = uut.add_edge("A", "C", "A->C");

  auto oe1 = uut.outgoing_edges(uut.find_node("A"));
  auto oe2 = uut.outgoing_edges(uut.find_node("B"));
  auto oe3 = uut.outgoing_edges(uut.find_node("C"));

  ASSERT(oe1.size() == 2);
  ASSERT(oe2.size() == 1);
  ASSERT(oe3.size() == 0);



  ASSERT(e1 == oe1[0]);
  ASSERT(e2 == oe2[0]);
  ASSERT(e3 == oe1[1]);

}


UNITTEST(find_edge_by_connected_nodes){
  g uut;
  uut.add_node("A");
  uut.add_node("B");
  uut.add_node("C");

  uut.add_edge("A", "B", "A->B");
  uut.add_edge("B", "C", "B->C");

  auto edge = uut.find_edge(1, 2);
  bool e = edge;
  ASSERT(!!edge);


}
UNITTEST(add_edge_by_data){
  g uut;
  auto a = uut.add_node("A");
  auto b = uut.add_node("B");
  auto e = uut.add_edge("A", "B", "A->B");
  ASSERT(e);
  ASSERT(e.tail() == a);
  ASSERT(e.head() == b);

  ASSERT(e.data() == "A->B");

}

UNITTEST(multi_add_edge_by_data){
  g uut;
  uut.add_node("A");
  uut.add_node("B");
  uut.add_node("C");


  auto e1 = uut.add_edge("A", "B", "A->B");
  auto e2 = uut.add_edge("B", "C", "B->C");

  ASSERT(uut.edge_count() == 2);

  ASSERT(e1.tail() == uut.find_node("A"));
  ASSERT(e1.head() == uut.find_node("B"));


  ASSERT(e2.tail() == uut.find_node("B"));
  ASSERT(e2.head() == uut.find_node("C"));
}



UNITTEST(single_add_edge_to_self){
  g uut;
  uut.add_node("A");
  auto view = uut.add_edge(uut.find_node("A"), uut.find_node("A"), "MyEdge");



  ASSERT(view);

  ASSERT(view.data() == "MyEdge");
  ASSERT(view.tail() == uut.find_node("A"));
  ASSERT(view.head() == uut.find_node("A"));
  ASSERT(view.tail_index() == view.head_index());
  ASSERT(uut.edge_count() == 1);
  ASSERT(uut.edges().size() == 1);
  ASSERT(uut.successors(uut.find_node("A")).size() == 1);
  ASSERT(uut.predecessors(uut.find_node("A")).size() == 1);
  ASSERT(uut.find_edge("MyEdge") == view);
  ASSERT(uut.find_edge(uut.find_node("A"), uut.find_node("A")) == view);



}
UNITTEST(add_multiple_edges){
  g uut;

  uut.add_node("A");
  uut.add_node("B");
  uut.add_node("C");


}
UNITTEST(single_add_edge){
  g uut;
  uut.add_node("A");
  uut.add_node("B");

  auto edge = uut.add_edge(uut.find_node("A"), uut.find_node("B"), "A->B");


  ASSERT(edge);
  ASSERT(edge.index() > -1);
  ASSERT(edge.tail() == uut.find_node("A"));
  ASSERT(edge.head() == uut.find_node("B"));
  ASSERT(uut.find_edge("A->B") == edge);
  ASSERT(uut.successors(uut.find_node("A")).size() == 1);
  ASSERT(uut.predecessors(uut.find_node("A")).size() == 0);
  ASSERT(uut.successors(uut.find_node("B")).size() == 0);
  ASSERT(uut.predecessors(uut.find_node("B")).size() == 1);
  ASSERT(uut.find_edge("A", "B") == edge);

}

UNITTEST(instance_test){
  g uut;
  ASSERT(uut.nodes().size() == 0);
  ASSERT(uut.node_count() == 0);
  ASSERT(uut.edge_count() == 0);
  ASSERT(uut.edges().size() == 0);

}
UNITTEST(add_node){
  g uut;

  auto a = uut.add_node("A");
  auto b = uut.add_node("B");
  auto c = uut.add_node("C");

  ASSERT(a.index() > -1);
  ASSERT(b.index() > -1);
  ASSERT(c.index() > -1);

  ASSERT(a.data() == "A");
  ASSERT(b.data() == "B");
  ASSERT(c.data() == "C");


  ASSERT(uut.nodes().size() == 3);


  auto nodes = uut.nodes();


  ASSERT(uut.resolve(0) == a);
  ASSERT(uut.resolve(1) == b);
  ASSERT(uut.resolve(2) == c);



  ASSERT(uut.node_count() == 3);
}



UNITTEST(find_node){
  g uut;
  uut.add_node("A");
  uut.add_node("B");
  uut.add_node("C");

  auto n = uut.find_node("B");
  ASSERT(n.index() == 1);
  ASSERT(n.data() == "B");
}

UNITTEST(find_node_no_nodes){
  g uut;
  ASSERT(!uut.find_node("B"));
}
UNITTEST(find_node_node_match){
  g uut;
  uut.add_node("A");
  uut.add_node("B");
  ASSERT(!uut.find_node("C"));
}

UNITTEST(node_after_delete){
  g uut;
  uut.add_node("A");
  uut.add_node("B");
  uut.add_node("C");
  uut.add_node("D");


  ASSERT(uut.remove_node(uut.find_node("B")));
  ASSERT(uut.remove_node(uut.find_node("C")));


  ASSERT(uut.node_count() == 2);
  ASSERT(uut.nodes().size() == 2);
  ASSERT(uut.resolve(std::string("A")));
  ASSERT(uut.resolve(std::string("D")));

}

//
//
//typedef adjacency_list<int> graph;
//
//UNITTEST(ShouldCreateAdjacencyList){
//  graph uut;
//
//  ASSERT(uut.node_count() == 0);
//  ASSERT(uut.edge_count() == 0);
//}
//
//
//UNITTEST(ShouldBeAbleToAddAUnconnectedNodeToGraph){
//  graph uut;
//
//  uut.add_node(1);
//
//  ASSERT(uut.node_count() == 1);
//  ASSERT(uut.edge_count() == 0);
//
//}
//UNITTEST(ShouldBeAbleToRemoveAnUnconnectedNodeFromGraph){
//  graph uut;
//
//  uut.add_node(1);
//  uut.remove_node(1);
//
//  ASSERT(uut.node_count() == 0);
//  ASSERT(uut.edge_count() == 0);
//
//}
//
//UNITTEST(ShouldReturnNodeList){
//  graph uut;
//  uut.add_node(1);
//  uut.add_node(2);
//
//  auto list = uut.nodes();
//  ASSERT(list.size() == 2);
//  ASSERT(list[0] == 1);
//  ASSERT(list[1] == 2);
//}
//
//UNITTEST(ShouldBeAbleToConnectNodes){
//  graph uut;
//  uut.add_node(1);
//  uut.add_node(2);
//
//  uut.add_edge(1, 2);
//  ASSERT(uut.node_count() == 2);
//  ASSERT(uut.edge_count() == 1);
//
//
//}
//
//UNITTEST(ShouldReturnCorrectEdgeCount){
//  graph uut;
//  uut.add_node(1);
//  uut.add_node(2);
//  uut.add_edge(1, 2);
//  uut.add_edge(2, 1);
//
//  ASSERT(uut.edge_count() == 2);
//}
//
//
//UNITTEST(ShouldReturnIdOfNode){
//  graph uut;
//
//  uut.add_node(1);
//  uut.add_node(2);
//  uut.add_node(3);
//
//
//  ASSERT(uut.id(1) == 0);
//  ASSERT(uut.id(2) == 1);
//  ASSERT(uut.id(3) == 2);
//
//  auto id = uut.id(4);
//  ASSERT(uut.id(4) == -1);
//}
//
//
//
//UNITTEST(SHouldShowIfNodesAreConnected){
//  graph uut;
//
//  uut.add_node(1);
//  uut.add_node(2);
//  uut.add_node(3);
//
//  uut.add_edge(1, 2);
//  uut.add_edge(3, 1);
//
//  ASSERT(!uut.has_edge(1, 1));
//  ASSERT(uut.has_edge(1, 2));
//  ASSERT(!uut.has_edge(1, 3));
//
//  ASSERT(!uut.has_edge(2, 1));
//  ASSERT(!uut.has_edge(2, 2));
//  ASSERT(!uut.has_edge(2, 3));
//
//  ASSERT(uut.has_edge(3, 1));
//  ASSERT(!uut.has_edge(3, 2));
//  ASSERT(!uut.has_edge(3, 3));
//
//
//
//}
//
//
//UNITTEST(ShouldGiveAccessToEdgeData){
//  adjacency_list<int, int> uut;
//
//  uut.add_node(1);
//  uut.add_node(2);
//
//  uut.add_edge(1, 2);
//
//  auto data = uut.edge(1, 2);
//  *data = 5;
//  ASSERT(data)
//    auto res = *uut.edge(1, 2);
//  ASSERT(res == 5);
//
//}
//
//
//UNITTEST(ShouldReturnTrueIfNodeEdgeDataAndEdgeExists){
//  adjacency_list<int> uut;
//  uut.add_node(1);
//  uut.add_node(2);
//  uut.add_edge(1, 2);
//
//  auto data = uut.edge(1, 2);
//  ASSERT(data);
//
//
//}
//UNITTEST(ShouldReturnFalseIfNoEdgeDataAndEdgeDoesNotExist){
//  adjacency_list<int> uut;
//  uut.add_node(1);
//  uut.add_node(2);
//  uut.add_edge(1, 2);
//  auto data = uut.edge(2, 1);
//  ASSERT(!data);
//}
//
//UNITTEST(ShouldRemoveEdgeWithoutChangingRestOfGraph){
//  graph uut;
//
//  uut.add_node(1);
//  uut.add_node(2);
//  uut.add_node(3);
//
//  uut.add_edge(1, 2);
//  uut.add_edge(2, 3);
//  uut.add_edge(3, 1);
//
//  uut.remove_edge(2, 3);
//
//  ASSERT(uut.edge_count() == 2);
//
//  ASSERT(uut.node_count() == 3);
//  ASSERT(uut.edge(1, 2));
//  ASSERT(uut.edge(3, 1));
//  ASSERT(!uut.edge(2, 3));
//
//}
//
///// returns a graph consisting of 3 unconnected nodes 1,2,3
//auto graph0()->graph{
//  graph uut;
//  uut.add_node(1);
//  uut.add_node(2);
//  uut.add_node(3);
//  return uut;
//}
//
//// returns a graph with 3 nodes which are connected to a cycle
//auto graph1()->graph{
//  graph uut;
//
//  uut.add_node(1);
//  uut.add_node(2);
//  uut.add_node(3);
//
//
//  uut.add_edge(1, 2);
//  uut.add_edge(2, 3);
//  uut.add_edge(3, 1);
//  return uut;
//}
//auto graph2()->graph{
//  graph uut = graph0();
//
//
//
//  uut.add_undirected_edge(1, 2);
//  uut.add_undirected_edge(2, 3);
//  uut.add_undirected_edge(3, 1);
//
//  return uut;
//
//}
//
//
//UNITTEST(ShouldAddUndirectedEdge){
//  graph uut = graph0();
//
//
//  auto res = uut.add_undirected_edge(1, 2);
//  ASSERT(res == 2);
//  ASSERT(uut.edge_count() == 2);
//
//  ASSERT(uut.edge(1, 2));
//  ASSERT(uut.edge(2, 1));
//
//
//
//}
//
//UNITTEST(SHouldAddUndirectedEdge2){
//  graph uut = graph0();
//  uut.add_edge(1, 2);
//
//  auto res = uut.add_undirected_edge(1, 2);
//
//  ASSERT(res == 1);
//  ASSERT(uut.edge_count() == 2);
//  ASSERT(uut.edge(1, 2));
//  ASSERT(uut.edge(2, 1));
//
//}
//
//UNITTEST(shouldAddUndirectedEdge3){
//  graph uut = graph0();
//  uut.add_edge(1, 2);
//  uut.add_edge(2, 1);
//
//  auto res = uut.add_undirected_edge(1, 2);
//  ASSERT(res == 0);
//  ASSERT(uut.edge_count() == 2);
//  ASSERT(uut.edge(1, 2));
//  ASSERT(uut.edge(2, 1));
//}
//
//UNITTEST(SHouldReturnTrueIfIsUndirectedEdge){
//
//  graph uut = graph2();
//
//  ASSERT(uut.is_undirected_edge(1, 2));
//  ASSERT(uut.is_undirected_edge(2, 1));
//
//
//
//}
//UNITTEST(ShoudReturnTrueIfNodesAreConnected){
//
//  graph uut = graph1();
//  ASSERT(uut.is_connected(2, 1) == 1);
//  ASSERT(uut.is_connected(1, 2) == 1);
//
//
//
//}
//
//UNITTEST(ShouldREturnTwoIfNodesAreConnectedUndirectionaly){
//  graph uut = graph2();
//
//  ASSERT(uut.is_connected(1, 2) == 2);
//}
//UNITTEST(ShouldReturnFalseIfNodesAreNoTConnected){
//  graph uut = graph0();
//  ASSERT(!uut.is_connected(1, 2));
//}
//
//
//UNITTEST(SHouldReturnFalseIfIsNotUndirectedEdge){
//  graph uut = graph1();
//
//
//  ASSERT(!uut.is_undirected_edge(1, 2));
//}
//
//
//
//UNITTEST(GetIncommingEdges){
//  graph uut = graph1();
//
//  auto predecessors = uut.predecessors(2);
//  ASSERT(predecessors.size() == 1);
//  ASSERT(predecessors[0] == 1);
//
//
//}
//
//UNITTEST(ShouldDisconnectOutgoingEdges){
//  graph uut = graph1();
//
//  uut.disconnect_outgoing_edges(2);
//
//  ASSERT(uut.edge(1, 2));
//  ASSERT(!uut.edge(2, 3));
//  ASSERT(uut.edge(3, 1));
//
//
//}
//
//UNITTEST(ShouldDisconnectIncommingEdges){
//
//  graph uut = graph1();
//
//
//  uut.disconnect_incomming_edges(2);
//
//  ASSERT(!uut.edge(1, 2));
//  ASSERT(uut.edge(2, 3));
//  ASSERT(uut.edge(3, 1));
//}
//
//
//UNITTEST(ShouldRemoveNodeWithoutChangingGraph){
//
//
//  graph uut;
//  uut.add_node(1);
//  uut.add_node(2);
//  uut.add_node(3);
//
//  uut.add_edge(1, 2);
//  uut.add_edge(2, 3);
//  uut.add_edge(3, 1);
//
//  uut.remove_node(2);
//
//  ASSERT(uut.edge_count() == 1);
//  ASSERT(uut.node_count() == 2);
//
//  ASSERT(!uut.edge(1, 2));
//  ASSERT(!uut.edge(2, 3));
//  ASSERT(uut.edge(3, 1));
//
//  ASSERT(uut.has_node(1));
//  ASSERT(!uut.has_node(2));
//  ASSERT(uut.has_node(3));
//
//}