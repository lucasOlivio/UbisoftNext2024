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
        float minSpeed = 1.0f;
        deltaTime = deltaTime/ 1000.0f;
        // Update velocity and position
        for (Entity entityId : SceneView<TransformComponent, MovementComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            MovementComponent* pMovement = pScene->Get<MovementComponent>(entityId);

            // Clip acceleration to max
            float currentAcceleration = pMovement->acceleration.Length();
            if (currentAcceleration > pMovement->maxAcceleration)
            {
                pMovement->acceleration = pMovement->acceleration.Normalize() * pMovement->maxAcceleration;
            }

            Vec2 newVelocity = pMovement->velocity + (pMovement->acceleration * deltaTime);
            Vec2 dragForce = newVelocity * -(pMovement->drag * deltaTime);
            pMovement->velocity = newVelocity + dragForce;

            // Clip velocity between min and max
            float currentSpeed = pMovement->velocity.Length();
            if (currentSpeed > pMovement->maxSpeed)
            {
                pMovement->velocity = pMovement->velocity.Normalize() * pMovement->maxSpeed;
            }
            else if (currentSpeed <= minSpeed)
            {
                pMovement->velocity = Vec2(0.0f, 0.0f);
            }

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
