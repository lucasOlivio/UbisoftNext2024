#pragma once

#include "Scene.h"
#include <string>

namespace MyEngine
{
	class iSceneSerializer
	{
	public:
		virtual ~iSceneSerializer() {};

		virtual bool DeserializeScene(const std::string& filePath, Scene& sceneOut) = 0;

		virtual bool SerializeScene(const std::string& filePath, Scene& sceneIn) = 0;
	};
}