#pragma once

#include "iSceneSerializer.h"

namespace MyEngine
{
	class SceneSerializerFactory
	{
	public:
		// Gets the right config reader and writer accordingly to the file type
		static iSceneSerializer* CreateSceneSerializer(std::string fileExt);
	};
}