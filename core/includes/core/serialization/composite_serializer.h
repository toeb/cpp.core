#pragma once
#include <core/core.h>

#include <map>
#include <core/serialization/serialization_config.h>

#include <core/serialization/serializer.h>
#include <core/serialization/typed_serializer.h>
NS_BEGIN(CORE_SERIALIZATION_NAMESPACE)

      /// a serializer which delegates the serialziation of a value to 
      /// its child serializers depending on the type of the value
      struct composite_serializer : public serializer{
        std::map<type_provider::type_id, serializer*> _serializers;

        template<typename T, int format> void add_formatter(){
          _serializers[type_provider::typeOf<T>()] = new typed_serializer<T, format>();
        }

        virtual void serialize(serialization_context & context, any value) override{
          auto id = value.type();
          auto it = _serializers.find(id);
          if (it == std::end(_serializers))return;
          _serializers[id]->serialize(context, value);
        }
      };

NS_END(CORE_SERIALIZATION_NAMESPACE)
