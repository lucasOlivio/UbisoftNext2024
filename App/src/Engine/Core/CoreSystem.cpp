#include "stdafx.h"

#include "CoreSystem.h"
#include "Engine/Core/EngineLocator.h"
#include "Engine/Core/SystemFactory.h"

#include "Engine/ECS/SceneView.hpp"

#include "Engine/Events/EventBusLocator.hpp"

namespace MyEngine
{
    std::vector<std::string> gameRunningSystems = 
    {
        // Physics systems
        "MovementSystem",
        "RotationSystem",
        "GridBroadPhaseSystem",
        "CollisionSystem",
        // Gameplay systems
        "PlayerControllerSystem",
        "TruckControllerSystem",
        "ZombieSpawnSystem",
        "FollowTargetSystem",
        "DestructionSystem",
        "ScoreSystem",
        "PlayerHealthSystem",
        "PlayerUISystem"
    };

    void CoreSystem::Init()
    {
        // Subscribe to enter collision event
        iEventBus<eGameStateEvents, GameStartedEvent>* pStartedBus = EventBusLocator<eGameStateEvents, GameStartedEvent>::Get();
        iEventBus<eGameStateEvents, GameRunningEvent>* pRunningBus = EventBusLocator<eGameStateEvents, GameRunningEvent>::Get();
        iEventBus<eGameStateEvents, GameLevelUpEvent>* pLevelUpBus = EventBusLocator<eGameStateEvents, GameLevelUpEvent>::Get();
        iEventBus<eGameStateEvents, GameOverEvent>* pGameOverBus = EventBusLocator<eGameStateEvents, GameOverEvent>::Get();

        pStartedBus->Subscribe(eGameStateEvents::GAME_STARTED, OnStart);
        pRunningBus->Subscribe(eGameStateEvents::GAME_RUNNING, OnRunning);
        pLevelUpBus->Subscribe(eGameStateEvents::GAME_LEVELUP, OnLevelUp);
        pGameOverBus->Subscribe(eGameStateEvents::GAME_OVER, OnGameOver);
    }

    void CoreSystem::Start(Scene* pScene)
    {
    }

    void CoreSystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void CoreSystem::Render(Scene* pScene)
    {
    }

    void CoreSystem::End(Scene* pScene)
    {
    }

    void CoreSystem::Shutdown()
    {
    }

    void CoreSystem::OnStart(const GameStartedEvent& event)
    {
    }

    void CoreSystem::OnRunning(const GameRunningEvent& event)
    {
        Engine* pEngine = EngineLocator::Get();
        for (std::string systemName : gameRunningSystems)
        {
            pEngine->AddSystem(SystemFactory::CreateSystem(systemName), event.pScene);
        }
    }

    void CoreSystem::OnLevelUp(const GameLevelUpEvent& event)
    {
    }

    void CoreSystem::OnGameOver(const GameOverEvent& event)
    {
        Engine* pEngine = EngineLocator::Get();
        for (std::string systemName : gameRunningSystems)
        {
            pEngine->RemoveSystem(systemName, event.pScene);
        }
    }
}
