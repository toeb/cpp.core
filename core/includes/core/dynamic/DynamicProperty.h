#pragma once
#include <core/dynamic/dynamic.h>
#include <core/dynamic/dynamic.types.h>
NS_BEGIN(CORE_DYNAMIC_NAMESPACE)
class DynamicObject;
/// Class for accessing DynamicObject's properties by indexer
class DynamicProperty{
  friend class DynamicObject;
protected:
  // constructor
  inline DynamicProperty(DynamicObject obj, const member_name_type & key);
public:
  // no copy constructor todo....
  //DynamicProperty(const DynamicProperty &) = delete;

  

  // custom conversion to any
  inline any to_any()const;
  template<typename T, typename TNext = typename std::enable_if<!std::is_same<typename std::decay<T>::type, DynamicProperty>::value, T>::type>
  DynamicProperty & operator=(T && val);
  inline DynamicProperty & operator=(const DynamicProperty & other);
  // set property;
  inline void set(DynamicObject  val);
  inline DynamicObject get()const;

  inline any value()const;// todo remove


  inline auto operator[](const member_name_type & key)->DynamicProperty;


  // cast operations
  template<typename T> operator T();
  template<typename T> T as();
  inline operator DynamicObject();

  // vararg call operator  DynamicProperty& prop; prop(1,2, any(3), DynamicObject(4));....
  template<typename ... TArgs> DynamicObject operator()(TArgs && ... args);

  // dynamic call operations for any type of std container or vector of any (initializer lsit constructor usable ie
  //  call({2,3,4}); // in that case usage of operator() would be easier
  template<typename TArgumentList> DynamicObject call(const TArgumentList & arguments);
  inline DynamicObject call(const argument_list_type & arguments);
private:
  DynamicObject  _object;
  member_name_type _name;
};
inline static std::ostream & operator<< (std::ostream & out, const DynamicProperty & prop){
  out << static_cast<DynamicObject>(prop);
  return out;
}
NS_END(CORE_DYNAMIC_NAMESPACE)

#include <core/dynamic/DynamicProperty.Implementation.h>
