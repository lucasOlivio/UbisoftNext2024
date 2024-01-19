#include "pch.h"

#include "TextureManagerLocator.h"

namespace MyEngine
{
	NullTextureManager TextureManagerLocator::m_nullService = NullTextureManager();
	iTextureManager* TextureManagerLocator::m_textureManager = &(TextureManagerLocator::m_nullService);

	iTextureManager* TextureManagerLocator::Get() { return m_textureManager; }

	void TextureManagerLocator::Set(iTextureManager* textureManager)
	{
		if (textureManager == nullptr)
		{
			m_textureManager = &m_nullService;
		}
		else
		{
			m_textureManager = textureManager;
		}
	}
}