#include "stdafx.h"

#include "SpriteManager.h"

#include <algorithm>

namespace MyEngine
{
    using mapConstIt = std::unordered_map<std::string, CSimpleSprite*>::const_iterator;
    using pairSprites = std::pair<const std::string, CSimpleSprite*>;

    SpriteManager::~SpriteManager()
    {
        std::for_each(m_mapSprite.begin(), m_mapSprite.end(), 
                     [](pairSprites& pair) { delete pair.second; });
        m_mapSprite.clear();
    }

    CSimpleSprite* SpriteManager::CreateSprite(const char* name, int cols, int rows)
    {
        CSimpleSprite* pSprite = GetSpriteInfo(name);
        if (pSprite)
        {
            // Sprite already exists
            return pSprite;
        }

        pSprite = App::CreateSprite(name, cols, rows);
        m_mapSprite.emplace(name, pSprite);

        return pSprite;
    }

    CSimpleSprite* SpriteManager::GetSpriteInfo(const std::string& name)
    {
        mapConstIt it = m_mapSprite.find(name);
        if (it == m_mapSprite.end())
        {
            // Not found
            return nullptr;
        }

        return it->second;
    }

    void SpriteManager::DeleteSprite(const std::string& name)
    {
        mapConstIt it = m_mapSprite.find(name);
        if (it == m_mapSprite.end())
        {
            return;
        }

        m_mapSprite.erase(it);
        delete it->second;
    }
}
