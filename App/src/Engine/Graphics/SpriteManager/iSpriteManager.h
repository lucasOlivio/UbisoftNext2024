#pragma once

#include <unordered_map>
#include <string>

#include <app.h>

namespace MyEngine
{
    class iSpriteManager
    {
    public:
        virtual ~iSpriteManager() {}

        virtual CSimpleSprite* CreateSprite(const char* name, int cols, int rows) = 0;
        virtual CSimpleSprite* GetSpriteInfo(const std::string& name) = 0;
        virtual void DeleteSprite(const std::string& name) = 0;
    };
}