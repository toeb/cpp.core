/**
 * Copyright (C) 2013 Tobias P. Becker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the  rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More information at: https://dslib.assembla.com/
 *
 */
#pragma once
#include <core/core.h>
#include <functional>
#include <algorithm>


#include <core/template/Comparator.h>
#include <core/container/Query.h>
#include <core/container/ObservableCollection.h>

NS_BEGIN(CORE_NAMESPACE)
  /**
   * \brief Set. a generic set (only unique elements allowed)
   */
  template<typename T>
  class Set : public ObservableCollection<T>{
private:

    /**
     * \brief the underlying element vector.
     */
    std::vector<T> _elements;
public:

    /**
     * \brief typedef for predicate.
     */
    typedef std::function<bool (T)> Predicate;

    /**
     * \brief enum of sorting directions.
     */
    enum SortDirection {
      Ascending,Descending
    };

    /**
     * \brief creates a copy from another set.
     *
     * \param original  The original to set.
     */
    Set(const Set<T> &original);

    /**
     * \brief creates a set from a single element.
     *
     * \param element The element to set.
     */
    Set(T element);

    /**
     * \brief creates an empty set.
     */
    Set();

    /**
     * \brief destroys the set.
     */
    virtual ~Set();

    /**
     * \brief removes all elements from the set.
     */
    void clear();

    /**
     * \brief adds a element to the set.
     *
     * \param element The element to add.
     *
     * \return  true if it succeeds, false if it fails.
     */
    virtual bool add(T element);

    /**
     * \brief removes a element from the set.
     *
     * \param element The element to remove.
     *
     * \return  true if it succeeds, false if it fails.
     */
    virtual bool remove(T element);

    /**
     * \brief returns cardinality  (size of the set)
     *
     * \return  .
     */
    operator unsigned int() const;

    /**
     * \brief returns true iff set is empty (size==0)
     *
     * \return  true if it succeeds, false if it fails.
     */
    bool empty() const;

    /**
     * \brief returns the size of the set.
     *
     * \return  .
     */
    size_t size() const;

    /**
     * \brief returns last element.
     *
     * \return  .
     */
    T last();

    /**
     * \brief returns last element.
     *
     * \return  .
     */
    /*const C4180*/ T last() const;

    /**
     * \brief returns the first element.
     *
     * \return  .
     */
    T first();

    /**
     * \brief Gets the first.
     *
     * \return  .
     */
    /*const */ T  first() const;

    /**
     * \brief Sets a value.
     *
     * \param index Zero-based index of the.
     * \param value The value.
     *
     * \return  true if it succeeds, false if it fails.
     */
    inline bool setValue(unsigned int index, const T& value);

    /**
     * \brief Gets a value.
     *
     * \param index           Zero-based index of the.
     * \param [in,out]  value The value.
     *
     * \return  true if it succeeds, false if it fails.
     */
    inline bool getValue(unsigned int index, T & value) const;

    /**
     * \brief Index of the given item.
     *
     * \param item  The item.
     *
     * \return  .
     */
    size_t indexOf(T item) const;

    /**
     * \brief returns the element at index.
     *
     * \param index Zero-based index of the.
     *
     * \return  .
     */
    T  at(unsigned int index);

    /**
     * \brief Ats the given index.
     *
     * \param index Zero-based index of the.
     *
     * \return  .
     */
    const T at(unsigned int index) const;

    /**
     * \brief returns the element at index.
     *
     * \return  The result of the operation.
     */
    T operator() (unsigned int index);

    /**
     * \brief  casting operator.
     *
     * \return  The result of the operation.
     */
    const T operator() (unsigned int index) const;

    /**
     * \brief read access to the std::vector of elements.
     *
     * \return  .
     */
    const std::vector<T> & elements() const;

    /**
     * \brief sorts the elements of this set by using the compare function.
     *
     * \param compare The compare.
     */
    void sort(std::function<bool (const T, const T) > compare);

    /**
     * \brief sorts the elements of this set by comparing their int values (obtained by the toIntValue
     *        function)
     *
     * \param toIntValue  to int value.
     * \param direction   (optional) the direction.
     */
    void sortByIntValue(std::function<int (const T)> toIntValue, SortDirection direction=Ascending);

    /**
     * \brief returns the first element matching the Compartype.
     *
     * \return  The result of the operation.
     */
    template<typename CompareType> T operator() (CompareType val) const;

    /**
     * \brief returns the subset of elements where the predicate evaluates to true.
     *
     * \param predicate The predicate.
     *
     * \return  .
     */
    Set<T> subset(std::function<bool (T)> predicate) const;

    /**
     * \brief returns the subset of elements which are of type T2.
     *
     * \tparam  typename T2 Type of the typename t 2.
     *
     * \return  .
     */
    template<typename T2> Set<T2> subset() const;

    /**
     * \brief selects ResultType from this sets element.
     *
     * \tparam  typename ResultType Type of the typename result type.
     * \param selector  The selector.
     *
     * \return  .
     */
    template<typename ResultType> Set<ResultType> select(std::function<ResultType (T)> selector) const;

    /**
     * \brief returns the first element were the predicate evaluates to true.
     *
     * \param predicate The predicate.
     *
     * \return  .
     */
    T first(Predicate predicate) const;

    /**
     * \brief copies every element were the predicate evaluates to true to the result set.
     *
     * \param [in,out]  result  The result.
     * \param predicate         The predicate.
     */
    void insertInto(Set<T> & result, Predicate predicate) const;

    /**
     * \brief copies every element from other set to this set.
     *
     * \param other Another instance to copy.
     */
    void copyFrom(const Set<T> & other);

    /**
     * \brief copies every element from this set to the other set.
     *
     * \param [in,out]  result  The result.
     */
    void copyTo(Set<T> & result);

    /**
     * \brief returns true if the element is part of the set.
     *
     * \param element The T to test for containment.
     *
     * \return  true if the object is in this collection, false if not.
     */
    bool contains(T element) const;

    bool all(Predicate predicate)const{
      return !any([predicate](T element){return !predicate(element);});
      //return reduce([predicate](T value, bool accu)->bool{return accu && predicate(value);},true);
    }
       
    bool any(Predicate predicate)const{
      for (size_t i = 0; i < size(); i++){
        if(predicate(at(i)))return true;
      }
      return false;
    }

    size_t count(Predicate predicate)const{
      size_t res = 0;
      for (size_t i = 0; i < size(); i++){
        if(predicate(at(i)))res++;
      }
      return res;
    }


    template<typename Result>
    Result reduce(std::function<Result (T , Result )> f, T seed)const{
      Result result = seed;
      foreachElement([f,&result](T value){
        result = f(value,result);
      });
      return result;
    }

    /**
     * \brief reduce into result.
     *
     * \tparam  typename Result Type of the typename result.
     * \param [in,out]  result  The result.
     * \param [in,out]  f       The std::function&lt;void(Result&amp;,T)&gt; to process.
     */
    template<typename Result> void reduce(Result & result, std::function<void (Result &, T )> f) const;

    /**
     * \brief executes action on each element.
     *
     * \param action  The action.
     */
    void foreachElement(std::function<void(T)> action) const;

    /**
     * \brief assigns the elements of another set to this set discarding all current content.
     *
     * \param a The const Set&lt;T&gt;&amp; to process.
     *
     * \return  A shallow copy of this object.
     */
    Set<T> & operator=(const Set<T>&a);

    /**
     * \brief union.
     *
     * \param b The const Set&lt;T&gt; &amp; to process.
     *
     * \return  The result of the operation.
     */
    Set<T> operator|(const Set<T> &b) const;

    /**
     * \brief difference.
     *
     * \param b The const Set&lt;T&gt; &amp; to process.
     *
     * \return  The result of the operation.
     */
    Set<T> operator/(const Set<T> &b) const;

    /**
     * \brief comma  extends the set by the elements of set b ( |= )
     *
     * \param b The const Set&lt;T&gt; &amp; to process.
     *
     * \return  The result of the operation.
     */
    Set<T> & operator,(const Set<T> &b);

    /**
     * \brief exten set by elements of set b.
     *
     * \param b The const Set&lt;T&gt; &amp; to process.
     *
     * \return  The result of the operation.
     */
    Set<T> & operator |=(const Set<T> &b);

    /**
     * \brief removes all elements from set which are also contained in set b (difference equals)
     *
     * \param b The const Set&lt;T&gt; &amp; to process.
     *
     * \return  The result of the operation.
     */
    Set<T> & operator /=(const Set<T> &b);

    /**
     * \brief returns the symmetric difference (xor)
     *
     * \param b The const Set&lt;T&gt; &amp; to process.
     *
     * \return  The result of the operation.
     */
    Set<T> operator ^(const Set<T> &b) const;

    /**
     * \brief returns the symmetric difference (xor)
     *
     * \param b The const Set&lt;T&gt; &amp; to process.
     *
     * \return  The result of the operation.
     */
    Set<T>& operator ^=(const Set<T> &b);

    /**
     * \brief returns the intersection of this set and set b;
     *
     * \param b The const Set&lt;T&gt; &amp; to process.
     *
     * \return  The result of the operation.
     */
    Set<T> operator &&(const Set<T> &b) const;

    /**
     * \brief assigns intersection of this set and set to this;
     *
     * \param b The const Set&lt;T&gt; &amp; to process.
     *
     * \return  The result of the operation.
     */
    Set<T> & operator &=(const Set<T> &b);




    /**
     * \brief returns true if the sets contain exactly the same elements (symmetric difference has a
     *        cardinality of zero)
     *
     * \param b The const Set&lt;T&gt; &amp; to process.
     *
     * \return  true if the parameters are considered equivalent.
     */
    bool operator ==(const Set<T> &b) const;

    /**
     * \brief static are equal test.
     *
     * \param a The const Set&lt;T&gt; &amp; to process.
     * \param b The const Set&lt;T&gt; &amp; to process.
     *
     * \return  true if equal, false if not.
     */
    static bool areEqual(const Set<T> &a, const Set<T> & b);

    /**
     * \brief static symmetric difference.
     *
     * \param a The const Set&lt;T&gt; &amp; to process.
     * \param b The const Set&lt;T&gt; &amp; to process.
     *
     * \return  .
     */
    static Set<T> symmetricDifference(const Set<T> &a, const Set<T> & b);

    /**
     * \brief static difference.
     *
     * \param a The const Set&lt;T&gt; &amp; to process.
     * \param b The const Set&lt;T&gt; &amp; to process.
     *
     * \return  .
     */
    static Set<T> difference(const Set<T> & a, const Set<T> & b);

    /**
     * \brief static union.
     *
     * \param a The const Set&lt;T&gt; &amp; to process.
     * \param b The const Set&lt;T&gt; &amp; to process.
     *
     * \return  .
     */
    static Set<T> unite(const Set<T> & a, const Set<T> & b);

    /**
     * \brief static intersection.
     *
     * \param a The const Set&lt;T&gt; &amp; to process.
     * \param b The const Set&lt;T&gt; &amp; to process.
     *
     * \return  .
     */
    static Set<T> intersect(const Set<T> & a, const Set<T> & b);

    /**
     * \brief tries to add item by dynamically casting it to T.
     *
     * \tparam  typename T2 Type of the typename t 2.
     * \param item  The item.
     *
     * \return  true if it succeeds, false if it fails.
     */
    template<typename T2> bool tryAdd(T2 item);

    /**
     * \brief tries to remove item by dynamically casting it to T.
     *
     * \tparam  typename T2 Type of the typename t 2.
     * \param item  The item.
     *
     * \return  true if it succeeds, false if it fails.
     */
    template<typename T2> bool tryRemove(T2 item);
  };

  //IMPLEMENTATION FOLLOWS:

  template<typename T>
  template<typename T2>
  bool Set<T>::tryAdd(T2 item){
    T test = dynamic_cast<T>(item);
    if(test) return add(test);
    return false;
  }
  template<typename T>
  template<typename T2>
  bool Set<T>::tryRemove(T2 item){
    T test = dynamic_cast<T>(item);
    if(test) return remove(test);
    return false;
  }
  template<typename T>
  Set<T> & Set<T>::operator &=(const Set<T> &b){
    *this = *this && b;
    return *this;
  }

  template<typename T>
  Set<T>&  Set<T>::operator ^=(const Set<T> &b){
    *this = *this ^ b;
    return *this;
  }
  template<typename T>
  void Set<T>::sort(std::function<bool (const T, const T) > compare){
    std::sort(_elements.begin(),_elements.end(),compare);
  }

  template<typename T>
  void Set<T>::sortByIntValue(std::function<int (const T)> toIntValue, SortDirection direction){
    sort([toIntValue,direction](const T a, const T b){
           return direction==Set<T>::Ascending ? (toIntValue(a)<toIntValue(b)) : (toIntValue(a)>toIntValue(b));
         });
  }

  // returns last element

  template<typename T>
  inline bool Set<T>::setValue(unsigned int index, const T& value){
    if(index >= size()) return false;
    if(contains(value)) {
      if(_elements[index]==value) return true;
      return false;
    }
    _elements[index] = value;
    return true;
  }
  template<typename T>
  inline bool Set<T>::getValue(unsigned int index, T & value) const {
    if(index>=size()) return false;
    value = at(index);
    return true;
  }
  template<typename T>
  size_t Set<T>::indexOf(T item) const {
    for (size_t i = 0; i < size(); i++) {
      if(at(i)==item) return i;
    }
    return size();
  }

  template<typename T>
  T Set<T>::last(){
    return at(size()-1);
  }
  // returns last element
  template<typename T>
  /*const*/ T Set<T>::last() const {
    return at(size()-1);
  }

  template<typename T>
  template<typename T2>
  Set<T2> Set<T>::subset() const {
    return subset([] (T t){return dynamic_cast<T2>(t)!=0; }).select<T2>([] (T t){return dynamic_cast<T2>(t); });
  }

  template<typename T>
  template<typename ResultType>
  Set<ResultType> Set<T>::select(std::function<ResultType (T)> selector) const {
    Set<ResultType> result;
    foreachElement([&result, selector](T element){
                     result |= selector(element);
                   });
    return result;
  }

  // returns cardinality  (size of the set)
  template<typename T>
  Set<T>::operator unsigned int() const {
    return size();
  }

  // returns the first element
  template<typename T>
  T Set<T>::first(){
    return at(0);
  }

  template<typename T>
  /*const*/ T Set<T>::first() const {
    return at(0);
  }
  template<typename T>
  T Set<T>::at(unsigned int index){
    if(index >= size()) return T();
    return _elements[index];
  }
  template<typename T>
  const T Set<T>::at(unsigned int index) const {
    if(index >= size()) return T();
    return _elements[index];
  }
  template<typename T>
  T Set<T>::operator() (unsigned int index){
    return at(index);
  }
  template<typename T>
  const T Set<T>::operator() (unsigned int index) const {
    return at(index);
  }

  template<typename T>
  template<typename CompareType>
  T Set<T>::operator() (CompareType val) const {
    return first([&val](T element){
                   return compare(element,val);
                 });
  }

  template<typename T>
  bool Set<T>::empty() const {
    return size()==0;
  }
  template<typename T>
  size_t Set<T>::size() const {
    return _elements.size();
  }
  template<typename T>
  const std::vector<T> & Set<T>::elements() const {
    return _elements;
  }
  template<typename T>
  void Set<T>::clear(){
    std::vector<T> elements = _elements;
    std::for_each(elements.begin(), elements.end(), [this](T element){
                    this->remove(element);
                  });
  }
  template<typename T>
  bool Set<T>::add(T element){
    if(contains(element)) return false;
    _elements.push_back(element);
    this->notifyElementAdded(element);
    return true;
  }
  template<typename T>
  bool Set<T>::remove(T element){
    bool result = Query<T>::remove(_elements,element);
    if(result) this->notifyElementRemoved(element);
    return result;
  }
  template<typename T>
  void Set<T>::copyFrom(const Set<T> & result){
    result.foreachElement([this](T t){
                            this->add(t);
                          });
  }
  template<typename T>
  void Set<T>::copyTo(Set<T> & result){
    foreachElement([&result](T t){
                     result.add(t);
                   });
  }
  template<typename T>
  void Set<T>::insertInto(Set<T> & result, std::function<bool (T) > f) const {
    Query<T>::select(result._elements,_elements,[f](bool & predicate, bool & cont, T elem){
                       predicate = f(elem);
                     });
  }
  template<typename T>
  bool Set<T>::contains(T element) const {
    return !this->subset([element](T e){return compare(e,element); }).empty();
  }

  template<typename T>
  Set<T> Set<T>::subset(std::function<bool (T)> f) const {
    Set<T> result;
    insertInto(result,f);
    return result;
  }

  template<typename T>
  T Set<T>::first(std::function<bool (T)> f) const {
    return Query<T>::selectFirst(_elements,f);
  }

  template<typename T>
  template<typename Result>
  void Set<T>::reduce(Result & result, std::function<void (Result &, T )> f) const {
    foreachElement([&result,f](T elem){
                     f(result,elem);
                   });
  }

  template<typename T>
  void Set<T>::foreachElement(std::function<void(T)> f) const {
    for(size_t i=0; i < _elements.size(); i++) {
      f(_elements[i]);
    }
  }
  template<typename T>
  Set<T> & Set<T>::operator=(const Set<T>&a){
    if(&a==this) return *this;
    clear();
    copyFrom(a);
    return *this;
  }
  template<typename T>
  Set<T>::Set(const Set<T> & original){
    copyFrom(original);
  }
  template<typename T>
  Set<T>::Set(T element){
    add(element);
  }

  template<typename T>
  Set<T>::Set(){}
  template<typename T>
  Set<T>::~Set(){

  }

  //union
  template<typename T>
  Set<T> Set<T>::operator|(const Set<T> &b) const {
    return unite(*this,b);
  }

  //difference
  template<typename T>
  Set<T> Set<T>::operator/(const Set<T> &b) const {
    return difference(*this,b);
  }
  template<typename T>
  Set<T> & Set<T>::operator,(const Set<T> &b){
    *this |= b;
    return *this;
  }
  template<typename T>
  Set<T> & Set<T>::operator |=(const Set<T> &b){
    b.reduce<Set<T> >(*this,[] (Set<T> &accu,T element){
                        accu.add(element);
                      });
    return *this;
  }
  template<typename T>
  Set<T> & Set<T>::operator /=(const Set<T> &b){
    b.reduce<Set<T> >(*this,[] (Set<T> &accu,T element){
                        accu.remove(element);
                      });
    return *this;
  }

  template<typename T>
  Set<T> Set<T>::operator ^(const Set<T> &b) const {
    return symmetricDifference(*this, b);
  }
  template<typename T>
  Set<T> Set<T>::operator &&(const Set<T> &b) const {
    return intersect(*this,b);
  }
  template<typename T>
  bool Set<T>::operator ==(const Set<T> &b) const {
    return areEqual(*this,b);
  }
  template<typename T>
  bool Set<T>::areEqual(const Set<T> &a, const Set<T> & b){
    return symmetricDifference(a,b).size()==0;
  }
  template<typename T>
  Set<T> Set<T>::symmetricDifference(const Set<T> &a, const Set<T> & b){
    return unite(difference(a,b),difference(b,a));
  }
  template<typename T>
  Set<T> Set<T>::difference(const Set<T> & a, const Set<T> & b){
    Set<T> result;
    result.copyFrom(a);
    b.reduce<Set<T> >(result,[] (Set<T> &accu, T element){
                        accu.remove(element);
                      });
    return result;
  }
  template<typename T>
  Set<T> Set<T>::unite(const Set<T> & a, const Set<T> & b){
    Set<T> result;
    result.copyFrom(a);
    b.reduce<Set<T> >(result,[] (Set<T>&accu, T element){
                        if(!accu.contains(element)) accu.add(element);
                      });
    return result;
  }
  template<typename T>
  Set<T> Set<T>::intersect(const Set<T> & a, const Set<T> & b){
    Set<T> result;
    b.reduce<Set<T> >(result,[&a](Set<T> &accu, T element){
                        if(a.contains(element)) accu.add(element);
                      });
    return result;
  }
NS_END(CORE_NAMESPACE)
