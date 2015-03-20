#pragma once
#include <core/dynamic/dynamic.h>
#include <memory>
#include <ostream>
#include <core/any.h>
#include <core/dynamic/IDynamicObjectImplementation.h>

NS_BEGIN(CORE_DYNAMIC_NAMESPACE)
// forward declaration of any
//forward declartion for used classes
class DynamicProperty;
class DynamicObject {
public:
  typedef  std::shared_ptr<IDynamicObjectImplementation> implementation_ptr;
protected:
  implementation_ptr _implementation;
public:
  // interface operations

  // constructors
  inline DynamicObject(implementation_ptr imp);
  inline DynamicObject();
  template<typename T, typename TDecayed = typename std::decay<T>::type, bool concept =
    !std::is_same<DynamicObject, TDecayed>::value
    &&
    !std::is_same<DynamicProperty, TDecayed>::value
    &&
    !std::is_same<any, TDecayed>::value >

    DynamicObject(T && value,
    typename std::enable_if<concept>::type* = 0
    );
  inline DynamicObject(const DynamicProperty & property);
  inline DynamicObject(const any & value);
  inline DynamicObject(any && value);

  // indexer access to properties (set and get)
  inline auto operator[](const member_name_type & key)->DynamicProperty;
  inline auto operator[](const member_name_type & key)const->const DynamicProperty;
  // call operator
  template<typename... TArgs>
  DynamicObject operator()(TArgs && ... args);
  // list of member names
  inline auto members()const->member_list;

  // set member value
  inline void set(const member_name_type & name, DynamicObject other);
  // get member value
  inline DynamicObject get(const member_name_type & name)const;


  // assignment operators  and copy constructor
  inline DynamicObject(const DynamicObject & other);

  inline DynamicObject & operator=(const DynamicObject & other);
  inline DynamicObject & operator=(const DynamicObject && other);
  inline DynamicObject & operator =(const any & any);
  template<typename T> DynamicObject & operator=(T && t);


  // cast operator
  template<typename T> T as();
  inline  operator any();
  template<typename T> operator T();

  // type id operators
  template<typename T> bool isConvertibleTo();
  inline bool isConvertibleTo(any::type_id typeId);
  inline any::type_id getType()const;

  /// less used operations

  // custom conversion to any 
  inline any to_any()const;

  friend class DynamicProperty;

  // to string conversion
  inline std::string toString()const;
  inline void toStream(std::ostream & out)const;

  // invoke dynamic object 
  template<typename TArgumentList>   DynamicObject call(const TArgumentList & container);
  inline DynamicObject call(const argument_list_type && arguments);

  // invoke member of dynamic object
  template<typename TArgumentList> DynamicObject callMember(const member_name_type & member, const TArgumentList & container);
  inline DynamicObject callMember(const member_name_type & member, const argument_list_type && arguments);



  // assign another dynamic object
  inline void assign(const DynamicObject  & other);




};

static inline std::ostream& operator<<(std::ostream & out, const DynamicObject  & obj){ obj.toStream(out); return out; }
NS_END(CORE_DYNAMIC_NAMESPACE)

#include <core/dynamic/DynamicObject.Implementation.template.h>
