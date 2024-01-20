#include "stdafx.h"
#include "RenderSystem.h"
#include "Engine/ECS/SceneView.hpp"

#include <app.h>

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

            pSprite->sprite = App::CreateSprite(pSprite->name.c_str(), pSprite->cols, pSprite->rows);
            m_UpdateSprite(pSprite, pTransform);

            m_CreateAnimation(pSprite);

            pSprite->sprite->SetAnimation(0);
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

            m_UpdateSprite(pSprite, pTransform);

            pSprite->sprite->Update(deltaTime);
        }
    }

    void RenderSystem::Render(Scene* pScene)
    {
        for (Entity entityId : SceneView<TransformComponent, SpriteComponent>(*pScene))
        {
            SpriteComponent* pSprite = pScene->Get<SpriteComponent>(entityId);

            pSprite->sprite->Draw();
        }
    }

    void RenderSystem::End(Scene* pScene)
    {
        // Deletes sprite objects
        for (Entity entityId : SceneView<TransformComponent, SpriteComponent>(*pScene))
        {
            SpriteComponent* pSprite = pScene->Get<SpriteComponent>(entityId);

            delete pSprite->sprite;
        }
    }

    void RenderSystem::m_CreateAnimation(SpriteComponent* pSprite)
    {
        int frame = 0;
        for (int i = 0; i < pSprite->rows; i++)
        {
            std::vector<int> animationFrames;

            for (int j = 0; j < pSprite->cols; j++) {
                animationFrames.push_back(frame++);
            }

            pSprite->sprite->CreateAnimation(i, pSprite->speed, animationFrames);
        }
    }

    void RenderSystem::m_UpdateSprite(SpriteComponent* pSprite, TransformComponent* pTransform)
    {
        pSprite->sprite->SetPosition(pTransform->position.x, pTransform->position.y);
        pSprite->sprite->SetAngle(pTransform->angle);
        pSprite->sprite->SetScale(pTransform->scale);
    }

    void RenderSystem::Shutdown()
    {
    }
}
