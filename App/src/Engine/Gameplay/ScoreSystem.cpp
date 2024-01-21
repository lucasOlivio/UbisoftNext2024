#include "stdafx.h"

#include "ScoreSystem.h"

#include "Engine/ECS/SceneView.hpp"

#include "Engine/Events/EventBusLocator.hpp"

#include "Engine/Utils/GameplayUtils.h"

namespace MyEngine
{
    void ScoreSystem::Init()
    {
    }

    void ScoreSystem::Start(Scene* pScene)
    {
        // Subscribe to enter collision event
        iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();

        pEventBus->Subscribe(eCollisionEvents::COLLISION_ENTER, OnCollision);
    }

    void ScoreSystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void ScoreSystem::Render(Scene* pScene)
    {
    }

    void ScoreSystem::End(Scene* pScene)
    {
    }

    void ScoreSystem::Shutdown()
    {
    }

    void ScoreSystem::OnCollision(const CollisionEnterEvent& event)
    {
        Scene* pScene = event.collisionData.pScene;
        Entity entityActive = event.collisionData.entityActive;
        Entity entityPassive = event.collisionData.entityPassive;

        PointComponent* pPoint = pScene->Get<PointComponent>(entityPassive);
        if (!pPoint)
        {
            // No points for this unit
            return;
        }

        Entity playerId = GameplayUtils::GetPlayerId(pScene);
        PlayerComponent* pPlayer = pScene->Get<PlayerComponent>(playerId);

        pPlayer->score += pPoint->points;
    }
}
