#pragma once

#include <vector>
#include <string>
#include <functional>
#include <map>

#include "iSystem.h"

namespace MyEngine
{
    class SystemBuilder 
    {
    public:
        using SystemFactory = std::function<iSystem* ()>;

        // Register system names and corresponding factory functions.
        // Engine systems are already registered, see SystemHeaders for the list.
        static void RegisterSystem(const std::string& name, SystemFactory factory);

        // Create a system based on the provided name
        static iSystem* CreateSystem(const std::string& name);

    private:
        static std::map<std::string, SystemFactory> m_systemFactories;
    };
}

