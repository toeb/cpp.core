#include <core.testing.h>

#include <core.math/statistics/all.h>
template<typename T>
class ringbuffer{
public:
  ringbuffer(size_t size):_size(0){
    resize(size);
  }
  void resize(size_t new_size){
    auto old_size = _size;

  }
private:
  size_t _size;
  std::vector<T> _buffer;
};
UNITTEST(RingbufferTest){

  ringbuffer<double> uut(3);





}

UNITTEST(AverageTest){
  NS_USE(CORE_MATH_NAMESPACE, statistics);

  Average uut(3);
  uut.addSample(3);
  uut.addSample(4);
  uut.addSample(5);
  uut.addSample(6);
  auto res = uut.calculate();
  DOUBLES_EQUAL(5, res, 0.0001);
}