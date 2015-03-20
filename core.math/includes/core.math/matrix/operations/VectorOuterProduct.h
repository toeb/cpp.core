/**
 * Copyright (C) 2013 Tobias P. Becker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the  rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More information at: https://dslib.assembla.com/
 *
 */
#pragma once
 
#include <core.math/core.math.h>

NS_BEGIN(CORE_MATH_NAMESPACE)
  template<typename Result, typename VecA, typename VecB>
  class VectorOuterProduct {
public:
    static inline void operation(Result &  result, const VecA & a, const VecB & b){
      if(result.rows()!=a.size()) {
        //ERROR("incompatible sizes");
        return;
      }
      if(result.cols()!=b.size()) {
        //ERROR("incompatible sizes");
        return;
      }

      for(int i=0; i < a.size(); i++) {
        for(int j=0; j < b.size(); i++) {
          result(i,j)=a(i)*b(j);
        }
      }
    }
  };
NS_END(CORE_MATH_NAMESPACE)
