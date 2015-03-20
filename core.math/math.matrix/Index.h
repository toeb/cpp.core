#pragma once

#include <config.h>
namespace nspace{
  // recursive data structure for indexing
  // gives access to row major and (later on column major) indexing for n dimensions
  // initialization: Idx<4> idx = {4,2,3,1}
  // note: in visual studio a maximum initializer depth of 5 is possible... that kinda sux
  template<size_t n>
  struct Idx{
    union{
      struct{
        size_t first;
        Idx<n-1> rest;
      };
      size_t e[n];
    };
    inline size_t operator[](size_t dir)const{
      return e[dir];
    }
    inline size_t rowMajor(const Idx<n> & dimensions)const{
      return first*dimensions.rest.permutations()+rest.rowMajor(dimensions.rest);
    }
    inline Idx<n> inverseRowMajor(const size_t & idx)const{
      Idx<n> result;
      result.first = idx/rest.permutations();
      result.rest = rest.inverseRowMajor(idx-result.first*rest.permutations());
      return result;
    }

    inline const size_t permutations()const{
      return first*rest.permutations();
    }

    friend Idx<n> operator-(const Idx<n> & a, const Idx<n> & b){
      Idx<n> result;
      for(size_t i=0; i < n; i++){
        result[i] = a[i]-b[i];
      }
      return result;
    }
    friend Idx<n> operator+(const Idx<n> & a, const Idx<n> & b){
      Idx<n> result;
      for(size_t i=0; i < n; i++){
        result[i] = a[i]+b[i];
      }
      return result;
    }

    friend std::ostream & operator<<(std::ostream & out, const Idx<n> & idx){
      out << "{"<<idx.first;
      for(int i=1; i < n; i++){
        out << ", "<<idx[i];
      }
      out << "}";
      return out;
    }
  };
  template<>
  struct Idx<0>{
    static const size_t first=1;
    inline Idx<0> inverseRowMajor(const size_t & idx)const{return Idx<0>();}
    inline size_t permutations()const{
      return 1;
    }
    inline size_t rowMajor(const Idx<0> & dimensions)const{
      return 0;
    }

    friend std::ostream & operator<<(std::ostream & out, const Idx<0> & idx){
      out<<"{}";
      return out;
    }
  };
}