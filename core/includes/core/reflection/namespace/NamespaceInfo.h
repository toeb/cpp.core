#pragma once
#include <core/core.h>

#include <core/container/Set.h>
#include <core.property.h>

#include <memory>
#include <sstream>
#include <core/reflection/ScopeInfo.h>
NS_BEGIN(CORE_NAMESPACE)


  // forward declaration for type
  class Type;
  class NamespaceInfo : public ScopeInfo{
  public:

    virtual ~NamespaceInfo();
    // returns the global (::) namespace
    static const NamespaceInfo * Global();
    std::set<const NamespaceInfo *> Namespaces()const;
    std::set<const Type *> Types()const;
    const NamespaceInfo * getNamespace(const std::string & name)const;
    const NamespaceInfo * getParentNamespace()const;
    NamespaceInfo();
  protected:
    friend class ScopeInfo;
  private:
    void namespaceAdded(const NamespaceInfo * ns);
    void namespaceRemoved(const NamespaceInfo * ns);

  };
NS_END(CORE_NAMESPACE)
