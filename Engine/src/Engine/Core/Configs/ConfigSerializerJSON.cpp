#include "pch.h"

#include "ConfigSerializerJSON.h"
#include "Engine/Utils/ParserJSON.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"
#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"

#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <fstream>

namespace MyEngine
{
    ConfigSerializerJSON::ConfigSerializerJSON()
    {
        m_doc.SetObject();
    }

    ConfigSerializerJSON::~ConfigSerializerJSON()
    {
    }

    bool ConfigSerializerJSON::DeserializeConfig(const std::string& filePath)
    {
        bool isLoaded = m_LoadDoc(filePath);
        if (!isLoaded)
        {
            return false;
        }

        // Parse scene json and load into object
        bool isParsed = m_ParseDocToConfig();
        if (!isParsed)
        {
            std::string errorMsg = "Error parsing file '" + filePath + "'";
            LOG_ERROR(errorMsg.c_str());
            return false;
        }

        return true;
    }

    bool ConfigSerializerJSON::SerializeConfig(const std::string& filePath)
    {
        // Convert the scene object to a JSON document
        bool isParsed = m_ParseConfigToDoc();
        if (!isParsed)
        {
            std::string errorMsg = "Error parsing doc to file '" + filePath + "'";
            LOG_ERROR(errorMsg.c_str());
            return false;
        }

        bool isSaved = m_SaveDoc(filePath);

        if (!isSaved) {
            std::string errorMsg = "Error saving json to file '" + filePath + "'";
            LOG_ERROR(errorMsg.c_str());
            return false;
        }

        m_doc.Clear();

        return true;
    }

    bool ConfigSerializerJSON::m_LoadDoc(const std::string& filePath)
    {
        using namespace rapidjson;

        // Load file stream into document object
        FILE* fp = 0;
        fopen_s(&fp, filePath.c_str(), "rb");

        if (!fp)
        {
            std::string errorMsg = "File '" + filePath + "' not found!";
            LOG_ERROR(errorMsg);
            return false;
        }

        char readBuffer[MAX_LINE_LENGTH];
        FileReadStream fs(fp, readBuffer, sizeof(readBuffer));

        m_doc.ParseStream(fs);

        fclose(fp);

        std::string infoMsg = "File '" + filePath + "' loaded!";
        LOG_INFO(infoMsg);

        return true;
    }

    bool ConfigSerializerJSON::m_SaveDoc(const std::string& filePath)
    {
        using namespace rapidjson;

        StringBuffer buf;
        PrettyWriter<StringBuffer> writer(buf);

        m_doc.Accept(writer);

        // Get the JSON string from the buffer
        std::string json = buf.GetString();

        // Write the JSON to a file
        std::ofstream of(filePath, std::ios::out | std::ios::trunc);
        of << json;

        if (!of.good()) {
            std::string errorMsg = "Error saving json to file '" + filePath + "'";
            LOG_ERROR(errorMsg.c_str());
            return false;
        }

        of.close();

        return true;
    }

    bool ConfigSerializerJSON::m_ParseConfigToDoc()
    {
        using namespace rapidjson;

        Document::AllocatorType& allocator = m_doc.GetAllocator();
        m_doc.SetObject();

        // Singleton components
        // All singleton components goes into the root object in the json
        //-------------------------------
       
        // Camera
        Value cameraObject;
        cameraObject.SetObject();

        CameraComponent* pCamera = GraphicsLocator::GetCamera();
        m_ParseCameraToDoc(cameraObject, *pCamera, allocator);
        m_doc.AddMember("camera", cameraObject, allocator);

        // Window
        Value windowObject;
        windowObject.SetObject();

        WindowComponent* pWindow = GraphicsLocator::GetWindow();
        m_ParseWindowToDoc(windowObject, *pWindow, allocator);
        m_doc.AddMember("window", windowObject, allocator);

        // Config
        Value configPathObject;
        configPathObject.SetObject();

        ConfigPathComponent* pConfigPath = CoreLocator::GetConfigPath();
        m_ParseConfigPathToDoc(configPathObject, *pConfigPath, allocator);
        m_doc.AddMember("configPath", configPathObject, allocator);

        return true;
    }

    bool ConfigSerializerJSON::m_ParseCameraToDoc(rapidjson::Value& jsonObject, CameraComponent& cameraIn, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        parser.SetMember(jsonObject, "upVector", cameraIn.upVector, allocator);
        parser.SetMember(jsonObject, "position", cameraIn.position, allocator);
        parser.SetMember(jsonObject, "orientation", cameraIn.orientation, allocator);
        parser.SetMember(jsonObject, "distance", cameraIn.distance, allocator);
        parser.SetMember(jsonObject, "height", cameraIn.height, allocator);
        parser.SetMember(jsonObject, "offsetTarget", cameraIn.offsetTarget, allocator);

        return true;
    }

    bool ConfigSerializerJSON::m_ParseWindowToDoc(rapidjson::Value& jsonObject, WindowComponent& windowIn, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        parser.SetMember(jsonObject, "name", windowIn.name, allocator);
        parser.SetMember(jsonObject, "height", windowIn.height, allocator);
        parser.SetMember(jsonObject, "width", windowIn.width, allocator);
        parser.SetMember(jsonObject, "fovy", windowIn.fovy, allocator);
        parser.SetMember(jsonObject, "zNear", windowIn.zNear, allocator);
        parser.SetMember(jsonObject, "zFar", windowIn.zFar, allocator);

        return true;
    }

    bool ConfigSerializerJSON::m_ParseConfigPathToDoc(rapidjson::Value& jsonObject, ConfigPathComponent& configPathIn, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        parser.SetMember(jsonObject, "pathAudio", configPathIn.pathAudio, allocator);
        parser.SetMember(jsonObject, "pathModels", configPathIn.pathModels, allocator);
        parser.SetMember(jsonObject, "pathScripts", configPathIn.pathScripts, allocator);
        parser.SetMember(jsonObject, "pathShaders", configPathIn.pathShaders, allocator);
        parser.SetMember(jsonObject, "pathTextures", configPathIn.pathTextures, allocator);
        parser.SetMember(jsonObject, "pathScenes", configPathIn.pathScenes, allocator);

        parser.SetMember(jsonObject, "pathDebugSquare", configPathIn.pathDebugSquare, allocator);
        parser.SetMember(jsonObject, "pathDebugSphere", configPathIn.pathDebugSphere, allocator);

        return true;
    }

    bool ConfigSerializerJSON::m_ParseDocToConfig()
    {
        using namespace rapidjson;

        bool isValid = m_doc.IsObject();
        if (!isValid)
        {
            LOG_ERROR("File not valid, expected dictionary with configurations!\n");
            return false;
        }

        // Go over each configuration object
        for (Value::ConstMemberIterator configMember = m_doc.MemberBegin();
            configMember != m_doc.MemberEnd(); ++configMember)
        {
            std::string configName = configMember->name.GetString();

            Value& configObject = m_doc[configMember->name];
            bool isValid = configObject.IsObject();
            if (!isValid)
            {
                std::string error = "Config: '" + configName + "' not valid\n";
                LOG_ERROR(error);
                return false;
            }

            if (configName == "camera")
            {
                CameraComponent* pCamera = GraphicsLocator::GetCamera();
                m_ParseDocToCamera(configObject, *pCamera);
            }
            else if (configName == "window")
            {
                WindowComponent* pWindow = GraphicsLocator::GetWindow();
                m_ParseDocToWindow(configObject, *pWindow);
            }
            else if (configName == "defaultPaths")
            {
                ConfigPathComponent* pConfigPath = CoreLocator::GetConfigPath();
                m_ParseDocToConfigPath(configObject, *pConfigPath);
            }
        }

        return true;
    }

    bool ConfigSerializerJSON::m_ParseDocToCamera(rapidjson::Value& jsonObject, CameraComponent& cameraOut)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        parser.GetValue(jsonObject["upVector"], cameraOut.upVector);
        parser.GetValue(jsonObject["position"], cameraOut.position);
        parser.GetValue(jsonObject["orientation"], cameraOut.orientation);
        parser.GetValue(jsonObject["distance"], cameraOut.distance);
        parser.GetValue(jsonObject["height"], cameraOut.height);
        parser.GetValue(jsonObject["offsetTarget"], cameraOut.offsetTarget);

        return true;
    }
    bool ConfigSerializerJSON::m_ParseDocToWindow(rapidjson::Value& jsonObject, WindowComponent& windowOut)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        parser.GetValue(jsonObject["name"], windowOut.name);
        parser.GetValue(jsonObject["height"], windowOut.height);
        parser.GetValue(jsonObject["width"], windowOut.width);
        parser.GetValue(jsonObject["fovy"], windowOut.fovy);
        parser.GetValue(jsonObject["zNear"], windowOut.zNear);
        parser.GetValue(jsonObject["zFar"], windowOut.zFar);

        return true;
    }
    bool ConfigSerializerJSON::m_ParseDocToConfigPath(rapidjson::Value& jsonObject, ConfigPathComponent& configPathOut)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        parser.GetValue(jsonObject["pathAudio"], configPathOut.pathAudio);
        parser.GetValue(jsonObject["pathModels"], configPathOut.pathModels);
        parser.GetValue(jsonObject["pathScripts"], configPathOut.pathScripts);
        parser.GetValue(jsonObject["pathShaders"], configPathOut.pathShaders);
        parser.GetValue(jsonObject["pathTextures"], configPathOut.pathTextures);
        parser.GetValue(jsonObject["pathScenes"], configPathOut.pathScenes);

        parser.GetValue(jsonObject["pathDebugSquare"], configPathOut.pathDebugSquare);
        parser.GetValue(jsonObject["pathDebugSphere"], configPathOut.pathDebugSphere);

        return true;
    }
}
