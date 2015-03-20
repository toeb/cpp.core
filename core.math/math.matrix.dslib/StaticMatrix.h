#pragma once
#include <math.matrix/Matrix.h>
#include <math.matrix/VectorOperations.h>
#include <math.matrix/MatrixOperations.h>
#include <queue>
#include <cstring>
namespace nspace{
  namespace matrix2{
    template<typename T, int RowCount, int ColumnCount>
    class StaticMatrix : public Matrix<T>{
    protected:
      //< the static data array
      T _data[RowCount*ColumnCount];
    public:
      
      StaticMatrix(const StaticMatrix<T,RowCount,ColumnCount> & orig);
      StaticMatrix(const T& x, const T& y);
      StaticMatrix(const Real * dataPtr);
      StaticMatrix(const T& w,const T& x,const T& y,const T& z);
      StaticMatrix();
      virtual ~StaticMatrix(){}

      StaticMatrix<T,ColumnCount,1> row(uint i)const;
      StaticMatrix<T,RowCount,1>col(uint j)const;
      inline const T * getRow(int index)const;

      inline StaticMatrix<T,RowCount,ColumnCount> & operator=(const StaticMatrix<T,RowCount,ColumnCount> & orig);
      inline T & operator()(int i, int j);
      inline T & operator()(int i);
      inline const T & operator()(int i)const;
      inline const T & operator()(int i, int j)const;

      inline T & w();
      inline const T & w()const;
      inline T & x();
      inline const T & x()const;
      inline T & y();
      inline const T & y()const;
      inline T & z();
      inline const T & z()const;

      inline StaticMatrix<T,RowCount,ColumnCount> operator -();

      inline int rows()const;
      inline int cols()const;
      inline bool isZero(const Real epsilon = EPSILON)const;
      inline void setZero();

      inline void assign(const T * dataPtr);
      inline void copyTo(T * dataPtr)const;
      T * data();
      const T * data()const;
      inline size_t dataByteSize()const;

      //inline StaticMatrix<T,1,ColumnCount> row(int i);
      StaticMatrix(const T& x,const T& y,const T& z);
      // returns the 3x1 x vector
      static const StaticMatrix<T,3,1> & UnitX();
      //returns the 3x1 y vector
      static const StaticMatrix<T,3,1> & UnitY();
      // returns the 3x1 z vector
      static const StaticMatrix<T,3,1> & UnitZ();
      static StaticMatrix<T,RowCount,ColumnCount> Ones();
      // access to identity matrix
      static const StaticMatrix<T,RowCount,ColumnCount> & Identity();
      // access to zero matrix
      inline static const StaticMatrix<T,RowCount,ColumnCount> & Zero();

      inline void transpose();
      inline void toTransposed(StaticMatrix<T,ColumnCount,RowCount> & AT)const;
      inline StaticMatrix<T,ColumnCount,RowCount> transposed()const;

      inline T length()const;
      inline T norm()const;
      inline T length2()const;
      inline T squaredNorm()const;
      inline T maximum()const;
      inline T minimum()const;
      inline void normalize();

      inline int index(int i, int j)const;
      inline bool resize(int rows, int cols);
      
    protected:
      // access read/write and read access to the values of the data array
      inline Real & value(int i, int j);
      inline const Real & value(int i, int j)const;
    };

    //IMPLEMENTATION

    template<typename T, int RowCount, int ColumnCount>
    inline Real & StaticMatrix<T,RowCount,ColumnCount>::value(int i, int j){
      return _data[index(i,j)];
    }
    template<typename T, int RowCount, int ColumnCount>
    inline const Real & StaticMatrix<T,RowCount,ColumnCount>::value(int i, int j)const{
      return _data[index(i,j)];
    }

    template<typename T, int RowCount, int ColumnCount>
    StaticMatrix<T,RowCount,ColumnCount>::StaticMatrix(const StaticMatrix<T,RowCount,ColumnCount> & orig){
      *this=orig;
    }
    template<typename T, int RowCount, int ColumnCount>
    StaticMatrix<T,RowCount,ColumnCount>::StaticMatrix(const T& x, const T& y){
      _data[0]=x;
      _data[1]=y;
    }
    template<typename T, int RowCount, int ColumnCount>
    StaticMatrix<T,RowCount,ColumnCount>::StaticMatrix(const Real * dataPtr){
      assign(dataPtr);
    }
    template<typename T, int RowCount, int ColumnCount>
    StaticMatrix<T,RowCount,ColumnCount> & StaticMatrix<T,RowCount,ColumnCount>::operator=(const StaticMatrix<T,RowCount,ColumnCount> & orig ){
      assignMatrix(*this,orig);
      return *this;
    }
    template<typename T, int RowCount, int ColumnCount>
    StaticMatrix<T,RowCount,ColumnCount>::StaticMatrix(){}
    template<typename T, int RowCount, int ColumnCount>
    inline size_t StaticMatrix<T,RowCount,ColumnCount>::dataByteSize()const{
      return RowCount*ColumnCount*sizeof(T);
    }
    template<typename T, int RowCount, int ColumnCount>
    inline int StaticMatrix<T,RowCount,ColumnCount>::index(int i, int j)const{return i* ColumnCount+j;}

    template<typename T, int RowCount, int ColumnCount>
    StaticMatrix<T,ColumnCount,1> StaticMatrix<T,RowCount,ColumnCount>::row(uint i)const{
      StaticMatrix<T,ColumnCount,1> result;
      result.assign(getRow(i));
      return result;
    }
    template<typename T, int RowCount, int ColumnCount>
    StaticMatrix<T,RowCount,1> StaticMatrix<T,RowCount,ColumnCount>::col(uint j)const{
      StaticMatrix<T,RowCount,1> result;
      for(int i=0; i < RowCount;i++ ){
        result(i)=value(i,j);
      }
      return result;
    }

    template<typename T, int RowCount, int ColumnCount>
    inline const T * StaticMatrix<T,RowCount,ColumnCount>::getRow(int index)const{
      return _data+index*ColumnCount;
    }

    template<typename T, int RowCount, int ColumnCount>
    inline T & StaticMatrix<T,RowCount,ColumnCount>::operator()(int i, int j){return _data[i* ColumnCount+j]; }
    template<typename T, int RowCount, int ColumnCount>
    inline T & StaticMatrix<T,RowCount,ColumnCount>::operator()(int i){return _data[i];}
    template<typename T, int RowCount, int ColumnCount>
    inline const T & StaticMatrix<T,RowCount,ColumnCount>::operator()(int i)const{
      return _data[i];
    }
    template<typename T, int RowCount, int ColumnCount>
    inline const T & StaticMatrix<T,RowCount,ColumnCount>::operator()(int i, int j)const{return _data[i* ColumnCount+j]; }
    template<typename T, int RowCount, int ColumnCount>
    inline int StaticMatrix<T,RowCount,ColumnCount>::rows()const{return RowCount;}
    template<typename T, int RowCount, int ColumnCount>
    inline int StaticMatrix<T,RowCount,ColumnCount>::cols()const{return ColumnCount;}
    template<typename T, int RowCount, int ColumnCount>
    T * StaticMatrix<T,RowCount,ColumnCount>::data(){return &_data[0];}
    template<typename T, int RowCount, int ColumnCount>
    const T * StaticMatrix<T,RowCount,ColumnCount>::data()const{return &_data[0];}
    template<typename T, int RowCount, int ColumnCount>
    inline void StaticMatrix<T,RowCount,ColumnCount>::assign(const T * dataPtr){      
      memcpy(_data, dataPtr,dataByteSize());
    }
    template<typename T, int RowCount, int ColumnCount>
    inline bool StaticMatrix<T,RowCount,ColumnCount>::isZero(const Real epsilon)const{
      bool result;
      matrix::compareMatrix(result,*this,StaticMatrix<T,RowCount,ColumnCount>::Zero() );
      return result;
    }

    template<typename T, int RowCount, int ColumnCount>
    inline void StaticMatrix<T,RowCount,ColumnCount>::copyTo(T * dataPtr)const{
      memcpy(dataPtr,_data,dataByteSize());
    }
    template<typename T, int RowCount, int ColumnCount>
    inline void StaticMatrix<T,RowCount,ColumnCount>::setZero(){
      memset(_data,0,dataByteSize());
    }

    template<typename T, int RowCount, int ColumnCount>
    StaticMatrix<T,RowCount,ColumnCount>::StaticMatrix(const T& x,const T& y,const T& z){
      _data[0]=x;
      _data[1]=y;
      _data[2]=z;
    }
    template<typename T, int RowCount, int ColumnCount>
    const StaticMatrix<T,3,1> & StaticMatrix<T,RowCount,ColumnCount>::UnitX(){
      static StaticMatrix<T,3,1> _unitXVector(1,0,0);
      return _unitXVector;
    }
    template<typename T, int RowCount, int ColumnCount>
    const StaticMatrix<T,3,1> & StaticMatrix<T,RowCount,ColumnCount>::UnitY(){
      static StaticMatrix<T,3,1> _unitYVector(0,1,0);
      return _unitYVector;
    }
    template<typename T, int RowCount, int ColumnCount>
    const StaticMatrix<T,3,1> & StaticMatrix<T,RowCount,ColumnCount>::UnitZ(){
      static StaticMatrix<T,3,1> _unitZVector(0,0,1);
      return _unitZVector;
    }
    template<typename T, int RowCount, int ColumnCount>
    StaticMatrix<T,RowCount,ColumnCount> StaticMatrix<T,RowCount,ColumnCount>::Ones(){
      StaticMatrix<T,RowCount,ColumnCount> matrix;
      matrix.setZero();
      for(int i=0; i < RowCount; i++)
        for(int j=0; j < ColumnCount; j++)
          matrix(i,j)=1;
      return matrix;
    }

    template<typename T, int RowCount, int ColumnCount>
    inline T & StaticMatrix<T,RowCount,ColumnCount>::w(){return _data[0];}
    template<typename T, int RowCount, int ColumnCount>
    inline const T & StaticMatrix<T,RowCount,ColumnCount>::w()const{return _data[0];}
    template<typename T, int RowCount, int ColumnCount>
    inline T & StaticMatrix<T,RowCount,ColumnCount>::x(){return RowCount==4?_data[1]:_data[0];}
    template<typename T, int RowCount, int ColumnCount>
    inline const T & StaticMatrix<T,RowCount,ColumnCount>::x()const{return RowCount==4?_data[1]:_data[0];}
    template<typename T, int RowCount, int ColumnCount>
    inline T & StaticMatrix<T,RowCount,ColumnCount>::y(){return RowCount==4?_data[2]:_data[1];}
    template<typename T, int RowCount, int ColumnCount>
    inline const T & StaticMatrix<T,RowCount,ColumnCount>::y()const{return RowCount==4?_data[2]:_data[1];}
    template<typename T, int RowCount, int ColumnCount>
    inline T & StaticMatrix<T,RowCount,ColumnCount>::z(){return RowCount==4?_data[3]:_data[2];}
    template<typename T, int RowCount, int ColumnCount>
    inline const T & StaticMatrix<T,RowCount,ColumnCount>::z()const{return RowCount==4?_data[3]:_data[2];}
    template<typename T, int RowCount, int ColumnCount>
    StaticMatrix<T,RowCount,ColumnCount>::StaticMatrix(const T& w,const T& x,const T& y,const T& z){
      _data[0]=w;
      _data[1]=x;
      _data[2]=y;
      _data[3]=z;
    }

    template<typename T, int RowCount, int ColumnCount>
    const StaticMatrix<T,RowCount,ColumnCount> & StaticMatrix<T,RowCount,ColumnCount>::Identity(){
      static StaticMatrix<T,RowCount,ColumnCount> * matrix=0;
      if(!matrix){
        matrix = new StaticMatrix<T,RowCount,ColumnCount>();
        matrix->setZero();
        for(uint i=0; i < RowCount && i < ColumnCount;i++) (*matrix)(i,i)=1.0;
      }
      return *matrix;
    }
    template<typename T, int RowCount, int ColumnCount>
    inline const StaticMatrix<T,RowCount,ColumnCount> & StaticMatrix<T,RowCount,ColumnCount>::Zero(){
      static StaticMatrix<T,RowCount,ColumnCount> *  matrix=0;
      if(!matrix){
        matrix = new StaticMatrix<T,RowCount,ColumnCount>();
        matrix->setZero();
      }
      return *matrix;
    }

    template<typename T, int RowCount, int ColumnCount>
    inline void StaticMatrix<T,RowCount,ColumnCount>::transpose(){
      if(RowCount!=ColumnCount){
        std::cerr << "cannot transpose non square StaticMatrix in place" << std::endl;
      }
      MatrixTransposeInPlace<StaticMatrix<T,RowCount,ColumnCount> >::operation(*this);
    }
    template<typename T, int RowCount, int ColumnCount>
    inline void StaticMatrix<T,RowCount,ColumnCount>::toTransposed(StaticMatrix<T,ColumnCount,RowCount> & AT)const{
        nspace::transpose(AT,*this);
        //MatrixTranspose<StaticMatrix<T,ColumnCount,RowCount>, StaticMatrix<T,RowCount,ColumnCount> >::operation(AT,*this);
      //MatrixOperations<T>::transpose(AT,*this);
    }
    template<typename T, int RowCount, int ColumnCount>
    inline StaticMatrix<T,ColumnCount,RowCount> StaticMatrix<T,RowCount,ColumnCount>::transposed()const{
      StaticMatrix<T,ColumnCount,RowCount> AT;
      nspace::transpose(AT,*this);
      //OperationMatrixTranspose<StaticMatrix<T,ColumnCount,RowCount>, StaticMatrix<T,RowCount,ColumnCount> >::operation(AT,*this);
      return AT;
    }

    template<typename T, int RowCount, int ColumnCount>
    inline T StaticMatrix<T,RowCount,ColumnCount>::length()const{
      T result;
      nspace::length(result,*this);
      return result;
    }
    template<typename T, int RowCount, int ColumnCount>
    inline T StaticMatrix<T,RowCount,ColumnCount>::norm()const{
      T result;
      nspace::length(result,*this);
      return result;
    }
    template<typename T, int RowCount, int ColumnCount>
    inline T StaticMatrix<T,RowCount,ColumnCount>::length2()const{
      T result;
      nspace::lengthSquared(result,*this);
      return result;
    }
    template<typename T, int RowCount, int ColumnCount>
    inline T StaticMatrix<T,RowCount,ColumnCount>::squaredNorm()const{
      T result;
      nspace::lengthSquared(result,*this);
      return result;
    }
    template<typename T, int RowCount, int ColumnCount>
    inline T StaticMatrix<T,RowCount,ColumnCount>::maximum()const{
      T result;
      vectorop::maximum(result,*this);
      return result;
    }
    template<typename T, int RowCount, int ColumnCount>
    inline T StaticMatrix<T,RowCount,ColumnCount>::minimum()const{
      T result;
      vectorop::minimum(result,*this);
    }
    template<typename T, int RowCount, int ColumnCount>
    inline void StaticMatrix<T,RowCount,ColumnCount>::normalize(){
      nspace::normalize(*this);
      //vectorop::normalize(*this);
    }

    template<typename T, int RowCount, int ColumnCount>
    inline bool StaticMatrix<T,RowCount,ColumnCount>::resize(int rows, int cols){
      if(rows==RowCount && cols == ColumnCount)return true;
      return false;
    }
    template<typename T, int RowCount, int ColumnCount>
    inline StaticMatrix<T,RowCount,ColumnCount> StaticMatrix<T,RowCount,ColumnCount>::operator -(){
      StaticMatrix<T,RowCount,ColumnCount> result;
      math::shorthands::matrix::negate(result,*this);
      return result;
    }
  }
}
