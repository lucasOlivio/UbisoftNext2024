#include "pch.h"

#include "ConfigSerializerFactory.h"
#include "ConfigSerializerJSON.h"
#include "Engine/Utils/Files.h"

namespace MyEngine
{
    iConfigSerializer* ConfigSerializerFactory::CreateConfigSerializer(std::string fileExt)
    {
        iConfigSerializer* pConfigSerializer = nullptr;
        bool fileLoaded = true;
        // in case the path is been passed
        fileExt = GetFileExtension(fileExt);

        if (fileExt == "json")
        {
            pConfigSerializer = new ConfigSerializerJSON();
        }

        if (!fileLoaded)
        {
            return nullptr;
        }

        return pConfigSerializer;
    }
}
