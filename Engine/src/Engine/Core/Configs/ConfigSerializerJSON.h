#pragma once

#include "iConfigSerializer.h"
#include "Engine/ECS/Components.h"
#include "Engine/ECS/SingletonComponents/Components.h"
#include <rapidjson/document.h>

namespace MyEngine
{
	class ConfigSerializerJSON : public iConfigSerializer
	{
	public:
		ConfigSerializerJSON();
		virtual ~ConfigSerializerJSON();

		virtual bool DeserializeConfig(const std::string& filePath);

		virtual bool SerializeConfig(const std::string& filePath);

	private:
		rapidjson::Document m_doc;

		bool m_LoadDoc(const std::string& filePath);
		bool m_SaveDoc(const std::string& filePath);

		// Parse values From the respective data structures into the doc
		bool m_ParseConfigToDoc();
		bool m_ParseCameraToDoc(rapidjson::Value& jsonObject, 
								  CameraComponent& cameraIn,
								  rapidjson::Document::AllocatorType& allocator);
		bool m_ParseWindowToDoc(rapidjson::Value& jsonObject, 
								  WindowComponent& windowIn,
								  rapidjson::Document::AllocatorType& allocator);
		bool m_ParseConfigPathToDoc(rapidjson::Value& jsonObject, 
								  ConfigPathComponent& configPathIn,
								  rapidjson::Document::AllocatorType& allocator);

		// Parse values from doc to the respective data structure
		bool m_ParseDocToConfig();
		bool m_ParseDocToCamera(rapidjson::Value& jsonObject, 
							   CameraComponent& cameraOut);
		bool m_ParseDocToWindow(rapidjson::Value& jsonObject, 
							   WindowComponent& windowOut);
		bool m_ParseDocToConfigPath(rapidjson::Value& jsonObject, 
							   ConfigPathComponent& configPathOut);
	};
}