#include <core.testing.h>
#include <core.graph.h>

NS_BEGIN(CORE_NAMESPACE)
  namespace graph{
    namespace test{

      TEST(CreateNode, DataNode){
        DataNode<int> uut(2);
        CHECK(uut.data() == 2);
      }

      TEST(CreateNode2, DataNode){
        DataNode<int> uut(2);
        uut = 9;
        CHECK(uut.data() == 9);
      }

      TEST(CreateNode3, DataNode){
        DataNode<int> uut(2);
        uut = 9;
        int a = uut;
        CHECK(a == 9);
      }


      TEST(Connect1, DataNode){
        DataNode<int> uut1(1);
        DataNode<int> uut2(2);
        uut1 << uut2;
        CHECK(uut1.predecessors().contains(&uut2));
        CHECK(uut2.successors().contains(&uut1));

      }


      TEST(DisConnect1, DataNode){
        DataNode<int> uut1(1);
        DataNode<int> uut2(2);
        uut1 << uut2;

        uut2.successors() /= &uut1;

        CHECK(!uut1.predecessors().contains(&uut2));
        CHECK(!uut2.successors().contains(&uut1));

      }

      TEST(DisConnect2, DataNode){
        DataNode<int> uut1(1);
        DataNode<int> uut2(2);
        uut1 << uut2;

        uut2.remove(&uut1);

        CHECK(!uut1.predecessors().contains(&uut2));
        CHECK(!uut2.successors().contains(&uut1));

      }

      TEST(DFS1, DataNode){
        DataNode<int> uut1 = 1;
        DataNode<int> uut2 = 2;
        DataNode<int> uut3 = 3;
        DataNode<int> uut4 = 4;
        DataNode<int> uut5 = 5;
        DataNode<int> uut6 = 6;
        DataNode<int> uut7 = 7;

        uut1 >> uut2;
        uut1 >> uut3;
        uut2 >> uut4;
        uut2 >> uut5;
        uut3 >> uut6;
        uut3 >> uut7;

        Set<DataNode<int> *> order;
        uut1.dfs([&order](bool & b, DataNode<int> * node){
          order |= node;

        }, [](Set<DataNode<int>* > & successors, const DataNode<int> & current){
          successors |= current.successors();
        });

        int current = 0;
        int actualorder[] = { 1, 2, 4, 5, 3, 6, 7 };

        order.foreachElement([&](DataNode<int> * n){
          int cv = n->data();
          CHECK_EQUAL(actualorder[current++], cv);
        });

      }


      TEST(BFS1, DataNode){
        DataNode<int> uut1 = 1;
        DataNode<int> uut2 = 2;
        DataNode<int> uut3 = 3;
        DataNode<int> uut4 = 4;
        DataNode<int> uut5 = 5;
        DataNode<int> uut6 = 6;
        DataNode<int> uut7 = 7;

        uut1 >> uut2;
        uut1 >> uut3;
        uut2 >> uut4;
        uut2 >> uut5;
        uut3 >> uut6;
        uut3 >> uut7;

        Set<DataNode<int> *> order;
        uut1.bfs([&order](bool & b, DataNode<int> * node){
          order |= node;

        }, [](Set<DataNode<int>* > & successors, const DataNode<int> & current){
          successors |= current.successors();
        });

        int current = 0;
        int actualorder[] = { 1, 2, 3, 4, 5, 6, 7 };

        order.foreachElement([&](DataNode<int> * n){
          int cv = n->data();
          CHECK_EQUAL(actualorder[current++], cv);
        });

      }

    }
  }
NS_END(CORE_NAMESPACE)
