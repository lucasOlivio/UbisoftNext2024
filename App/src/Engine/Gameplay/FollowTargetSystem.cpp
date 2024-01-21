#include "stdafx.h"

#include "FollowTargetSystem.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/Components.h"

#include "Engine/Utils/TransformUtils.h"

namespace MyEngine
{
    void FollowTargetSystem::Init()
    {
    }

    void FollowTargetSystem::Start(Scene* pScene)
    {
    }

    void FollowTargetSystem::Update(Scene* pScene, float deltaTime)
    {
        deltaTime = deltaTime / 1000.0f;

        for (Entity entityId : SceneView<TransformComponent, MovementComponent, FollowTargetComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            MovementComponent* pMovement = pScene->Get<MovementComponent>(entityId);
            FollowTargetComponent* pFollowTarget = pScene->Get<FollowTargetComponent>(entityId);

            TransformComponent* pTransformTarget = pScene->Get<TransformComponent>(pFollowTarget->entityToFollow);
            if (!pTransformTarget)
            {
                continue;
            }

            Vec2 direction = pTransformTarget->worldPosition - pTransform->worldPosition;
            Vec2 directionNormal = direction.Normalize();

            // Update facing direction
            float angle = FORWARD_VECTOR.Angle(direction);
            pTransform->angle = angle;

            // Update movement direction
            float currSpeed = pMovement->velocity.Length();
            pMovement->velocity = directionNormal * currSpeed;
        }
    }

    void FollowTargetSystem::Render(Scene* pScene)
    {
    }

    void FollowTargetSystem::End(Scene* pScene)
    {
    }

    void FollowTargetSystem::Shutdown()
    {
    }
}
