#include <core.testing.h>

#include <core.math.h>

typedef core::math::matrix::dslib::StaticMatrix<double, 3, 3> mat3x3;
typedef core::math::matrix::dslib::StaticMatrix<double, 6, 6> mat6x6;
typedef core::math::matrix::dslib::StaticMatrix<double, 3, 1> vec3;


UNITTEST(testSpatialTransformation){
  
  using namespace core::math;
  auto E = identity<mat3x3>();
  auto r = zero<vec3>();
  auto res =spatial::transform<mat6x6>(E,r);
  std::cout << res << std::endl;
}

UNITTEST(testSpatialTranslation){
  using namespace core::math;
  double p[3] = { 1, 2, 3 };
  auto res = spatial::xlt<mat6x6>(p);
  std::cout << res << std::endl;
}

UNITTEST(crossProductMatrixTest){
  using namespace core::math;
  double a[3] = {1,2,3};
  auto res = matrix::crossProductMatrix<mat3x3>(a);
  DOUBLES_EQUAL(0, res(0, 0), 0.00001);
  DOUBLES_EQUAL(-3, res(0, 1), 0.00001);
  DOUBLES_EQUAL(2, res(0, 2), 0.00001);
  DOUBLES_EQUAL(3, res(1, 0), 0.00001);
  DOUBLES_EQUAL(0, res(1, 1), 0.00001);
  DOUBLES_EQUAL(-1, res(1, 2), 0.00001);
  DOUBLES_EQUAL(-2, res(2, 0), 0.00001);
  DOUBLES_EQUAL(1, res(2, 1), 0.00001);
  DOUBLES_EQUAL(0, res(2, 2), 0.00001);
}

UNITTEST(testSpatialRotX){
  using namespace core::math;
  // act
  auto actual = spatial::rotx<mat6x6>(0.0);
  //assert
  std::cout << actual << std::endl;
}
UNITTEST(testSpatialRotY){
  using namespace core::math;
  // act
  auto actual = spatial::roty<mat6x6>(0.0);
  //assert
  std::cout << actual << std::endl;
}
UNITTEST(testSpatialRotZ){
  using namespace core::math;
  // act
  auto actual = spatial::rotz<mat6x6>(0.0);
  //assert
  std::cout << actual << std::endl;
}


UNITTEST(testRx1){
  using namespace core::math::matrix;
  // dual 
  mat3x3 m = rx<mat3x3>(0.0);

  DOUBLES_EQUAL(1, m(0, 0), 0.00001);
  DOUBLES_EQUAL(0, m(0, 1), 0.00001);
  DOUBLES_EQUAL(0, m(0, 2), 0.00001);
  DOUBLES_EQUAL(0, m(1, 0), 0.00001);
  DOUBLES_EQUAL(1, m(1, 1), 0.00001);
  DOUBLES_EQUAL(0, m(1, 2), 0.00001);
  DOUBLES_EQUAL(0, m(2, 0), 0.00001);
  DOUBLES_EQUAL(0, m(2, 1), 0.00001);
  DOUBLES_EQUAL(1, m(2, 2), 0.00001);
}
UNITTEST(testRx2){
  using namespace core::math::matrix;
  using namespace core::math::scalar;
  // dual 
  mat3x3 m = rx<mat3x3>(pi<double>() / 2.0);

  DOUBLES_EQUAL(1, m(0, 0), 0.00001);
  DOUBLES_EQUAL(0, m(0, 1), 0.00001);
  DOUBLES_EQUAL(0, m(0, 2), 0.00001);
  DOUBLES_EQUAL(0, m(1, 0), 0.00001);
  DOUBLES_EQUAL(0, m(1, 1), 0.00001);
  DOUBLES_EQUAL(1, m(1, 2), 0.00001);
  DOUBLES_EQUAL(0, m(2, 0), 0.00001);
  DOUBLES_EQUAL(-1, m(2, 1), 0.00001);
  DOUBLES_EQUAL(0, m(2, 2), 0.00001);
}

UNITTEST(testRy1){
  // dual 
  using namespace core::math::matrix;
  mat3x3 m = ry<mat3x3>(0.0);

  DOUBLES_EQUAL(1, m(0, 0), 0.00001);
  DOUBLES_EQUAL(0, m(0, 1), 0.00001);
  DOUBLES_EQUAL(0, m(0, 2), 0.00001);
  DOUBLES_EQUAL(0, m(1, 0), 0.00001);
  DOUBLES_EQUAL(1, m(1, 1), 0.00001);
  DOUBLES_EQUAL(0, m(1, 2), 0.00001);
  DOUBLES_EQUAL(0, m(2, 0), 0.00001);
  DOUBLES_EQUAL(0, m(2, 1), 0.00001);
  DOUBLES_EQUAL(1, m(2, 2), 0.00001);
}
UNITTEST(testRy2){
  using namespace core::math::matrix;
  using namespace core::math::scalar;
  // dual 
  mat3x3 m = ry<mat3x3>(pi<double>() / 2.0);

  DOUBLES_EQUAL(0, m(0, 0), 0.00001);
  DOUBLES_EQUAL(0, m(0, 1), 0.00001);
  DOUBLES_EQUAL(-1, m(0, 2), 0.00001);
  DOUBLES_EQUAL(0, m(1, 0), 0.00001);
  DOUBLES_EQUAL(1, m(1, 1), 0.00001);
  DOUBLES_EQUAL(0, m(1, 2), 0.00001);
  DOUBLES_EQUAL(1, m(2, 0), 0.00001);
  DOUBLES_EQUAL(0, m(2, 1), 0.00001);
  DOUBLES_EQUAL(0, m(2, 2), 0.00001);
}

UNITTEST(testRz1){
  // dual 
  using namespace core::math::matrix;
  mat3x3 m = rz<mat3x3>(0.0);

  DOUBLES_EQUAL(1, m(0, 0), 0.00001);
  DOUBLES_EQUAL(0, m(0, 1), 0.00001);
  DOUBLES_EQUAL(0, m(0, 2), 0.00001);
  DOUBLES_EQUAL(0, m(1, 0), 0.00001);
  DOUBLES_EQUAL(1, m(1, 1), 0.00001);
  DOUBLES_EQUAL(0, m(1, 2), 0.00001);
  DOUBLES_EQUAL(0, m(2, 0), 0.00001);
  DOUBLES_EQUAL(0, m(2, 1), 0.00001);
  DOUBLES_EQUAL(1, m(2, 2), 0.00001);
}
UNITTEST(testRz2){
  using namespace core::math::matrix;
  using namespace core::math::scalar;
  // dual 
  mat3x3 m = rz<mat3x3>(pi<double>() / 2.0);

  DOUBLES_EQUAL(0, m(0, 0), 0.00001);
  DOUBLES_EQUAL(1, m(0, 1), 0.00001);
  DOUBLES_EQUAL(0, m(0, 2), 0.00001);
  DOUBLES_EQUAL(-1, m(1, 0), 0.00001);
  DOUBLES_EQUAL(0, m(1, 1), 0.00001);
  DOUBLES_EQUAL(0, m(1, 2), 0.00001);
  DOUBLES_EQUAL(0, m(2, 0), 0.00001);
  DOUBLES_EQUAL(0, m(2, 1), 0.00001);
  DOUBLES_EQUAL(1, m(2, 2), 0.00001);
}