#include "pch.h"

#include "TransformParentSystem.h"
#include "Engine/ECS/Scene/SceneView.hpp"
#include "Engine/ECS/Components.h"
#include "Engine/Utils/TransformUtils.h"

namespace MyEngine
{
    void TransformParentSystem::Init()
    {
    }

    void TransformParentSystem::Start(Scene* pScene)
    {
    }

    void TransformParentSystem::Update(Scene* pScene, float deltaTime)
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
                pTransform->worldOrientation = pTransform->orientation;
                pTransform->worldScale = pTransform->scale;
                
                continue;
            }

            TransformComponent* pTransformParent = pScene->Get<TransformComponent>(pParent->parentId);

            if (!pTransformParent)
            {
                LOG_ERROR("Parent ID not found: " + std::to_string(pParent->parentId));
                continue;
            }

            glm::mat4 matParent = glm::mat4(1.0f);
            TransformUtils::GetTransform(pTransformParent->worldPosition, 
                                         pTransformParent->worldOrientation,
                                         pTransformParent->worldScale, 
                                         matParent);

            pTransform->worldPosition = matParent * glm::vec4(pTransform->position, 1.0f);
            pTransform->worldScale = pTransform->scale * pTransformParent->scale;
            pTransform->worldOrientation = pTransform->orientation * pTransformParent->worldOrientation;
        }
    }

    void TransformParentSystem::Render(Scene* pScene)
    {
    }

    void TransformParentSystem::End(Scene* pScene)
    {
    }

    void TransformParentSystem::Shutdown()
    {
    }
}
