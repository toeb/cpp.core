#pragma once
#include <core.math/core.math.h>

#include <core.math/matrix/operations/MatrixOperationMacros.h>


/**
 * \brief A macro that defines binary matrix operations with a return type other than returnType(A,B)
 *        the methods will be called <OPNAME>
 *        @TODO: Not every implementation should have an InPlace method.
 *
 * \param OPNAME      The operations name. 
 * \param RETURNTYPE  The return type.
 */
#define BinaryMatrixOperationOtherReturnType(OPNAME,RETURNTYPE)\
  template<typename C, typename A, typename B> inline void OPNAME(C & c, const A & a, const B  & b);\
  template<typename C, typename A, typename B> inline C OPNAME(const A & a, const B & b){C c; OPNAME(c,a,b);return c;}\
  template<typename A, typename B> inline auto OPNAME(const A & a, const B & b) -> typename RETURNTYPE{return OPNAME<typename RETURNTYPE,A,B>(a,b);}\
  template<typename A, typename B> inline void OPNAME##InPlace(A & a,const B&b){OPNAME(a,a,b);}

#define UnaryMatrixOperationOtherReturnType(OPNAME,RETURNTYPE)\
  template<typename A,typename B> inline void OPNAME(B & b, const A & a);\
  template<typename A,typename B> inline B OPNAME(const A & a){B b; OPNAME(b,a); return b;}\
  template<typename A> inline auto OPNAME(const A & a)->typename RETURNTYPE{return OPNAME<typename RETURNTYPE,A,B>(a);}\
  template<typename A> inline void OPNAME##InPlace(A & a){OPNAME(a,a);}

#define NullaryMatrixOperation(OPNAME)\
  template<typename A> inline void OPNAME(A&a);\
  template<typename A> inline A OPNAME(){A a; OPNAME(a); return a;}

#define NullaryOperationImplementation(OPNAME) template<typename A> inline void OPNAME(A&a)

#define MatrixOperation(NAME) OperationMatrix##NAME
#define MatrixOperationClass(NAME) class MatrixOperation(NAME)
#define MatrixOperationMethod public: static inline void operation


#define VectorOperation(NAME) OperationVector##NAME
#define VectorOperationClass(NAME) class VectorOperation(NAME)
#define VectorOperationMethod public : static inline void operation

/**
 * \brief A macro that defines the methods for binary a matrix operation.
 *        define methods void OPNAME(c,a,b); C OPNAME(c,a,b) auto OPNAME(c,a,b)
 *
 * \param OPNAME  The operation name.
 */
#define BinaryMatrixOperation(OPNAME) BinaryMatrixOperationOtherReturnType(OPNAME,returnType(A,B))

/**
 * \brief A macro that defines binary operation's implementation. 
 *        e.g. BinaryOperationImplementation(subtract){c=a-b;}
 *
 * \param OPNAME  The opname.
 */
#define BinaryOperationImplementation(OPNAME)template<typename C, typename A, typename B> void OPNAME(C & c, const A & a, const B  & b)


#define UnaryMatrixOperation(OPNAME) UnaryMatrixOperationOtherReturnType(OPNAME,A)

#define UnaryOperationImplementation(OPNAME)template<typename A,typename B> void OPNAME(B & b, const A & a)
