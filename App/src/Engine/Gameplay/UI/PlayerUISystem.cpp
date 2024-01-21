#include "stdafx.h"

#include "PlayerUISystem.h"

#include "Engine/ECS/SceneView.hpp"

#include "Engine/Utils/GameplayUtils.h"
#include "Engine/Utils/GraphicsUtils.h"

#include <app.h>

namespace MyEngine
{
    const Vec2 START_RECT_UI = Vec2(55.0f, 635.0f);
    const Vec2 END_RECT_UI = Vec2(975.0f, 725.0f);

    const float HEALTH_X = 75.0f;
    const float HEALTH_Y = 700.0f;

    const float AMMO_X = 75.0f;
    const float AMMO_Y = 675.0f;

    const float SCORE_X = 75.0f;
    const float SCORE_Y = 650.0f;

    void PlayerUISystem::Init()
    {
    }

    void PlayerUISystem::Start(Scene* pScene)
    {
    }

    void PlayerUISystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void PlayerUISystem::Render(Scene* pScene)
    {
        Entity playerId = GameplayUtils::GetPlayerId(pScene);
        PlayerComponent* pPlayer = pScene->Get<PlayerComponent>(playerId);

        GraphicsUtils::DrawRectangle(START_RECT_UI, END_RECT_UI, CYAN);

        GraphicsUtils::PrintBarWidget("Health", pPlayer->health, HEALTH_X, HEALTH_Y, GREEN);
        GraphicsUtils::PrintBarWidget("Ammo  ", pPlayer->currentAmmo, AMMO_X, AMMO_Y, RED);

        std::string scoreText = "Score " + std::to_string(pPlayer->score);
        App::Print(SCORE_X, SCORE_Y, scoreText.c_str(), BLUE[0], BLUE[1], BLUE[2]);
    }

    void PlayerUISystem::End(Scene* pScene)
    {
    }

    void PlayerUISystem::Shutdown()
    {
    }
}
