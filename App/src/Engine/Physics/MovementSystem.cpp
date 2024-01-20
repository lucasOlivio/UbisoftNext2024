#include "stdafx.h"

#include "MovementSystem.h"

#include "Engine/ECS/SceneView.hpp"

namespace MyEngine
{
    void MovementSystem::Init()
    {
    }

    void MovementSystem::Start(Scene* pScene)
    {
    }

    void MovementSystem::Update(Scene* pScene, float deltaTime)
    {
        deltaTime = deltaTime / 1000.0f;
        // Update velocity and position
        for (Entity entityId : SceneView<TransformComponent, MovementComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            MovementComponent* pMovement = pScene->Get<MovementComponent>(entityId);

            pMovement->velocity = pMovement->velocity + (pMovement->acceleration * deltaTime);
            pTransform->position = pTransform->position + (pMovement->velocity * deltaTime);
        }
    }

    void MovementSystem::Render(Scene* pScene)
    {
    }

    void MovementSystem::End(Scene* pScene)
    {
    }

    void MovementSystem::Shutdown()
    {
    }
}
