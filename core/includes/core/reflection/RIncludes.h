#pragma once
#include <core/core.h>
#include <core/any.h>
#define CORE_REFLECTION2_NAMESPACE CORE_NAMESPACE, refl
NS_BEGIN(CORE_REFLECTION2_NAMESPACE)

typedef std::vector<any> argument_list;


class AttributeTarget;
class ScopeInfo;
class CallableInfo;
class ScopeDeclaration;
class NamespaceInfo;
class ParameterInfo;
class CallableInfo;
class MemberInfo;
class ConstructorInfo;
class MethodInfo;
class FieldInfo;
class TypeInfo;


typedef std::vector< std::shared_ptr<ParameterInfo>> parameter_list;


// access methods
NamespaceInfo & defaultNamespace();
NamespaceInfo & global();
const ScopeDeclaration & unknown();
template<typename T> TypeInfo & reflect();
template<int argumentIndex, typename CallableType> ParameterInfo & reflect_parameter(CallableType callable);
template<typename TCallable> CallableInfo & reflect_callable(TCallable  callable);
template<typename T, int idx> std::shared_ptr<ParameterInfo> create_parameter(CallableInfo & cinfo);
template<typename TTuple, int ... S>  parameter_list create_parameters(CallableInfo & callableInfo, const sequence<S...> & s);
template< int argumentIndex, typename CallableType >  ParameterInfo & reflect_parameter(CallableType callable);
template<typename TClass, typename ... TArgs>  ConstructorInfo & reflect_constructor();
template<typename TCallable>  MethodInfo & reflect_m(TCallable callable);


/// Represents a reflectable element which can have attributes
class AttributeTarget{

};

/// represents a object that can contain declarations like a class, namespace, method
class ScopeInfo{
public:
  typedef std::map<std::string, ScopeDeclaration*>  declaration_map;

  ScopeDeclaration & resolveDeclaration(ScopeDeclaration & declaration);
  // declares a scope declaration returning registering it or returning the existing declaration
  template<typename T>
  typename std::enable_if<std::is_base_of<ScopeDeclaration, T>::value, T>::type &
    declare(T & declaration);

  // declares an scope declaration item
  template<typename T, typename... TArgs>
  typename std::enable_if<std::is_base_of<ScopeDeclaration, T>::value, T>::type &
    declare(TArgs... args);


  // declares a declaration type
  template<typename T>
  typename std::enable_if<
    !std::is_base_of<ScopeDeclaration, T>::value
    &&
    !std::is_function<T>::value
    // &&
    // !std::is_member_function_pointer<T>::value
    , TypeInfo>::type &
    declare();

  // returns the map of all declarations
  const declaration_map & declarations()const;
  // access declarations by id
  const ScopeDeclaration & operator[](const std::string & id)const;
  const ScopeDeclaration & operator[](const std::string & id);
protected:
  virtual void onDeclaration(const ScopeDeclaration & declaration){}
private:
  friend class ScopeDeclaration;
  declaration_map _declarations;
};

// comparison operator for ScopeInfo
bool operator==(const ScopeInfo & lhs, const ScopeInfo & rhs);




// a declaration inside of a scope
class ScopeDeclaration : public AttributeTarget{
public:
  ScopeDeclaration();
  ScopeDeclaration(ScopeInfo * parentScope);

  void setName(const std::string & name);
  const std::string & name()const;
  void setScope(ScopeInfo & scope);
  const ScopeInfo & scope()const;

  virtual const std::string & id()const;

protected:
  void initScopeDeclaration();
  virtual std::string get_id()const = 0;
  virtual std::string get_name()const = 0;

private:
  std::string _id;
  std::string _name;
  ScopeInfo * _scope;
  friend class ScopeInfo;
};
// comparison operator for ScopeDeclaration
bool operator==(const ScopeDeclaration & lhs, const ScopeDeclaration & rhs);



/// NamespaceInfo 

class NamespaceInfo : public ScopeInfo, public ScopeDeclaration{
public:
  NamespaceInfo(ScopeInfo * scope, const std::string & fullName);

  virtual void onDeclaration(const ScopeDeclaration & declaration);

protected:
  std::string get_id()const override;
  std::string get_name()const override;
private:
  std::string _fullName;
};
// comparison operator for NamespaceInfo
bool operator==(const NamespaceInfo & lhs, const NamespaceInfo & rhs);


/// TypeInfo

class TypeInfo : public ScopeDeclaration, public ScopeInfo{
public:
  typedef size_t type_id;
protected:
  /// methods that need to be implemented
  virtual const TypeInfo & get_pure_type()const = 0;
  virtual const TypeInfo & get_underlying_type()const = 0;
  virtual std::string get_rttiName()const = 0;
  virtual std::string get_rttiRawName()const = 0;
  virtual size_t get_rttiHashCode()const = 0;
  virtual bool get_isConst()const = 0;
  virtual bool get_isReference()const = 0;
  virtual bool get_isVolatile()const = 0;
  virtual bool get_isFundamental()const = 0;
  virtual bool get_isRValueReference()const = 0;
  virtual size_t get_sizeof()const = 0;


  // implementation for ScopeDeclaration
  std::string get_id()const;
  std::string get_name()const;

  // default constructor
  TypeInfo();
  // initialize type info
  void initTypeInfo();
public:
  type_id hash_code()const;
  TypeInfo(const TypeInfo & what) = delete;
  TypeInfo & operator=(const TypeInfo & other) = delete;
  bool operator==(const TypeInfo & other)const;
  bool isFundamental()const;
  bool isConst()const;
  bool isReference()const;
  bool isVolatile()const;
  bool isRValueReference()const;
  const TypeInfo & pure_type()const;
  const TypeInfo & underlying_type()const;
  std::string fullName()const;
private:
  type_id _rtti_hashcode;
  std::string _rtti_name;
  std::string _rtti_rawName;
  std::string _fullName;
};

// CallableInfo

class CallableInfo{
public:
  virtual const TypeInfo & returnType()const = 0;
  virtual const parameter_list & parameters()const = 0;
  virtual bool isConstCall()const = 0;
  virtual bool isVolatileCall()const = 0;

  virtual NS(CORE_NAMESPACE)::any callImplementation(const argument_list & args)const;

  // isTemplated, templateArguments,...
};


// ParameterInfo
class ParameterInfo{
public:
  virtual const CallableInfo & callable()const = 0;
  virtual const TypeInfo & parameterType()const = 0;
  virtual const std::string & parameterName()const = 0;
  virtual int parameterIndex()const = 0;
};

/// MemberInfo
class MemberInfo : public ScopeDeclaration{
public:
  virtual const TypeInfo & definingType()const = 0;
  virtual const TypeInfo & declaringType()const = 0;
  virtual const std::string & memberName()const = 0;
  virtual bool isStatic()const = 0;

};

/// FieldInfo
class FieldInfo : public MemberInfo{

};



/// ConstructorInfo
class ConstructorInfo : public MemberInfo, public virtual CallableInfo {
public:

  const std::string & memberName()const override;
  bool isStatic()const override;

  template<typename ... TArgs> NS(CORE_NAMESPACE)::any make(TArgs&&... args);
  template<typename ... TArgs> NS(CORE_NAMESPACE)::any make_new(TArgs&&... args);
  template<typename ... TArgs> NS(CORE_NAMESPACE)::any make_placement_new(void * place, TArgs&&... args);

  virtual NS(CORE_NAMESPACE)::any make(const argument_list  & args) = 0;
  virtual NS(CORE_NAMESPACE)::any make_new(const argument_list  & args) = 0;
  virtual NS(CORE_NAMESPACE)::any make_placement_new(void* place, const argument_list  & args) = 0;

  bool operator==(const ConstructorInfo & other)const;
};






NS_END(CORE_REFLECTION2_NAMESPACE)
