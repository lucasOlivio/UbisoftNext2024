#pragma once
#include "pch.h"

#include "iTextureManager.h"

namespace MyEngine
{
    // Null service only to avoid crashes in locator
    class NullTextureManager : public iTextureManager
    {
    public:
        NullTextureManager() {}
        virtual ~NullTextureManager() {};

		virtual bool Create2DTextureFromBMPFile(std::string textureFileName, bool bGenerateMIPMap)
		{
			LOG_ERROR("TextureManager not set!");

			return false;
		}

		// Picks a random texture from the textures loaded
		virtual std::string PickRandomTexture(void)
		{
			LOG_ERROR("TextureManager not set!");

			return "";
		}

		virtual bool CreateCubeTextureFromBMPFiles(std::string cubeMapName,
			std::string posX_fileName, std::string negX_fileName,
			std::string posY_fileName, std::string negY_fileName,
			std::string posZ_fileName, std::string negZ_fileName,
			bool bIsSeamless, std::string& errorString)
		{
			LOG_ERROR("TextureManager not set!");

			return false;
		}


		// returns 0 on error
		virtual GLuint GetTextureIDFromName(std::string textureFileName)
		{
			LOG_ERROR("TextureManager not set!");

			return 0;
		}

		// gets the sampler to be used based on the texture type
		virtual GLuint GetSamplerId(eTextureType textureType)
		{
			LOG_ERROR("TextureManager not set!");

			return 0;
		}

		virtual sSamplerInfo* GetSamplerInfo(eTextureType textureTypeIn)
		{
			LOG_ERROR("TextureManager not set!");

			return nullptr;
		}
		virtual sSamplerInfo* GetSamplerInfoFromName(std::string samplerName)
		{
			LOG_ERROR("TextureManager not set!");

			return nullptr;
		}

		// If texture not already in any sampler, then loads into next available
		virtual void BindTexture(std::string textureName,
			eTextureType textureType, float ratio)
		{
			LOG_ERROR("TextureManager not set!");
		}

		// Reset all ratios to 0
		virtual void ResetSamplers()
		{
			LOG_ERROR("TextureManager not set!");
		}

		virtual void SetBasePath(std::string basepath)
		{
			LOG_ERROR("TextureManager not set!");
		}

		virtual std::string GetLastError()
		{
			LOG_ERROR("TextureManager not set!");

			return "";
		}
    };
}
