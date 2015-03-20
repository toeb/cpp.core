#include <core.h>

#include <iostream>
using namespace std;

NS_BEGIN(CORE_NAMESPACE)
  
    namespace utility{

      TEST(1, ParseLong){
        long l = parse<long>("-312");
        CHECK_EQUAL(-312l, l);
      }

      TEST(2, ParseLong){
        long l = parse<long>("3asd12");
        CHECK_EQUAL(3, l);
      }

      TEST(3, ParseLong){
        long l = parse<long>("asda");
        CHECK_EQUAL(0, l);
      }


      TEST(1, ParseDouble){
        double l = parse<double>("-312");
        DOUBLES_EQUAL(-312.0, l, 0.00001);
      }

      TEST(2, ParseDouble){
        double l = parse<double>("3asd12");
        DOUBLES_EQUAL(3.0, l, 0.00001);
      }

      TEST(3, ParseDouble){
        double l = parse<double>("asda");
        DOUBLES_EQUAL(0.0, l, 0.00001);
      }




      TEST(1, ParseULong){
        auto l = parse<unsigned long>("312");
        CHECK_EQUAL(312l, l);
      }

      TEST(2, ParseULong){
        auto l = parse<unsigned long>("3asd12");
        CHECK_EQUAL(3, l);
      }

      TEST(3, ParseULong){
        auto l = parse<unsigned long>("asda");
        CHECK_EQUAL(0, l);
      }

      TEST(4, ParseULong){
        auto l = parse<unsigned long>("-12");
        //CHECK_EQUAL(0,l);
        // this does not work yet
      }
    
  }
NS_END(CORE_NAMESPACE)
