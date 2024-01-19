#include "pch.h"

#include "ConfigSerializer.h"
#include "ConfigSerializerFactory.h"

namespace MyEngine
{
    ConfigSerializer::ConfigSerializer()
    {
    }

    bool ConfigSerializer::Serialize(const std::string& filepath)
    {
        iConfigSerializer* pSerializer = ConfigSerializerFactory::CreateConfigSerializer(filepath);

        bool isSerialized = pSerializer->SerializeConfig(filepath);

        return isSerialized;
    }

    bool ConfigSerializer::Deserialize(const std::string& filepath)
    {
        iConfigSerializer* pSerializer = ConfigSerializerFactory::CreateConfigSerializer(filepath);

        bool isSerialized = pSerializer->DeserializeConfig(filepath);

        return isSerialized;
    }
}
