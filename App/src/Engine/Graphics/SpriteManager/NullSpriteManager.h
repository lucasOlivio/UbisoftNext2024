#pragma once

#include "Engine/Graphics/SpriteManager/iSpriteManager.h"

#include "Engine/Utils/Log.h"

namespace MyEngine
{
    class NullSpriteManager : public iSpriteManager 
    {
    public:
        // Implementation of iSpriteManager interface
        CSimpleSprite* CreateSprite(const char* name, int cols, int rows) 
        {
            LOG_ERROR("Sprite manager not implemented!");
            return nullptr;
        }

        CSimpleSprite* GetSpriteInfo(const std::string& name) 
        {
            LOG_ERROR("Sprite manager not implemented!");
            return nullptr;
        }

        void DeleteSprite(const std::string& name)
        {
            LOG_ERROR("Sprite manager not implemented!");
            return;
        }
    };
}
