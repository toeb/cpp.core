#pragma once
#include <core/core.h>
#include <map>
#include <memory>
NS_BEGIN(CORE_NAMESPACE)
  class ScopeInfo;
  class NamespaceInfo;
  class Type;


    namespace reflection{
      typedef std::shared_ptr<ScopeInfo> ScopePointer;
      typedef std::map<std::string,ScopePointer> ScopeRegistryType;
      ScopeRegistryType & registry();      
      ScopePointer scope(const std::string &  fullName);
      const std::shared_ptr<const ScopeInfo> findScope(const std::string & fullyQualifiedName);
      const std::shared_ptr<const NamespaceInfo> findNamespace(const std::string & fullyQualifiedName);
      const std::shared_ptr<const Type> findType(const std::string & fullyQualifiedName);
      const std::shared_ptr<const NamespaceInfo> Global();
    }
  
NS_END(CORE_NAMESPACE)
