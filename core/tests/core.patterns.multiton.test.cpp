#include <core.h>
NS_BEGIN(CORE_NAMESPACE)
  namespace multiton{
    class A : public Object{

    public:
      std::string asd(){ return "das"; }
    };
    class B : public Object{

    };
/*
    TEST(1, Multiton){
      Multiton<Object> uut;
      auto a = uut.request<A>();
      CHECK(a == 0);
    }
    TEST(2, Multiton){

      Multiton<Object> uut;
      auto a = uut.require<A>();
      
      CHECK(a != 0);
    }
    TEST(3, Multiton){
      Multiton<Object> uut;
      uut.registerType<B>();
      auto b = uut.request<B>();
      CHECK(b != 0);
    }
    TEST(4, Multiton){
      Multiton<Object> uut;
      auto aa = uut.require<A>();
      auto ab = uut.require<A>();

      CHECK(aa == ab);
    }
*/
  }
NS_END(CORE_NAMESPACE)
