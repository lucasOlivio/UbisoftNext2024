#pragma once

#include "pch.h"
#include "iMaterialManager.h"

namespace MyEngine
{
	class NullMaterialManager : public iMaterialManager
	{
	public:
		NullMaterialManager() {};
		virtual ~NullMaterialManager() {};

		virtual void BindMaterial(Scene* pScene, std::string materialName)
		{
			LOG_ERROR("MaterialManager not set!");
		}

		virtual void UnbindMaterial()
		{
			LOG_ERROR("MaterialManager not set!");
		}

		virtual MaterialComponent* GetMaterialByName(Scene* pScene, std::string materialName)
		{
			LOG_ERROR("MaterialManager not set!");
			return nullptr;
		}

		virtual void DeleteMaterial(Scene* pScene, std::string materialName)
		{
			LOG_ERROR("MaterialManager not set!");
			return;
		}
	};
}