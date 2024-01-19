#include "pch.h"

#include "SystemBuilder.h"

#include "Engine/Core/WindowFrameSystem.h"
#include "Engine/Core/TransformParentSystem.h"
#include "Engine/Core/InputSystem.h"
#include "Engine/Core/StateSystem.h"

#include "Engine/Graphics/Shaders/ShaderSystem.h"
#include "Engine/Graphics/UI/BaseUISystem.h"
#include "Engine/Graphics/CameraSystem.h"
#include "Engine/Graphics/WindowSystem.h"
#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/Lights/LightSystem.h"

#include "Engine/Physics/MovementSystem.h"
#include "Engine/Physics/RotationSystem.h"
#include "Engine/Physics/GravitySystem.h"
#include "Engine/Physics/BroadPhase/GridBroadPhaseSystem.h"
#include "Engine/Physics/NarrowPhase/CollisionSystem.h"
#include "Engine/Physics/RegisterCollisionSystem.h"

#include "Engine/Debug/DebugSystem.h"
#include "Engine/Debug/DrawGridSystem.h"
#include "Engine/Debug/DrawCollisionSystem.h"

namespace MyEngine
{
    std::map<std::string, SystemBuilder::SystemFactory> SystemBuilder::m_systemFactories
    {
        // Any other system from engine should come into this map
        // 
        // Core Systems
        {"WindowFrameSystem", []() { return new WindowFrameSystem; }},
        {"TransformParentSystem", []() { return new TransformParentSystem; }},
        {"InputSystem", []() { return new InputSystem; }},
        {"StateSystem", []() { return new StateSystem; }},
        // Graphics systems
        {"WindowSystem", []() { return new WindowSystem; }},
        {"BaseUISystem", []() { return new BaseUISystem; }},
        {"ShaderSystem", []() { return new ShaderSystem; }},
        {"CameraSystem", []() { return new CameraSystem; }},
        {"RenderSystem", []() { return new RenderSystem; }},
        {"LightSystem", []() { return new LightSystem; }},
        // Physics systems
        {"MovementSystem", []() { return new MovementSystem; }},
        {"RotationSystem", []() { return new RotationSystem; }},
        {"GravitySystem", []() { return new GravitySystem; }},
        {"GridBroadPhaseSystem", []() { return new GridBroadPhaseSystem; }},
        {"CollisionSystem", []() { return new CollisionSystem; }},
        {"RegisterCollisionSystem", []() { return new RegisterCollisionSystem; }},
        // Debug Systems
        {"DebugSystem", []() { return new DebugSystem; }},
        {"DrawGridSystem", []() { return new DrawGridSystem; }},
        {"DrawCollisionSystem", []() { return new DrawCollisionSystem; }},
    };

    void SystemBuilder::RegisterSystem(const std::string& name, SystemFactory factory)
    {
        m_systemFactories[name] = factory;
    }

    iSystem* SystemBuilder::CreateSystem(const std::string& name)
    {
        auto it = m_systemFactories.find(name);
        if (it != m_systemFactories.end())
        {
            // Call the factory function to create an instance
            return it->second();
        }
        else
        {
            std::cerr << "Error: Unknown system '" << name << "'" << std::endl;
            return nullptr;
        }
    }


}
