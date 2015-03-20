#include <exception>

NS_BEGIN(CORE_NAMESPACE)
class not_implemented_exception: public std::exception{
private:
    const char * _message;
public:
    not_implemented_exception(const char * message):_message(message){}
    not_implemented_exception():_message("not implemented"){}

    virtual const char* what() const noexcept override{  return _message;  }

    virtual ~not_implemented_exception() noexcept{}
};
NS_END(CORE_NAMESPACE)