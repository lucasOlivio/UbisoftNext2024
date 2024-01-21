#include "stdafx.h"

#include "RenderSystem.h"

#include "Engine/Graphics/SpriteManager/SpriteManagerLocator.h"

#include "Engine/ECS/SceneView.hpp"

#include "Engine/Utils/GraphicsUtils.h"

namespace MyEngine
{
    void RenderSystem::Init()
    {
    }

    void RenderSystem::Start(Scene* pScene)
    {
        // Create sprites objects
        for (Entity entityId : SceneView<TransformComponent, SpriteComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            SpriteComponent* pSprite = pScene->Get<SpriteComponent>(entityId);

            GraphicsUtils::SetupSprite(pSprite, pTransform);
        }
        return;
    }

    void RenderSystem::Update(Scene* pScene, float deltaTime)
    {
        // Update transform and deltatime for each sprite
        for (Entity entityId : SceneView<TransformComponent, SpriteComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            SpriteComponent* pSprite = pScene->Get<SpriteComponent>(entityId);

            GraphicsUtils::UpdateAnimation(pSprite, pTransform, deltaTime);
        }
    }

    void RenderSystem::Render(Scene* pScene)
    {
        for (Entity entityId : SceneView<SpriteComponent>(*pScene))
        {
            SpriteComponent* pSprite = pScene->Get<SpriteComponent>(entityId);

            GraphicsUtils::DrawSprite(pSprite);
        }
    }

    void RenderSystem::End(Scene* pScene)
    {
    }

    void RenderSystem::Shutdown()
    {
    }
}
