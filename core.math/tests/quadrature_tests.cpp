#include <core.testing.h>


#include <core.math/integration/all.h>
#include <core.math/matrix.dslib/all.h>

typedef core::math::matrix::dslib::DynamicMatrix<double> MatrixNxM;
typedef  core::math::matrix::dslib::StaticMatrix<double, 2, 2> mat33;
typedef  core::math::matrix::dslib::StaticMatrix<double, 3, 1> vec3;


TEST(1, time_step_type){
  TEST_DESCRIPTION(gets the second type of a integrable function which is the time step type);

  auto f = [](double x, std::string b){};
  NS_USE(CORE_MATH_NAMESPACE, integration);
  //CHECK_TYPES(step_size_type<decltype(f)>::type,std::string);  
  CHECK_TYPES(integrable_traits<decltype(f)>::step_size_type, std::string)
}

TEST(2, time_step_type){
  setTestDescription("gets the timestep type of a integrable function - if the function has only one argument it defaults to coefficient type of function's return value");
  auto f = [](double x){return x; };
  NS_USE(CORE_MATH_NAMESPACE, integration);

  CHECK_TYPES(integrable_traits<decltype(f)>::step_size_type, double);
}

TEST(1, time_type){
  setTestDescription("get the time type of an integrable function (argument 3)");
  auto f = [](double x, double h, std::string t){};
  NS_USE(CORE_MATH_NAMESPACE, integration);
  CHECK_TYPES(integrable_traits<decltype(f)>::time_type, std::string);

}

TEST(2, time_type){
  setTestDescription("get the time type of an integrable function (argument 3 or step_size_type)");
  auto f = [](double x, std::string h){};
  NS_USE(CORE_MATH_NAMESPACE, integration);
  CHECK_TYPES(integrable_traits<decltype(f)>::time_type, std::string);

}

TEST(1, IStepper){
  NS_USE(CORE_MATH_NAMESPACE, integration);
  setTestDescription("checks if IStepper correctly increments step count and call virtual doStep method");
  struct TestIStepper : public IStepper{
    std::string called;
    void doStep(){
      called = "was called";
    }
  }uut;
  IStepper & stepper = uut;
  CHECK_EQUAL(0, stepper.i());
  stepper.step();
  CHECK_EQUAL(1, stepper.i());
  CHECK(uut.called == "was called");

}



template<typename F>
struct TestStepper
  :public NS(CORE_MATH_NAMESPACE, integration)::Stepper < F > {
  TestStepper(F f) :Stepper<F>(f){}
  void doStep(){
  }
};



TEST(0, Stepper){
  setTestDescription("Checks if Stepper is initialized correctly");
  auto f = [](double x, double h, double t, int step){return x; };
  TestStepper<decltype(f)> uut(f);

  CHECK_EQUAL(0.0, uut.x());
  CHECK_EQUAL(0.0, uut.x0());
  CHECK_EQUAL(0.0, uut.t0());
  CHECK_EQUAL(0.0, uut.t());
  CHECK_EQUAL(0.02, uut.h0());
  CHECK_EQUAL(0.02, uut.h());

}
TEST(1, Stepper){
  setTestDescription("Checks if Stepper correctly advances time");
  auto f = [](double x, double h, double t, int step){return x; };
  TestStepper<decltype(f)> uut(f);
  uut.step();
  CHECK_EQUAL(0.0, uut.x0());
  CHECK_EQUAL(0.0, uut.x());
  CHECK_EQUAL(0.02, uut.t());
  CHECK_EQUAL(0.0, uut.t0());
}



TTEST(StepperFunctionCall, StateType){
  NS_USE(CORE_MATH_NAMESPACE, integration);
  NS_USE(CORE_MATH_NAMESPACE);
  auto f = [](StateType x){return x; };
  typedef integrable_traits<decltype(f)> traits;
  typename traits::step_size_type h;
  typename traits::time_type t;
  typename traits::state_type x;

  elementWiseSetConstant(h, 0.01);
  elementWiseSetConstant(t, 0.0);
  elementWiseSetConstant(x, 1.5);
  TestStepper<decltype(f)> uut(f);
  auto result = uut.f(x, h, t);
  //CHECK_TYPES(typename decltype(result), typename std::decay<StateType>::type);
  CHECK_EQUAL(x, result);
}

TTEST_INSTANCE(StepperFunctionCall, double);
TTEST_INSTANCE(StepperFunctionCall, float);
TTEST_INSTANCE(StepperFunctionCall, int);
TTEST_INSTANCE(StepperFunctionCall, vec3);
TTEST_INSTANCE(StepperFunctionCall, mat33);
TTEST_INSTANCE(StepperFunctionCall, double[4]);
TTEST_INSTANCE(StepperFunctionCall, float[4]);

TEST(1, ExplicitEuler){
  NS_USE(CORE_MATH_NAMESPACE, integration);

  auto f = [](double x, double h, double t, int i)->double{return t; };

  ExplicitEuler<decltype(f)> uut(f);
  uut.h() = 0.001;
  uut.stepUntil(1.0);

  logInfo("error: " << abs(uut.x() - 0.5));
  DOUBLES_EQUAL(0.5, uut.x(), 0.001);
}

UNITTEST(DelgateStepperExplicitEuler){
  NS_USE(CORE_MATH_NAMESPACE, integration);
  auto uut = stepper([](double x, double h, double t){return t; }, [](std::function<double(double, double, double)> f, double x, double h, double t, int i){
    return x + h*f(x, h, t);
  });
  uut.h() = 0.001;
  uut.stepUntil(1.0);

  logInfo("error: " << abs(uut.x() - 0.5));
  DOUBLES_EQUAL(0.5, uut.x(), 0.001);
}


PTEST(PerformanceExplicitEuler){
  NS_USE(CORE_MATH_NAMESPACE, integration);
  static auto f = [](double x, double h, double t, int i){return t; };
  static auto uut = ExplicitEuler<decltype(f)>(f);
  static auto temp = []()->bool{uut.h() = 0.001;  return true; }();
  uut();
}

PTEST(PerformanceExplicitEulerManual){
  static auto f = [](double x, double h, double t, int i)->double{return t; };
  static double x = 0.0;
  static int i = 0;
  static double t = 0;
  static double h = 0.001;

  t = t + h;
  i++;
  x = x + f(x, h, t, i)*h;

}

TEST(2, ExplicitEuler){
  NS_USE(CORE_MATH_NAMESPACE, integration);
  NS_USE(CORE_MATH_NAMESPACE);

  auto f = [](double x, double h, double t, int i)->double{return scalar::sine(t); };
  ExplicitEuler<decltype(f)> uut(f);
  uut.h() = 0.001;
  uut.stepUntil(scalar::pi<double>());

  auto analyticalResult = 2.0; // integral from t=0 to Pi over sin(t) = -cos(Pi)+cos(0) = 1+1=2

  logInfo("error: " << abs(uut.x() - analyticalResult));
  DOUBLES_EQUAL(analyticalResult, uut.x(), 0.001);
}

TEST(1, ImplicitEuler){
  NS_USE(CORE_MATH_NAMESPACE, integration);
  auto f = [](double x, double h, double t, int i)->double{return t; };
  ImplicitEuler<decltype(f)> uut(f);
  uut.h() = 0.001;
  uut.stepUntil(1.0);

  logInfo("error: " << abs(uut.x() - 0.5));
  DOUBLES_EQUAL(0.5, uut.x(), 0.001);
}
PTEST(PerformanceImplicitEuler){
  NS_USE(CORE_MATH_NAMESPACE, integration);
  static auto f = [](double x, double h, double t, int i)->double{return t; };
  static auto uut = ImplicitEuler<decltype(f)>(f);
  static auto temp = []()->bool{uut.h() = 0.001;  return true; }();

  uut();
}
TEST(2, ImplicitEuler){
  NS_USE(CORE_MATH_NAMESPACE, integration);
  NS_USE(CORE_MATH_NAMESPACE);
  auto f = [](double x, double h, double t, int i)->double{return scalar::sine(t); };
  ImplicitEuler<decltype(f)> uut(f);
  uut.h() = 0.001;
  uut.stepUntil(scalar::pi<double>());

  auto analyticalResult = 2.0; // integral from t=0 to Pi over sin(t) = -cos(Pi)+cos(0) = 1+1=2

  logInfo("error: " << abs(uut.x() - analyticalResult));
  DOUBLES_EQUAL(analyticalResult, uut.x(), 0.001);
}

TEST(1, RungeKutta2){
  NS_USE(CORE_MATH_NAMESPACE, integration);
  auto f = [](double x, double h, double t, int i)->double{return t; };
  RungeKutta2<decltype(f)> uut(f);
  uut.h() = 0.001;
  uut.stepUntil(1.0);

  logInfo("error: " << abs(uut.x() - 0.5));
  DOUBLES_EQUAL(0.5, uut.x(), 0.001);
}




TEST(2, RungeKutta2){
  NS_USE(CORE_MATH_NAMESPACE, integration);
  NS_USE(CORE_MATH_NAMESPACE);
  auto f = [](double x, double h, double t, int i)->double{return scalar::sine(t); };
  RungeKutta2<decltype(f)> uut(f);
  uut.h() = 0.001;
  uut.stepUntil(scalar::pi<double>());

  auto analyticalResult = 2.0; // integral from t=0 to Pi over sin(t) = -cos(Pi)+cos(0) = 1+1=2

  logInfo("error: " << abs(uut.x() - analyticalResult));
  DOUBLES_EQUAL(analyticalResult, uut.x(), 0.001);
}

TEST(1, RungeKutta4){
  NS_USE(CORE_MATH_NAMESPACE, integration);
  auto f=[](double x, double h, double t, int i)->double{return t;};
  RungeKutta4<decltype(f)> uut(f);
  uut.h()=0.001;
  uut.stepUntil(1.0);

  logInfo("error: "<<abs(uut.x()-0.5));
  DOUBLES_EQUAL(0.5,uut.x(),0.001);
}



TEST(2, RungeKutta4){
  NS_USE(CORE_MATH_NAMESPACE, integration);
  NS_USE(CORE_MATH_NAMESPACE);
  auto f=[](double x, double h, double t, int i)->double{return scalar::sine(t);};
  RungeKutta4<decltype(f)> uut(f);
  uut.h()=0.001;
  uut.stepUntil(scalar::pi<double>());

  auto analyticalResult = 2.0; // integral from t=0 to Pi over sin(t) = -cos(Pi)+cos(0) = 1+1=2

  logInfo("error: "<< abs(uut.x()-analyticalResult));
  DOUBLES_EQUAL(analyticalResult,uut.x(), 0.001);
}
