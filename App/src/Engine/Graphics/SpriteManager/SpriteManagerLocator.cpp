#include "stdafx.h"

#include "SpriteManagerLocator.h"
#include "Engine/Graphics/SpriteManager/NullSpriteManager.h"

namespace MyEngine
{
    iSpriteManager* SpriteManagerLocator::m_pNullSpriteManager = new NullSpriteManager();
    iSpriteManager* SpriteManagerLocator::m_pSpriteManager = m_pNullSpriteManager;

    iSpriteManager* SpriteManagerLocator::GetSpriteManager()
    {
        return m_pSpriteManager;
    }

    void SpriteManagerLocator::SetSpriteManager(iSpriteManager* pSpriteManagerLocator)
    {
        if (pSpriteManagerLocator)
        {
            m_pSpriteManager = pSpriteManagerLocator;
        }
        else
        {
            m_pSpriteManager = m_pNullSpriteManager;
        }
    }
}
