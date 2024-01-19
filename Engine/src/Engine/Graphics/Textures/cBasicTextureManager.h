#ifndef _cBasicTextureManager_HG_
#define _cBasicTextureManager_HG_

#include "CTextureFromBMP.h"
#include "Engine/Core/types.h"
#include "iTextureManager.h"
#include <map>

namespace MyEngine
{
	class cBasicTextureManager : public iTextureManager
	{
	public:
		cBasicTextureManager();
		virtual ~cBasicTextureManager();

		virtual bool Create2DTextureFromBMPFile(std::string textureFileName, bool bGenerateMIPMap);

		// Picks a random texture from the textures loaded
		virtual std::string PickRandomTexture(void);

		virtual bool CreateCubeTextureFromBMPFiles(std::string cubeMapName,
												std::string posX_fileName, std::string negX_fileName,
												std::string posY_fileName, std::string negY_fileName,
												std::string posZ_fileName, std::string negZ_fileName,
												bool bIsSeamless, std::string& errorString);


		// returns 0 on error
		virtual GLuint GetTextureIDFromName(std::string textureFileName);

		// gets the sampler to be used based on the texture type
		virtual GLuint GetSamplerId(eTextureType textureType);

		virtual sSamplerInfo* GetSamplerInfo(eTextureType textureTypeIn);
		virtual sSamplerInfo* GetSamplerInfoFromName(std::string samplerName);

		// If texture not already in any sampler, then loads into next available
		virtual void BindTexture(std::string textureName,
								 eTextureType textureType, float ratio);

		// Reset all ratios to 0
		virtual void ResetSamplers();

		virtual void SetBasePath(std::string basepath);

		virtual std::string GetLastError();

	private:
		std::string m_basePath;
		std::string m_lastError;
		void m_AppendErrorString(std::string nextErrorText);
		void m_AppendErrorStringLine(std::string nextErrorTextLine);

		std::map< std::string, CTextureFromBMP* > m_mapTexNameToTexture;
		std::map< std::string /*sampler name*/, sSamplerInfo* > m_mapSamplerNameToInfo;

		int m_nextColorSamplerId;
	};
}
#endif
