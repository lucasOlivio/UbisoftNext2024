#include "stdafx.h"

#include "ZombieSpawnSystem.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/SingletonComponents/Components.h"
#include "Engine/ECS/SingletonComponents/GameplayLocator.h"

#include "Engine/Utils/GameplayUtils.h"
#include "Engine/Utils/Random.h"

namespace MyEngine
{
    const float ZOMBIE_SPAWN_DISTANCE = 650.0f;
    const float ZOMBIE_SPAWN_RATE = 0.2f;
    const float ZOMBIE_INITIAL_SPEED = 75.0f;
    const int MAX_ZOMBIES = 200;

    void ZombieSpawnSystem::Init()
    {
    }

    void ZombieSpawnSystem::Start(Scene* pScene)
    {
        ZombieSpawnComponent* pZSpawn = GameplayLocator::GetZombieSpawn();
        pZSpawn->spawnRate = ZOMBIE_SPAWN_RATE;
        pZSpawn->lastSpawn = 0.0f;
        pZSpawn->totalZombies = 0;
        pZSpawn->maxZombies = MAX_ZOMBIES;
        pZSpawn->spawnDistance = ZOMBIE_SPAWN_DISTANCE;
        pZSpawn->initialZombieSpeed = ZOMBIE_INITIAL_SPEED;
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

        pZSpawn->aliveZombies++;
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
