#include <core/reflection/type/Type.h>
#include <core/reflection/member/property/PropertyInfo.h>
#include <core/reflection/member/method/MethodInfo.h>
#include <core/reflection/member/constructor/ConstructorInfo.h>
#include <core.utility.h>
#include <core/reflection/namespace/NamespaceInfo.h>
#include <sstream>
NS_USE(CORE_NAMESPACE);

auto Type::removeConst()const->const Type *{
  if(!getIsConst()){
    return this;
  }
  return getUnderlyingType();
}
auto Type::removeReference()const->const Type *{
  if(!getIsReference()){
    return this;
  }
  return getUnderlyingType();
}
auto Type::removePointer()const->const Type *{
  if(!getIsPointer()){
    return this;
  }
  return getUnderlyingType();
}



void Type::setRttiName(const std::string & name){
  _rttiTypeName = name;
}
void Type::setRttiHashCode(size_t hash_code){
  _rttiHashCode = hash_code;
}
const std::string & Type::getRttiName()const{ return _rttiTypeName; }
const size_t Type::getRttiHashCode()const{ return _rttiHashCode; }



Type::~Type(){

  //  const_cast<NamespaceInfo*>(getNamespace())->Types() /= this;
}


const NamespaceInfo * Type::getNamespace()const{
  return dynamic_cast<const NamespaceInfo*>(getScope());
}
bool Type::isValid() const{
  return Constructors().size()!=0;
}
Argument Type::callImplementation(const Callable::ArgumentList & args)const {
  std::vector<const Type*> types;
  for(auto arg : args){
    types.push_back(arg.type);
  }
  auto constructor = getConstructor(types);
  if(!constructor)return Argument();
  return constructor->callImplementation(args);
}
Argument Type::dereference(Argument & argument)const{
  throw std::exception();//("not implemented yet");
}
Type::Type():
  ScopeInfo(),
  _Id(_typeCounter++),
  _IsPointer(false),
  _IsReference(false),
  _IsVolatile(false),
  _IsConst(false),
  _UnderlyingType(0),
  _UnqualifiedType(this),
  _IsTemplated(false)  
{ 
  /* auto n = getName().find_first_of('<');
  auto tName = getName().substr(0,n);
  setTemplateName(tName);
  n=getFullyQualifiedName().find_first_of('<');
  tName = getFullyQualifiedName().substr(0,n);
  setFullyQualifiedTemplateName(tName);*/


}



bool Type::isDefaultConstructible()const{
  return getConstructor(std::vector<const Type*>())!=0;  
}



bool Type::isUnqualifiedType()const{return getUnqualifiedType()==this;}


Type::TypeId Type::_typeCounter=0;

NS_BEGIN(CORE_NAMESPACE)
  bool operator!=(const Type & a, const Type & b) {
    return !(a==b);
  }
  bool operator==(const Type & a, const Type & b){
    return a._Id==b._Id;
  }
  std::ostream & operator <<(std::ostream & out, const Type & type){
    out << "<Type name='"<< type.getName()<<"' id='"<< type.getId()<<"'/>";
    return out;
  }
  std::ostream & operator <<(std::ostream & out, const Type * type){
    if(type) out << *type;
    return out;
  }
NS_END(CORE_NAMESPACE)




const MemberInfo * Type::getMember(const std::string & name)const{
  auto member = Members().first([&name](const MemberInfo * member){return member->getName()==name;});
  return member;
}


const MethodInfo * Type::getMethod(const std::string & name)const{
  return Members()
    .subset<const MethodInfo*>()
    .first([&name](const MethodInfo* method)->bool{
      if(method->getPureName()==name||method->getName()==name||method->getFullName()==name)return true;
      // implicit arguments allows identification without arguments e.g. at(...)const, at(...) would identify the const method version
      auto parts = stringtools::split(name,"...");
      if(parts.size()==2){
        if(stringtools::startsWith(method->getName(),parts[0])&&stringtools::endsWith(method->getName(),parts[1])){
          return true;
        }
      };
      return false;
  });
}

const ConstructorInfo * Type::getConstructor(const std::vector<const Type*> & types)const{
  return Constructors().first([&types](const ConstructorInfo * info)->bool{
    if(types.size()!=info->Arguments().size())return false;
    for(size_t i=0; i < types.size(); i++){
      if(types[i]!=info->Arguments()[i]->getArgumentType().get())return false;
    }
    return true;
  });
}


const PropertyInfo * Type::getProperty(const std::string & name)const{
  auto member = getMember(name);
  if(!member)return 0;
  auto prop = dynamic_cast<const PropertyInfo*>(member);
  return prop;
}
bool Type::isSuperClassOf(const Type * other)const{
  if(!other)return false;  
  if(other == this)return true;
  for(size_t i=0; i < other->predecessors(); i++){
    auto current = other->predecessor(i);
    if(isSuperClassOf(current))return true;
  }
  return false;
}


bool Type::isSubClassOf(const Type * other)const{
  return other->isSuperClassOf(other);
}



Set<const PropertyInfo*> Type::Properties()const{  
  return Members().subset<const PropertyInfo*>();
}

Set<const MethodInfo*> Type::Methods()const{
  return Members().subset<const MethodInfo*>();
}

Set<const ConstructorInfo*> Type::Constructors()const{
  return Members().subset<const ConstructorInfo*>();
}

void Type::itemAdded(const MemberInfo * , Members){
}
void Type::itemRemoved(const MemberInfo * , Members){
}

void Type::onPredecessorAdded( Type* type){
  Members()|=type->Members();  
  _SuperClasses |=type;
  _RootClasses |=type->getRootClasses();
}
void Type::onPredecessorRemoved( Type* type){
  Members()/=type->Members();

  _SuperClasses /=type;
  _RootClasses /=type->getRootClasses();
}

void Type::onSuccessorAdded( Type * type){

}
void Type::onSuccessorRemoved( Type* type){

}
