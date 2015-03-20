#pragma once
#include <config.h>
#include <math.matrix/MatrixOperations.h>
#include <math.matrix.dslib/StaticMatrix.h>
namespace nspace
{
  namespace matrix2{
    template<typename T>
    class QuaternionOperations{
    public:
      template<typename Quat, typename Vec>
      inline static void fromAngularVelocity(Quat & qDot, const Vec & omega, const Quat & orientation){
        qDot.w()=0;
        qDot.x()=omega(0);
        qDot.y()=omega(1);
        qDot.z()=omega(2);
        qDot = 0.5*qDot*orientation;
      }
      template<typename Quat, typename Vec>
      inline static void  toAngularVelocity(Vec  & result,const Quat& qDot, const Quat & orientation){
        Quat conj;
        conjugate(conj,orientation);
        Quat omegaTilde;
        multiplyQuaternion(omegaTilde, conj,qDot);
        math::shorthands::matrix::multiplyScalar(omegaTilde,omegaTilde,2.0);
        // MatrixOperations<T>::multiplyScalar(omegaTilde,omegaTilde,2.0);
        result(0)=omegaTilde.x();
        result(1)=omegaTilde.y();
        result(2)=omegaTilde.z();
      }
      template<typename Quat>
      inline static void multiplyQuaternion(Quat & c, const Quat & a, const Quat &b){
        c.w() =  a.w()*b.w() - a.x()*b.x() - a.y()*b.y() - a.z()*b.z();
        c.x() =  b.w()*a.x() + a.w()*b.x() - b.y()*a.z() + a.y()*b.z();
        c.y() =  b.w()*a.y() + a.w()*b.y() + b.x()*a.z() - a.x()*b.z();
        c.z() = -b.x()*a.y() + a.x()*b.y() + b.w()*a.z() + a.w()*b.z();
      }
      template<typename Quat,typename QMatrixType>
      inline static void matrixQ(QMatrixType  & result,const Quat & q){
        result(0,0) =-q(1);
        result(0,1) =-q(2);
        result(0,2) =-q(3);
        result(1,0) = q(0);
        result(1,1) =-q(3);
        result(1,2) = q(2);
        result(2,0) = q(3);
        result(2,1) = q(0);
        result(2,2) =-q(1);
        result(3,0) =-q(2);
        result(3,1) = q(1);
        result(3,2) = q(0);
      }
      template<typename Quat>
      static inline void conjugate(Quat & q_conj, const Quat & q){
        q_conj.w()=q.w();
        q_conj.x()=-q.x();
        q_conj.y()=-q.y();
        q_conj.z()=-q.z();
      }

      template<typename Quat, typename RPYVector>
      static inline void fromRollPitchYaw(Quat & q, const RPYVector rpy){
        Quat roll,pitch,yaw;
        QuaternionOperations<T>::fromAxisAngle(roll,RPYVector::UnitX(),rpy(0));
        QuaternionOperations<T>::fromAxisAngle(pitch,RPYVector::UnitY(),rpy(1));
        QuaternionOperations<T>::fromAxisAngle(yaw,RPYVector::UnitZ(),rpy(2));
        QuaternionOperations<T>::multiplyQuaternion(q,pitch,roll);
        QuaternionOperations<T>::multiplyQuaternion(roll,yaw,q);
        q = roll;
        //q = yaw*pitch*roll;
      }

      template<typename Quat, typename RotationMatrixType>
      static inline void fromRotationMatrix(Quat & q, const RotationMatrixType  & m){
        Real tr = 1.0 + m(0,0) +m(1,1) + m(2,2);
        Real s;
        Real & w=q.w();
        Real & x=q.x();
        Real & y=q.y();
        Real & z=q.z();
        if (tr > 1.0e-9)
        {
          s = sqrt (tr);
          w = 0.5*s;
          s = 0.5 /s;
          x = (m(2,1) - m(1,2)) * s;
          y = (m(0,2) - m(2,0)) * s;
          z = (m(1,0) - m(0,1)) * s;
        }
        else
        {
          int i = 0;
          if (m(1,1) > m(0,0))
            i = 1;
          if (m(2,2) >m(i,i))
            i = 2;

          switch (i)
          {
          case 0:
            s = sqrt (m(0,0)- (m(1,1) + m(2,2)) + 1);
            x = 0.5 * s;
            s = 0.5 / s;
            y = (m(0,1) + m(1,0)) * s;
            z = (m(2,0) + m(0,2)) * s;
            w = (m(2,1) - m(1,2)) * s;
            break;
          case 1:
            s = sqrt (m(1,1) - (m(2,2) + m(0,0)) + 1);
            y = 0.5 * s;
            s = 0.5 / s;
            z = (m(1,2) + m(2,1)) * s;
            x = (m(0,1) + m(1,0)) * s;
            w = (m(0,2) - m(2,0)) * s;
            break;
          case 2:
            s = sqrt (m(2,2) - (m(0,0) + m(1,1)) + 1);
            z = 0.5 * s;
            s = 0.5 / s;
            x =(m(2,0) + m(0,2)) * s;
            y =(m(1,2) + m(2,1)) * s;
            w =(m(1,0) - m(0,1)) * s;
            break;
          }
        }
      }
      template<typename Quat, typename AxisVectorType>
      static inline void fromAxisAngle(Quat & q, const AxisVectorType & axis, const T & angle){
        T a = 0.5 * angle;
        T sinus;
        q.w() = math::shorthands::scalar::cosine(a);
        sinus = scalar::sine(a);
        q.x() = sinus * axis(0);
        q.y() = sinus * axis(1);
        q.z() = sinus * axis(2);
      }
      template<typename Quat, typename AxisVectorType>
      static inline void toAxisAngle(AxisVectorType & axis, T & angle, const Quat & q){
        T x = q.x();
        T y = q.y();
        T z = q.z();
        T w = q.w();

        T l2 = x*x + y*y + z*z;
        if (l2 > EPSILON)
        {
          if (w > 1.0)
            w = 1.0;
          else if (w < -1.0)
            w = -1.0;
          math::shorthands::scalar::arcusCosinus(angle,w);
          //ScalarOperations<T>::acos(angle,w);
          angle = 2*angle;
          //angle = (Real) 2.0 * ScalarOperations<T>::acos (w);
          T l;
          //ScalarOperations<T>::sqrt(l,l2);
          math::shorthands::scalar::squareRoot(l,l2);
          axis(0) = x / l;
          axis(1) = y / l;
          axis(2) = z / l;
        }
        else
        {
          angle = 0.0;
          axis(0) = 1.0;
          axis(1) = 0.0;
          axis(2) = 0.0;
        }
      }
    };

    template<typename T, typename Quat, typename RotationMatrixType>
    class QuaternionToRotationMatrix{
    public:
      static inline void operation(RotationMatrixType  & R, const Quat & q){
        T xx = q.x()*q.x();
        T yy = q.y()*q.y();
        T zz = q.z()*q.z();
        T xy = q.x()*q.y();
        T wz = q.w()*q.z();
        T xz = q.x()*q.z();
        T wy = q.w()*q.y();
        T yz = q.y()*q.z();
        T wx = q.w()*q.x();
        T ww =  q.w()*q.w();

        //m(0,0) = 1.0 - 2.0*(yy + zz);
        R(0,1) = 2.0*(xy-wz);
        R(0,2) = 2.0*(xz+wy);

        R(1,0) = 2.0*(xy+wz);
        //m(1,1) = 1.0 - 2.0*(xx+zz);
        R(1,2) = 2.0*(yz-wx);

        R(2,0) = 2.0*(xz-wy);
        R(2,1) = 2.0*(yz+wx);
        //m(2,2) = 1.0 - 2.0*(xx+yy);

        // (Besl, McKay 1992)

        R(0,0) = ww+xx-yy-zz;
        R(1,1) = ww+yy-xx-zz;
        R(2,2) = ww+zz-xx-yy;
      }
    };
    template<typename T, typename Quat, typename RotationMatrixType>
    class QuaternionToTransposedRotationMatrix{
    public:
      static inline void operation(RotationMatrixType  & RT, const Quat & q){
        QuaternionToRotationMatrix<T,Quat,RotationMatrixType>::operation(RT,q);
        MatrixTransposeInPlace<RotationMatrixType>::operation(RT);
      }
    };
    template<typename T>
    class Quaternion : public StaticMatrix<T,4,1>{
    public:
      Quaternion(const StaticMatrix<T,4,1> & vec){
        assign(vec.data());
      }
      Quaternion(){}
      Quaternion(const T & w,const T & x, const T & y, const T & z):StaticMatrix<T,4,1>(w,x,y,z){}

      static const Quaternion & Identity(){
        static Quaternion _zeroRotationVector(1,0,0,0);
        return _zeroRotationVector;
      }

      template<typename RotationMatrixType>
      inline void toRotationMatrix(RotationMatrixType & R)const{
        QuaternionToRotationMatrix<T,Quaternion<T>,RotationMatrixType>::operation(R,*this);
      }

      inline StaticMatrix<T,3,3> toRotationMatrix()const{
        StaticMatrix<T,3,3> R;
        QuaternionToRotationMatrix<T,Quaternion<T>,StaticMatrix<T,3,3>>::operation(R,*this);
        return R;
      }
      template<typename RotationMatrixType>
      inline void toTransposedRotationMatrix(RotationMatrixType & R)const{
        QuaternionToTransposedRotationMatrix<T,Quaternion<T>, RotationMatrixType>::operation(R,*this);
      }

      inline StaticMatrix<T,3,3> toTransposedRotationMatrix()const{
        StaticMatrix<T,3,3> R;
        QuaternionToTransposedRotationMatrix<T,Quaternion<T>, StaticMatrix<T,3,3> >::operation(R,*this);
        return R;
      }
      template<typename AxisVector>
      inline void fromAxisAngle(const AxisVector & axis, const T & angle){
        QuaternionOperations<T>::fromAxisAngle(*this,axis,angle);
      }

      template<typename RPYVector>
      inline void fromRollPitchYaw(const RPYVector & rpy){
        QuaternionOperations<T>::fromRollPitchYaw(*this,rpy);
      }

      inline void fromRollPitchYaw(T roll, T pitch, T yaw){
        StaticMatrix<T,3,1> rpy(roll,pitch,yaw);
        QuaternionOperations<T>::fromRollPitchYaw(*this,rpy);
      }
    };

    template<typename T>
    class QuaternionToRotationMatrix<T, Quaternion<Real>,StaticMatrix<Real,3,3> >{
    public:
      inline static void operation(StaticMatrix<T,3,3> & Rmat, const Quaternion<T> & qQuat){
        T * R = Rmat.data();
        const Real * q = qQuat.data();
        T w = q[0];
        T x = q[1];
        T y = q[2];
        T z = q[3];

        T xx = x*x;
        T yy = y*y;
        T zz = z*z;
        T xy = x*y;
        T wz = w*z;
        T xz =x*z;
        T wy = w*y;
        T yz = y*z;
        T wx = w*x;
        T ww =  w*w;

        R[0] = ww+xx-yy-zz;
        R[1] = 2.0*(xy-wz);
        R[2] = 2.0*(xz+wy);
        R[3] = 2.0*(xy+wz);
        R[4] = ww+yy-xx-zz;
        R[5] = 2.0*(yz-wx);
        R[6] = 2.0*(xz-wy);
        R[7] = 2.0*(yz+wx);
        R[8] = ww+zz-xx-yy;
      }
    };

    template<typename T>
    Quaternion<T> operator * (const Quaternion<T> & a, const Quaternion<T> & b){
      Quaternion<T> c;
      QuaternionOperations<T>::multiplyQuaternion(c,a,b);
      return c;
    }

    template<typename QuatC, typename QuatA, typename T>
    class QuaternionMultiplicationScalar{
    public:
      inline static void operation(QuatC & c, const QuatA & a, const T & b){
        c.w() = a.w()*b;
        c.x() = a.x()*b;
        c.y() = a.y()*b;
        c.z() = a.z()*b;
      }
    };

    template<typename T>
    Quaternion<T> operator * (const T & s, const Quaternion<T> & q){
      Quaternion<T> result;
      QuaternionMultiplicationScalar<Quaternion<T> ,Quaternion<T> ,T>::operation(result, q,s);
      return result;
    }
    template<typename T>
    Quaternion<T> operator * ( const Quaternion<T> & q,const T & s){
      Quaternion<T> result;
      QuaternionMultiplicationScalar<Quaternion<T> ,Quaternion<T> ,T>::operation(result, q,s);
      return result;
    }
  }
}
