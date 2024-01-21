#include "stdafx.h"

#include "GameStateUISystem.h"

#include "Engine/ECS/SingletonComponents/GameplayLocator.h"

#include <app.h>

namespace MyEngine
{
    float const STARTGAME_X = 375.0f;
    float const STARTGAME_Y = 450.0f;

    float const GAMEOVER_X = 475.0f;
    float const GAMEOVER_Y = 450.0f;

    void GameStateUISystem::Init()
    {
    }

    void GameStateUISystem::Start(Scene* pScene)
    {
    }

    void GameStateUISystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void GameStateUISystem::Render(Scene* pScene)
    {
        GameStateComponent* pState = GameplayLocator::GetGameState();
        if (pState->currState == eGameStates::STARTED)
        {
            App::Print(STARTGAME_X, STARTGAME_Y, "Press any key to start the game...", 
                       BLUE[0], BLUE[1], BLUE[2]);
        }
        else if (pState->currState == eGameStates::GAMEOVER)
        {
            App::Print(GAMEOVER_X, GAMEOVER_Y, "GAME OVER",
                       RED[0], RED[1], RED[2]);
        }
    }

    void GameStateUISystem::End(Scene* pScene)
    {
    }

    void GameStateUISystem::Shutdown()
    {
    }
}
