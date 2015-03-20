#pragma once

#include <math.matrix.dslib/DynamicMatrix.h>
#include <math.matrix.dslib/specialization/DynamicMatrixSpecialization.h>
#include <math.matrix.dslib/DynamicMatrixOperators.h>

#include <math.matrix.dslib/StaticMatrix.h>
#include <math.matrix.dslib/specialization/StaticMatrixNxNSpecialization.h>
#include <math.matrix.dslib/specialization/StaticMatrix3x3Specialization.h>
#include <math.matrix.dslib/specialization/StaticMatrix3x1Specialization.h>
#include <math.matrix.dslib/StaticMatrixOperators.h>

#include <math.matrix.dslib/Quaternion.h>
#include <math.matrix.dslib/specialization/QuaternionSpecialization.h>
#include <math.matrix.dslib/QuaternionOperators.h>
namespace nspace{
  namespace math{
    namespace dslib{
      typedef matrix2::StaticMatrix<Real,2,1> Vector2D;
      typedef matrix2::StaticMatrix<Real,3,1> Vector3D;
      typedef matrix2::StaticMatrix<Real, 3,3> Matrix3x3;
      typedef matrix2::StaticMatrix<Real, 2,2> Matrix2x2;
      typedef matrix2::StaticMatrix<Real, 4,4> Matrix4x4;
      typedef matrix2::StaticMatrix<Real, 4,3> Matrix4x3;
      typedef matrix2::StaticMatrix<Real, 3,4> Matrix3x4;
      typedef matrix2::Quaternion<Real> Quaternion;
      typedef matrix2::DynamicMatrix<Real> VectorND;
      typedef matrix2::DynamicMatrix<Real> MatrixNxM;
    }
  }
}