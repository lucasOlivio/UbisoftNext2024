#include "stdafx.h"

#include "MediaPlayerSystem.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/Components.h"

#include <app.h>

namespace MyEngine
{
    void MediaPlayerSystem::Init()
    {
    }

    void MediaPlayerSystem::Start(Scene* pScene)
    {
    }

    void MediaPlayerSystem::Update(Scene* pScene, float deltaTime)
    {
        deltaTime = deltaTime / 1000.0f;

        for (Entity entityId : SceneView<SoundComponent>(*pScene))
        {
            SoundComponent* pSound = pScene->Get<SoundComponent>(entityId);

            if (pSound->currentProgress >= pSound->audioDuration && !pSound->isLoop)
            {
                pSound->currentProgress = 0.0f;
                pSound->isPlaying = false;
                continue;
            }

            if (pSound->isPlaying)
            {
                pSound->currentProgress += deltaTime;
                continue;
            }

            if (pSound->play)
            {
                App::PlaySoundW(pSound->name.c_str(), pSound->isLoop);
                pSound->isPlaying = true;
                pSound->currentProgress = 0.0f;
                pSound->play = false;
            }
        }
    }

    void MediaPlayerSystem::Render(Scene* pScene)
    {
    }

    void MediaPlayerSystem::End(Scene* pScene)
    {
    }

    void MediaPlayerSystem::Shutdown()
    {
    }
}
