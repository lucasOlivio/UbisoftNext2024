#pragma once

#include "pch.h"
#include "Engine/Graphics/VAO/iVAOManager.h"

namespace MyEngine
{
	class NullVAOManager : public iVAOManager
	{
	public:
		NullVAOManager() {};
		virtual ~NullVAOManager() {};

		virtual void DestroyVBO(std::string modelName)
		{
			LOG_ERROR("VAOManager not set!");
		}

		virtual sMesh* LoadModelIntoVAO(std::string& fileName, bool bIsDynamicBuffer,
										bool hasNormals, bool hasTexture)
		{
			LOG_ERROR("VAOManager not set!");
			return nullptr;
		}

		// Normals and texture as default
		virtual sMesh* LoadModelIntoVAO(std::string& fileName, bool bIsDynamicBuffer)
		{
			LOG_ERROR("VAOManager not set!");
			return nullptr;
		}

		virtual bool UpdateVAOBuffers(std::string& fileName,
									  std::string& shaderProgram,
									  sMesh* pUpdatedMesh)
		{
			LOG_ERROR("VAOManager not set!");
			return false;
		}

		virtual sMesh* FindMeshByModelName(std::string& filename)
		{
			LOG_ERROR("VAOManager not set!");
			return nullptr;
		}

		virtual void SetBasePath(std::string basePath)
		{
			LOG_ERROR("VAOManager not set!");
		}
	};
}
