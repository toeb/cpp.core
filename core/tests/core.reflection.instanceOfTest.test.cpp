

#ifdef nohtingi
#include <core.h>

NS_BEGIN(CORE_NAMESPACE)
  namespace reflection{
    class A {
      TYPED_OBJECT(A);
    };
    class B:public virtual A{
      TYPED_OBJECT(B);
      SUBCLASSOF(A);


    };

    class C:public virtual B{
      TYPED_OBJECT(C);
      SUBCLASSOF(B);

    };
    class D : public virtual A{
      TYPED_OBJECT(D);
      SUBCLASSOF(A);

    };
    class E {
      TYPED_OBJECT(E);

    };
    class F: public virtual E, public virtual C{
      TYPED_OBJECT(F);
      SUBCLASSOF(E);
      SUBCLASSOF(C);

    };

    TEST(instanceOf1, Object){

      A a;
      B b;
      C c;
      D d;
      E e;
      F f;
      CHECK(f.isInstanceOf(typeof(A)));
    }

    TEST(instanceOf2, Object){

      A a;
      B b;
      C c;
      D d;
      E e;
      F f;
      CHECK(f.isInstanceOf(typeof(E)));
    }
    TEST(instanceOf3, Object){

      A a;
      B b;
      C c;
      D d;
      E e;
      F f;
      CHECK(!e.isInstanceOf(typeof(A)));
    }

  }
NS_END(CORE_NAMESPACE)

#endif