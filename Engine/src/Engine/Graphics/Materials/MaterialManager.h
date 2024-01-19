#pragma once

#include "iMaterialManager.h"
#include <map>

namespace MyEngine
{
	class MaterialManager : public iMaterialManager
	{
	public:
		MaterialManager();
		virtual ~MaterialManager();

		virtual void BindMaterial(Scene* pScene, std::string materialName);
		virtual void UnbindMaterial();

		// Search in cached or in scene for the material
		virtual MaterialComponent* GetMaterialByName(Scene* pScene, std::string materialName);

		virtual void DeleteMaterial(Scene* pScene, std::string materialName);

	private:
		std::map<std::string, MaterialComponent*> m_materials;

		// Textures and variables in the uniforms and units at the moment
		std::string m_currMaterial;
	};
}