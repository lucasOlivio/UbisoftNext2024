#pragma once

#include "Engine/ECS/Scene/Scene.h"
#include "Engine/ECS/Components.h"
#include <string>

namespace MyEngine
{
	class iMaterialManager
	{
	public:
		iMaterialManager() {};
		virtual ~iMaterialManager() {};

		virtual void BindMaterial(Scene* pScene, std::string materialName) = 0;
		virtual void UnbindMaterial() = 0;

		// Search in cached or in scene for the material
		virtual MaterialComponent* GetMaterialByName(Scene* pScene, std::string materialName) = 0;

		virtual void DeleteMaterial(Scene* pScene, std::string materialName) = 0;
	};
}