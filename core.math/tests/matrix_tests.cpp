
#include <core.testing.h>


#include <core.math/matrix/all.h>
#include <core.math/matrix.dslib/all.h>



NS_USE(CORE_MATH_NAMESPACE);



typedef matrix::dslib::DynamicMatrix<double> MatrixNxM;
typedef matrix::dslib::StaticMatrix<double, 2, 2> Matrix2x2;
typedef matrix::dslib::StaticMatrix<double, 3, 1> Vector3D;



UNITTEST(upperTMatTest){
  auto res = core::math::matrix::upperTriangleMatrix<Matrix2x2>(1, 2, 3);
  DOUBLES_EQUAL(1, res(0, 0), 0.00001);
  DOUBLES_EQUAL(2, res(0, 1), 0.00001);
  DOUBLES_EQUAL(0, res(1, 0), 0.00001);
  DOUBLES_EQUAL(3, res(1, 1), 0.00001);

}

UNITTEST(symmetricMatTest){
  auto uut = core::math::matrix::symmetricMatrix<Matrix2x2>(1, 2, 3);
  DOUBLES_EQUAL(1, uut(0, 0), 0.00001);
  DOUBLES_EQUAL(2, uut(0, 1), 0.00001);
  DOUBLES_EQUAL(2, uut(1, 0), 0.00001);
  DOUBLES_EQUAL(3, uut(1, 1), 0.00001);
}


UNITTEST(lowerTMatTest){
  auto res = core::math::matrix::upperTriangleMatrix<Matrix2x2>(1, 2, 3);
  DOUBLES_EQUAL(1, res(0, 0), 0.00001);
  DOUBLES_EQUAL(0, res(0, 1), 0.00001);
  DOUBLES_EQUAL(2, res(1, 0), 0.00001);
  DOUBLES_EQUAL(3, res(1, 1), 0.00001);

}


UNITTEST(DynamicMatrixCreate){
  NS_USE(CORE_MATH_NAMESPACE, matrix, dslib);
  DynamicMatrix<double> uut(20, 20);
}
UNITTEST(DynamicMatrixZero){
  MatrixNxM uut(2, 2);
  zeros(uut);
}
UNITTEST(StaticMatrixCreate){
  NS_USE(CORE_MATH_NAMESPACE, matrix, dslib);
  StaticMatrix<double, 20, 20> uut;

}

TEST(2, OperationMatrixIdentity){
  auto vector = identity<Vector3D>();
  CHECK(vector(0) == 1);
  CHECK(vector(1) == 0);
  CHECK(vector(2) == 0);

}

TEST(1, OperationMatrixIdentity){
  unsigned int a[2][2];
  matrixSetIdentity(a);
  CHECK(a[0][0] == 1);
  CHECK(a[1][1] == 1);
  CHECK(a[0][1] == 0);
  CHECK(a[1][0] == 0);
}
UNITTEST(OperaationMatrixIdentityShouldSetDynamicMatrix){
  
}

TEST(1, MatrixBlockExtract){
  MatrixNxM matrix = identity<MatrixNxM>(4, 4);
  Matrix2x2 block;
  matrixBlockExtract(block, matrix, 1, 1);
  auto a = block(0, 0) + block(1, 1);
  DOUBLES_EQUAL(2, a, 0.00001);
}

TEST(1, OperationMatrixAddition){
  auto result = add(identity<Matrix2x2>(), identity<Matrix2x2>());
  auto res = result(0, 0) + result(1, 1);
  DOUBLES_EQUAL(4, res, 0.00001);
};

/*

#include <string>
#include <random>

#include <core.testing.h>
#include <core.math.h>

#include <core.logging.h>
#include <core.task.h>


#include <core/template/is_same_type.h>

using namespace std;
NS_BEGIN(CORE_MATH_NAMESPACE)



TEST(1, OperationMatrixRandom){
auto vector = random<Vector3D>();
CHECK(vector(0) >= 0 && vector(0)<=1);
CHECK(vector(1) >= 0 && vector(1)<=1);
CHECK(vector(2) >= 0 && vector(2)<=1);
}

TEST(3, OperationMatrixScalarMultiplication){

Vector3D v=Vector3D::UnitX();

auto result =matrixMultiplyScalar(v,0.25);

CHECK(result(0)==0.25);
CHECK(result(1)==0.0);
CHECK(result(2)==0.0);

}

TEST(2, OperationMatrixScalarMultiplication){
unsigned int a =4;
unsigned int b=5;

matrixMultiplyScalar(a,a,b);

CHECK(a==20);

}


TEST(1, OperationMatrixScalarMultiplication){
unsigned int a[2][2];
a[0][0]=1;
a[1][1]=2;
a[0][1]=3;
a[1][0]=4;
unsigned int b=5;

matrixMultiplyScalar(a,a,b);

CHECK(a[0][0]==5);
CHECK(a[1][1]==10);
CHECK(a[0][1]==15);
CHECK(a[1][0]==20);

}

TEST(1, unsignedIntMatrixAssignment){
unsigned int * rhs = new  unsigned int[3];

rhs[0]=5;
rhs[1] =4;
rhs[2] =23;
unsigned int lhs[3];
auto v1= coefficient(rhs,1,0);
auto & v2 = coefficient(lhs,1,0);

indexTypeOfType(unsigned int[3]) r1 = rows(lhs);
indexTypeOfType(const unsigned int *) r2 = rows(rhs);
indexTypeOfType(unsigned int[3]) c1 = cols(lhs);
indexTypeOfType(const unsigned int *) c2 = cols(rhs);
coefficient(lhs,1,0)=coefficient(rhs,1,0);
assignMatrixBlindly(lhs,rhs);
}




template<typename T ,T defaultValue, bool variable>
class variableIf{};
template<typename T, T defaultValue>
class variableIf<T,defaultValue,true>{
private:
T _value;
public:
inline operator T (){return get();}
inline variableIf(){set(defaultValue);}
inline variableIf<T,defaultValue,true> &  operator =(const T other){set(other);return *this;}
inline void set(const T value){_value = value;}
inline T get()const{return _value;}
};
template<typename T, T defaultValue>
class variableIf<T,defaultValue,false>{
public :
inline variableIf<T,defaultValue,false> &  operator =(const T other){set(other);return *this;}
inline operator T (){return get();}
inline void set(const T value){}
inline T get(){return defaultValue;}
};




TEST(1,templateTest){
variableIf<int,5,true> var;
variableIf<int,5,false> var2;

int val = var;
int val2 = var2;

CHECK(val==5);
CHECK(var2==5);

var = 5125;
var2 = 3235;

CHECK(var==5125);
CHECK(var2==5);
}



TEST(1, Normal){
auto n =triangleNormal(Vector3D::UnitX(),Vector3D::UnitY(),Vector3D::UnitZ());


double d;
d = math::shorthands::scalar::squareRoot(1.0/3.0);
DOUBLES_EQUAL(n(0),d,0.0001);
DOUBLES_EQUAL(n(1),d,0.0001);
DOUBLES_EQUAL(n(2),d,0.0001);
}

TEST(3, Normalized){
Vector3D vec(5,5,5);
Vector3D result = normalized(vec);
double d;
d = math::shorthands::scalar::squareRoot(1.0/3.0);
CHECK(result(0)==d && result(1)==d && result(2)==d);

}

TEST(2, Normalized){
float vec[3]={3,0,0};
float result[3];
normalized(result,vec);
CHECK(vec[0]==3);
CHECK(result[0]==1);
}

TEST(1, Normalized){
float vec[3]={3,0,0};

normalize(vec);
CHECK(vec[0]==1);
}
TEST(1, lengthSquared){
auto l2 = lengthSquared(2.0);
CHECK(l2==4.0);
}

TEST(5, EigenSpecialization){
float matrix[4][4];
Eigen::Matrix<float,4,4> id = Eigen::Matrix<float,4,4>::Identity();
assignMatrix(matrix, id);
CHECK(matrix[2][2]==1);
}

TEST(4 ,EigenSpecialization){
Eigen::Matrix<float,Eigen::Dynamic, Eigen::Dynamic> matrix(4,4);
matrix.setIdentity();
CHECK(rows(matrix)==4);
CHECK(cols(matrix)==4);
CHECK(!isScalarMatrix(matrix));
CHECK(rowTraits(matrix)==Dynamic);
CHECK(columnTraits(matrix)==Dynamic);
auto sametype = isSameType<coefficientTypeOfInstance(matrix), float>();
CHECK(sametype);
auto c11 = coefficient(matrix,0,0);
CHECK(c11==1.0f);
}
TEST(3 ,EigenSpecialization){
Eigen::Matrix<float,4, Eigen::Dynamic> matrix(4,4);
matrix.setIdentity();
CHECK(rows(matrix)==4);
CHECK(cols(matrix)==4);
CHECK(!isScalarMatrix(matrix));
CHECK(rowTraits(matrix)==Fixed);
CHECK(columnTraits(matrix)==Dynamic);
auto sametype = isSameType<coefficientTypeOfInstance(matrix), float>();
CHECK(sametype);
auto c11 = coefficient(matrix,0,0);
CHECK(c11==1.0f);
}

TEST(2 ,EigenSpecialization){
Eigen::Matrix<float,Eigen::Dynamic, 4> matrix(4,4);
matrix.setIdentity();
CHECK(rows(matrix)==4);
CHECK(cols(matrix)==4);
CHECK(!isScalarMatrix(matrix));
CHECK(rowTraits(matrix)==Dynamic);
CHECK(columnTraits(matrix)==Fixed);
auto sametype = isSameType<coefficientTypeOfInstance(matrix), float>();
CHECK(sametype);
auto c11 = coefficient(matrix,0,0);
CHECK(c11==1.0f);
}
TEST(1 ,EigenSpecialization){
Eigen::Matrix<float, 3,3> matrix;
matrix.setIdentity();
CHECK(rows(matrix)==3);
CHECK(cols(matrix)==3);
CHECK(!isScalarMatrix(matrix));
CHECK(rowTraits(matrix)==Fixed);
CHECK(columnTraits(matrix)==Fixed);
auto sametype = isSameType<coefficientTypeOfInstance(matrix), float>();
CHECK(sametype);
auto c11 = coefficient(matrix,0,0);
CHECK(c11==1.0f);
}

TEST(1, MatrixTranspose){
int arrayMatrix[2][2]={{1,2},{3,4}};
int resultMatrix[2][2];
nspace::transpose(resultMatrix,arrayMatrix);
CHECK(resultMatrix[0][0]== 1 && resultMatrix[0][1]==3 && resultMatrix[1][0] == 2 && resultMatrix[1][1]==4);


}

TEST(1 ,MatrixWrapper){
int arrayMatrix[4][4];
auto matrix = wrapMatrix(arrayMatrix);

CHECK(matrix.rows()==4);
CHECK(matrix.cols()==4);
matrix(1,1)= 55;
CHECK(arrayMatrix[1][1]==55);

}

TEST(1 , indexOfRowMaximum){

auto matrix = Matrix3x3::Identity();
auto index = indexOfColumnMaximum(matrix, 1, [](const Matrix3x3 & mat, int i, int j){return coefficient(mat,i,j);});
CHECK(index==1);
index = indexOfColumnMaximum(matrix, 2, [](const Matrix3x3 & mat, int i, int j){return coefficient(mat,i,j);});
CHECK(index==2);
}

TEST(1 , rowIndexOfMaximumColumnValue){

auto matrix = Matrix3x3::Identity();
auto index = indexOfColumnMaximum(matrix, 1, [](const Matrix3x3 & mat, int i, int j){return coefficient(mat,i,j);});
CHECK(index==1);
index = indexOfColumnMaximum(matrix, 2, [](const Matrix3x3 & mat, int i, int j){return coefficient(mat,i,j);});
CHECK(index==2);
}



TEST(1, MaxMatrixElemnt){
auto matrix = Matrix3x3::Identity();
matrix(1,2)=2;

int i; int j;
indexOfMaximum(matrix,i,j,[](const Matrix3x3 & matrix, int i, int j){return coefficient(matrix,i,j);});

CHECK(i==1 && j==2);

}



TEST(1, swapRows){
Matrix3x3 matrix = Matrix3x3::Identity();
swapRows(matrix,0,2);
CHECK(matrix(0,2)==1 && matrix(2,0)==1);
}


TEST(1, SwapCols){
Matrix3x3 matrix = Matrix3x3::Identity();
swapColumns(matrix,0,1);
CHECK(matrix(0,1)==1 && matrix(1,0)==1);
}



TEST(1, MachinCodeRowCOunt){
int arr[]={1,2,3};
auto r = rows(arr);
auto c = coefficient(arr,1);
CHECK(c==2);
CHECK(r==3);
}
TEST(5, GaussJordanElimination){
Matrix3x3 A; Matrix3x3 b;
A(0,0) = 3;  A(0,1) = 1;   A(0,2)=2;
A(1,0) = 3;  A(1,1) = 1;  A(1,2)=4;
A(2,0) = 5; A(2,1) = 2; A(2,2)=1;
b = Matrix3x3::Identity();

//OperationMatrixGaussJordan<Matrix3x3, Matrix3x3>::operation(A,b);
//    GaussJordanElimination<Matrix3x3,Matrix3x3,matrix2::StaticMatrix<int,3,1>>::gaussJordanEleminitation(A,b);

}

TEST(4, GaussJordanElimination){
Matrix3x3 A; Matrix3x3 b;
A(0,0) = 3;  A(0,1) = 2;   A(0,2)=-1;
A(1,0) = 2;  A(1,1) = -2;  A(1,2)=4;
A(2,0) = -1; A(2,1) = 0.5; A(2,2)=-1;
b = Matrix3x3::Identity();


// GaussJordanElimination<Matrix3x3,Matrix3x3,matrix2::StaticMatrix<int,3,1>>::gaussJordanEleminitation(A,b);

}
TEST(3,GaussJordanElimination){
Matrix3x3 A; Vector3D b;
A = Matrix3x3::Identity();
b(0)=1;
b(1)=3;
b(2)=2;

//GaussJordanElimination<Matrix3x3,Vector3D,matrix2::StaticMatrix<int,3,1>>::gaussJordanEleminitation(A,b);
}

TEST(2, GaussJordanElimination){
Matrix3x3 A; Vector3D b;
A(0,0) = 3;  A(0,1) = 2;   A(0,2)=-1; b(0)=1;
A(1,0) = 2;  A(1,1) = -2;  A(1,2)=4;  b(1)=-2;
A(2,0) = -1; A(2,1) = 0.5; A(2,2)=-1; b(2)=0;


// GaussJordanElimination<Matrix3x3,Vector3D,matrix2::StaticMatrix<int,3,1>>::gaussJordanEleminitation(A,b);

}

TEST(1, GaussJordanElimination){
auto identity =Matrix3x3::Identity();
auto b = Matrix3x3::Identity();
//GaussJordanElimination<Matrix3x3,Matrix3x3,matrix2::StaticMatrix<int,3,1> >::gaussJordanEleminitation(identity,b);

}
TEST(1, RowColCount){
auto identity = Matrix3x3::Identity();
auto rowCount = rows(identity);
auto colCount = cols(identity);
CHECK(rowCount==3);
}
TEST(1, OperationMatrixElementWiseUnary){
double a[3]={9,81,64};
elementWiseSquareRootInPlace(a);
CHECK(a[0]==3&&a[1]==9&&a[2]==8);

}
TEST(2, OperationMatrixElementWiseUnary){
MatrixNxM mat(100,100);
assignMatrixFunction(mat,[](int i,int j)->double{return (i-50)*(j-50);});
elementWiseSignumInPlace(mat);
}
TEST(3, OperationMatrixElementWiseUnary){
matrix2::StaticMatrix<double,10,10> mat;
assignMatrixFunction(mat,[](int i,int j)->double{return (i-5)*(j-5);});
elementWiseSignumInPlace(mat);

}

TEST(4,MatrixElementWiseUnaryRuntimeOperation){
matrix2::StaticMatrix<double,10,10> mat;
assignMatrixFunction(mat,std::function<double(int,int)>([](int i, int j)->double{return (i-5)*(j-5);}));
elementWiseUnaryInPlace(mat,[](double d)->double{return d*2;});

}



TEST(1, OperationMatrixCoefficientAccess){
double a[3]={4,5,6};
auto a1 = coefficient(a,0,0);
auto a2 = coefficient(a,1,0);
auto a3 = coefficient(a,2,0);

double d;
auto sameType = isSameType(a1,d);
CHECK(sameType)
CHECK(a1==4);
CHECK(a2==5);
CHECK(a3==6);


}
TEST(2, OperationMatrixCoefficientAccess){
double a[3]={4,5,6};
const auto & constA = a;

auto a1 = coefficient(constA,0,0);
auto a2 = coefficient(constA,1,0);
auto a3 = coefficient(constA,2,0);

double d;
auto sameType = isSameType(a1,d);
CHECK(sameType);
CHECK(a1==4);
CHECK(a2==5);
CHECK(a3==6);


}

TEST(1, CrossProduct){
double a[3]={1,0,0};
Vector3D b(0,1,0);
{
auto c = cross(a,b);
CHECK(c(0)==0);
CHECK(c(1)==0);
CHECK(c(2)==1);
}
{
auto c=cross(b,a);
CHECK(c(0)==0);
CHECK(c(1)==0);
CHECK(c(2)==-1);
}
}

TEST(1,innerProduct){
double a[3]={2,3,1};
Vector3D b(1,2,3);

{
auto c = dot(a,b);
auto type = isSameType(c,double(0));
CHECK(type);
CHECK(c==11);
}
}

TEST(1,MatrixCoefficientType){
Matrix2x2 matA[2][2];
auto a= isSameType<coefficientTypeOfInstance(matA), Matrix2x2>();
CHECK(a);
}


TEST(2,MatrixElementWiseMultiply){
matrix2::StaticMatrix<Matrix2x2,2,2> matA,matB;
matA(0,0)=Matrix2x2::Identity();
matA(0,1)=Matrix2x2::Identity();
matA(1,0)=Matrix2x2::Identity();
matA(1,1)=Matrix2x2::Identity();
matB(0,0)=Matrix2x2::Identity();
matB(0,1)=Matrix2x2::Zero();
matB(1,0)=Matrix2x2::Zero();
matB(1,1)=Matrix2x2::Identity();

auto result = multiply(matA,matB);
auto sameType = isSameType(result,matA);
CHECK(sameType);

for(int i=0; i < 2;i++)for(int j=0; j < 2; j++)for(int k=0;k < 2; k++)for(int l=0; l< 2;l++){
bool r=false;
auto val = result(i,j)(k,l);
if(i==j&&k==l)r=val==1;
else r = val==0;
CHECK(r);
}

}


TEST(1,MatrixElementWiseMultiply){
double a=4;
double b = 0.5;
auto result  =multiply(a,b);
auto sameType=isSameType(a,result);
CHECK(sameType);
CHECK(result==2.0);
}

TEST(MatrixTraitIsScalar1, Traits){
CHECK(isScalarMatrix(2));
CHECK(isScalarMatrix<double>());
}
TEST(MatrixTraitIsScalar2, Traits){
Matrix3x3 mat;
CHECK(!isScalarMatrix(mat));
CHECK(!isScalarMatrix<Matrix3x3>());

}

TEST(RowTraits, MatrixTraits){
double d;
CHECK(rowTraits(d)==Fixed);
CHECK(rowTraits<int>()==Fixed);
}
TEST(RowTraits2,MatrixTraits){
matrix2::DynamicMatrix<double> mat;
CHECK(rowTraits(mat)==Dynamic);
CHECK(rowTraits<matrix2::DynamicMatrix<double> >()==Dynamic);
}
TEST(RowTraits3,MatrixTraits){
matrix2::StaticMatrix<double,1,1> mat;
CHECK(rowTraits(mat)==Fixed);
auto traits = rowTraits<matrix2::StaticMatrix<double,1,1> >();
CHECK(traits==Fixed);
}
TEST(RowTraits4,MatrixTraits){
std::function<double(int,int)> foo=[](int i, int j){return i==j?1.0:0.0;};
CHECK(rowTraits(foo)==Infinite);
CHECK(rowTraits<std::function<double(int,int)> >()==Infinite);
}



TEST(ColTraits, MatrixTraits){
double d;
CHECK(columnTraits(d)==Fixed);
CHECK(columnTraits<int>()==Fixed);
}
TEST(ColTraits2,MatrixTraits){
matrix2::DynamicMatrix<double> mat;
CHECK(columnTraits(mat)==Dynamic);
CHECK(columnTraits<matrix2::DynamicMatrix<double> >()==Dynamic);
}



TEST(ColTraits3,MatrixTraits){
matrix2::StaticMatrix<double,1,1> mat;
CHECK(columnTraits(mat)==Fixed);
auto traits = columnTraits<matrix2::StaticMatrix<double,1,1> >();
CHECK(traits==Fixed);
}
TEST(ColTraits4,MatrixTraits){
std::function<double(int,int)> foo=[](int i, int j){return i==j?1.0:0.0;};
CHECK(columnTraits(foo)==Infinite);
CHECK(columnTraits<std::function<double(int,int)> >()==Infinite);
}



TEST(MatrixAssign2, Func){
Vector3D vec;
assignMatrixFunction(vec,[](int i, int j)->double{return  3.0-i;});
for(int i=0; i < 3; i++){
CHECK(3-i==vec(i));
}
}

TEST(MatrixAssign, Func){
MatrixNxM matrix(4,4);
assignMatrixBlindly(matrix,std::function<double(size_t,size_t)>([](size_t i, size_t j){return i==j?1.0:0.0;}));
for(int i=0; i < 4; i++){
for(int j=0; j < 4;j++){
if(i==j){
CHECK(matrix(i,j)==1.0);
}else{
CHECK(matrix(i,j)==0.0);
}
}
}
}

TEST(MatrixResize4, staticMatrix){
Matrix3x3 mat;
CHECK(resize(mat,3,3));
}

TEST(MatrixResize3, dynamicMatrix){
MatrixNxM matrix(3,3);
bool result = resize(matrix,5,5);
CHECK(result);
CHECK(matrix.rows()==5 && matrix.cols()==5);
}

TEST(MatrixResize1,double){
double d =32;
CHECK(!resize(d,2,2))
}
TEST(MatrixResize2,double){
double d =32;
CHECK(resize(d,1,1))
}

TEST(MatrixCoefficientType,double){
// only compilation matters
double d = coefficientTypeOfType(double)(0.0);
d = coefficientTypeOfInstance(d)(0.0);
CHECK(true);
}
TEST(MatrixCoefficientType,int){
// only compilation matters
int d = coefficientTypeOfType(int)(0.0);
d = coefficientTypeOfInstance(d)(0.0);
CHECK(true);
}


TEST(MatrixCoefficientAccess,double){
double matrix = 5.0;
auto coeff = coefficient(matrix,0,0);
CHECK(coeff==5.0);
}


TEST(MatrixCoefficientAccess1,doubleArr){
double matrix[3][3] = {{1.0,2.0,3.0},{1.0,2.0,3.0},{1.0,5.0,3.0}};
auto & coeff = coefficient(matrix,2,1);
coeff = 2.3;
CHECK(matrix[2][1]==2.3);
}
TEST(MatrixCoefficientAccess2,doubleArr){
double matrix[3][2] = {{1.0,2.0},{1.0,2.0},{1.0,5.0}};
auto & coeff = coefficient(matrix,1,1);
coeff = 2.3;
CHECK(matrix[1][1]==2.3);
}
TEST(MatrixCoefficientAccess2,doubleArr1d){
double matrix[3]={1.0,5.0,3.0};
auto & coeff = coefficient(matrix,1,0);
CHECK(coeff==5.0);
coeff = 2.3;
CHECK(matrix[1]==2.3);
}


TEST(MatrixCoefficientAccess1, StandardMatrix){
matrix2::StaticMatrix<double,5,2> mat;
auto & coeff = coefficient(mat,3,1);
coeff = 22;
CHECK(mat(3,1)==22);
}

TEST(MatrixAssign, FuncMatrix){
matrix2::StaticMatrix<double,3,3> mat;
bool result = assignMatrix(mat,lazyMatrix(3,3,[](int i, int j)->double{return i==j?1.0:0.0;}));
CHECK(result);
for(int i=0; i < mat.rows(); i++){
for(int j=0; j < mat.cols();j++){
if(i==j) {
CHECK(mat(i,j)==1.0);
}else{
CHECK(mat(i,j)==0.0);
}
}
}
}



TEST(rowcolcount1, scalar){
double d = 23;
CHECK(rows(d)==1);
CHECK(cols(d)==1);
}


#define BINARYOP_TEST(NAME, OP, TYPE_A, TYPE_B, TYPE_C, STRING_A, STRING_B, STRING_C)\
TEST(NAME##OP##TYPE_A##_##TYPE_B##_##TYPE_C,BinaryOperation){\
typedef nspace::TYPE_A TypeA;\
typedef nspace::TYPE_B TypeB;\
typedef nspace::TYPE_C TypeC;\
\
TypeA a;\
TypeB b;\
TypeC cExpected;\
TypeC cActual;\
\
nspace::deserializeString(a,STRING_A);\
nspace::deserializeString(b,STRING_B);\
nspace::deserializeString(cExpected,STRING_C);\
\
OP<TypeC,TypeA,TypeB>::operation(cActual,a,b);\
bool result =nspace::math::shorthands::matrix::matricesEqual(cExpected,cActual, Real(0.0001));\
CHECK(result);\
};





#define MATRIX_EQUALS_TEST(NAME,TYPE_A,TYPE_B,STRING_A,STRING_B,EPS,RESULT)\
TEST(NAME##equals##TYPE_A##TYPE_B, MatrixComparison){\
typedef TYPE_A TypeA;\
typedef TYPE_B TypeB;\
typedef Real ElementType;\
bool actualResult =false;\
TypeA a;\
TypeB b;\
deserializeString(a,STRING_A);\
deserializeString(b,STRING_B);\
ElementType epsilon=EPS;\
bool expectedResult = RESULT;\
OperationMatrixEquals<TypeA,TypeB,ElementType>::operation(actualResult,a,b,epsilon);\
CHECK(actualResult==expectedResult);\
};

MATRIX_EQUALS_TEST(eq1,Vector3D,Vector3D,"1 2 3","1 2 3",0.001,true);
MATRIX_EQUALS_TEST(eq2,Vector3D,Vector3D,"1 2 3","1.0001 2.0001 3.0001",0.001,true);
MATRIX_EQUALS_TEST(eq3,Vector3D,Vector3D,"1 2 3","1.0001 2.0001 3.001001",0.001,false);

BINARYOP_TEST(add1,MatrixAddition,Vector3D,Vector3D,Vector3D,"1 2 3", "4 5 6", "5 7 9");
BINARYOP_TEST(add2,MatrixAddition,Vector3D,Vector3D,Vector3D,"0 0 0", "0 0 0", "0 0 0");
BINARYOP_TEST(add3,MatrixAddition,Vector3D,Vector3D,Vector3D,"0 0 1", "0 2 0", "0 2 1");

BINARYOP_TEST(add1,MatrixAddition,Matrix3x3,Matrix3x3,Matrix3x3,
"1 0 0 0 1 0 0 0 1",
"2 2 2 2 2 2 2 2 2",
"3 2 2 2 3 2 2 2 3");

BINARYOP_TEST(add2,MatrixAddition,Matrix3x3,Matrix3x3,Matrix3x3,
"0 0 0 0 0 0 0 0 0",
"2 2 2 2 2 2 2 2 2",
"2 2 2 2 2 2 2 2 2");



TTEST(elementWiseSetConstantFixedDimensions, MatrixType){
MatrixType matrix;
elementWiseSetConstant(matrix, 0.0);
matrixForEach(matrix){
auto val = coefficient(matrix,i,j);
CHECK_EQUAL(0.0, val);
}
}


TTEST_INSTANCE(elementWiseSetConstantFixedDimensions, double);
TTEST_INSTANCE(elementWiseSetConstantFixedDimensions, float);
TTEST_INSTANCE(elementWiseSetConstantFixedDimensions, Vector2D);
TTEST_INSTANCE(elementWiseSetConstantFixedDimensions, Vector3D);
TTEST_INSTANCE(elementWiseSetConstantFixedDimensions, Matrix3x3);
TTEST_INSTANCE(elementWiseSetConstantFixedDimensions, double[4][3]);







}
*/