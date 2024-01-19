#pragma once

#include "NullTextureManager.hpp"
#include "iTextureManager.h"

namespace MyEngine
{
	class TextureManagerLocator
	{
	public:
		static iTextureManager* Get();

		static void Set(iTextureManager* textureManager);

	private:
		static iTextureManager* m_textureManager;
		static NullTextureManager m_nullService;
	};
}
