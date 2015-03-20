#include <core.testing.h>
int main(int argc, char** argv){
  return NS(CORE_NAMESPACE)::UnitTestRunner::runCommandLine(argc,argv);
}