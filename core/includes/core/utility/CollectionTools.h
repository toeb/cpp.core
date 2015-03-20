#pragma once
#include <core/core.h>
#include <type_traits>

//todo rename file to cotnainertools.h

NS_BEGIN(CORE_NAMESPACE)

/// return true iff c contains val
template<typename TContainer, typename T>
bool contains(const TContainer & c, const T & val);
/// return true iff an element e of c exists for which pred(c) ==true
template<typename TContainer, typename TPredicate>
bool any_of(const TContainer & c, TPredicate pred);
/// returns true iff a contains any element of b
template<typename TContainerA, typename TContainerB>
bool containsAnyOf(const TContainerA & a, const TContainerB & b);
/// returns true iff a contains any element of args
template<typename TContainer, typename ... TArgs>
bool containsAny(const TContainer & a, TArgs && ... args);
/// returns true iff all specified variable args are element of Container
template<typename TContainer, typename ... TArgs>
bool containsAll(const TContainer & container, TArgs && ... args);
/// returns true if all elements of containerB are contained in containerA
template<typename TContainerA, typename TContainerB>
bool containsAllOf(const TContainerA & containerA, const TContainerB & containerB);
// assumes a and b are sorted return the difference of cotnainer a and cotnainer b
template<typename TContainer1, typename TContainer2, typename TResultContainer = std::vector<typename TContainer1::value_type>>
TResultContainer difference(const TContainer1 & a, const TContainer2 & b);
/// concatenates container1 to container 2 
template<typename TContainer>
typename std::decay< TContainer >::type  concat(TContainer && container1, TContainer && container2);
/// return true if every element of b is contained in a and no more(order is irrelevant)
template<typename TContainerA, typename TContainerB>
bool elements_equal(const TContainerA & a, const TContainerB & b);
/// returns true iff container only contains the elements specified as args (order is irrelevant)
template<typename TContainer, typename ... TArgs>
bool elements_equal_arguments(const TContainer & container, TArgs && ...args);
/// uses the selector funciton on every element of the container returning a new container of elements with the same type as the return value of selector
template<typename TContainer, typename TSelectorFunc, typename TRes = std::vector<typename std::decay<decltype(std::declval<TSelectorFunc>()(std::declval<typename TContainer::value_type>()))>::type>>
TRes select(const TContainer & container, TSelectorFunc selector);
/// checks wether container a and container b have exactly the same elements in the same order
template<typename TContainerA, typename TContainerB>
bool order_equals(const TContainerA & a, const TContainerB& b);
/// checks wether container a has exactly same elements as passed as varargs
template<typename TContainer, typename... TArgs>
bool order_equals_arguments(const TContainer& a, TArgs&&... args);
/// returns truef iff all elements of b are found in a in the same order as specified in b.
/// a=[1,2,3,4]
/// b=[1,3,4] 
/// -> true
template<typename TContainerA, typename TContainerB>
bool contains_partial_order(const TContainerA & a, const TContainerB&b);
/// returns true iff all arguments are found in container in the specified order
template < typename TContainer, typename... TArgs >
bool contains_partial_order_arguments(const TContainer& container, TArgs && ... args);
/// returns the element matched by predicate. if none is found exception is thrown if multiple are found an exception is also thrown, 
/// if no predicate is specified and the container contains exactly one element it is retunred else an exception is thrown
template<typename TContainer, typename TPredicate>
typename TContainer::value_type single(const TContainer & container, TPredicate predicate);
/// returns the first element of the container that matches the predicate. if no predicate is specified the first element of the container is returned
template<typename TContainer, typename TPredicate>
typename TContainer::value_type first(const TContainer&container, TPredicate predicate);
/// same as single however returns the default value if no element of container matches predicate
template<typename TContainer, typename TPredicate>
typename std::enable_if<std::is_default_constructible<typename TContainer::value_type>::value, typename TContainer::value_type>::type
single_or_default(const TContainer & container, TPredicate predicate);
/// same as first however returns the default value if no element matches the predicate
template<typename TContainer, typename TPredicate>
typename std::enable_if<std::is_default_constructible<typename TContainer::value_type>::value, typename TContainer::value_type>::type
first_or_default(const TContainer&container, TPredicate predicate);
/// filters input returning a TResultContainer [default = std::vector] with all elements of input for which predicate holds
template<typename TContainer, typename TPredicate, typename TResultContainer = std::vector<typename TContainer::value_type>>
TResultContainer filter(const TContainer & input, TPredicate predicate);

template<typename TContainer>
auto single_or_default(const TContainer& container)->typename std::enable_if < std::is_default_constructible<typename TContainer::value_type>::value, typename TContainer::const_reference >::type {
  static typename TContainer::value_type default_value;
  auto first = true;

  auto begin = std::begin(container);
  auto end = std::end(container);

  if (begin == end)return default_value;
  if (begin + 1 != end)throw std::exception();
  return *begin;
}

template<typename TContainer>
auto first(const TContainer & container)->typename TContainer::const_reference{
  auto first = std::begin(container);
  if (first == std::end(container))throw std::exception();
  return *first;
}
template<typename TContainer>
auto single(const TContainer & container)->typename TContainer::const_reference{
  auto first = std::begin(container);
  auto end = std::end(container);
  if (first == end)throw std::exception();
  if (first + 1 != end)throw std::exception();
  return *first;
}
}

// implementation
#include <vector>
#include <algorithm>



NS_BEGIN(CORE_NAMESPACE)

template<typename TContainer, typename TPredicate, typename TResultContainer>
TResultContainer filter(const TContainer & input, TPredicate predicate){
  TResultContainer res;
  auto inserter = std::back_inserter(res);
  for (auto & it : input){
    if (predicate(it))*inserter = it;
  }
  return res;
}

template<typename TContainer, typename TPredicate>
typename std::enable_if<std::is_default_constructible<typename TContainer::value_type>::value, typename TContainer::value_type>::type
single_or_default(const TContainer & container, TPredicate predicate ){

  auto it = std::find_if(std::begin(container), std::end(container), predicate);
  if (it == std::end(container))return typename TContainer::value_type();

  auto next = std::find_if(it + 1, std::end(container), predicate);
  if (next != std::end(container))throw std::exception();

  return *it;
}

template<typename TContainer, typename TPredicate >
typename std::enable_if<std::is_default_constructible<typename TContainer::value_type>::value, typename TContainer::value_type>::type
first_or_default(const TContainer&container, TPredicate predicate){
  auto it = std::find_if(std::begin(container), std::end(container), predicate);
  if (it == std::end(container))return typename TContainer::value_type();
  return *it;
}


template<typename TContainer, typename TPredicate>
typename TContainer::value_type single(const TContainer & container, TPredicate predicate){

  auto it = std::find_if(std::begin(container), std::end(container), predicate);
  if (it == std::end(container))throw  std::exception();

  auto next = std::find_if(it + 1, std::end(container), predicate);
  if (next != std::end(container))throw std::exception();

  return *it;
}

template<typename TContainer, typename TPredicate>
typename TContainer::value_type first(const TContainer&container, TPredicate predicate ){
  auto it = std::find_if(std::begin(container), std::end(container), predicate);
  if (it == std::end(container))throw std::exception();
  return *it;
}

template<typename TContainerA, typename TContainerB>
bool contains_partial_order(const TContainerA & a, const TContainerB&b){
  auto currentA = std::begin(a);
  auto currentB = std::begin(b);

  while (currentB != std::end(b)){
    if (currentA == std::end(a))return false;// end of a reached before sequence could be matched
    if (*currentA != *currentB){
      currentA++;
      continue;
    }
    currentB++;
  }
  return true;
}
template < typename TContainer, typename... TArgs >
bool contains_partial_order_arguments(const TContainer& container, TArgs && ... args){
  return contains_partial_order(container, std::vector < typename TContainer::value_type > {args...});
}

template<typename TContainer, typename TSelectorFunc, typename TRes>
TRes select(const TContainer & container, TSelectorFunc selector){
  using namespace std;
  typedef TRes result_container_type;
  typedef typename result_container_type::value_type result_type;
  result_container_type result;
  auto inserter = std::inserter(result, begin(result));
  for (auto & current : container){
    *inserter = selector(current);
  }
  return result;
}


template<typename TContainer>
typename std::decay< TContainer >::type  concat(TContainer && container1, TContainer && container2){
  typedef typename std::decay< TContainer >::type result_type;
  result_type result;
  result.insert(std::end(result), std::begin(container1), std::end(container1));
  result.insert(std::end(result), std::begin(container2), std::end(container2));
  return result;
}

template<typename TContainer, typename T>
bool contains(const TContainer & c, const T & val){
  return std::find(begin(c), end(c), val) != end(c);
}



template<typename TContainer, typename TPredicate>
bool any_of(const TContainer & c, TPredicate pred){
  return std::any_of(std::begin(c), std::end(c), pred);
}

// assumes a and b are sorted
template<typename TContainer1, typename TContainer2, typename TResultContainer>
TResultContainer difference(const TContainer1 & a, const TContainer2 & b){
  TResultContainer result;
  std::set_difference(begin(a), end(a), begin(b), end(b), std::back_inserter(result));
  return result;
}

/// returns true if all elements of containerB are contained in containerA
template<typename TContainerA, typename TContainerB>
bool containsAllOf(const TContainerA & containerA, const TContainerB & containerB){
  bool result = true;
  for (auto & it : containerB){
    result = result && std::find(std::begin(containerA), std::end(containerA), it) != std::end(containerA);
  }
  return result;
}
/// returns true iff all specified variable args are element of Container
template<typename TContainer, typename ... TArgs>
bool containsAll(const TContainer & container, TArgs && ... args){
  return containsAllOf(container, std::vector < typename TContainer::value_type > { args... });
}




template<typename TContainerA, typename TContainerB>
bool containsAnyOf(const TContainerA & a, const TContainerB & b){
  using namespace std;
  static_assert(is_same<typename TContainerA::value_type, typename TContainerB::value_type>::value, "containers' value types need to match");
  for (auto & it : b){
    if (find(begin(a), end(a), it) != end(a))return true;
  }
  return false;
}
template<typename TContainer, typename ... TArgs>
bool containsAny(const TContainer & a, TArgs && ... args){
  return containsAnyOf(a, std::vector < typename TContainer::value_type > {args...});
}
template<typename TContainerA, typename TContainerB>
bool elements_equal(const TContainerA & a, const TContainerB & b){
  return containsAllOf(a, b) && containsAll(b, a);
}

//
template<typename TContainer, typename ... TArgs>
bool elements_equal_arguments(const TContainer & container, TArgs && ...args){
  return elements_equal(container, std::initializer_list<typename TContainer::value_type>{ args... });
}


/// checks wether container a and container b have exactly the same elements in the same order
template<typename TContainerA, typename TContainerB>
bool order_equals(const TContainerA & a, const TContainerB& b){
  static_assert(std::is_same<typename TContainerA::value_type, typename TContainerB::value_type>::value, "expected a and b to have the same value_type");
  auto currentA = std::begin(a);
  auto currentB = std::begin(b);

  while (true){
    auto aEnd = currentA == end(a);
    auto bEnd = currentB == end(b);
    if (aEnd && bEnd)return true;// iterators at same time
    if (aEnd || bEnd)return false;// iterators do not end at same time
    if (*currentA != *currentB)return false;// elements not equal
    currentA++;
    currentB++;
  }
  throw std::exception();
}

/// checks wether container a has exactly same elements as passed as varargs
template<typename TContainer, typename... TArgs>
bool order_equals_arguments(const TContainer& a, TArgs&&... args){
  return order_equals(a, std::vector < typename TContainer::value_type > {args...});
}

NS_END(CORE_NAMESPACE)




