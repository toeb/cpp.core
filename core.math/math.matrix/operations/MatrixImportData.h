template<typename T, typename TargetType>
class MatrixAssignData{
public:
  static inline void operation(TargetType  & target, const T * source){
    for(uint i=0; i < target.size(); i++){
      target(i) = source[i];
    }
  }
};
