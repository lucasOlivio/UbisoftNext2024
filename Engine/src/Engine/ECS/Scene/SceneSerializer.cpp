#include "pch.h"

#include "SceneSerializer.h"
#include "SceneSerializerFactory.h"

namespace MyEngine
{
    SceneSerializer::SceneSerializer(Scene* pScene)
        : m_pScene(pScene)
    {
    }

    bool SceneSerializer::Serialize(const std::string& filepath)
    {
        iSceneSerializer* pSerializer = SceneSerializerFactory::CreateSceneSerializer(filepath);

        bool isSerialized = pSerializer->SerializeScene(filepath, *m_pScene);

        return isSerialized;
    }

    bool SceneSerializer::Deserialize(const std::string& filepath)
    {
        iSceneSerializer* pSerializer = SceneSerializerFactory::CreateSceneSerializer(filepath);

        bool isSerialized = pSerializer->DeserializeScene(filepath, *m_pScene);

        return isSerialized;
    }
}
