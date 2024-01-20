#include "stdafx.h"

#include "ZombieBrainSystem.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/Components.h"

#include <app.h>

namespace MyEngine
{
    void ZombieBrainSystem::Init()
    {
    }

    void ZombieBrainSystem::Start(Scene* pScene)
    {
    }

    void ZombieBrainSystem::Update(Scene* pScene, float deltaTime)
    {
        deltaTime = deltaTime / 1000.0f;

    }

    void ZombieBrainSystem::Render(Scene* pScene)
    {
    }

    void ZombieBrainSystem::End(Scene* pScene)
    {
    }

    void ZombieBrainSystem::Shutdown()
    {
    }
}
