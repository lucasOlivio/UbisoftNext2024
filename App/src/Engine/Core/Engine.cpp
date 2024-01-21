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

    void Engine::RemoveSystem(std::string systemName, Scene* pScene)
    {
        for (int i = 0; i < m_systems.size(); i++)
        {
            if (m_systems[i]->SystemName() != systemName)
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

        m_pEventBusGameStarted = new EventBus<eGameStateEvents, GameStartedEvent>();
        m_pEventBusGameRunning = new EventBus<eGameStateEvents, GameRunningEvent>();
        m_pEventBusGameLevelUp = new EventBus<eGameStateEvents, GameLevelUpEvent>();
        m_pEventBusGameOver = new EventBus<eGameStateEvents, GameOverEvent>();

        EventBusLocator<eGameStateEvents, GameStartedEvent>::Set(m_pEventBusGameStarted);
        EventBusLocator<eGameStateEvents, GameRunningEvent>::Set(m_pEventBusGameRunning);
        EventBusLocator<eGameStateEvents, GameLevelUpEvent>::Set(m_pEventBusGameLevelUp);
        EventBusLocator<eGameStateEvents, GameOverEvent>::Set(m_pEventBusGameOver);
    }

    void Engine::Update(float deltaTime)
    {
        for (int i = 0; i < m_systems.size(); i++)
        {
            m_systems[i]->Update(m_pScene, deltaTime);
        }

        // Remove entities marked
        m_pScene->DestroyEntities();
    }

    void Engine::Render()
    {
        for (int i = 0; i < m_systems.size(); i++)
        {
            m_systems[i]->Render(m_pScene);
        }
    }

    void Engine::Shutdown()
    {
        EndSystems(m_pScene);

        ShutdownSystems();

        // Delete singleton components
        CoreLocator::Clear();
        PhysicsLocator::Clear();
        GameplayLocator::Clear();
        DebugLocator::Clear();

        // Delete event bus
        delete m_pEventBusCollision;

        delete m_pEventBusGameStarted;
        delete m_pEventBusGameRunning;
        delete m_pEventBusGameLevelUp;
        delete m_pEventBusGameOver;

        delete m_pScene;
    }

    void Engine::StartSystems(Scene* pScene)
    {
        for (int i = 0; i < m_systems.size(); i++)
        {
            m_systems[i]->Start(m_pScene);
        }
    }

    void Engine::EndSystems(Scene* pScene)
    {
        for (int i = 0; i < m_systems.size(); i++)
        {
            m_systems[i]->End(m_pScene);
        }
    }

    void Engine::ShutdownSystems()
    {
        for (int i = 0; i < m_systems.size(); i++)
        {
            m_systems[i]->Shutdown();
        }
    }

    Scene* Engine::GetScene()
    {
        return m_pScene;
    }
}
