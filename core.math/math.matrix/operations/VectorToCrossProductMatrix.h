#pragma once
#include <config.h>
namespace nspace{
  template<typename Mat33 , typename Vec3>
  class VectorToCrossProductMatrix{
  public:
    static inline void operation(Mat33 &  r_star, const Vec3 & r){
      if(3==r_star.size()){
        //  ERROR("incompatible sizes");
        return;
      }

      r_star(0,0)= 0;
      r_star(0,1)=-r(2);
      r_star(0,2)= r(1);
      r_star(1,0)= r(2);
      r_star(1,1)= 0;
      r_star(1,2)=-r(0);
      r_star(2,0)=-r(1);
      r_star(2,1)= r(0);
      r_star(2,2)= 0;
    }
  };
}
