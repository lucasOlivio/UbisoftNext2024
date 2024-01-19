#pragma once

#include "Engine/Graphics/opengl.h"

namespace MyEngine
{
	enum eTextureType
	{
		COLOR = 0,
		TRANSPARENCY = 4,
		HEIGHTMAP = 8,
		NORMAL = 12,
		DISCARD = 16,
		CUBE = 20,
		SPECULAR = 24
	};

	struct sSamplerInfo
	{
		GLint samplerRatioUL;
		GLint samplerToggleUL;
		GLint samplerUL;
		GLint samplerId;
	};
}
