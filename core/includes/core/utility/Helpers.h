
template<typename T>
T* make_pointer(const T & val){
  return new T(val);
}