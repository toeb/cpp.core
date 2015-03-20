#include <core/NamedObject.h>
#include <core/reflection/type/TypeInfo.h>
NS_USE(CORE_NAMESPACE);
using namespace std;

//reflect_type_default_definition(NS(CORE_NAMESPACE)::NamedObject);

NamedObject::~NamedObject(){
  if(_name)delete _name;
  _name=0;
}

const string & NamedObject::DefaultName(){
  static auto n =string("<DEFAULTOBJECTNAME>");
  return n;
}
NamedObject::NamedObject(const string & name):_name(new string(name)){}
NamedObject::NamedObject():_name(0){}
const string & NamedObject::name()const{
  if(!_name)return NamedObject::DefaultName();
  return *_name;
}
void NamedObject::setName(const std::string & name){
  if(!_name)_name = new string;
  _name->assign(name);
}
void NamedObject::setName(const std::string * name){
  if(!name){
    _name=0;
    return;
  }
  setName(*name);
}
bool NamedObject::hasName()const{
  return _name!=0;
}

bool NamedObject::operator == (const std::string & str)const{
  return name()==str;
}
// equalitiy operator. returns true if this objects name equals the c string
bool NamedObject::operator==(const char * str)const{
  return *this==std::string(str);
}
NS_BEGIN(CORE_NAMESPACE)
  // equality operator compares a NamedObject's name to a std::string and returns true iff they are equal
  bool operator==(const NamedObject * obj, const std::string & name){
    return *obj==name;
  }

  const std::string & name(const Object * object){
    static std::string nullString="null-object";
    static std::string notNamed="unnamed-object";
    if(!object)return nullString;
    const NamedObject* no = dynamic_cast<const NamedObject*>(object);
    if(!no)return notNamed;    
    return no->name();
  }

  bool hasObjectName(const Object * object){
    if(!isObjectNameable(object))return false;
    const NamedObject* no = dynamic_cast<const NamedObject*>(object);
    return no->hasName();
  }

  bool setObjectName(Object * object, const std::string &name){
    if(!isObjectNameable(object))return false;
    auto no = dynamic_cast<NamedObject*>(object);
    no->setName(name);
    return true;
  }

  bool isObjectNameable(const Object * object){
    const NamedObject* no = dynamic_cast<const NamedObject*>(object);
    return no !=0;
  }
NS_END(CORE_NAMESPACE)
