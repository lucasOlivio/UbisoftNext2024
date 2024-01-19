#include "pch.h"

#include "cBasicTextureManager.h"
#include "TextureProperties.h"
#include "Engine/Utils/Math.h"
#include "Engine/Graphics/Shaders/ShaderManager.h"

#include <sstream>

#define MAX_SAMPLER 20
#define MAX_COLOR_SAMPLER 4

namespace MyEngine
{
	cBasicTextureManager::cBasicTextureManager() :
		m_nextColorSamplerId(0),
		m_mapSamplerNameToInfo({})
	{
	}

	cBasicTextureManager::~cBasicTextureManager()
	{
		for (std::pair<std::string, sSamplerInfo*> pairSampler : m_mapSamplerNameToInfo)
		{
			delete pairSampler.second;
		}
	}

	void cBasicTextureManager::BindTexture(std::string textureName,
		eTextureType textureType, float ratio)
	{
		int unitId = GL_TEXTURE0;
		GLuint textureId = GetTextureIDFromName(textureName);

		sSamplerInfo* pSampler;
		pSampler = GetSamplerInfo(textureType);
		int samplerId = GetSamplerId(textureType);

		unitId += samplerId;

		glActiveTexture(unitId);

		if (textureType == eTextureType::CUBE)
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, textureId);
		}

		// Color textures are the only one been setted by the renderer now, on Draw function
		if (textureType != eTextureType::COLOR)
		{
			glUniform1i(pSampler->samplerToggleUL, true);
		}
		glUniform1i(pSampler->samplerUL, samplerId);
		glUniform1f(pSampler->samplerRatioUL, ratio);

		return;
	}

	void cBasicTextureManager::ResetSamplers()
	{
		m_nextColorSamplerId = 0;

		for (std::pair<std::string, sSamplerInfo*> pairSampler : m_mapSamplerNameToInfo)
		{
			if (pairSampler.second->samplerRatioUL > -1)
			{
				glUniform1f(pairSampler.second->samplerRatioUL, 0.0f);
			}
			glUniform1i(pairSampler.second->samplerToggleUL, false);
		}
	}

	void cBasicTextureManager::SetBasePath(std::string basepath)
	{
		m_basePath = basepath;
		return;
	}

	std::string cBasicTextureManager::GetLastError()
	{
		std::string error = m_lastError;
		m_lastError = "";
		return error;
	}

	bool cBasicTextureManager::Create2DTextureFromBMPFile(std::string textureFileName, bool bGenerateMIPMap)
	{
		std::string fileToLoadFullPath = m_basePath + textureFileName;

		GLuint textId = GetTextureIDFromName(textureFileName);
		if (textId > 0)
		{
			// Texture already loaded
			return true;
		}

		CTextureFromBMP* pTempTexture = new CTextureFromBMP();
		if (!pTempTexture->CreateNewTextureFromBMPFile2(textureFileName, fileToLoadFullPath,
			/*textureUnit,*/ bGenerateMIPMap))
		{
			m_AppendErrorString("Can't load ");
			m_AppendErrorString(fileToLoadFullPath);
			m_AppendErrorString("\n");
			return false;
		}

		m_mapTexNameToTexture[textureFileName] = pTempTexture;

		return true;
	}


	void cBasicTextureManager::m_AppendErrorString(std::string nextErrorText)
	{
		std::stringstream ss;
		ss << m_lastError << nextErrorText;
		m_lastError = ss.str();
		return;
	}

	GLuint cBasicTextureManager::GetTextureIDFromName(std::string textureFileName)
	{
		std::map< std::string, CTextureFromBMP* >::iterator itTexture
			= m_mapTexNameToTexture.find(textureFileName);
		// Found it?
		if (itTexture == m_mapTexNameToTexture.end())
		{
			return 0;
		}
		// Reutrn texture number (from OpenGL genTexture)
		return itTexture->second->getTextureNumber();
	}

	GLuint cBasicTextureManager::GetSamplerId(eTextureType textureType)
	{
		if (textureType == eTextureType::COLOR)
		{
			GLuint samplerId = m_nextColorSamplerId;

			m_nextColorSamplerId += 1;
			WrapMinMax(0, MAX_COLOR_SAMPLER, m_nextColorSamplerId);

			return samplerId;
		}
		else
		{
			return (GLint)textureType;
		}
	}

	sSamplerInfo* cBasicTextureManager::GetSamplerInfo(eTextureType textureTypeIn)
	{
		sSamplerInfo* pSamplerInfo;
		std::string samplerName = "";
		std::string samplerRatioName = "";
		std::string samplerToggle = "";

		// Set names of ULs
		if (textureTypeIn == eTextureType::COLOR)
		{
			samplerName = "colorTexture0" + std::to_string(m_nextColorSamplerId);
			samplerRatioName = "colorTextureRatio0" + std::to_string(m_nextColorSamplerId);
			samplerToggle = "bUseColorTexture";
		}
		else if (textureTypeIn == eTextureType::HEIGHTMAP)
		{
			samplerName = "heightMapTexture";
			samplerRatioName = "heightScale";
			samplerToggle = "bUseHeightMapTexture";
		}
		else if (textureTypeIn == eTextureType::TRANSPARENCY)
		{
			samplerName = "alphaTexture";
			samplerRatioName = "";
			samplerToggle = "bUseAlphaTexture";
		}
		else if (textureTypeIn == eTextureType::NORMAL)
		{
			samplerName = "normalTexture";
			samplerRatioName = "";
			samplerToggle = "bUseNormalTexture";
		}
		else if (textureTypeIn == eTextureType::SPECULAR)
		{
			samplerName = "specularTexture";
			samplerRatioName = "";
			samplerToggle = "bUseSpecularTexture";
		}
		else if (textureTypeIn == eTextureType::DISCARD)
		{
			samplerName = "discardTexture";
			samplerRatioName = "";
			samplerToggle = "bUseDiscardTexture";
		}
		else if (textureTypeIn == eTextureType::CUBE)
		{
			samplerName = "cubeTexture";
			samplerRatioName = "";
			samplerToggle = "bUseCubeTexture";
		}

		pSamplerInfo = GetSamplerInfoFromName(samplerName);
		if (pSamplerInfo)
		{
			// sampler already on cache
			return pSamplerInfo;
		}

		iShaderProgram* pShader = ShaderManager::GetActiveShader();

		// Load sampler info and store in cache
		pSamplerInfo = new sSamplerInfo();
		pSamplerInfo->samplerUL = pShader->GetUL(samplerName.c_str());
		pSamplerInfo->samplerRatioUL = pShader->GetUL(samplerRatioName.c_str());
		pSamplerInfo->samplerToggleUL = pShader->GetUL(samplerToggle.c_str());

		m_mapSamplerNameToInfo[samplerName.c_str()] = pSamplerInfo;

		return pSamplerInfo;
	}

	sSamplerInfo* cBasicTextureManager::GetSamplerInfoFromName(std::string samplerName)
	{
		std::map< std::string, sSamplerInfo* >::iterator itTexture = m_mapSamplerNameToInfo.find(samplerName);
		// Found it?
		if (itTexture == m_mapSamplerNameToInfo.end())
		{
			return nullptr;
		}
		// Reutrn texture number (from OpenGL genTexture)
		return itTexture->second;
	}

	void cBasicTextureManager::m_AppendErrorStringLine(std::string nextErrorTextLine)
	{
		std::stringstream ss;
		ss << m_lastError << std::endl;
		ss << nextErrorTextLine << std::endl;
		m_lastError = ss.str();
		return;
	}


	// Picks a random texture from the textures loaded
	std::string cBasicTextureManager::PickRandomTexture(void)
	{
		if (m_mapTexNameToTexture.empty())
		{
			// There are no textures loaded, yet.
			return "";
		}

		int textureIndexRand = rand() % (m_mapTexNameToTexture.size() + 1);
		if (textureIndexRand >= m_mapTexNameToTexture.size())
		{
			textureIndexRand = 0;
		}

		std::map< std::string, CTextureFromBMP* >::iterator itTex = m_mapTexNameToTexture.begin();
		for (unsigned int count = 0; count != textureIndexRand; count++, itTex++)
		{
		}

		return itTex->second->getTextureName();
	}


	bool cBasicTextureManager::CreateCubeTextureFromBMPFiles(
		std::string cubeMapName,
		std::string posX_fileName, std::string negX_fileName,
		std::string posY_fileName, std::string negY_fileName,
		std::string posZ_fileName, std::string negZ_fileName,
		bool bIsSeamless, std::string& errorString)
	{
		std::string posX_fileName_FullPath = m_basePath + "/" + posX_fileName;
		std::string negX_fileName_FullPath = m_basePath + "/" + negX_fileName;
		std::string posY_fileName_FullPath = m_basePath + "/" + posY_fileName;
		std::string negY_fileName_FullPath = m_basePath + "/" + negY_fileName;
		std::string posZ_fileName_FullPath = m_basePath + "/" + posZ_fileName;
		std::string negZ_fileName_FullPath = m_basePath + "/" + negZ_fileName;

		GLenum errorEnum;
		std::string errorDetails;
		CTextureFromBMP* pTempTexture = new CTextureFromBMP();
		if (!pTempTexture->CreateNewCubeTextureFromBMPFiles(
			cubeMapName,
			posX_fileName_FullPath, negX_fileName_FullPath,
			posY_fileName_FullPath, negY_fileName_FullPath,
			posZ_fileName_FullPath, negZ_fileName_FullPath,
			bIsSeamless, errorEnum, errorString, errorDetails))
		{
			m_AppendErrorString("Can't load ");
			m_AppendErrorString(cubeMapName);
			m_AppendErrorString(" because:\n");
			m_AppendErrorString(errorString);
			m_AppendErrorString("\n");
			m_AppendErrorString(errorDetails);
			errorString += ("\n" + errorDetails);
			return false;
		}//if ( ! pTempTexture->CreateNewCubeTextureFromBMPFiles()

		// Texture is loaded OK
		//m_nextTextureUnitOffset++;

		m_mapTexNameToTexture[cubeMapName] = pTempTexture;

		return true;
	}
}
