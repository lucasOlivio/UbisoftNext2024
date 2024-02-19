#include "stdafx.h"

#include "ItemSystem.h"

#include "Engine/ECS/SceneView.hpp"

#include "Engine/Events/EventBusLocator.hpp"

#include "Engine/Utils/GameplayUtils.h"

namespace MyEngine
{
    void ItemSystem::Init()
    {
        // Subscribe to enter collision event
        iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();

        pEventBus->Subscribe(eCollisionEvents::COLLISION_ENTER, OnCollision);
    }

    void ItemSystem::Start(Scene* pScene)
    {
    }

    void ItemSystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void ItemSystem::Render(Scene* pScene)
    {
    }

    void ItemSystem::End(Scene* pScene)
    {
    }

    void ItemSystem::Shutdown()
    {
        // Subscribe to enter collision event
        iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();

        pEventBus->Unsubscribe(eCollisionEvents::COLLISION_ENTER, OnCollision);
    }

    void ItemSystem::OnCollision(const CollisionEnterEvent& event)
    {
        Scene* pScene = event.collisionData.pScene;
        Entity entityActive = event.collisionData.entityActive;
        Entity entityPassive = event.collisionData.entityPassive;

        TagComponent* pTagActive = pScene->Get<TagComponent>(entityActive);
        TagComponent* pTagPassive = pScene->Get<TagComponent>(entityPassive);
        if (pTagPassive->name != "Item")
        {
            return;
        }

        Entity playerId = GameplayUtils::GetPlayerId(pScene);
        PlayerComponent* pPlayer = pScene->Get<PlayerComponent>(playerId);
        ItemComponent* pItem = pScene->Get<ItemComponent>(entityPassive);

        if (pItem->refilAmmo)
        {
            pPlayer->currentAmmo = pPlayer->maxAmmo;
        }

        if (pItem->refilHealth)
        {
            pPlayer->health = pPlayer->maxHealth;
        }
    }
}
