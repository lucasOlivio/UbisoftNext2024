#pragma once

#include "Engine/Graphics/SpriteManager/iSpriteManager.h"

namespace MyEngine
{
    class SpriteManager : public iSpriteManager
    {
    public:
        virtual ~SpriteManager();

        CSimpleSprite* CreateSprite(const char* name, int cols, int rows);

        CSimpleSprite* GetSpriteInfo(const std::string& name);

        virtual void DeleteSprite(const std::string& name);

    private:
        std::unordered_map<std::string, CSimpleSprite*> m_mapSprite;
    };
}
