#include "stdafx.h"

#include "DestructionSystem.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/SingletonComponents/GameplayLocator.h"

#include "Engine/Events/EventBusLocator.hpp"

#include "Engine/Utils/TransformUtils.h"

namespace MyEngine
{
    void DestructionSystem::Init()
    {
    }

    void DestructionSystem::Start(Scene* pScene)
    {
        // Subscribe to enter collision event
        iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();

        pEventBus->Subscribe(eCollisionEvents::COLLISION_ENTER, OnCollision);
    }

    void DestructionSystem::Update(Scene* pScene, float deltaTime)
    {
        // Check if projectiles went off screen to destroy
        for (Entity entityId : SceneView<TransformComponent, ProjectileComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);

            bool isOutside = TransformUtils::IsOutsideWindow(pTransform->worldPosition.x, pTransform->worldPosition.y);
            if (isOutside)
            {
                pScene->RemoveEntity(entityId);
            }
        }
    }

    void DestructionSystem::Render(Scene* pScene)
    {
    }

    void DestructionSystem::End(Scene* pScene)
    {
        // Subscribe to enter collision event
        iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();

        pEventBus->Unsubscribe(eCollisionEvents::COLLISION_ENTER, OnCollision);
    }

    void DestructionSystem::Shutdown()
    {
    }

    void DestructionSystem::OnCollision(const CollisionEnterEvent& event)
    {
        Scene* pScene = event.collisionData.pScene;
        Entity entityActive = event.collisionData.entityActive;
        Entity entityPassive = event.collisionData.entityPassive;

        TagComponent* pTagActive = pScene->Get<TagComponent>(entityActive);
        if (pTagActive && pTagActive->name != "Player")
        {
            pScene->RemoveEntity(entityActive);
        }

        pScene->RemoveEntity(entityPassive);

        TagComponent* pTagPassive = pScene->Get<TagComponent>(entityPassive);
        if (pTagPassive->name == "Zombie")
        {
            ZombieSpawnComponent* pZSpawn = GameplayLocator::GetZombieSpawn();
            pZSpawn->aliveZombies--;
        }
    }
}
