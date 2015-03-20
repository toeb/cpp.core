#include <core/Time.h>

#ifdef WIN32
#include <Windows.h>
NS_BEGIN(CORE_NAMESPACE)
  static LARGE_INTEGER frequency;
  class InitTime{
  public:
    InitTime(){
      QueryPerformanceFrequency(&frequency);
    }
  };
  InitTime __initTime;

  NS(CORE_NAMESPACE)::Time systemTime(){
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    if(!frequency.QuadPart)return 0.0;
    return time.QuadPart /(double)frequency.QuadPart;
  }
NS_END(CORE_NAMESPACE)

#else
#include <sys/time.h>
NS_BEGIN(CORE_NAMESPACE)
  Time systemTime(){
    timeval t;
    gettimeofday(&t,0);
    Time result =  t.tv_sec+t.tv_usec /1000000.0;
    return result;
  }
NS_END(CORE_NAMESPACE)

#endif
NS_BEGIN(CORE_NAMESPACE)
  const NS(CORE_NAMESPACE)::Time __startUpTime=NS(CORE_NAMESPACE)::systemTime();

  NS(CORE_NAMESPACE)::Time startupTime(){
    return __startUpTime;
  }

  NS(CORE_NAMESPACE)::Time applicationTime(){
    Time result = NS(CORE_NAMESPACE)::systemTime()-__startUpTime;

    return result;
  }
NS_END(CORE_NAMESPACE)
