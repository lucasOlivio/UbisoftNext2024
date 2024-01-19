#include "pch.h"

#include "ShaderProgram.h"
#include "ShaderManager.h"
#include "Engine/Graphics/opengl.h"
#include "Engine/Core/Constants.h"

namespace MyEngine
{
	iShaderProgram* ShaderManager::m_pActiveShader = nullptr;

	ShaderManager::ShaderManager(std::string basePath)
	{
		m_basepath = basePath;
		return;
	}

	ShaderManager::~ShaderManager()
	{
		typedef std::pair< uint, iShaderProgram*> pairShader;

		for (pairShader shader : m_IDToShaderProgram)
		{
			delete shader.second;
		}

		return;
	}


	bool ShaderManager::AddShaderProgram(std::string shaderProgram)
	{
		bool shaderCompiled = CreateProgramFromFile(shaderProgram, 
													"vertex" + shaderProgram + ".glsl", 
													"fragment" + shaderProgram + ".glsl");

		if (!shaderCompiled) {
			std::string error = "Couldn't compile or link: " + GetLastError();
			LOG_ERROR(error);
			return false;
		}

		return true;
	}

	bool ShaderManager::UseShaderProgram(uint ID)
	{
		m_pActiveShader = GetShaderProgramFromID(ID);
		glUseProgram(ID);
		return true;
	}

	bool ShaderManager::UseShaderProgram(std::string& shaderProgram)
	{
		uint shaderProgramID = GetIDFromShaderProgramName(shaderProgram);

		if (shaderProgramID == 0)
		{
			return false;
		}

		UseShaderProgram(shaderProgramID);

		return true;
	}

	uint ShaderManager::GetIDFromShaderProgramName(std::string& shaderProgram)
	{
		std::map< std::string /*name*/, uint /*ID*/ >::iterator
			itShad = m_shaderProgramNameToID.find(shaderProgram);

		if (itShad == m_shaderProgramNameToID.end())
		{	// Didn't find it
			return 0;
		}
		return itShad->second;
	}

	iShaderProgram* ShaderManager::GetShaderProgramFromName(std::string& shaderProgram)
	{
		uint shaderProgramID = GetIDFromShaderProgramName(shaderProgram);

		// Now get the actual shader

		std::map< uint /*ID*/, iShaderProgram* >::iterator
			itShaderProgram = m_IDToShaderProgram.find(shaderProgramID);

		if (itShaderProgram == m_IDToShaderProgram.end())
		{	// Didn't find it
			return NULL;		// or 0 or nullptr
		}

		iShaderProgram* pShaderProgram = itShaderProgram->second;

		return pShaderProgram;
	}

	iShaderProgram* ShaderManager::GetShaderProgramFromID(uint shaderProgramID)
	{
		// Now get the actual shader
		std::map< uint /*ID*/, iShaderProgram* >::iterator
			itShaderProgram = m_IDToShaderProgram.find(shaderProgramID);

		if (itShaderProgram == m_IDToShaderProgram.end())
		{	// Didn't find it
			return NULL;		// or 0 or nullptr
		}

		iShaderProgram* pShaderProgram = itShaderProgram->second;

		return pShaderProgram;
	}

	iShaderProgram* ShaderManager::GetActiveShader()
	{
		return m_pActiveShader;
	}

	void ShaderManager::SetBasePath(std::string basepath)
	{
		m_basepath = basepath;
		return;
	}

	// Returns bool if didn't load
	bool ShaderManager::m_LoadSourceFromFile(std::string filename,
											 std::vector<std::string>& vecSource, 
											 std::string& errorText)
	{
		std::string fullFileName = m_basepath + filename;
		std::string info = "Opening shader file " + fullFileName;
		LOG_INFO(info);

		std::ifstream theFile(fullFileName.c_str());
		if (!theFile.is_open())
		{
			errorText = "Error: shader file " + fullFileName + " not found!\n";
			return false;
		}

		vecSource.clear();

		char* pLineTemp = new char[MAX_LINE_LENGTH];
		while (theFile.getline(pLineTemp, MAX_LINE_LENGTH))
		{
			std::string tempString(pLineTemp);
			vecSource.push_back(tempString);
		}

		theFile.close();
		return true;		// Return the string (from the sstream)
	}

	// Returns empty string if no error
	// returns false if no error
	bool ShaderManager::m_WasThereACompileError(uint shaderID, std::string& errorText)
	{
		errorText = "";	// No error

		GLint isCompiled = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			char* pLogText = new char[maxLength];

			glGetShaderInfoLog(shaderID, maxLength, &maxLength, pLogText);
			// Copy char array to string
			errorText.append(pLogText);

			m_lastError.append("\n");
			m_lastError.append(errorText);


			delete[] pLogText;

			return true;	// There WAS an error
		}
		return false; // There WASN'T an error
	}

	bool ShaderManager::m_WasThereALinkError(uint programID, std::string& errorText)
	{
		errorText = "";	// No error

		GLint wasError = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, &wasError);
		if (wasError == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

			char* pLogText = new char[maxLength];
			// Fill with zeros, maybe...?
			glGetProgramInfoLog(programID, maxLength, &maxLength, pLogText);
			// Copy char array to string
			errorText.append(pLogText);

			// Extra code that Michael forgot wasn't there... 
			m_lastError.append("\n");
			m_lastError.append(errorText);


			delete[] pLogText;

			// There WAS an error
			return true;
		}

		// There WASN'T an error
		return false;
	}


	std::string ShaderManager::GetLastError(void)
	{
		std::string lastErrorTemp = m_lastError;
		m_lastError = "";
		return lastErrorTemp;
	}

	bool ShaderManager::m_CompileShaderFromSource(uint shaderId,
												  std::vector<std::string>& vecSource, 
												  std::string& error)
	{
		error = "";

		uint numberOfLines = static_cast<uint>(vecSource.size());

		// This is an array of pointers to strings. aka the lines of source
		char** arraySource = new char* [numberOfLines];
		// Clear array to all zeros (i.e. '\0' or null terminator)
		memset(arraySource, 0, numberOfLines);

		LOG_INFO("Loading shader text...\n");
		for (uint indexLine = 0; indexLine != numberOfLines; indexLine++)
		{
			uint numCharacters = (uint)vecSource[indexLine].length();
			// Create an array of chars for each line
			arraySource[indexLine] = new char[numCharacters + 2];		// For the '\n' and '\0' at end
			memset(arraySource[indexLine], 0, numCharacters + 2);;

			// The "secure" version to copy arrays, where you specify the number of chars to copy
			strcpy_s(arraySource[indexLine],
				strlen(vecSource[indexLine].c_str()) + 1,	// Number of char in copy + 0 terminator
				vecSource[indexLine].c_str());
			arraySource[indexLine][numCharacters + 0] = '\n';
			arraySource[indexLine][numCharacters + 1] = '\0';
		}

		LOG_INFO("Compiling shader..\n");
		glShaderSource(shaderId, numberOfLines, arraySource, NULL);
		glCompileShader(shaderId);

		// Get rid of the temp source "c" style array
		for (uint indexLine = 0; indexLine != numberOfLines; indexLine++)
		{	// Delete this line
			delete[] arraySource[indexLine];
		}
		// And delete the original char** array
		delete[] arraySource;

		// Did it work? 
		std::string errorText = "";
		if (m_WasThereACompileError(shaderId, errorText))
		{
			std::stringstream ssError;
			ssError << " compile error: ";
			ssError << errorText;
			error = ssError.str();
			return false;
		}

		return true;
	}

	bool ShaderManager::CreateProgramFromFile(std::string shaderProgram,
											std::string vertexName,
											std::string fragName)
	{
		std::string errorText = "";

		Shader vertexShader;
		vertexShader.fileName = "vertex" + shaderProgram + ".glsl";

		Shader fragmentShader;
		fragmentShader.fileName = "fragment" + shaderProgram + ".glsl";

		// Shader loading happening before vertex buffer array
		vertexShader.ID = glCreateShader(GL_VERTEX_SHADER);
		vertexShader.shaderType = Shader::VERTEX_SHADER;

		// Load some text from a file...
		if (!m_LoadSourceFromFile(vertexShader.fileName, vertexShader.vecSource, errorText))
		{
			m_lastError = errorText;
			return false;
		}

		errorText = "";
		if (!m_CompileShaderFromSource(vertexShader.ID, vertexShader.vecSource, errorText))
		{
			m_lastError = errorText;
			return false;
		}

		fragmentShader.ID = glCreateShader(GL_FRAGMENT_SHADER);
		fragmentShader.shaderType = Shader::FRAGMENT_SHADER;
		if (!m_LoadSourceFromFile(fragmentShader.fileName, fragmentShader.vecSource, errorText))
		{
			m_lastError = errorText;
			return false;
		}

		if (!m_CompileShaderFromSource(fragmentShader.ID, fragmentShader.vecSource, errorText))
		{
			m_lastError = errorText;
			return false;
		}

		ShaderProgram* curProgram = new ShaderProgram();
		curProgram->ID = glCreateProgram();

		glAttachShader(curProgram->ID, vertexShader.ID);
		glAttachShader(curProgram->ID, fragmentShader.ID);
		glLinkProgram(curProgram->ID);

		// Was there a link error? 
		errorText = "";
		if (m_WasThereALinkError(curProgram->ID, errorText))
		{
			std::stringstream ssError;
			ssError << "Shader program link error: ";
			ssError << errorText;
			m_lastError = ssError.str();
			return false;
		}

		// At this point, shaders are compiled and linked into a program

		curProgram->name = shaderProgram;

		// Add the shader to the map
		m_IDToShaderProgram[curProgram->ID] = curProgram;
		// Save to other map, too
		m_shaderProgramNameToID[curProgram->name] = curProgram->ID;

		return true;
	}
}
