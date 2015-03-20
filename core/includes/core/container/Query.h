#pragma once
#include <core/core.h>
#include <vector>
#include <functional>
#include <algorithm>

NS_BEGIN(CORE_NAMESPACE)
  /**
  * \brief Class contains static methods for common Collection operations.
  * 				CollectionType needs to implement begin() and end() methods which expose the corresponding std::iterators
  * 				also the default constructor needs available
  *
  */
  template<typename T, typename CollectionType=std::vector<T> >
  class Query{
  public:
    static bool remove(CollectionType & elements, T element){
      auto it = find(elements.begin(), elements.end(),element);
      if(it==elements.end())return false;
      elements.erase(it);
      return true;
    }

    //tries to cast all elements of type B to type A returns the number of successful casts
    template<typename A>
    static int cast(CollectionType & result, const CollectionType & source){
      int elementsCast =0;
      std::for_each(source.begin(), source.end(),[&elementsCast,&result](T element){
        A currentElement = dynamic_cast<A>(element);
        if(currentElement){
          result.push_back(currentElement);
          elementsCast++;
        }
      });
      return elementsCast;
    }

    /**
    * \brief executes action on each element.
    *
    * \param collection  The collection.
    * \param action      The action.
    */
    static void foreachElement(const CollectionType & collection, std::function<void (T) > action){
      std::for_each(collection.begin(), collection.end(), action);
    }

    // searches all elements of type t. evaluates predicate function f if first bool is set to true, the element is kept if second element is set to false the search is aborted
    static void select(CollectionType & result, const CollectionType & elements, std::function<void (bool & ,bool & , T) > f){
      for(unsigned int i=0; i < elements.size(); i++){
        bool continueSearch=true;
        bool predicate = false;
        T  currentElement = elements[i];
        f(predicate,continueSearch,currentElement);
        if(predicate){
          result.push_back(currentElement);
        }
        if(!continueSearch) return;
      }
    }
    static T selectFirst( const CollectionType & elements, std::function<bool (T)> f){
      CollectionType result;
      Query<T>::select(result,elements,[f](bool & predicate, bool & continueSearch, T element){
        predicate = f(element);
        if(predicate) continueSearch=false;
      });
      if(result.size())return *result.begin();
      else return 0;
    }
  };
NS_END(CORE_NAMESPACE)
