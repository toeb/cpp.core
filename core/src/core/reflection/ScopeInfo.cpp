#include <core/reflection/ScopeInfo.h>

#include <core/reflection/type/Type.h>
#include <core/reflection/namespace/NamespaceInfo.h>
#include <string>
#include <core/utility/StringTools.h>
NS_USE(CORE_NAMESPACE);
using namespace std;

template<typename T> auto make_mutable(T t)->typename std::remove_const<T>::type{
  return const_cast<typename std::remove_const<T>::type>(t);
}

auto ScopeInfo::ChildScopes()const->const std::set<const ScopeInfo*> & {return _ChildScopes;}
bool ScopeInfo:: addChildScope(const ScopeInfo*  node){
  //try to insert node int set
  if(!_ChildScopes.insert(node).second)return false;
  onChildScopeAdded(node);
  return true;
}
bool ScopeInfo::removeChildScope( const ScopeInfo* node){
  // search for node if found erase it from set
  auto it = _ChildScopes.find(node);
  if(it== std::end(_ChildScopes))return false;
  _ChildScopes.erase(it);
  onChildScopeRemoved(node);
  return true;
}
/*
const ScopeInfo* ScopeInfo::Global(){
  return NamespaceInfo::Global();
}
*/



std::string ScopeInfo::normalizeName(const std::string & nameOrFullyQualifiedName){
  using namespace stringtools;
  // returns the last part of :: separated names.  also works if last element is ::
  auto parts = split(nameOrFullyQualifiedName,"::");
  std::string n = parts[parts.size()-1];
  if(n==""){
    if(parts.size()>1)n = parts[parts.size()-2];
  }
  return n;
}
std::string ScopeInfo::normalizeFullyQualifiedName(const std::string & nameOrFullyQualifiedName){
  // ensures that nameOrFullyQualifiedName has the correcto format (starting with :: and not ending with ::
  using namespace stringtools;
  std::string name = nameOrFullyQualifiedName;
  if(!startsWith(name,"::"))name = DS_INLINE_STRING("::"<<name);
  if(endsWith(name,"::"))name =name.substr(0,name.size()-2);
  return name;
}

ScopeInfo::~ScopeInfo(){
  setScope(0);
  // create a copy of child scopes (because setScope (0) causes the scope to be removed which destroys the iterators being used)
  std::vector<ScopeInfo*> scopes;
  for_each(begin(ChildScopes()),end(ChildScopes()),
    [&scopes](const ScopeInfo * it){
    auto child = const_cast<ScopeInfo*>(it);
    scopes.push_back(child);
  });

  for_each(begin(scopes),end(scopes),[&scopes](ScopeInfo* scope){
    scope->setScope(0);
  });

}


const ScopeInfo * ScopeInfo::findChild(const std::string & name)const{
  for(auto it : ChildScopes()){
    if(it->getName()==name)return it;
  }
  return 0;
}

std::vector<std::shared_ptr<ScopeInfo>> createdScopes;
/*
const ScopeInfo* ScopeInfo::requireScope(const std::string & n){
  // searches for scope.  if found it is returned else scopes are created as namespaces
  std::string name = n;
  auto scope = findScope(name);
  if(scope)return scope;

  using namespace stringtools;
  const NamespaceInfo * ns =0;
  if(startsWith(name,"::")){
    //global else default
    ns = NamespaceInfo::Global();
    name = name.substr(2);
  }
  
  if(name==""||name=="::"){
    //global else default
    ns = NamespaceInfo::Global();
    return ns;
  }


  auto parts = split(name,"::");
  size_t i= 0;
  const NamespaceInfo * found = ns;
  while(true){
    if(i >= parts.size())return 0;
    found = ns;
    if(!ns)break;
    auto scope =  ns->findChild(parts[i]);
    if(!scope)break;
    // if scope is not a namespace it could be a class or a method.  no automatic scope creation can be performed then
    if(!(ns=dynamic_cast<const NamespaceInfo*>(scope)))return 0;
    i++;
  }
  ns = found;
  
  for(;i<parts.size();i++){
    auto part = parts[i];
    auto scope = std::shared_ptr<NamespaceInfo>(new NamespaceInfo(part));
    scope->setScope(ns);
    // store pointer so scope is not deleted after exiting function
    createdScopes.push_back(scope);
    ns = scope.get();

  }
  return ns;
}*/


std::string ScopeInfo::parentScopeName(const std::string & fullyQualifiedName){
  auto last = fullyQualifiedName.find_last_of("::");
  if(last==fullyQualifiedName.size())return 0;
  std::string n = fullyQualifiedName.substr(0,last-1);
  return n;
}
/*
const ScopeInfo* ScopeInfo::findParentScope(const std::string & name){
  auto last = name.find_last_of("::");
  if(last==name.size())return 0;
  std::string n = name.substr(0,last-1);
  return findScope(n);
}
const ScopeInfo* ScopeInfo::findScope(const std::string & n){
  std::string name = n;
  using namespace stringtools;

  const ScopeInfo * ns = 0;
  if(startsWith(name,"::")){
    ns = Global();
    name = name.substr(2);
  }
  auto parts = split(name,"::");
  size_t i=0;
  while(ns && i < parts.size()){
    ns = ns->findChild(parts[i]);
    i++;
  }
  return ns;
}
*/

ScopeInfo::ScopeInfo():_Name(""),_Scope(0){
}
auto ScopeInfo::before_set(Scope){
  auto newScope = const_cast<ScopeInfo*>(*newvalue);
  auto currentScope = const_cast<ScopeInfo*>(_Scope);
  if(newScope==currentScope)return BeforeSetAction::Cancel;
  if(currentScope)currentScope->removeChildScope(this);
  return BeforeSetAction::Accept;
}

std::string ScopeInfo::formatName(const std::string & separator, const std::string & prefix, const std::string & postfix)const{
  auto scope = getScope();
  std::stringstream stream;
  if(scope==0)stream<<prefix;
  else stream<< scope->formatName(separator,prefix,"")<<separator;
  stream<<getName()<<postfix;
  return stream.str();
}

std::string ScopeInfo::formatScopeName(const std::string & separator, const std::string & prefix, const std::string & postfix)const{
  auto scope = getScope();
  if(!scope)return "";
  return scope->formatName(separator,prefix,postfix);
}


auto ScopeInfo::after_set(Scope){
  auto scope =const_cast<ScopeInfo*>(getScope());
  if(!scope){
    return;
  }  
  scope->addChildScope(this);;
  onScopeSet(scope);
}

void ScopeInfo::onScopeSet(const ScopeInfo * parent){

}

void ScopeInfo::onChildScopeAdded(const ScopeInfo *  child){
 // std::cout << "added "<< child->getName()<< " to " << getFullyQualifiedName() << std::endl;

}
void ScopeInfo::onChildScopeRemoved(const ScopeInfo * child){

 // std::cout << "removed "<< child->getName()<< " from " << getFullyQualifiedName()<<std::endl;
}