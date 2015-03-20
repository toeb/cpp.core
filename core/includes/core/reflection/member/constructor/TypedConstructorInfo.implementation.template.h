#pragma once
#include <core/core.h>

#include <core/reflection/member/MemberInfo.h>
#include <core/reflection/type/Argument.h>

NS_BEGIN(CORE_NAMESPACE)
  /*
struct ConstructorInfo : public MemberInfo{
protected:

  virtual std::shared_ptr<void> call(std::vector<Argument> args)=0;
};

template<typename ClassType>
struct TypedConstructorInfo : public ConstructorInfo{

};

#define GENERIC_ARG_NAME(X) DS_CONCAT(a_,X)
#define GENERIC_ARG_DEF(X) traits:: nested_template arg<X>::type GENERIC_ARG_NAME(X)


#define GENERIC_ARG_LIST(...) \
  DS_REDUCE_COMMA(GENERIC_ARG_DEF, DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))
#define GENERIC_ARG_NAME_LIST(...) DS_REDUCE_COMMA(GENERIC_ARG_NAME, DS_SEQUENCE(DS_MINUS_ONE(DS_NUM_ARGS(__VA_ARGS__))))


#define DS_CONSTRUCTOR_STRUCT(...)                                                              \
  typedef CurrentClassType ConstructorOwningClassType;                                          \
  struct Helper{                                                                                \
      void operator ()(__VA_ARGS__)const;                                                       \
  };                                                                                            \
struct Constructor:public TypedConstructorInfo<ConstructorOwningClassType>{                     \
  typedef Constructor CurrentClassType;                                                         \
  typedef NS(CORE_NAMESPACE)::function_traits<Helper> traits;                                               \
  ConstructorOwningClassType * construct(GENERIC_ARG_LIST(__VA_ARGS__))const{                   \
    return new ConstructorOwningClassType(GENERIC_ARG_NAME_LIST(__VA_ARGS__));                  \
}                                                                                               \
protected:                                                                                      \
  std::shared_ptr<void> call(std::vector<Argument> args){                                       \
  auto method = typeof(CurrentClassType)->getMethodInfo("construct");                           \
  auto result = std::shared_ptr<void>((ConstructorOwningClassType*)method->call(this,args));    \
  return result;                                                                                \
}                                                                                               \
  reflect_method(construct);                                                                    \
  SINGLETON(Constructor){}                                                                      \
};                                                                                              \
  DS_ONCE{                                                                                      \
  static std::shared_ptr<Constructor>  c = Constructor::instance();                             \
}


#define reflect_constructor(TYPE, ...) DS_CONSTRUCTOR_STRUCT(__VA_ARGS__)  TYPE ( __VA_ARGS__)*/
NS_END(CORE_NAMESPACE)
