#pragma once
#include <stdio.h>
#include <iostream>
#include <functional>
#include <config.h>

#include <math.scalar/core.h>

#include <math.matrix/operations/MatrixAdditionInPlace.h>
#include <math.matrix/operations/MatrixAddition.h>
#include <math.matrix/operations/MatrixAssignment.h>
#include <math.matrix/operations/MatrixConvolution.h>
#include <math.matrix/operations/MatrixFilter.h>
#include <math.matrix/operations/MatrixFrobeniusNorm.h>
#include <math.matrix/operations/MatrixInversion.h>
#include <math.matrix/operations/MatrixMinimumElement.h>
#include <math.matrix/operations/MatrixMaximumElement.h>
#include <math.matrix/operations/MatrixMultiplicationInPlace.h>
#include <math.matrix/operations/MatrixMultiplication.h>
#include <math.matrix/operations/MatrixNegationInPlace.h>
#include <math.matrix/operations/MatrixNegation.h>
#include <math.matrix/operations/MatrixNormalization.h>
#include <math.matrix/operations/MatrixMultiplication.h>
#include <math.matrix/operations/MatrixAllocate.h>
#include <math.matrix/operations/MatrixDeallocate.h>
#include <math.matrix/operations/MatrixCoefficientAccess.h>
#include <math.matrix/operations/MatrixScalarDivisionInPlace.h>
#include <math.matrix/operations/MatrixScalarDivision.h>
#include <math.matrix/operations/MatrixScalarMultiplicationInPlace.h>
#include <math.matrix/operations/MatrixScalarMultiplication.h>
#include <math.matrix/operations/MatrixSetConstant.h>
#include <math.matrix/operations/MatrixSetFunction.h>
#include <math.matrix/operations/MatrixSubtractionInPlace.h>
#include <math.matrix/operations/MatrixSubtraction.h>
#include <math.matrix/operations/MatrixInversionSymmetric.h>
#include <math.matrix/operations/MatrixTranspositionInPlace.h>
#include <math.matrix/operations/MatrixTransposition.h>
#include <math.matrix/operations/VectorCrossProduct.h>
#include <math.matrix/operations/VectorInnerProduct.h>
#include <math.matrix/operations/VectorOuterProduct.h>
#include <math.matrix/operations/VectorToCrossProductMatrix.h>
#include <math.matrix/operations/QuaternionMultiplication.h>
#include <math.matrix/operations/QuaternionConjugation.h>
#include <math.matrix/operations/QuaternionToRotationMatrix.h>
#include <math.matrix/operations/MatrixBlockAssign.h>
#include <math.matrix/operations/MatrixBlockExtract.h>
#include <math.matrix/operations/MatrixElementWiseMultiplication.h>
#include <math.matrix/operations/MatrixElementWiseDivision.h>
#include <math.matrix/operations/MatrixReduce.h>
#include <math.matrix/operations/MatrixReduceSum.h>
#include <math.matrix/operations/MatrixScalarAddition.h>
#include <math.matrix/operations/MatrixScalarSubtraction.h>
#include <math.matrix/operations/MatrixCompare.h>
#include <math.matrix/operations/MatrixInversion.h>
#include <math.matrix/operations/MatrixInversionSymmetric.h>
#include <math.matrix/operations/MatrixCartesianToHomogenousCoordinates.h>
#include <math.matrix/operations/MatrixHomogenousToCartesianCoordinates.h>
#include <math.matrix/operations/MatrixExportData.h>
#include <math.matrix/operations/MatrixImportData.h>
#include <math.matrix/operations/MatrixResize.h>
#include <math.matrix/operations/MatrixSubtractionConstant.h>
#include <math.matrix/operations/MatrixElementWiseUnary.h>
#include <math.matrix/operations/MatrixElementWiseBinary.h>
#include <math.matrix/operations/MatrixPad.h>

#include <math.matrix/operations/MatrixEquals.h>
#include <math.matrix/operations/MatrixLessThan.h>
#include <math.matrix/operations/MatrixGreaterThan.h>

#include <math.matrix/operations/MatrixColumnCount.h>
#include <math.matrix/operations/MatrixRowCount.h>
#include <math.matrix/operations/MatrixElementAssignment.h>

#include <math.matrix/operations/MatrixTypeSelector.h>
#include <math.matrix/operations/MatrixTraits.h>
#include <math.matrix/operations/MatrixRowTraits.h>
#include <math.matrix/operations/MatrixColumnTraits.h>

#include <math.matrix/operations/MatrixSetZero.h>

#include <math.matrix/operations/MatrixMaximumElement.h>
#include <math.matrix/operations/MatrixMinimumElement.h>
#include <math.matrix/operations/MatrixSwap.h>
#include <math.matrix/operations/MatrixSwapColumns.h>
#include <math.matrix/operations/MatrixSwapRows.h>
#include <math.matrix/operations/MatrixOperations.h>

#include <math.matrix/operations/GaussJordanElimination.h>
#include <math.matrix/operations/VectorNormalize.h>
#include <math.matrix/operations/VectorNorm.h>

#include <math.matrix/operations/VectorNormal.h>
#include <math.matrix/operations/VectorTriangleNormal.h>

#include <math.matrix/operations/MatrixRandomize.h>
#include <math.matrix/operations/MatrixSetZero.h>
#include <math.matrix/operations/MatrixIdentity.h>

#include <math.matrix/specialization/Scalars.h>
#include <math.matrix/specialization/Array1D.h>
#include <math.matrix/specialization/Array2D.h>
#include <math.matrix/specialization/StdVector.h>




namespace nspace{
  namespace math{
    namespace shorthands{
      namespace matrix{
        template<typename MatA, typename MatB, typename Elem>
        inline bool matricesEqual(const MatA & a,const MatB & b,const Elem & eps){
          bool result=false;
          OperationMatrixEquals<MatA,MatB,Elem>::operation(result,a,b,eps);
          return result;
        }

        template<typename MatA, typename Vec>
        inline void crossProductMatrix(MatA & a_star, const Vec& a){
          VectorToCrossProductMatrix<MatA,Vec>::operation(a_star,a);
        }

        template<typename MatA, typename MatB>
        inline void negate(MatA & result, const MatB & orig){
          MatrixNegation<MatA,MatB>::operation(result,orig);
        }

        template<typename Vec3A ,typename Vec3B, typename Vec3C>
        inline void crossProduct(Vec3C & c, const Vec3A & a, const Vec3B & b){
          VectorCrossProduct<Vec3C,Vec3A,Vec3B>::operation(c,a,b);
        }


        template<typename MatType,typename BlockType>
        inline void setBlock(MatType & target, const BlockType & source, uint rowoffset, uint coloffset){
          MatrixBlockAssign<BlockType,MatType>::operation(target,source,rowoffset,coloffset);
        }

        template<typename BlockType, typename MatType>
        inline void getBlock(BlockType & block, const MatType & mat, uint rowoffset, uint coloffset){
          MatrixBlockExtract<BlockType,MatType>::operation(block,mat,rowoffset,coloffset);
        }

        template<typename T, typename TargetType>
        inline void assign(TargetType & target, const T* source){
          MatrixAssignData<T,TargetType>::operation(target,source);
        }

        template<typename T, typename SourceType>
        inline void copyTo(T * target, const SourceType & source){
          MatrixCopyToPointer<T,SourceType>::operation(target,source);
        }
        template<typename T, typename VectorTypeA, typename VectorTypeB>
        inline void innerProduct(T & result, const VectorTypeA & a, const VectorTypeB & b){
          VectorInnerProduct<T, VectorTypeA,VectorTypeB>::operation(result,a,b);
        }

        template<typename Result,typename Mat>
        inline void maximum(Result & result, const Mat & mat){
          MatrixMaximumElement<Result,Mat>::operation(result,mat);
        }
        template<typename Mat>
        inline Real maximum(const Mat & mat){
          Real result;
          maximum(result,mat);
          return result;
        }

        template<typename C, typename A, typename B>
        inline void elementWiseMultiply(C & result, const A & a, const B& b ){
          MatrixElementWiseMultiply<C,A,B>::operation(result,a,b);
        }
        template<typename C, typename A, typename B>
        inline void elementWiseDivide(C & result, const A & a, const B& b ){
          MatrixElementWiseDivide<C,A,B>::operation(result,a,b);
        }
        template<typename OutputMatrix, typename InputMatrix>
        void padMatrix(OutputMatrix & out, const InputMatrix & inputMatrix,uint rowsTop, uint rowsBottom, uint colsLeft, uint colsRight){
          MatrixPad<OutputMatrix,InputMatrix>::operation(out,inputMatrix, rowsTop,  rowsBottom,  colsLeft,  colsRight);
        }

        template<typename OutputMatrix, typename InputMatrix, typename KernelMatrix>
        void convolve(OutputMatrix & result, const InputMatrix & original, const KernelMatrix & kernel){
          MatrixConvolution<OutputMatrix,InputMatrix,KernelMatrix,Real>::operation(result,original,kernel);
        }

        template<typename MatA, typename MatB>
        void compareMatrix(bool & result, const MatA & a, const MatB & b, Real epsilon = EPSILON){
          MatrixCompare<MatA,MatB,Real>::operation(result,a,b,epsilon);
        }

        template<typename OutputMatrix, typename InputMatrix, typename KernelMatrix>
        void convolveSame(OutputMatrix & result, const InputMatrix & original, const KernelMatrix & kernel, int borderStrategy=0){
          uint rowsTop = kernel.rows()/2-1+kernel.rows()%2;
          uint rowsBottom = kernel.rows()/2;
          uint colsLeft = kernel.cols()/2-1+kernel.cols()%2;
          uint colsRight = kernel.cols()/2;
          InputMatrix padded;
          padMatrix(padded,original,rowsTop,rowsBottom,colsLeft,colsRight);
          MatrixConvolution<OutputMatrix,InputMatrix,KernelMatrix,Real>::operation(result,padded,kernel);
        }

        template<typename OutputMatrix, typename InputMatrix, typename FilterFunction, typename FilterArgument>
        void filter(OutputMatrix & result, const InputMatrix & original, FilterFunction filter,uint width, uint height){
          MatrixFilter<OutputMatrix,InputMatrix,FilterFunction,FilterArgument>::operation(result,original,filter,width,height);
        }

        template<typename C, typename A, typename B>
        void add(C & c, const A& a, const B & b){
          MatrixAddition<C,A,B>::operation(c,a,b);
        }
        template<typename C, typename A, typename B>
        void subtract(C & c, const A& a, const B & b){
          MatrixSubtraction<C,A,B>::operation(c,a,b);
        }
        template<typename C, typename A, typename B>
        void multiplyMatrix(C & c, const A& a, const B & b){
          MatrixMultiplication<Real,C,A,B>::operation(c,a,b);
        }
        template<typename C, typename A, typename B>
        void multiplyScalar(C & c, const A& a, const B & s){
          MatrixScalarMultiplication<C,A,B>::operation(c,a,s);
        }

        template<typename A, typename B>
        inline void cart2hom(A & hom, const B & car){
          MatrixCartesianToHomogenousCoordinates<A,B>::operation(hom,car);
        }

        template<typename A, typename B>
        inline void hom2car(A & cart, const B & hom){
          MatrixHomogenousToCartesianCoordinates<A,B>::operation(cart,hom);
        }

        template<typename InvertedMatrixType, typename InputMatrixType>
        void invertSymmetricMatrix(InvertedMatrixType & inv, const InputMatrixType & symmetricMatrix){
          MatrixInversion<InvertedMatrixType,InputMatrixType,MatrixProperty::Symmetric>::operation(inv,symmetricMatrix);
        }
        template<typename InvertedMatrixType, typename InputMatrixType>
        void invertMatrix(InvertedMatrixType & inv, const InputMatrixType & matrix){
          MatrixInversion<InvertedMatrixType,InputMatrixType,MatrixProperty::Symmetric>::operation(inv,matrix);
        }

        template<typename TAssignee, typename TValue>
        inline bool assignMatrix(TAssignee & assignee, const TValue & value){
          return nspace::assignMatrix(assignee,value);
        }
        template<typename TAssignee, typename TValue>
        inline bool assignElement(TAssignee & assignee, uint i, uint j, const TValue & value){
          return MatrixElementAssignment<TAssignee,TValue>::operation(assignee,i,j,value);
        }

        
      }
    }
  }

  //create shortcut for matrix operations
  namespace matrix = nspace::math::shorthands::matrix;
}
