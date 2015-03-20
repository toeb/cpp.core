#pragma once
#include <core/core.h>

#include <core/serialization/serialization_config.h>

 NS_BEGIN(CORE_SERIALIZATION_NAMESPACE)

/// serializes a value into the ostream out
template<int format = DefaultFormat, typename T = void>
void serialize(typename std::ostream & out, const T & value);

// serializes a value into the specified string
template<int format = DefaultFormat, typename T = void>
std::string serialize(const T & value);

/// serializes any value with into a string of specified format
//template<int format = DefaultFormat>
//std::string serialize(any value);
NS_END(CORE_SERIALIZATION_NAMESPACE)


#include <core/serialization/utility.implementation.h>

/// macros for specializing serializers


/// specializes the typed_serializer template for a specific format and type allowing template arguments
/// declaration only
/// usage:
/// (only in namespace NS(CORE_SERIALIZATION_NAMESPACE)::core::serialization)
/// template<typename T> custom_template_serializer_declaration(3,std::vector<T>);
#define custom_template_serializer_declaration(FORMAT,...)\
  struct typed_serializer<__VA_ARGS__, FORMAT>: public typed_serializer_base<__VA_ARGS__, FORMAT,typed_serializer<__VA_ARGS__, FORMAT>>{\
  typedef __VA_ARGS__ value_type;\
  static void serialize(serialization_context & context , const value_type & value);\
};

/// specializes the typed_serializer template for a non template type
/// (declaration only)
/// usage: (only in namespace NS(CORE_SERIALIZATION_NAMESPACE)::core::serialization
/// custom_serializer_declaration(4,int);
#define custom_serializer_declaration(FORMAT, ...)\
template<> custom_template_serializer_declaration(FORMAT,__VA_ARGS__)

/// implementation for the declare custom_serializer, custom_template_serializer
/// (only in namespace NS(CORE_SERIALIZATION_NAMESPACE)::core::serialization)
/// immediately follow by { ... } in chich you can use the variables context : serialization_context &  and value (which is the specified tyep)
#define custom_serializer_definition(FORMAT,...) void typed_serializer<__VA_ARGS__,FORMAT>::serialize(serialization_context & context, const value_type & value)

/// declaration and implementation of the the specialization of typed_serialzier
/// only usable in NS(CORE_SERIALIZATION_NAMESPACE)::core::serialization
/// use the serialization_context context and value to serialize
/// usage:
/// custom_serializer(4,int){ context.stream << value; }
#define custom_serializer(FORMAT,...) custom_serializer_declaration(FORMAT,__VA_ARGS__) custom_serializer_definition(FORMAT,__VA_ARGS__)

/// declaration and implementation for defualt serializer
/// usage
/// default_serialzier(int){ context.stream << "hello"<<value;}
#define default_serializer(...) custom_serializer(DefaultFormat,__VA_ARGS__)


