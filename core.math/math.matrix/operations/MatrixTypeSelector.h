#pragma once
#include <config.h>
namespace nspace{

  /**
   * \brief Matrix type selector.  this class allows to choose what type to return when to input types are involved
   *        the default implementation will always choose the first type
   *        this class may be specialized e.g. scalar vs matrix selection
   */
  template<typename A, typename B>
  class MatrixTypeSelector{
  public:
    typedef A Type;
  };

/**
 * \brief A macro that defines return type for an operation with two types
 *        e.g. returnType(int,double) should return double
 *
 * \param A The first type
 * \param B The second type.
 */
#define RETURN_TYPE(A,B) MatrixTypeSelector<A,B>::Type
#define returnType(A,B) RETURN_TYPE(A,B)

/**
 * \brief A macro that specializes the return type for an operation of two types.
 *
 * \param TYPEA       The typea.
 * \param TYPEB       The typeb.
 * \param RESULTTYPE  The resulttype.
 */
#define SpecializeTypeSelector(TYPEA, TYPEB, RESULTTYPE) template<> class MatrixTypeSelector<TYPEA,TYPEB> {public: typedef RESULTTYPE Type;}
#define SpecializeTypeSelectorPartially(TYPEA,TYPEB, RESULTTYPE) class MatrixTypeSelector<TYPEA,TYPEB> {public: typedef RESULTTYPE Type;};

  /**
   * \brief Default specialization .  the result type of T and T is T
   *
   * \param parameter1  The first parameter.
   * \param parameter2  The second parameter.
   * \param parameter3  The third parameter.
   */
  template<typename T>SpecializeTypeSelectorPartially(T,T,T)

}
