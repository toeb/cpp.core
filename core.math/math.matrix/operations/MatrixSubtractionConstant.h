template<typename MatrixResult, typename Matrix, typename Scalar>
class MatrixSubtractionConstant{
public:
  static inline void operation(MatrixResult & c, const Matrix & a, const Scalar & b){
    c.resize(a.rows(),a.cols());
    for(int i=0; i < a.rows(); i++){
      for(int j=0; j < a.cols(); j++){
        c(i,j)=a(i,j)-b;
      }
    }
  }
};
