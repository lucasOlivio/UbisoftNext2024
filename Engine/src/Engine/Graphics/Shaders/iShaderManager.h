#pragma once

#include "iShaderProgram.h"
#include "Engine/Core/types.h"
#include <string>

namespace MyEngine
{
	class iShaderManager
	{
	public:
		iShaderManager() {};
		virtual ~iShaderManager() {};

		// Where we initialize all things that could go wrong
		virtual bool AddShaderProgram(std::string shaderProgram) = 0;

		virtual bool CreateProgramFromFile(std::string shaderProgram,
										   std::string vertexName,
										   std::string fragName) = 0;
		virtual void SetBasePath(std::string basepath) = 0;

		// Clears last error
		virtual std::string GetLastError(void) = 0;

		virtual uint GetIDFromShaderProgramName(std::string& shaderProgram) = 0;

		// Used to load the uniforms. Returns NULL if not found.
		virtual iShaderProgram* GetShaderProgramFromName(std::string& shaderProgram) = 0;
		virtual iShaderProgram* GetShaderProgramFromID(uint shaderProgramID) = 0;

		// Bind opengl to this shader program
		virtual bool UseShaderProgram(uint ID) = 0;
		virtual bool UseShaderProgram(std::string& shaderProgram) = 0;
	};
}