#include "stdafx.h"

#include "GraphicsUtils.h"

#include <app.h>

namespace MyEngine
{
    void GraphicsUtils::UpdateAnimation(SpriteComponent* pSprite, TransformComponent* pTransform, const float& deltaTime)
    {
        pSprite->sprite->SetPosition(pTransform->worldPosition.x, pTransform->worldPosition.y);
        pSprite->sprite->SetAngle(pTransform->worldAngle);
        pSprite->sprite->SetScale(pTransform->worldScale);

        pSprite->sprite->Update(deltaTime);
    }

    void GraphicsUtils::CreateAnimation(SpriteComponent* pSprite)
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

    void GraphicsUtils::SetupSprite(SpriteComponent* pSprite, TransformComponent* pTransform)
    {
        /*iSpriteManager* pSpriteManager = SpriteManagerLocator::GetSpriteManager();
        pSprite->sprite = pSpriteManager->CreateSprite(pSprite->name.c_str(), pSprite->cols, pSprite->rows);*/
        pSprite->sprite = App::CreateSprite(pSprite->name.c_str(), pSprite->cols, pSprite->rows);
        UpdateAnimation(pSprite, pTransform, 0.1f);

        CreateAnimation(pSprite);

        pSprite->sprite->SetAnimation(0);

        return;
    }

    void GraphicsUtils::DrawSprite(SpriteComponent* pSprite)
    {
        if (pSprite->sprite)
        {
            pSprite->sprite->Draw();
        }
    }

    void GraphicsUtils::DrawRectangle(const Vec2& min, const Vec2& max, const float color[3])
    {
        App::DrawLine(min.x, min.y, max.x, min.y, color[0], color[1], color[2]);
        App::DrawLine(max.x, min.y, max.x, max.y, color[0], color[1], color[2]);
        App::DrawLine(max.x, max.y, min.x, max.y, color[0], color[1], color[2]);
        App::DrawLine(min.x, max.y, min.x, min.y, color[0], color[1], color[2]);
    }

    void GraphicsUtils::PrintBarWidget(const std::string& label, const int& size, 
                                       const float& x, const float& y, const float color[3])
    {
        float labelPadding = 75.0f;

        std::string progressBar = std::string(size, '|');

        // Print the label
        App::Print(x, y, label.c_str(), color[0], color[1], color[2]);

        // Print the progress bar
        App::Print(x + labelPadding, y, progressBar.c_str(), color[0], color[1], color[2]);
    }
}