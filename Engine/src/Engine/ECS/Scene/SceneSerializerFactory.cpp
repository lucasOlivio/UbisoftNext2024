#include "pch.h"

#include "SceneSerializerFactory.h"
#include "SceneSerializerJSON.h"
#include "Engine/Utils/Files.h"

namespace MyEngine
{
    iSceneSerializer* SceneSerializerFactory::CreateSceneSerializer(std::string fileExt)
    {
        iSceneSerializer* pSceneSerializer = nullptr;
        bool fileLoaded = true;
        // in case the path is been passed
        fileExt = GetFileExtension(fileExt);

        if (fileExt == "json")
        {
            pSceneSerializer = new SceneSerializerJSON();
        }

        if (!fileLoaded)
        {
            return nullptr;
        }

        return pSceneSerializer;
    }
}
