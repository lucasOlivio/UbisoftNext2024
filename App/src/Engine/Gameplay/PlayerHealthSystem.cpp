#include "stdafx.h"

#include "PlayerHealthSystem.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/SingletonComponents/GameplayLocator.h"

#include "Engine/Events/EventBusLocator.hpp"

#include "Engine/Utils/GameplayUtils.h"

namespace MyEngine
{
    void PlayerHealthSystem::Init()
    {
        // Subscribe to enter collision event
        iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();

        pEventBus->Subscribe(eCollisionEvents::COLLISION_ENTER, OnCollision);
    }

    void PlayerHealthSystem::Start(Scene* pScene)
    {
    }

    void PlayerHealthSystem::Update(Scene* pScene, float deltaTime)
    {
        GameStateComponent* pState = GameplayLocator::GetGameState();
        if (pState->currState == eGameStates::GAMEOVER)
        {
            return;
        }

        Entity playerId = GameplayUtils::GetPlayerId(pScene);
        PlayerComponent* pPlayer = pScene->Get<PlayerComponent>(playerId);
        if (pPlayer->health > 0)
        {
            return;
        }

        pState->currState = eGameStates::GAMEOVER;
    }

    void PlayerHealthSystem::Render(Scene* pScene)
    {
    }

    void PlayerHealthSystem::End(Scene* pScene)
    {
    }

    void PlayerHealthSystem::Shutdown()
    {
        // Subscribe to enter collision event
        iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();

        pEventBus->Unsubscribe(eCollisionEvents::COLLISION_ENTER, OnCollision);
    }

    void PlayerHealthSystem::OnCollision(const CollisionEnterEvent& event)
    {
        Scene* pScene = event.collisionData.pScene;
        Entity entityActive = event.collisionData.entityActive;
        Entity entityPassive = event.collisionData.entityPassive;

        PlayerComponent* pPlayer = pScene->Get<PlayerComponent>(entityActive);
        if (!pPlayer)
        {
            // Not colliding against player
            return;
        }

        if (pPlayer->health == 0)
        {
            return;
        }

        EnemyComponent* pEnemy = pScene->Get<EnemyComponent>(entityPassive);
        if (!pEnemy)
        {
            // Unit doesnt do damages
            return;
        }

        pPlayer->health -= pEnemy->damage;
    }
}
