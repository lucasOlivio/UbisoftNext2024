#include "stdafx.h"

#include "ZombieSpawnSystem.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/SingletonComponents/Components.h"
#include "Engine/ECS/SingletonComponents/GameplayLocator.h"

#include "Engine/Utils/GameplayUtils.h"
#include "Engine/Utils/Random.h"

#include <app.h>

namespace MyEngine
{
    void ZombieSpawnSystem::Init()
    {
    }

    void ZombieSpawnSystem::Start(Scene* pScene)
    {
        ZombieSpawnComponent* pZSpawn = GameplayLocator::GetZombieSpawn();
        pZSpawn->spawnRate = 0.5f;
        pZSpawn->lastSpawn = 0.0f;
        pZSpawn->totalZombies = 0;
        pZSpawn->maxZombies = 200;
        pZSpawn->spawnDistance = 650.0f;
        pZSpawn->initialZombieSpeed = 100.0f;
    }

    void ZombieSpawnSystem::Update(Scene* pScene, float deltaTime)
    {
        deltaTime = deltaTime / 1000.0f;
        ZombieSpawnComponent* pZSpawn = GameplayLocator::GetZombieSpawn();

        pZSpawn->lastSpawn += deltaTime;

        if (pZSpawn->lastSpawn < pZSpawn->spawnRate)
        {
            return;
        }

        if (pZSpawn->totalZombies >= pZSpawn->maxZombies)
        {
            return;
        }

        float halfWidth = APP_VIRTUAL_WIDTH / 2;
        float halfHeight = APP_VIRTUAL_HEIGHT / 2;

        uint32_t seed = (uint32_t)pZSpawn->totalZombies;
        Vec2 randomDir = Random::Vector2(seed, -1, 1);
        Vec2 normalizedDir = randomDir.Normalize();

        float randomX = (normalizedDir.x * pZSpawn->spawnDistance) + halfWidth;
        float randomY = (normalizedDir.y * pZSpawn->spawnDistance) + halfHeight;

        GameplayUtils::CreateZombie(pScene, Vec2(randomX, randomY), pZSpawn->initialZombieSpeed);

        pZSpawn->totalZombies++;
        pZSpawn->lastSpawn = 0.0f;
    }

    void ZombieSpawnSystem::Render(Scene* pScene)
    {
    }

    void ZombieSpawnSystem::End(Scene* pScene)
    {
    }

    void ZombieSpawnSystem::Shutdown()
    {
    }
}
