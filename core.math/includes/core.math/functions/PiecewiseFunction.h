#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <core.math/core.math.h>

#include <core.math/Interval.h>
#include <core.math/functions/Function.h>

NS_BEGIN(CORE_MATH_NAMESPACE)

template <typename TY, typename TX = double, typename TFunc = std::function<TY(const TX &)> >
class PiecewiseFunction : public Function < TY, TX > {
public:
  typedef TFunc piece_function_type;
  typedef Interval<TX> interval_type;
  struct Piece{
    Piece(){}
    
    interval_type interval;
    piece_function_type function;
  };

  typedef std::vector<Piece> piece_container;
  typedef typename piece_container::iterator iterator;


public:
  const piece_container & Pieces()const{  return _Pieces; }

  PiecewiseFunction(){

  }

  iterator begin(){ return std::begin(_Pieces); }
  iterator end(){ return std::end(_Pieces); }

  iterator findPiece(x_type x){
    auto res = std::find_if(std::begin(_Pieces), std::end(_Pieces), [&x](const Piece & piece){
      return piece.interval.isElementOf(x);
    });
    return res;
  }

  
  
  void addPiece(const Piece & piece){
    _Pieces.push_back(piece);
    
  }


  void add(piece_function_type func, interval_type interval){
    return;
    /*auto p = findPiece(xStart);
    if (p == end())return;
    Piece  newPiece;
    newPiece.interval.a = xStart;
    newPiece.interval.b = p->interval.b;
    newPiece.function = func;
    p->interval.b = xStart;
    addPiece(newPiece);
  */}

  interval_type getDefinitionInterval() const{
    interval_type interval;
    interval.setInvalid();
    
    for (auto & piece : Pieces()){
      if (piece.interval.a < interval.a)interval.a = piece.interval.a;
      if (piece.interval.b > interval.b)interval.b = piece.interval.b;
    }
    return interval;
  }
  y_type operator()(const x_type & x){
    y_type result;
    evaluate(result, x);
    return result;
  }
  inline bool evaluate(y_type & result, const x_type & x){
    auto piece = findPiece(x);
    if (piece == end())return false;
    //x_type deltaX = x-piece->first.a;
    return piece->function(x);
  }
private:
  piece_container _Pieces;
};

NS_END(CORE_MATH_NAMESPACE)
