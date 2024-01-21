#pragma once

#include "Engine/Graphics/SpriteManager/iSpriteManager.h"

namespace MyEngine
{
	class SpriteManagerLocator
	{
	public:
		static iSpriteManager* GetSpriteManager();

		static void SetSpriteManager(iSpriteManager* pSpriteManager);

	private:
		static iSpriteManager* m_pSpriteManager;
		static iSpriteManager* m_pNullSpriteManager;
	};
}
