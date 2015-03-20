template<typename C,typename A, typename B, typename OP>
class MatrixElementWiseBinary{
public:
  static inline void operation(C & c, const A &  a, const B & b){
    if(a.rows() != b.rows() ||a.cols()!=b.cols()){
      std::cerr<< __FUNCSIG__ << ": Dimensions mismatch" <<std::endl;
      return;
    }
    c.resize(a.rows(),a.cols(),false);
    for(int i=0; i < a.rows(); i++){
      for(int j=0; j < a.cols(); j++){
        OP::operation(c(i,j), a(i,j),b(i,j));
      }
    }
  }
};