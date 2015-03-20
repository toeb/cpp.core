#include <core.testing.h>

#include <core.math/scalar/all.h>
#include <core.preprocessor.h>

using namespace NS(CORE_MATH_NAMESPACE);






#define EPSILON 0.00001
typedef double Real;
TEST(Signum,ScalarOperations){

  CHECK_EQUAL(-1.0,scalar::signum(-3.0));
  CHECK_EQUAL(1.0,scalar::signum(+93.0));
  CHECK_EQUAL(1.0,scalar::signum(0.0));
}


TEST(Cosine,ScalarOperations){
  DOUBLES_EQUAL(1.0,scalar::cosine(0.0),EPSILON);
  DOUBLES_EQUAL(-1.0,scalar::cosine(M_PI),EPSILON);
  DOUBLES_EQUAL(0,scalar::cosine(M_PI_2),EPSILON);
  DOUBLES_EQUAL(0,scalar::cosine(3.0*M_PI_2),EPSILON);
}

TEST(Sinus,ScalarOperations){
  DOUBLES_EQUAL(0.0,scalar::sine(0.0),EPSILON);
  DOUBLES_EQUAL(0.0,scalar::sine(M_PI),EPSILON);
  DOUBLES_EQUAL(1.0,scalar::sine(M_PI_2),EPSILON);
  DOUBLES_EQUAL(-1.0,scalar::sine(3.0*M_PI_2),EPSILON);
}

TEST(Absolute,ScalarOperations){
  DOUBLES_EQUAL(4.0,scalar::absolute(-4.0),EPSILON);
  DOUBLES_EQUAL(4.0,scalar::absolute(4.0),EPSILON);
}

TEST(ArcusSinus,ScalarOperations){
  DOUBLES_EQUAL(-M_PI_2,scalar::arcusSinus(-1.0),EPSILON);
  DOUBLES_EQUAL(M_PI_2,scalar::arcusSinus(1.0),EPSILON);
  DOUBLES_EQUAL(0,scalar::arcusSinus(0.0),EPSILON);
}
TEST(SquareRoot,ScalarOperations){
  DOUBLES_EQUAL(0.0,scalar::squareRoot(0.0),EPSILON);
  DOUBLES_EQUAL(M_SQRT2,scalar::squareRoot(2.0),EPSILON);
}
TEST(Reciprocal,ScalarOperations){
  DOUBLES_EQUAL(0.5,scalar::reciprocal(2.0),EPSILON);
  DOUBLES_EQUAL(0.25,scalar::reciprocal(4.0),EPSILON);
}

TEST(Pi,ScalarOperations){
  DOUBLES_EQUAL(M_PI,scalar::pi<Real>(),EPSILON);
}

TEST(
  ,ScalarOperations){
  DOUBLES_EQUAL(0.0,scalar::zero<Real>(),EPSILON);
}

TEST(SquareRootOfTwo,ScalarOperations){
  DOUBLES_EQUAL(M_SQRT2,scalar::squareRootOfTwo<Real>(),EPSILON);
}
TEST(EulersNumber,ScalarOperations){
  DOUBLES_EQUAL(M_E,scalar::e<Real>(),EPSILON);
}
