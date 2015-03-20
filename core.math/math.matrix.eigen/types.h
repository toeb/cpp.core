#pragma once
#include <math.matrix/MatrixOperations.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace nspace{

    template<typename T, int Rows,int Cols> class MatrixCoefficientType<Eigen::Matrix<T,Rows,Cols> >{public: typedef T Type; };
template<typename T, int Rows,int Cols>class MatrixIndexType<Eigen::Matrix<T,Rows,Cols> >{public: typedef int Type;};
//template<typename T, int Rows, int Cols> class MatrixRowCount<Eigen::Matrix<T,Rows,Cols> >{public : int operation(const Eigen::Matrix<T,Rows,Cols>  & matrix){return matrix.rows();});

  namespace math{
    namespace eigen{
      // it is significant that the NxM matrix format is set to RowMajor . Else simulation.state will not work
      typedef Eigen::Matrix<Real,Eigen::Dynamic,Eigen::Dynamic, Eigen::AutoAlign|Eigen::RowMajor> MatrixNxM;

      typedef Eigen::Matrix<Real,2,2> Matrix2x2;
      typedef Eigen::Matrix<Real,3,3> Matrix3x3;
      typedef Eigen::Matrix<Real,3,2> Matrix3x2;
      typedef Eigen::Matrix<Real,2,3> Matrix2x3;
      typedef Eigen::Matrix<Real,3,1> Vector3D;
      typedef Eigen::Matrix<Real,2,1> Vector2D;
      typedef Eigen::Matrix<Real,1,1> Vector1D;
      typedef Eigen::Matrix<Real,4,4> Matrix4x4;
      typedef Eigen::Matrix<Real,4,3> Matrix4x3;
      typedef Eigen::Matrix<Real,3,4> Matrix3x4;
      typedef Eigen::Matrix<Real,Eigen::Dynamic,1> VectorND;
      typedef Eigen::Quaternion<Real> Quaternion;
    }
  }
  //specialization
  template<>
  class VectorCrossProduct<math::eigen::Vector3D,math::eigen::Vector3D,math::eigen::Vector3D>{
  public:
    static inline void operation(math::eigen::Vector3D & result,const math::eigen::Vector3D & a,const math::eigen::Vector3D & b){
      result = a.cross(b);
    }
  };
}
