#include <core.testing.h>
#include <core/core.h>
#include <iterator>
#define CORE_COLLECTION_NAMESPACE CORE_NAMESPACE, collection

NS_BEGIN(CORE_COLLECTION_NAMESPACE)

UNITTEST(filter){
  std::vector<int> uut = { 1, 2, 3, 4, 5 };
  auto res = filter(uut, [](const int & v){return v % 2 == 0; });
  ASSERT(core::containsAll(res, 2, 4));
}

UNITTEST(single_or_default_test){
  std::vector<int> uut = { 1, 2, 3, 4 };
  auto res = single_or_default(uut, [](int i){return false; });
  ASSERT(res == 0);
}

UNITTEST(single_or_default_default_test){
  std::vector<int> uut = { 1 };
  auto res = single_or_default(uut);
  ASSERT(res == 1);
}

UNITTEST(first_or_default_test2){
  std::vector<int> uut{ 1, 2, 34 };
  auto res = first_or_default(uut, [](int i){return i == 2; });
  ASSERT(res == 2);
}


UNITTEST(first_test_default_parameter){
  std::vector<int> uut = { 1, 2, 3 };
  auto res = first(uut);
  ASSERT(res == 1);
}
UNITTEST(first_test){
  std::vector<int> uut = { 1, 2, 3, 4 };
  auto res = first(uut, [](int i){return i == 3; });
  ASSERT(res == 3);
}

EXPECTED_EXCEPTION_TEST(first_fail_test, ...){
  std::vector<int> uut{ 1, 2, 3, 4 };
  auto res = first(uut, [](int i){return i == 5; });
}

UNITTEST(single_test){
  std::vector<int> uut = { 1, 3, 2, 4 };
  auto res = single(uut, [](int i){return i == 2; });
  ASSERT(res == 2);

}
EXPECTED_EXCEPTION_TEST(single_fail_test, ...){
  std::vector<int> uut = { 1, 2, 2, 3 };
  single(uut, [](int i){return i == 2; });

}
UNITTEST(single_default_param_test){
  std::vector<int> uut = { 1 };
  auto res = single(uut);
  ASSERT(res == 1);
}


UNITTEST(contains_partial_order_test){
  std::vector<int> uut = { 1, 3, 2, 6, 4, 8, 7 };

  ASSERT(contains_partial_order_arguments(uut, 3, 6, 4, 7));
  ASSERT(contains_partial_order_arguments(uut, 1, 3, 2, 6, 4, 8, 7));
  ASSERT(!contains_partial_order_arguments(uut, 1, 2, 3));
  ASSERT(!contains_partial_order_arguments(uut, 1, 3, 2, 6, 5));
}


UNITTEST(order_equals_test){

  std::vector<int> uut{ 3, 5, 2, 3 };
  ASSERT(order_equals_arguments(uut, 3, 5, 2, 3));
  ASSERT(!order_equals_arguments(uut, 3, 5, 2, 4));
  ASSERT(!order_equals_arguments(uut, 3, 5, 2));
  ASSERT(!order_equals_arguments(uut, 3, 5, 2, 3, 4));

}


UNITTEST(ContainsAllTest){
  std::vector<int> uut = { 1, 2, 3, 4, 5 };
  auto res = containsAll(uut, 3, 4);
  ASSERT(res);
  auto res2 = containsAll(uut, 3, 4, 6);
  ASSERT(!res2);
}

UNITTEST(select_test1){
  std::vector<int> uut = { 1, 2, 3, 4 };
  auto res = select(uut, [](int i){return i * 2; });
  ASSERT(elements_equal_arguments(res, 2, 4, 6, 8));
}
UNITTEST(select_test2){
  std::vector<const char*> uut = { "123", "256" };
  auto res = select(uut, [](const char * str){return atoi(str); });
  ASSERT(elements_equal_arguments(res, 123, 256));

}




UNITTEST(elements_equal_test){
  std::vector<int> uut = { 1, 2, 3 };
  ASSERT(elements_equal_arguments(uut, 3, 1, 2));
  ASSERT(!elements_equal_arguments(uut, 1, 2));
  ASSERT(!elements_equal_arguments(uut, 3, 1, 2, 4));
}

UNITTEST(containsAnyTest){
  std::vector<int> uut = { 1, 2, 3, 4, 5 };
  ASSERT(containsAny(uut, 1, 6, 7, 8));
  ASSERT(!containsAny(uut, 6, 7, 8));
}
template<typename TEnumerator>
struct EnumeratorIterator : public std::iterator<std::input_iterator_tag, typename TEnumerator::value_type>{
  typedef TEnumerator enumerator_type;
  typedef EnumeratorIterator<TEnumerator> iterator_type;
  EnumeratorIterator(enumerator_type & enumerator) :enumerator(enumerator){

  }
  auto operator*()->value_type{
    if (enumerator.before_first())enumerator.move_next();
    return enumerator.operator*();
  }
  auto operator->()->value_type{
    if (enumerator.before_first())enumerator.move_next();
    return enumerator.operator->();
  }
  auto operator++()->EnumeratorIterator& {
    if (enumerator.before_first())enumerator.move_next();
    enumerator.move_next();
    return *this;
  }
  auto operator++(int)->EnumeratorIterator{
    if (enumerator.before_first())enumerator.move_next();
    enumerator.move_next();
    return *this;
  }
  auto operator == ( iterator_type other)const-> bool{
    if (&enumerator != &(other.enumerator))return false;
    enumerator_type a = other.enumerator;
    enumerator_type b = this->enumerator;
    if (a.move_next() || b.move_next())return false;
    return true;
  }
  auto operator != ( iterator_type  other)const-> bool{
    return !operator==(other);
  }
  enumerator_type & enumerator;
};


template<typename TEnumerable>
struct Enumerator {
  typedef TEnumerable enumerable_type;
  typedef typename enumerable_type::const_iterator const_iterator;
  typedef typename enumerable_type::value_type value_type;
  typedef Enumerator<TEnumerable> enumerator_type;
  Enumerator(enumerable_type enumerable) :
    first(true),
    enumerable(enumerable){}

  EnumeratorIterator<enumerator_type> begin(){
    return EnumeratorIterator<enumerator_type>(*this);
  }

  EnumeratorIterator<enumerator_type> end(){
    return EnumeratorIterator<enumerator_type>(*this);
  }


  inline bool move_next(){
    if (first){
      current = enumerable.cbegin();
      first = false;
    }
    else{
      current++;
    }

    return current != enumerable.cend();
  }
  inline bool before_first()const{ return first; }

  inline auto operator*()const -> value_type{ return *current; }


  bool first;
  enumerable_type enumerable;
  const_iterator current;

};

template<typename TEnumerator>
struct EnumeratorBase{
  typedef TEnumerator enumerator_type;
  typedef typename enumerator_type::value_type value_type;
  EnumeratorBase(enumerator_type enumerator) :enumerator(enumerator){}
  inline bool move_next(){
    return enumerator.move_next();
  }
  inline auto operator*()const -> value_type{ return *enumerator; }
  enumerator_type enumerator;
};

template<typename TCollection>
struct Enumerable{
  typedef TCollection collection_type;
  typedef typename collection_type::const_iterator const_iterator;
  typedef Enumerable<TCollection> enumerable_type;
  typedef typename collection_type::value_type value_type;

  Enumerable(const TCollection & collection) :collection(collection){}


  const collection_type & collection;

  Enumerator<enumerable_type> enumerator()const{ return Enumerator<enumerable_type>(*this); }

  const_iterator cbegin()const{ return std::cbegin(collection); }
  const_iterator cend()const{ return std::cend(collection); }

};

template<typename TEnumerator, typename TPredicate>
struct WhereEnumerator : public EnumeratorBase < TEnumerator > {
  typedef TPredicate predicate_type;

  WhereEnumerator(enumerator_type enumerator, predicate_type predicate)
    :EnumeratorBase<TEnumerator>(enumerator),
    predicate(predicate){

  }

  inline bool move_next(){
    while (enumerator.move_next()){
      if (predicate(*enumerator))return true;
    }
    return false;
  }

private:
  predicate_type predicate;
};

template<typename TCollection > 
Enumerable<TCollection> enumerable(const TCollection & collection){
  return Enumerable<TCollection>(collection);
}

template<typename TCollection>
Enumerator<Enumerable<TCollection>> enumerator(const TCollection & collection){
  return Enumerable<TCollection>(collection).enumerator();
}

template<typename T>
Enumerator<Enumerable<std::initializer_list<T>>> enumerator(const std::initializer_list<T> & collection){
  return Enumerable<std::initializer_list<T>>(collection).enumerator();
}
template<typename TCollection, typename TPredicate >
WhereEnumerator<Enumerator<Enumerable<TCollection>>, TPredicate> filter(const TCollection & collection, TPredicate predicate){
  return WhereEnumerator<Enumerator<Enumerable<TCollection>>, TPredicate>(enumerator(collection), predicate);
}
template<typename TEnumerator, typename TSelector>
struct SelectEnumerator : public EnumeratorBase < TEnumerator > {
  typedef TSelector selector_type;
  selector_type selector;
  typedef  decltype(std::declval<selector_type>()(std::declval<typename enumerator_type::value_type>())) value_type;

  SelectEnumerator(enumerator_type enumerator, selector_type selector) :EnumeratorBase(enumerator), selector(selector){}

  inline auto operator*()const -> value_type{ return selector(*enumerator); }

};
template<typename TEnumerator, typename TTarget>
struct CastEnumerator : public EnumeratorBase < TEnumerator > {
  CastEnumerator(enumerator_type enumerator) :EnumeratorBase(enumerator){}


};
//template<typename TTarget, typename TCollection>
//CastEnumerator<Enumerator<Enumerable<TCollection>>, TTarget> cast(const TCollection & collection){
//
//}

template<typename TCollection, typename TSelector>
SelectEnumerator<Enumerator<Enumerable<TCollection>>, TSelector> select(const TCollection & collection, TSelector selector){
  return SelectEnumerator<Enumerator<Enumerable<TCollection>>, TSelector>(enumerator(collection), selector);
}
template<typename TResult, typename TInputEnumerator>
struct EnumeratorOperation{

};



NS_END(CORE_COLLECTION_NAMESPACE)


UNITTEST(Enumerable){
  NS_USE(CORE_COLLECTION_NAMESPACE);
  std::vector<int> vals = { 1, 3, 4, 6, 7, 8, 4, 21, 6, 4, 6 };
  auto uut = enumerable(vals);
  ASSERT(&uut.collection == &vals);
}

UNITTEST(Enumerator){
  NS_USE(CORE_COLLECTION_NAMESPACE);
  std::vector<int> vals = { 1, 2 };
  auto uut = enumerator(vals);
  ASSERT(uut.move_next());
  ASSERT(*uut == 1);
  ASSERT(uut.move_next());
  ASSERT(*uut == 2);
  ASSERT(!uut.move_next());
}
UNITTEST(EmptyEnumerator){
  NS_USE(CORE_COLLECTION_NAMESPACE);
  std::vector<int> vals;
  auto uut = enumerator(vals);
  ASSERT(!uut.move_next());
}

UNITTEST(WhereEnumerator){
  NS_USE(CORE_COLLECTION_NAMESPACE);
  std::vector<int> vals = { 1, 2, 3, 4 };
  auto uut = filter(vals, [](int val){return val % 2 == 1; });
  ASSERT(uut.move_next());
  ASSERT(*uut == 1);
  ASSERT(uut.move_next());
  ASSERT(*uut == 3);
  ASSERT(!uut.move_next());
}
UNITTEST(EmptyWhereEnumerator){
  NS_USE(CORE_COLLECTION_NAMESPACE);
  std::vector<int> vals;
  auto uut = filter(vals, [](int val){return val % 2 == 1; });
  ASSERT(!uut.move_next());
}
UNITTEST(EmptyWhereEnumerator2){
  NS_USE(CORE_COLLECTION_NAMESPACE);
  std::vector<int> vals = { 2, 4, 56 };
  auto uut = filter(vals, [](int val){return val % 2 == 1; });
  ASSERT(!uut.move_next());
}
UNITTEST(SelectEnumerator){
  NS_USE(CORE_COLLECTION_NAMESPACE);
  std::vector<int> vals = { 1, 3 };
  auto uut = select(vals, [](int val)->std::string{std::stringstream ss; ss << val; return ss.str(); });
  ASSERT(uut.move_next());
  ASSERT(*uut == "1");
  ASSERT(uut.move_next());
  ASSERT(*uut == "3");
  ASSERT(!uut.move_next());
}
UNITTEST(SelectEnumerator2){
  NS_USE(CORE_COLLECTION_NAMESPACE);
  std::vector<const char *> vals = { "23", "44" };
  auto uut = select(vals, [](const char * val){return atoi(val); });
  ASSERT(uut.move_next());
  ASSERT(*uut == 23);
  ASSERT(uut.move_next());
  ASSERT(*uut == 44);
  ASSERT(!uut.move_next());
}


UNITTEST(CopyEnumerator){
  NS_USE(CORE_COLLECTION_NAMESPACE);
  
  auto uut =  enumerator({1, 2, 3});
  uut.move_next();
  uut.move_next();
  auto uut2 = uut;
  ASSERT(*uut == 2);
  ASSERT(*uut2 == 2);
  uut2.move_next();
  ASSERT(*uut2 == 3);
  ASSERT(*uut == 2);
  uut.move_next();
  ASSERT(*uut == 3);
  ASSERT(*uut2 == 3);
}



UNITTEST(EnumeratorIterator){
  NS_USE(CORE_COLLECTION_NAMESPACE);
  auto uut = enumerator({ 1, 2, 3, 4 });
  for (auto it : uut){
    auto aa = it;
  }
}