#pragma once

#include <type_traits>
#include <memory>

#include <core/core.h>
#include <core.shim.h>
#include <core/template/is_callable.h>
NS_BEGIN(CORE_NAMESPACE)

  class Type;


  // definitions for type system
  struct type_provider{
    //typedef const Type * type_id;
    typedef size_t type_id;
    inline static bool  areEqual(type_id a, type_id b);
    /// return true if a is assignable to b (a conversion a to be exists or b is the superclass of a)
    inline static bool  isAssignableTo(type_id a, type_id b);
    
    template<typename T> static type_id typeOf();
    template<typename T> static type_id typeOf(const T & t);
    const static type_id unknown_type = 0;
  };
  class any;
  

  /// any class taken from boost and modified
  class any
  {
  public: // structors
    class placeholder;
    typedef type_provider::type_id type_id;
    inline any()noexcept;
    template<typename ValueType, bool = is_callable<ValueType>::value> any(const ValueType & value);
    inline any(const any & other);

    // Move constructor
    inline any(any&& other) noexcept;

    // Perfect forwarding of ValueType
    template<typename ValueType, bool = is_callable<ValueType>::value, bool = has_to_any_op<ValueType>::value>
    any(ValueType&& value
      , typename std::enable_if<!std::is_same<any&, ValueType>::value >::type* = 0 // disable if value has type `any&`
      , typename std::enable_if<!std::is_const<ValueType>::value >::type* = 0// disable if value has type `const ValueType&&`
      , typename std::enable_if<!has_to_any_op<ValueType>::value>::type* = 0// disable if type is custom convertible to any
      );
    
    template<typename ValueType>
    static any explicit_any(ValueType && value);

    template<typename T>
    static placeholder* createContent(T&& t, typename std::enable_if<has_to_any_op<T>::value>::type* = 0);

    template<typename T>
    static placeholder* createContent(T&& t, typename std::enable_if<!has_to_any_op<T>::value>::type* = 0);


    inline ~any() noexcept;
    template<typename T> operator T();

    template<typename TArgumentList> any call(TArgumentList & args);
    template<typename... TArgs> any operator()(TArgs&& ... args);

  public: // modifiers
    inline bool toStream(std::ostream & stream)const;
    inline any & swap(any & rhs) noexcept;
    inline any & operator=(const any& rhs);
    // move assignement
    inline any & operator=(any&& rhs) noexcept;
    // Perfect forwarding of ValueType
    template <class ValueType>  any & operator=(ValueType&& rhs);

  public: // queries
    template<typename T> typename std::enable_if<std::is_default_constructible<T>::value, T>::type as();
    template<typename T> typename std::enable_if<!std::is_default_constructible<T>::value, T>::type as();

    inline bool empty() const noexcept;
    inline void clear() noexcept;
    inline bool isCallable()const;
    inline type_id  type() const noexcept;
    template<typename T> bool is()const{ return type_provider::typeOf<T>() == type(); }
    template<typename T> bool isAssignableTo()const{ return type_provider::isAssignableTo(type(), type_provider::typeOf<T>()); }

  private: // representation

    template<typename ValueType>  friend ValueType * any_cast(any *) noexcept;
    template<typename ValueType>  friend ValueType * unsafe_any_cast(any *) noexcept;
    placeholder * content;
  };

  inline std::ostream & operator<< (std::ostream & out, const any & val){
    val.toStream(out);
    return out;
  }




  /// thrown an any cast is not correct
  class  bad_any_cast : public std::bad_cast
  {
  public:
    virtual const char * what() const noexcept
    {
      return "bad_any_cast: "
      "failed conversion using boost::any_cast";
    }
  };

  /// swaps the contents of the left hand side and right hand side
  inline void swap(any & lhs, any & rhs) noexcept;
  /// casts the any type pointer to a value type
  template<typename ValueType>  ValueType * any_cast(any * operand) noexcept;
  /// 
  template<typename ValueType>  inline const ValueType * any_cast(const any * operand) noexcept;
  template<typename ValueType>  ValueType any_cast(any & operand);
  template<typename ValueType>  inline ValueType any_cast(const any & operand);
  //  template<typename ValueType>  inline ValueType&& any_cast(any&& operand);
  template<typename ValueType>  inline ValueType * unsafe_any_cast(any * operand) noexcept;
  template<typename ValueType>  inline const ValueType * unsafe_any_cast(const any * operand) noexcept;

  //speciializion for custom conversion to any
  template<typename TFrom>
  struct convert_to_any{
    static any convert(TFrom && value){ return value; }
  };
NS_END(CORE_NAMESPACE)

#include <core/any.implementation.h>
