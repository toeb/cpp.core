#pragma once
#include <core/patterns/ArrayPool.h>

#include <math.matrix/Matrix.h>
#include <math.matrix/MatrixOperations.h>
#include <math.matrix/VectorOperations.h>


namespace nspace{
  namespace matrix2{
    template<typename T>
    class DynamicMatrix  : public nspace::Matrix<T>{
    protected:
      uint _rows;
      uint _cols;
      T * _data;
      inline T & value(int i, int j);
      inline const T & value(int i, int j)const;
    public:

      inline void toUnitInterval();

      inline void setConstant(const T & val);
      inline void setFunction(std::function<void (T& ,int,int)> f);
      inline void setZero();
      inline void assign(const DynamicMatrix<T> & mat);
      template<typename SourceType>
      inline void assign(const DynamicMatrix<SourceType> & mat);
      template<typename TargetType>
      inline void copyTo(DynamicMatrix<TargetType> & target)const;
      template<typename TSource>
      inline void assign(const TSource * data);
      template<typename Converter, typename TSource>
      inline void assign(const TSource * data);

      inline void filter(DynamicMatrix<T> &out,std::function<void (T & ,DynamicMatrix<T> & ) >f, uint filterWidth, uint filterHeight )const;
      inline DynamicMatrix<T>  filter(std::function<void (T & ,DynamicMatrix<T> & ) >f,uint filterWidth,uint filterHeight);

      inline void assign(const T * valuesRowMajor);
      inline void getBlock(DynamicMatrix<T> & block, uint i, uint j)const;
      template<typename OutputMatrix>
      inline void block(OutputMatrix & r, uint i, uint j)const;
      template<typename OutputMatrix>
      inline void block(OutputMatrix & r, uint i, uint j, uint rows, uint cols)const;
      inline void setBlock(uint i,uint j, const DynamicMatrix<T> & block);
      inline void assignRows(uint rowCount, const DynamicMatrix<T> & mat );
      inline T norm()const;

      DynamicMatrix(const DynamicMatrix<T> & orig);
      inline int size()const;
      ~DynamicMatrix();
      inline  T maximum()const;
      inline  T minimum()const;
      DynamicMatrix();
      DynamicMatrix(int rows, int cols);

      inline size_t dataByteSize()const;
      inline DynamicMatrix<T> & operator=(const DynamicMatrix<T> & orig );

      inline bool resize(int n, int m);
      inline DynamicMatrix<T> transpose()const ;
      inline Real * rowData(int i);
      inline const Real * rowData(int i)const;
      template<typename T2>
      inline void copyTo(T2 * valuePtr);
      inline int index(int i, int j)const;
      inline T & operator()(int i, int j);
      inline const T & operator()(int i, int j)const;
      inline T & operator()(int i);
      inline const T & operator()(int i)const;

      inline int rows()const;
      inline int cols()const;
      T * data();
      const T * data()const;
    };

    template<typename T>
    inline T & DynamicMatrix<T>::value(int i, int j){
      return _data[index(i,j)];
    }
    template<typename T>
    inline const T & DynamicMatrix<T>::value(int i, int j)const{
      return _data[index(i,j)];
    }

    template<typename T>
    inline void DynamicMatrix<T>::toUnitInterval(){
      Real mini = minimum();
      *this -= mini;
      Real maxim = maximum();
      *this /= maxim;
    }

    template<typename T>
    inline void DynamicMatrix<T>::setConstant(const T & val){
      MatrixSetConstant<T, DynamicMatrix<T> >::operation(*this,val);
    }
    template<typename T>
    inline void DynamicMatrix<T>::setFunction(std::function<void (T& ,int,int)> f){
      MatrixSetFunction<DynamicMatrix<T> ,std::function<void (T& ,int,int)> >::operation(*this,f);
    }
    template<typename T>
    inline void DynamicMatrix<T>::setZero(){
      MatrixSetConstant<T, DynamicMatrix<T> >::operation(*this,0.0);

    }
    template<typename T>
    inline void DynamicMatrix<T>::assign(const DynamicMatrix<T> & mat){
      assignMatrixForced(*this,mat);
    }
    template<typename T>
    template<typename SourceType>
    inline void DynamicMatrix<T>::assign(const DynamicMatrix<SourceType> & mat){
      assignMatrixForced(*this,mat);
    }
    template<typename T>
    template<typename TargetType>
    inline void DynamicMatrix<T>::copyTo(DynamicMatrix<TargetType> & target)const{
      target.assign(*this);
    }
    template<typename T>
    template<typename TSource>
    inline void DynamicMatrix<T>::assign(const TSource * data){
      for(int i=0; i< size();i++){
        _data[i]=data[i];
      }
    }
    template<typename T>
    template<typename Converter, typename TSource>
    inline void DynamicMatrix<T>::assign(const TSource * data){
      for(int i=0; i< size();i++){
        _data[i]=(T)(Converter)data[i];
      }
    }

    template<typename T>
    inline void DynamicMatrix<T>::filter(DynamicMatrix<T> &out,std::function<void (T & ,DynamicMatrix<T> & ) >f, uint filterWidth, uint filterHeight )const{
      MatrixFilter<DynamicMatrix<T>,DynamicMatrix<T>,std::function<void (T & ,DynamicMatrix<T> & ) >,DynamicMatrix<T>>::operation(out,*this,f,filterWidth,filterHeight);
    }
    template<typename T>
    inline DynamicMatrix<T>  DynamicMatrix<T>::filter(std::function<void (T & ,DynamicMatrix<T> & ) >f,uint filterWidth,uint filterHeight){
      DynamicMatrix<T> result;
      filter(result, f,filterWidth,filterHeight);
      return result;
    }

    template<typename T>
    inline void DynamicMatrix<T>::assign(const T * valuesRowMajor){
      memcpy(_data,valuesRowMajor,dataByteSize());
    }
    template<typename T>
    inline void DynamicMatrix<T>::getBlock(DynamicMatrix<T> & block, uint i, uint j)const{
      // do eome safety checks here
      if(i+block.rows() > _rows){
        std::cerr << "getBlock error"<<std::endl;
        return;
      }
      if(j+block.cols()>_cols){
        std::cerr << "getBlock error" << std::endl;
        return;
      }
      for(int k=0; k < block.rows();k++){
        T * rowPtr = block.rowData(k);
        memcpy(rowPtr,_data+(i+k)*cols(),block.cols()*sizeof(T));
      }
    }
    template<typename T>
    template<typename OutputMatrix>
    inline void DynamicMatrix<T>::block(OutputMatrix & r, uint i, uint j)const{
      MatrixExtractBlock<OutputMatrix,DynamicMatrix<T> >::operation(r,*this,i,j,r.rows(),r.cols());
    }
    template<typename T>
    template<typename OutputMatrix>
    inline void DynamicMatrix<T>::block(OutputMatrix & r, uint i, uint j, uint rows, uint cols)const{
      MatrixExtractBlock<OutputMatrix,DynamicMatrix<T> >::operation(r,*this,i,j,rows,cols);
    }
    template<typename T>
    inline void DynamicMatrix<T>::setBlock(uint i,uint j, const DynamicMatrix<T> & block){
      // do eome safety checks here
      if(i+block.rows() > _rows){
        std::cerr << "getBlock error"<<std::endl;
        return;
      }
      if(j+block.cols()>_cols){
        std::cerr << "getBlock error" << std::endl;
        return;
      }
      for(int k=0; k < block.rows();k++){
        const T * rowPtr = block.rowData(k);
        memcpy(_data+(i+k)*cols(),rowPtr,block.cols()*sizeof(T));
      }
    }
    template<typename T>
    inline void DynamicMatrix<T>::assignRows(uint rowCount, const DynamicMatrix<T> & mat ){
      memcpy(_data,mat._data,sizeof(T)*rowCount*_cols);
    }
    template<typename T>
    inline T DynamicMatrix<T>::norm()const{
      T result;
      nspace::length(result,*this);
      //vectorop::norm(result,*this);
      return result;
    }

    template<typename T>
    DynamicMatrix<T>::DynamicMatrix(const DynamicMatrix<T> & orig):_rows(0),_cols(0),_data(0){
      assign(orig);
    }
    template<typename T>
    inline int DynamicMatrix<T>::size()const{
      return _rows*_cols;
    }
    template<typename T>
    DynamicMatrix<T>::~DynamicMatrix(){
      ArrayPool<T>::freeArray(&_data,size());
      _rows = 0;
      _cols = 0;
    }
    template<typename T>
    inline  T DynamicMatrix<T>::maximum()const{
      T t;
      MatrixMaximumElement<T,DynamicMatrix<T> >::operation(t,*this);
      return t;
    }
    template<typename T>
    inline  T DynamicMatrix<T>::minimum()const{
      T t;
      MatrixMinimumElement<T,DynamicMatrix<T> >::operation(t,*this);
      return t;
    }
    template<typename T>
    DynamicMatrix<T>::DynamicMatrix():_rows(0),_cols(0),_data(0){resize(0,0);}
    template<typename T>
    DynamicMatrix<T>::DynamicMatrix(int rows, int cols):_rows(0),_cols(0),_data(0){
      resize(rows,cols);
    }

    template<typename T>
    inline size_t DynamicMatrix<T>::dataByteSize()const{
      return _rows*_cols*sizeof(T);
    }
    template<typename T>
    DynamicMatrix<T> & DynamicMatrix<T>::operator=(const DynamicMatrix<T> & orig ){
      assign(orig);
      return *this;
    }

    template<typename T>
    inline bool DynamicMatrix<T>::resize(int n, int m){
      if(_rows==n && _cols==m){
        return true;
      }
      ArrayPool<T>::freeArray(&_data,size());
      _rows = n;
      _cols=m;
      ArrayPool<T>::createArray(&_data,size());

      _rows = n;
      _cols =m;

      return true;
    }
    template<typename T>
    inline DynamicMatrix<T> DynamicMatrix<T>::transpose()const {     
      DynamicMatrix<T> result;
      nspace::transpose(result,*this);
      return result;
    }
    template<typename T>
    inline Real * DynamicMatrix<T>::rowData(int i){
      return _data +(i*_cols);
    }
    template<typename T>
    inline const Real * DynamicMatrix<T>::rowData(int i)const{
      return _data+(i*_cols);
    }
    template<typename T>
    template<typename T2>
    inline void DynamicMatrix<T>::copyTo(T2 * valuePtr){
      for(int i=0; i < size();i++){
        valuePtr[i]=_data[i];
      }
    }
    template<typename T>
    inline int DynamicMatrix<T>::index(int i, int j)const{return i* _cols+j;}
    template<typename T>
    inline T & DynamicMatrix<T>::operator()(int i, int j){return _data[i* _cols+j]; }
    template<typename T>
    inline const T & DynamicMatrix<T>::operator()(int i, int j)const{return _data[i* _cols+j]; }
    template<typename T>
    inline T & DynamicMatrix<T>::operator()(int i){return _data[i]; }
    template<typename T>
    inline const T & DynamicMatrix<T>::operator()(int i)const{return _data[i]; }

    template<typename T>
    inline int DynamicMatrix<T>::rows()const{return _rows;}
    template<typename T>
    inline int DynamicMatrix<T>::cols()const{return _cols;}
    template<typename T>
    T * DynamicMatrix<T>::data(){return _data;}
    template<typename T>
    const T * DynamicMatrix<T>::data()const{return _data;}
  }
}
