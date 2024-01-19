#pragma once

#include "Engine/Core/types.h"
#include <string>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

namespace MyEngine
{
	class iShaderProgram
	{
	public:
		virtual ~iShaderProgram() {};

		// Uses the current shader program to retrieve the given uniform location
		// (-1 if not found)
		virtual int GetUL(const char* ulName) = 0;
		// Uses the current shader program to retrieve the given attribute location
		// (-1 if not found)
		virtual int GetAL(const char* alName) = 0;

		virtual void SetUniformFloat(const char* variableName, float value) = 0;
		virtual void SetUniformInt(const char* variableName, int value) = 0;
		virtual void SetUniformMatrix4f(const char* variableName, const glm::mat4& value) = 0;
		virtual void SetUniformVec4(const char* variableName, const glm::vec4& value) = 0;
		virtual void SetUniformVec2(const char* variableName, const glm::vec2& value) = 0;

		// Sets to draw only line or to fill the polygon
		virtual void IsWireframe(bool isWireframe) = 0;

		// Bind texture to the unit
		virtual void BindTexture(uint textureUnit, uint textureId) = 0;
	};
}
