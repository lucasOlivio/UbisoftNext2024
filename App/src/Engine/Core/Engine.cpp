#include "stdafx.h"

#include "Engine.h"

#include "Engine/Events/EventBus.hpp"
#include "Engine/Events/EventBusLocator.hpp"

#include "Engine/ECS/SingletonComponents/CoreLocator.h"
#include "Engine/ECS/SingletonComponents/DebugLocator.h"
#include "Engine/ECS/SingletonComponents/PhysicsLocator.h"
#include "Engine/ECS/SingletonComponents/GameplayLocator.h"

namespace MyEngine
{
    Engine::Engine()
    {
        m_pScene = new Scene();
    }

    Engine::~Engine()
    {
    }

    void Engine::AddSystem(iSystem* pSystem, Scene* pScene)
    {
        m_systems.push_back(pSystem);
        pSystem->Init();

        pSystem->Start(pScene);
    }

    void Engine::RemoveSystem(iSystem* pSystem, Scene* pScene)
    {
        for (int i = 0; i < m_systems.size(); i++)
        {
            if (m_systems[i] != pSystem)
            {
                continue;
            }

            iSystem* pDelSystem = m_systems[i];

            // Clean system before deleting
            pDelSystem->End(pScene);
            pDelSystem->Shutdown();

            m_systems.erase(m_systems.begin() + i);

            delete pDelSystem;
        }
    }

    void Engine::Init()
    {
        // Setting up events
        m_pEventBusCollision = new EventBus<eCollisionEvents, CollisionEnterEvent>();
        EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Set(m_pEventBusCollision);
    }

    void Engine::Update(float deltaTime)
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->Update(m_pScene, deltaTime);
        }

        // Remove entities marked
        m_pScene->DestroyEntities();
    }

    void Engine::Render()
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->Render(m_pScene);
        }
    }

    void Engine::Shutdown()
    {
        EndSystems(m_pScene);

        ShutdownSystems();

        for (iSystem* pSystem : m_systems)
        {
            delete pSystem;
        }

        // Delete singleton components
        CoreLocator::Clear();
        PhysicsLocator::Clear();
        GameplayLocator::Clear();
        DebugLocator::Clear();

        // Delete event bus
        delete m_pEventBusCollision;

        delete m_pScene;
    }

    void Engine::StartSystems(Scene* pScene)
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->Start(pScene);
        }
    }

    void Engine::EndSystems(Scene* pScene)
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->End(pScene);
        }
    }

    void Engine::ShutdownSystems()
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->Shutdown();
        }
    }

    Scene* Engine::GetScene()
    {
        return m_pScene;
    }
}
