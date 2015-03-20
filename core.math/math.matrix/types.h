#pragma once
#include <config.h>
#include <core.serialization.h>
#include <core.utility.h>
#include <core.reflection/type/Type.h>
#ifndef MATRIX_CLASSES
#define MATRIX_CLASSES 2
#endif
#if MATRIX_CLASSES ==1

#elif MATRIX_CLASSES == 2
#include <math.matrix.dslib/types.h>

namespace nspace{
  typedef nspace::math::dslib::Vector2D   Vector2D;
  typedef nspace::math::dslib::Vector3D   Vector3D;
  typedef nspace::math::dslib::Matrix3x3  Matrix3x3;
  typedef nspace::math::dslib::Matrix2x2  Matrix2x2;
  typedef nspace::math::dslib::Matrix4x4  Matrix4x4;
  typedef nspace::math::dslib::Matrix4x3  Matrix4x3;
  typedef nspace::math::dslib::Matrix3x4  Matrix3x4;
  typedef nspace::math::dslib::Quaternion Quaternion;
  typedef nspace::math::dslib::VectorND   VectorND;
  typedef nspace::math::dslib::MatrixNxM  MatrixNxM;

  META(nspace::math::dslib::Vector2D  );
  META(nspace::math::dslib::Vector3D  );
  META(nspace::math::dslib::Matrix3x3 );
  META(nspace::math::dslib::Matrix2x2 );
  META(nspace::math::dslib::Matrix4x4 );
  META(nspace::math::dslib::Matrix4x3 );
  META(nspace::math::dslib::Matrix3x4 );
  META(nspace::math::dslib::Quaternion);
  //META(nspace::math::dslib::VectorND  );
  META(nspace::math::dslib::MatrixNxM );
}
#elif MATRIX_CLASSES == 3
#include <math.matrix.dslib/types.h>
#include <math.matrix.eigen/types.h>

namespace nspace{
  typedef nspace::math::eigen::Vector2D   Vector2D;
  typedef nspace::math::eigen::Vector3D   Vector3D;
  typedef nspace::math::eigen::Matrix3x3  Matrix3x3;
  typedef nspace::math::eigen::Matrix2x2  Matrix2x2;
  typedef nspace::math::eigen::Matrix4x4  Matrix4x4;
  typedef nspace::math::eigen::Matrix4x3  Matrix4x3;
  typedef nspace::math::eigen::Matrix3x4  Matrix3x4;
  typedef nspace::math::dslib::Quaternion Quaternion;
  typedef nspace::math::eigen::VectorND   VectorND;
  typedef nspace::math::eigen::MatrixNxM  MatrixNxM;
}
#endif

namespace nspace{
  SERIALIZERS(Vector3D,      
    stream<<(*value)(0) <<" "<< (*value)(1)<<" " << (*value)(2),
    auto & vec=*value; vec(0)=parseNext<Real>(stream); vec(1)=parseNext<Real>(stream); vec(2)=parseNext<Real>(stream); 
    )
    SERIALIZERS(Vector2D,
    stream<<(*value)(0) <<" "<< (*value)(1),
    auto & vec=*value; vec(0)=parseNext<Real>(stream);vec(1)=parseNext<Real>(stream);
    )
    SERIALIZERS(Matrix3x3,
  {
    const Matrix3x3 & matrix = *value;
    stream << "["<<matrix(0,0)<<", "<<matrix(0,1)<<", "<<matrix(0,2)<<"; "
      << matrix(1,0)<<", "<<matrix(1,1)<<", "<<matrix(1,2)<<"; "
      << matrix(2,0)<<", "<<matrix(2,1)<<", "<<matrix(2,2)<<"]";
  },
  {
    Matrix3x3 & matrix = *value;
    for(int i=0; i < 9; i++){      
      matrix(i)=parseNext<Real>(stream);
    }
  }
  );

  namespace math{
    namespace operators{
      inline Vector3D operator ^ (const Vector3D & a, const Vector3D & b){
        Vector3D result;
        shorthands::matrix::crossProduct(result, a,b);
        return result;
      }
    }
  }
}
