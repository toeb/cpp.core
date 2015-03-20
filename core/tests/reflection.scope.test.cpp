#include<core.testing.h>
#include <core.reflection.h>


NS_USE(CORE_REFLECTION2_NAMESPACE);


UNITTEST(CreateScopeDeclaration){
  ScopeInfo info;
  auto & declaration = info.declare<NamespaceInfo>("::");
  ASSERT(info.declarations().size() == 1);
  ASSERT(info.declarations().at("::") == &declaration);
  ASSERT(declaration.scope() == info);

}

UNITTEST(DeclarationShouldOnlyBeCreatedOnce){
  ScopeInfo info;
  auto declaration = &info.declare<NamespaceInfo>("::");
  auto declaration2 = &info.declare<NamespaceInfo>("::");
  ASSERT(declaration == declaration2);
  ASSERT(*declaration == *declaration2);
}

UNITTEST(ScopeInfoShouldReturnUnknownIfDeclarationIsUnknown)
{
  ScopeInfo info;
  auto & res = info["unknowndecl"];
  ASSERT(res == unknown());
}
