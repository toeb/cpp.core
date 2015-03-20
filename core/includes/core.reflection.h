#pragma once

#include <core/reflection/namespace/NamespaceInfo.h>

#include <core/reflection/attribute/Attribute.h>
#include <core/reflection/attribute/AttributeTarget.h>
#include <core/reflection/type/Type.h>
#include <core/reflection/type/TypeInfo.h>



#include <core/reflection/member/MemberInfo.h>
#include <core/reflection/member/property/PropertyInfo.h>
#include <core/reflection/member/method/MethodInfo.h>
#include <core/reflection/member/method/TypedMethodInfo.h>

// implementations depending on Member classes

#include <core/reflection/type/TypeInfo.implementation.template.h>


// specializations
#include <core/reflection/type/specialization/fundementalTypes.h>
#include <core/reflection/type/specialization/qualifierTypes.h>
#include <core/reflection/type/specialization/stdTypes.h>


// implementations depending on TypeInfo
#include <core/reflection/type/Argument.implementation.template.h>



#include <core/reflection/member/property/TypedPropertyInfo.h>
#include <core/reflection/member/property/PropertySetInfo.h>
#include <core/reflection/member/property/TypedPropertySetInfo.h>

#include <core/reflection/member/constructor/ConstructorInfo.h>
#include <core/reflection/member/constructor/TypedConstructorInfo.h>


#include <core/reflection/attribute/Attribute.h>


#include <core/reflection/adapter/MethodAdapter.h>
#include <core/reflection/adapter/MemberAdapter.h>
#include <core/reflection/adapter/PropertyAdapter.h>
#include <core/reflection/callable/CallableFunctor.h>


//#include <core/reflection/Action.h>
//#include <core/reflection/DelegateAction.h>
#include <core/reflection/value/DelegateValue.h>
#include <core/reflection/value/IModifiableValue.h>
#include <core/reflection/value/IReadableValue.h>
#include <core/reflection/value/DelegateValue.h>

//#include <core/reflection/ITypedModifiableValue.h>
//#include <core/reflection/ITypedReadableValue.h>
//#include <core/reflection/ReferenceValue.h>
//#include <core/reflection/ITypedSerializableValue.h>

//#include <core.serialization/Serialization.h>

#include <core/reflection/preprocessor/properties.h>

#include <core/reflection/Reflection.h>


#include <core/reflection/RIncludes.h>