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

            float newVelocity = pRotation->velocity + (pRotation->acceleration * deltaTime);
            float dragForce = newVelocity * -(pRotation->drag * deltaTime);
            pRotation->velocity = newVelocity + dragForce;

            float absVelocity = Math::Sign<float>(pRotation->velocity) * pRotation->velocity;
            if (absVelocity > pRotation->maxSpeed)
            {
                pRotation->velocity = pRotation->maxSpeed;
            }
            else if (absVelocity <= minSpeed)
            {
                pRotation->velocity = 0.0f;
            }

            pTransform->angle = pTransform->angle + (pRotation->velocity * deltaTime);

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
