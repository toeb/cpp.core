#include <core/reflection/namespace/NamespaceInfo.h>


#include <core/utility/StringTools.h>
#include <core/reflection/type/Type.h>
#include <iostream>
NS_USE(CORE_NAMESPACE);



template<typename TTarget, typename TOriginal>
std::set<TTarget> dynamic_set_cast(const std::set<TOriginal> & source){
  std::set<TTarget> result;
  std::for_each(std::begin(source), std::end(source), [&result](TOriginal orig){
    auto it = dynamic_cast<TTarget>(orig);
    if(it)   result.insert(it);
  });
  return result;
}

std::set<const NamespaceInfo *> NamespaceInfo::Namespaces()const{

  return dynamic_set_cast<const NamespaceInfo*>(ChildScopes());
}
std::set<const Type *> NamespaceInfo::Types()const{
  return dynamic_set_cast<const Type *>(ChildScopes());

}


NamespaceInfo::NamespaceInfo():ScopeInfo()
{

}

void NamespaceInfo::namespaceAdded(const NamespaceInfo * ns){
  std::cout << "adding namespace "<< ns->getName() << " to "<< this->getName()<<std::endl; 
}
void NamespaceInfo::namespaceRemoved(const NamespaceInfo * ns){

  std::cout << "removing namespace "<< ns->getName() << " from "<< this->getName()<<std::endl; 
}
const NamespaceInfo* NamespaceInfo::Global(){
  static std::unique_ptr<NamespaceInfo> ns(new NamespaceInfo());
  return ns.get();
}



std::string createName(const std::string & name, const NamespaceInfo * parent){
  std::stringstream stream;
  if(parent==0) parent = NamespaceInfo::Global();
  stream << parent->getFullyQualifiedName() << name << "::";
  return stream.str();
}



const NamespaceInfo * NamespaceInfo::getNamespace(const std::string & nameOrFullyQualified)const{
  auto transformed = stringtools::replace(nameOrFullyQualified,"::",".");
  if(stringtools::startsWith(transformed,"."))transformed=transformed.substr(1);
  if(stringtools::endsWith(transformed,"."))transformed = transformed.substr(0,transformed.size()-1);
  auto parts = stringtools::split(transformed,'.');
  if(parts.size()==0)return 0;
  for(auto it: Namespaces()){
    if(it->getName()==parts[0]){
      if(parts.size()==1)return it;
      return it->getNamespace(transformed.substr(parts[0].size()));
    }
  }
  return 0;
}


NamespaceInfo::~NamespaceInfo(){
/*  auto parent = const_cast<NamespaceInfo*>(getParentNamespace());
  if(!parent){
    parent->Namespaces().remove(this);
  }*/
}
const NamespaceInfo* NamespaceInfo::getParentNamespace()const{
  return dynamic_cast<const NamespaceInfo*>(getScope()); 
}



