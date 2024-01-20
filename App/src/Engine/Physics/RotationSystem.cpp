#include "stdafx.h"

#include "RotationSystem.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/Components.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

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
        deltaTime = deltaTime / 1000.0f;
        // Update velocity and position
        for (Entity entityId : SceneView<TransformComponent, RotationComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            RotationComponent* pRotation = pScene->Get<RotationComponent>(entityId);

            pRotation->velocity = pRotation->velocity + (pRotation->acceleration * deltaTime);
            pTransform->angle = pTransform->angle + (pRotation->velocity * deltaTime);

            if (pTransform->angle > 359.9f)
            {
                pTransform->angle = 0.0f;
            }
            else if (pTransform->angle < 0.0f)
            {
                pTransform->angle = 359.0f;
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
