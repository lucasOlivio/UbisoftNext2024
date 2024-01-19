#pragma once

#include "Engine/Graphics/GraphicsProperties.h"
#include "iVAOManager.h"

#include <string>
#include <map>

namespace MyEngine
{
	class VAOManager : public iVAOManager
	{
	public:
		VAOManager();
		virtual ~VAOManager();

		virtual void DestroyVBO(std::string modelName);

		virtual sMesh* LoadModelIntoVAO(std::string& fileName, bool bIsDynamicBuffer,
										bool hasNormals, bool hasTexture);
		
		// Normals and texture as default
		virtual sMesh* LoadModelIntoVAO(std::string& fileName, bool bIsDynamicBuffer);

		virtual bool UpdateVAOBuffers(std::string& fileName,
									  std::string& shaderProgram,
									  sMesh* pUpdatedMesh);

		virtual sMesh* FindMeshByModelName(std::string& filename);

		virtual void SetBasePath(std::string basePath);
	private:
		std::string m_basePath;
		std::map< std::string    /*model name*/,
			sMesh* /* info needed to draw*/ >
			m_mapModelNameToMesh;

		bool m_LoadMeshData(std::string theFileName, sMesh* drawInfo);
	};
}

