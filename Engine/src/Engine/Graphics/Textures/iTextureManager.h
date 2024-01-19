#pragma once

#include "TextureProperties.h"
#include "Engine/Graphics/opengl.h"
#include <string>

namespace MyEngine
{
    class iTextureManager
    {
    public:
        iTextureManager() {}
        virtual ~iTextureManager() {};

		virtual bool Create2DTextureFromBMPFile(std::string textureFileName, bool bGenerateMIPMap) = 0;

		// Picks a random texture from the textures loaded
		virtual std::string PickRandomTexture(void) = 0;

		virtual bool CreateCubeTextureFromBMPFiles(std::string cubeMapName,
												std::string posX_fileName, std::string negX_fileName,
												std::string posY_fileName, std::string negY_fileName,
												std::string posZ_fileName, std::string negZ_fileName,
												bool bIsSeamless, std::string& errorString) = 0;


		// returns 0 on error
		virtual GLuint GetTextureIDFromName(std::string textureFileName) = 0;

		// gets the sampler to be used based on the texture type
		virtual GLuint GetSamplerId(eTextureType textureType) = 0;

		virtual sSamplerInfo* GetSamplerInfo(eTextureType textureTypeIn) = 0;
		virtual sSamplerInfo* GetSamplerInfoFromName(std::string samplerName) = 0;

		// If texture not already in any sampler, then loads into next available
		virtual void BindTexture(std::string textureName,
								 eTextureType textureType, float ratio) = 0;

		// Reset all ratios to 0
		virtual void ResetSamplers() = 0;

		virtual void SetBasePath(std::string basepath) = 0;

		virtual std::string GetLastError() = 0;
    };
}
