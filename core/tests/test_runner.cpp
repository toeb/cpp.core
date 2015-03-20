#include <core.h>

#include <core.dynamic.h>
int main(int argc, char ** argv){
  return NS(CORE_NAMESPACE)::UnitTestRunner::runCommandLine(argc, argv);
  
}