#pragma once
#include <core/core.h>
#include <core/container/Query.h>
#include <core/Observable.h>

NS_BEGIN(CORE_NAMESPACE)
  /**
  * \brief A collection that will notify its observers if elements were added or removed
  */
  template<typename T> class ObservableCollection: public Observable{
  public:
    /**
    * \brief Observer class.
    */
    class Observer{
    public:
      virtual void collectionChanged(ObservableCollection<T> * sender){}
      virtual void elementAdded(ObservableCollection<T> * sender, T element){}
      virtual void elementRemoved(ObservableCollection<T> * sender, T element){}
    };
    class DelegateElementAddedObserver: public Observer{
      std::function<void (ObservableCollection<T> *,T) > _callback;
    public:
      DelegateElementAddedObserver(std::function<void (ObservableCollection<T> *,T) > callback):_callback(callback){}
      void elementAdded(ObservableCollection<T> * sender, T element){_callback(sender,element);}
    };
    class DelegateElementRemovedObserver: public Observer{
      std::function<void (ObservableCollection<T>* ,T) > _callback;
    public:
      DelegateElementRemovedObserver(std::function<void (ObservableCollection<T>* ,T) > callback):_callback(callback){}
      void elementRemoved(ObservableCollection<T> * sender, T element){_callback(sender,element);}
    };
    class DelegateObserver : public Observer{
      std::function<void (ObservableCollection<T> *,T) > _elementAddedCallback;
      std::function<void (ObservableCollection<T> *,T) > _elementRemovedCallback;
    public:
      DelegateObserver(std::function<void (ObservableCollection<T>* ,T) > addedCallback,std::function<void (ObservableCollection<T> *,T) > removedCallback):
        _elementAddedCallback(addedCallback),_elementRemovedCallback(removedCallback){}
      void elementAdded(ObservableCollection<T> * sender, T element){_elementAddedCallback(sender,element);}
      void elementRemoved(ObservableCollection<T> * sender, T element){_elementRemovedCallback(sender,element);}
    };

  private:
    std::vector<Observer*> _observers;
    //std::vector<ObjectObserver*> _objectObservers;
  protected:

    /**
    * \brief gets called when an element is added
    * 				subclasses may implement this
    *
    * \param element The element.
    */
    virtual void onElementAdded(T element){}

    /**
    * \brief called when an element is removed
    * 				subclasses may implement this
    *
    * \param element The element.
    */
    virtual void onElementRemoved(T element){}

    /**
    * \brief Notifies observers that an element was added.
    * 				subclasses should call this
    *
    * \param element The element.
    */
    void notifyElementAdded(T element){
      onElementAdded(element);
      Query<Observer* >::foreachElement(_observers,[this,&element](Observer * observer){
        observer->elementAdded(this,element);
        observer->collectionChanged(this);
      });
      raiseObjectChanged();
      /*      Query<ObjectObserver* >::foreachElement(_objectObservers,[this,&element](ObjectObserver * observer){
      observer->onChange(static_cast<void*>(this));
      });
      */
    }

    /**
    * \brief Notifies observers that an element was removed.
    * 				subclasses should call this
    *
    * \param element The element.
    */
    void notifyElementRemoved(T element){
      onElementRemoved(element);
      Query<Observer* >::foreachElement(_observers,[this,&element](Observer * observer){
        observer->elementRemoved(this,element);
        observer->collectionChanged(this);
      });
      raiseObjectChanged();
      /*
      Query<ObjectObserver* >::foreachElement(_objectObservers,[this,&element](ObjectObserver * observer){
      observer->onChange(static_cast<void*>(this));
      });
      */
    }
  public:

    /**
    * \brief Adds an observer which is notified when collection is changed
    *
    * \param [in]  observer  If non-null, the observer.
    */
    void addObserver(Observer * observer){
      _observers.push_back(observer);
    }
    /*
    void addObserver(ObjectObserver * observer){
    _objectObservers.push_back(observer);
    }*/

    /**
    * \brief Removes the observer described by observer.
    *
    * \param [in]  observer  the observer.
    */

    void removeObserver(Observer * observer){
      Query<Observer*>::remove(_observers,observer);
    }
    /*
    void removeObserver(ObjectObserver * observer){
    Query<ObjectObserver*>::remove(_objectObservers,observer);
    }*/
  };
NS_END(CORE_NAMESPACE)
