#pragma once
#include <math/Interval.h>
#include <math.functions/Function.h>
namespace nspace{
  template <typename TY>
  class PiecewiseFunction : public Function<TY,Real>{
    typedef std::pair<Interval,Function<TY,Real>*> Piece;
  private:
    Set<Piece*> _Pieces;

  public:
    Set<Piece*> & Pieces(){return _Pieces;}
    const Set<Piece*> & Pieces()const{return _Pieces;}
    PiecewiseFunction(){
      Piece * p=new Piece();
      p->first=Interval();
      p->second=0;
      Pieces().add(p);
    }
    Piece * PiecePair(Real x){
      auto func = Pieces().first([x](Piece * pair){
        return pair->first.a<=x && pair->first.b>x;
      });
      return func;
    }
    Function<TY,Real>* PieceFunction(Real x){
      auto p = PiecePair(x);
      return p->second;
    }

    void add(Real xStart, Function<TY,Real>* func){
      auto p = PiecePair(xStart);
      if(!p)return;
      Piece * newPiece = new Piece;
      newPiece->first.a=xStart;
      newPiece->first.b=p->first.b;
      newPiece->second = func;
      p->first.b=xStart;
      Pieces()|=newPiece;
      //newPiece->first.b=
    }

    Interval getDefinitionInterval() const{
      Interval interval(0,0);
      for(int i=0; i < Pieces(); i++){
        const Piece * piece = Pieces().at(i);
        if(piece->first.a < interval.a)interval.a = piece->first.a;
        if(piece->first.b > interval.b)interval.b = piece->first.b;
      }
      return interval;
    }

    inline bool evaluate(TY & result,  const Real & x){
      auto piece =PiecePair(x);
      if(!piece->second)return false;
      //Real deltaX = x-piece->first.a;
      return piece->second->evaluate(result,x);
    }
  };
}
