#include "stdafx.h"

#include "DestructionSystem.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/SingletonComponents/Components.h"

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

            bool isOutside = TransformUtils::IsOutsideWindow(pTransform->position.x, pTransform->position.y);
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
    }

    void DestructionSystem::Shutdown()
    {
    }

    void DestructionSystem::OnCollision(const CollisionEnterEvent& event)
    {
        TagComponent* pTagA = event.collisionData.pScene->Get<TagComponent>(event.collisionData.entityA);
        if (pTagA && pTagA->name != "Player")
        {
            event.collisionData.pScene->RemoveEntity(event.collisionData.entityA);
        }

        TagComponent* pTagB = event.collisionData.pScene->Get<TagComponent>(event.collisionData.entityB);
        if (pTagB && pTagB->name != "Player")
        {
            event.collisionData.pScene->RemoveEntity(event.collisionData.entityB);
        }
    }
}
