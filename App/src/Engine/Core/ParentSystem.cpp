#include "stdafx.h"

#include "ParentSystem.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/Components.h"

namespace MyEngine
{
    void ParentSystem::Init()
    {
    }

    void ParentSystem::Start(Scene* pScene)
    {
    }

    void ParentSystem::Update(Scene* pScene, float deltaTime)
    {
        // Update each local to world transforms
        for (Entity entityId : SceneView<TransformComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            ParentComponent* pParent = pScene->Get<ParentComponent>(entityId);

            if (!pParent)
            {
                // Entity have no parent so world and local transforms are the same
                pTransform->worldPosition = pTransform->position;
                pTransform->worldAngle = pTransform->angle;
                pTransform->worldScale = pTransform->scale;

                continue;
            }

            TransformComponent* pTransformParent = pScene->Get<TransformComponent>(pParent->parentId);

            if (!pTransformParent)
            {
                LOG_ERROR("Parent ID not found: " + std::to_string(pParent->parentId));
                continue;
            }

            pTransform->worldPosition = pTransform->position + pTransformParent->worldPosition;
            pTransform->worldAngle = pTransform->angle + pTransformParent->worldAngle;
            pTransform->worldScale = pTransform->scale + pTransformParent->worldScale;
        }
    }

    void ParentSystem::Render(Scene* pScene)
    {
    }

    void ParentSystem::End(Scene* pScene)
    {
    }

    void ParentSystem::Shutdown()
    {
    }
}
