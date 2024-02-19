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
        // Subscribe to level up event
        iEventBus<eGameStateEvents, GameLevelUpEvent>* pLeveUpBus = EventBusLocator<eGameStateEvents, GameLevelUpEvent>::Get();
        iEventBus<eGameStateEvents, GameOverEvent>* pEventBus = EventBusLocator<eGameStateEvents, GameOverEvent>::Get();

        pLeveUpBus->Subscribe(eGameStateEvents::GAME_LEVELUP, OnLevelUp);
        pEventBus->Subscribe(eGameStateEvents::GAME_OVER, OnGameOver);
    }

    void LevelSystem::Start(Scene* pScene)
    {
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

        if (pState->currState == eGameStates::RUNNING)
        {
            ZombieSpawnComponent* pZSpawn = GameplayLocator::GetZombieSpawn();

            if (pZSpawn->aliveZombies == 0 
                && pZSpawn->totalZombies > 0
                && pZSpawn->totalZombies == pZSpawn->maxZombies)
            {
                pState->currState = eGameStates::LEVELUP;
            }
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
        // Subscribe to level up event
        iEventBus<eGameStateEvents, GameLevelUpEvent>* pLeveUpBus = EventBusLocator<eGameStateEvents, GameLevelUpEvent>::Get();
        iEventBus<eGameStateEvents, GameOverEvent>* pEventBus = EventBusLocator<eGameStateEvents, GameOverEvent>::Get();

        pLeveUpBus->Unsubscribe(eGameStateEvents::GAME_LEVELUP, OnLevelUp);
        pEventBus->Unsubscribe(eGameStateEvents::GAME_OVER, OnGameOver);
    }

    void LevelSystem::OnLevelUp(const GameLevelUpEvent& event)
    {
        Scene* pScene = event.pScene;
        float diffRate = 1.1f; // Increase zombies and ammo by 10%
        Entity playerId = GameplayUtils::GetPlayerId(pScene);

        // Increase player ammo
        PlayerComponent* pPlayer = pScene->Get<PlayerComponent>(playerId);
        pPlayer->maxAmmo *= diffRate;

        // Reset zombie count and increase difficulty
        ZombieSpawnComponent* pZSpawn = GameplayLocator::GetZombieSpawn();
        pZSpawn->spawnRate *= (2.0f - diffRate); // Decrease spawn rate by same proportion
        pZSpawn->maxZombies *= diffRate;
        pZSpawn->totalZombies = 0;

        // Health and ammo reffils
        Vec2 halfpos = Vec2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);
        GameplayUtils::CreateHealthPack(pScene, Vec2(halfpos.x + 50.f, halfpos.y));
        GameplayUtils::CreateBulletPack(pScene, Vec2(halfpos.x - 50.f, halfpos.y));
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
