#include "stdafx.h"

#include "RotationSystem.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/Components.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Utils/Math.h"

namespace MyEngine
{
    void RotationSystem::Init()
    {
    }

    void RotationSystem::Start(Scene* pScene)
    {
    }

    void RotationSystem::Update(Scene* pScene, float deltaTime)
    {
        float minSpeed = 0.02f;
        float fullCircle = Math::DegreesToRadians(360.0f);
        deltaTime = deltaTime/ 1000.0f;
        // Update velocity and position
        for (Entity entityId : SceneView<TransformComponent, RotationComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            RotationComponent* pRotation = pScene->Get<RotationComponent>(entityId);


            // Clip acceleration to max
            int clockwiseAcceleration = Math::Sign<float>(pRotation->acceleration);
            float currentAcceleration = clockwiseAcceleration * pRotation->acceleration;
            if (currentAcceleration > pRotation->maxAcceleration)
            {
                pRotation->acceleration = pRotation->maxAcceleration * clockwiseAcceleration;
            }

            float newVelocity = pRotation->velocity + (pRotation->acceleration * deltaTime);
            float dragForce = newVelocity * -(pRotation->drag * deltaTime);
            pRotation->velocity = newVelocity + dragForce;

            // Clip velocity between min and max
            int clockwiseVelocity = Math::Sign<float>(pRotation->velocity);
            float currentVelocity = clockwiseVelocity * pRotation->velocity;
            if (currentVelocity > pRotation->maxSpeed)
            {
                pRotation->velocity = pRotation->maxSpeed * clockwiseVelocity;
            }
            else if (currentVelocity <= minSpeed)
            {
                pRotation->velocity = 0.0f;
            }

            pTransform->angle = pTransform->angle + (pRotation->velocity * deltaTime);

            // Clip angle between 0 degrees and 360 degrees
            if (pTransform->angle > fullCircle)
            {
                pTransform->angle = 0.0f;
            }
            else if (pTransform->angle < 0.0f)
            {
                pTransform->angle = fullCircle - 0.01f;
            }
        }
    }

    void RotationSystem::Render(Scene* pScene)
    {
    }

    void RotationSystem::End(Scene* pScene)
    {
    }

    void RotationSystem::Shutdown()
    {
    }
}
