#pragma once
#include <core/core.h>


NS_BEGIN(CORE_NAMESPACE)
  /**
  * \brief Allows the sharing / desharing of a value.
  * 				Inspiration was taken from the Dissertation of Martin Friedmann (SIM Tu Darmstadt)
  *
  */
  template<typename T>
  class ValueHolder{
  private:
    T _privateValue;
    T* _sharedValue;
  public:

    /**
    * \brief Constructor.
    *  sorry for the bad comment.
    * \author Tobi
    * \date 01.07.2012
    *
    * \param safetyFlagValueARbitrary   added safety flag because else automatic type conversion might occur which would lead to situating were the developer would assign the value holders
    * value in a wrong way:  vh = val results in a new value holder vh() = val results in the values holders value being set
    * \param initialValue The initial value.
    */
    ValueHolder(const T & initialValue, bool safetyFlagValueARbitrary):_privateValue(initialValue),_sharedValue(&_privateValue){
    }
    ValueHolder():_sharedValue(&_privateValue){
    }
    ~ValueHolder(){
      unshare();
    }

    /**
    * \brief Unshares the value continues using a local copy
    *
    */
    void unshare(){
      _privateValue = *_sharedValue;
      _sharedValue = & _privateValue;
    }

    /**
    * \brief Shares newValue with this ValueHolder
    *
    *
    *
    * \param [in,out] newValue The new value.
    */
    void share(T & newValue ){
      _sharedValue = &newValue;
    }
    // causes the other value holders shared value to be copied to this shared value
    void mirror(ValueHolder<T> & source){
      _sharedValue = source._sharedValue;
    }

    /**
    * \brief accessor for the value
    */
    inline T & operator()(){
      return *_sharedValue;
    }
    /**
    * \brief const accessor for the value
    */
    inline const T & operator()()const{
      return *_sharedValue;
    }

    /**
    * \brief shorthand for share using rhs valueholder as source
    */
    ValueHolder<T> & operator<< (ValueHolder<T> & source){
      mirror(source);
      return *this;
    }
    /**
    * \brief shorthand for share using lhs valueholder as source
    */
    ValueHolder<T> & operator>> (ValueHolder<T> & sink){
      sink.mirror(*this);
      return *this;
    }
  };
NS_END(CORE_NAMESPACE)
