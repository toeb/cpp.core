#include <core.testing.h>

#include <core/dynamic_call.h>
NS_USE(CORE_NAMESPACE);
using namespace std;
int dynamic_call_function_test(int i, int l){ return i + l; }
UNITTEST(dynamic_call_function){
  auto result = dynamic_call(&dynamic_call_function_test, { 1, 2 });
  ASSERT(result.as<int>() == 3);
}

void dynamic_call_function_test_void(int i, int j){}
UNITTEST(dynamic_call_member_function_const_from_value_type){
  auto result = dynamic_call(&dynamic_call_function_test_void, vector < any > {1, 2});
}

UNITTEST(dynamic_call_member_function_const_from_const_value_type){
  struct A{ int _val;  A(int i) :_val(i){}; int add(int i, int j)const{ return i + j + _val; }; };
  const A a(2);
  auto result = dynamic_call(&A::add, vector < any > {a, 1, 2});
  ASSERT(result.as<int>() == 5);
}
UNITTEST(dynamic_call_member_function_const_from_raw_ptr){
  struct A{ int _val;  A(int i) :_val(i){}; int add(int i, int j)const{ return i + j + _val; }; };
  auto result = dynamic_call(&A::add, vector < any > {new A(3), 1, 2});
  ASSERT(result.as<int>() == 6);
}

UNITTEST(dynamic_call_member_function_const_from_const_raw_ptr){
  struct A{ int _val;  A(int i) :_val(i){}; int add(int i, int j)const{ return i + j + _val; }; };
  const A* a = new A(3);
  auto result = dynamic_call(&A::add, vector < any > {a, 1, 2});
  ASSERT(result.as<int>() == 6);
}
UNITTEST(dynamic_call_member_function_const_from_shared_ptr){
  struct A{ int _val;  A(int i) :_val(i){}; int add(int i, int j)const{ return i + j + _val; }; };
  auto ptr = make_shared<A>(4);
  auto result = dynamic_call(&A::add, vector < any > {ptr, 1, 2});
  ASSERT(result.as<int>() == 7);
}
UNITTEST(dynamic_call_member_function_const_from_const_shared_ptr){
  struct A{ int _val;  A(int i) :_val(i){}; int add(int i, int j)const{ return i + j + _val; }; };
  const std::shared_ptr<const A> ptr = make_shared<const A>(4);
  auto result = dynamic_call(&A::add, vector < any > {ptr, 1, 2});
  ASSERT(result.as<int>() == 7);
}

UNITTEST(dynamic_call_member_function_const_from_weak){
  struct A{ int _val;  A(int i) :_val(i){}; int add(int i, int j)const{ return i + j + _val; }; };
  auto ptr = make_shared<A>(5);
  auto wptr = std::weak_ptr<A>(ptr);
  auto result = dynamic_call(&A::add, vector < any > {wptr, 1, 2});
  ASSERT(result.as<int>() == 8);

}



UNITTEST(dynamic_call_member_function_non_const_from_raw_ptr){
  struct A{ int _val;  A(int i) :_val(i){}; int add(int i, int j){ return i + j + _val; }; };
  auto result = dynamic_call(&A::add, vector < any > {new A(3), 1, 2});
  ASSERT(result.as<int>() == 6);
}


UNITTEST(dynamic_non_void_const_call_functor_from_value_type){
  struct A{ int _val; A(int i) :_val(i){}; int operator()(int i, int j)const{ return i + j + _val; } };

  auto result = dynamic_call(A(-1), { 1, 1 });
  ASSERT(result.as<int>() == 1);
}



UNITTEST(dynamic_void_non_const_call_functor_from_value_type){
  struct A{ int & _val; A(int & i) :_val(i){}; void operator()(int i, int j){ _val = _val + i + j; } };
  int i = 3;
  A a(i);
  auto result = dynamic_call(a, { 1, 1 });

  ASSERT(i == 5);
}

UNITTEST(dynamic_void_const_call_functor_from_value_type){
  struct A{ int & _val; A(int & i) :_val(i){}; void operator()(int i, int j)const{ _val = _val + i + j; } };
  int i = 3;
  A a(i);
  auto result = dynamic_call(a, { 1, 1 });

  ASSERT(i == 5);
}

UNITTEST(dynamic_non_void_non_const_call_functor_from_value_type){
  struct A{ int _val; A(int i) :_val(i){}; int operator()(int i, int j){ return i + j + _val; } };

  auto result = dynamic_call(A(-1), { 1, 1 });
  ASSERT(result.as<int>() == 1);
}
UNITTEST(dynamic_call_lambda_test){

  auto result = dynamic_call([](int i, int j){return i + j + 2; }, { 1, 3 });
  ASSERT(result.as<int>() == 6);

}
UNITTEST(dynamic_std_call_test){
  auto result = dynamic_call(std::function<int(int, int)>([](int i, int j){
    return i + j - 4;
  }), { 3, 3 });
  ASSERT(result.as<int>() == 2);
}
