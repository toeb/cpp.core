template<typename MatrixResult, typename MatrixSummandA, typename ScalarSummandB>
class MatrixAdditionConstant{
public:
  static inline void operation(MatrixResult & c, const MatrixSummandA & a, const ScalarSummandB & b){
    c.resize(a.rows(),a.cols(),false);
    for(int i=0; i < a.rows(); i++){
      for(int j=0; j < a.cols(); j++){
        c(i,j)=a(i,j)+b;
      }
    }
  }
};