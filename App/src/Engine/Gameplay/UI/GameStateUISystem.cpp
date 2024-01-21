#include "stdafx.h"

#include "GameStateUISystem.h"

#include "Engine/ECS/SingletonComponents/GameplayLocator.h"

#include <app.h>

namespace MyEngine
{
    float const STARTGAME_X = 375.0f;
    float const STARTGAME_Y = 450.0f;
    const char* STARTGAME_TXT = "Press E to start the game...";

    float const GAMEOVER_X = 475.0f;
    float const GAMEOVER_Y = 500.0f;
    const char* GAMEOVER_TXT = "GAME OVER";

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
            App::Print(STARTGAME_X, STARTGAME_Y, STARTGAME_TXT,
                       BLUE[0], BLUE[1], BLUE[2]);
        }
        else if (pState->currState == eGameStates::GAMEOVER)
        {
            App::Print(GAMEOVER_X, GAMEOVER_Y, GAMEOVER_TXT,
                       RED[0], RED[1], RED[2]);
            App::Print(STARTGAME_X, STARTGAME_Y, STARTGAME_TXT,
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
