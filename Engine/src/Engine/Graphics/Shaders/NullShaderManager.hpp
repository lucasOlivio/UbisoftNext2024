#pragma once

#include "pch.h"

#include "iShaderManager.h"

namespace MyEngine
{
	class NullShaderManager : public iShaderManager
	{
	public:
		NullShaderManager() {};
		virtual ~NullShaderManager() {};

		// Where we initialize all things that could go wrong
		virtual bool AddShaderProgram(std::string shaderProgram)
		{
			LOG_ERROR("Shader manager not set!");
			return false;
		}

		virtual bool CreateProgramFromFile(std::string shaderProgram,
			std::string vertexName,
			std::string fragName)
		{
			LOG_ERROR("Shader manager not set!");
			return false;
		}

		virtual void SetBasePath(std::string basepath)
		{
			LOG_ERROR("Shader manager not set!");
		}

		// Clears last error
		virtual std::string GetLastError(void)
		{
			LOG_ERROR("Shader manager not set!");
			return "";
		}

		virtual uint GetIDFromShaderProgramName(std::string& shaderProgram)
		{
			LOG_ERROR("Shader manager not set!");
			return 0;
		}

		// Used to load the uniforms. Returns NULL if not found.
		virtual iShaderProgram* GetShaderProgramFromName(std::string& shaderProgram)
		{
			LOG_ERROR("Shader manager not set!");
			return nullptr;
		}

		virtual iShaderProgram* GetShaderProgramFromID(uint shaderProgramID)
		{
			LOG_ERROR("Shader manager not set!");
			return nullptr;
		}

		// Bind opengl to this shader program
		virtual bool UseShaderProgram(uint ID)
		{
			LOG_ERROR("Shader manager not set!");
			return false;
		}
		virtual bool UseShaderProgram(std::string& shaderProgram)
		{
			LOG_ERROR("Shader manager not set!");
			return false;
		}
	};
}