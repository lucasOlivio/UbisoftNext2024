#include "stdafx.h"

#include "ProjectileSystem.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/SingletonComponents/Components.h"

#include "Engine/Utils/TransformUtils.h"

namespace MyEngine
{
    void ProjectileSystem::Init()
    {
    }

    void ProjectileSystem::Start(Scene* pScene)
    {
    }

    void ProjectileSystem::Update(Scene* pScene, float deltaTime)
    {
        for (Entity entityId : SceneView<TransformComponent, ProjectileComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);

            bool isOutside = TransformUtils::IsOutsideWindow(pTransform->position.x, pTransform->position.y);
            if (isOutside)
            {
                pScene->RemoveEntity(entityId);
            }
        }
    }

    void ProjectileSystem::Render(Scene* pScene)
    {
    }

    void ProjectileSystem::End(Scene* pScene)
    {
    }

    void ProjectileSystem::Shutdown()
    {
    }
}
