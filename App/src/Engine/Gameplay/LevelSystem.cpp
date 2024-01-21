#include "stdafx.h"

#include "LevelSystem.h"

#include "Engine/Core/InputProperties.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/Components.h"
#include "Engine/ECS/SingletonComponents/GameplayLocator.h"

#include "Engine/Events/EventBusLocator.hpp"

#include "Engine/Utils/GameplayUtils.h"

#include <app.h>

namespace MyEngine
{
    void LevelSystem::Init()
    {
    }

    void LevelSystem::Start(Scene* pScene)
    {
        // Subscribe to level up event
        iEventBus<eGameStateEvents, GameLevelUpEvent>* pLeveUpBus = EventBusLocator<eGameStateEvents, GameLevelUpEvent>::Get();
        iEventBus<eGameStateEvents, GameOverEvent>* pEventBus = EventBusLocator<eGameStateEvents, GameOverEvent>::Get();

        pLeveUpBus->Subscribe(eGameStateEvents::GAME_LEVELUP, OnLevelUp);
        pEventBus->Subscribe(eGameStateEvents::GAME_OVER, OnGameOver);
    }

    void LevelSystem::Update(Scene* pScene, float deltaTime)
    {
        GameStateComponent* pState = GameplayLocator::GetGameState();

        if ((pState->currState == eGameStates::STARTED 
            || pState->currState == eGameStates::GAMEOVER)
            && App::IsKeyPressed(eKeyCodes::E))
        {
            pState->currState = eGameStates::RUNNING;
        }
    }

    void LevelSystem::Render(Scene* pScene)
    {
    }

    void LevelSystem::End(Scene* pScene)
    {
    }

    void LevelSystem::Shutdown()
    {
    }

    void LevelSystem::OnLevelUp(const GameLevelUpEvent& event)
    {
    }

    void LevelSystem::OnGameOver(const GameOverEvent& event)
    {
        // Clean all zombies/items/bullets from scene
        Scene* pScene = event.pScene;
        for (Entity entityId : SceneView<TagComponent>(*pScene))
        {
            TagComponent* pTag = pScene->Get<TagComponent>(entityId);
            if (pTag->name == "Player" || pTag->name == "Truck")
            {
                continue;
            }

            pScene->RemoveEntity(entityId);
        }

        // Reset player position and stats
        Entity playerId = GameplayUtils::GetPlayerId(pScene);
        ParentComponent* pParent = pScene->Get<ParentComponent>(playerId);
        Entity truckId = pParent->parentId;

        PlayerComponent* pPlayer = pScene->Get<PlayerComponent>(playerId);
        TransformComponent* pTransformPlayer = pScene->Get<TransformComponent>(playerId);
        TransformComponent* pTransformTruck = pScene->Get<TransformComponent>(truckId);

        pTransformPlayer->angle = 0.0f;

        pTransformTruck->position = Vec2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);
        pTransformTruck->angle = 0.0f;

        pPlayer->health = pPlayer->maxHealth;
        pPlayer->currentAmmo = pPlayer->maxAmmo;
        pPlayer->lastFire = pPlayer->fireRate;
        pPlayer->score = 0;

        // Reset zombie count
        ZombieSpawnComponent* pZSpawn = GameplayLocator::GetZombieSpawn();
        pZSpawn->lastSpawn = pZSpawn->spawnRate;
        pZSpawn->totalZombies = 0;
    }
}
