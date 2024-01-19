#include "pch.h"

#include "GravitySystem.h"

#include "Engine/ECS/Scene/SceneView.hpp"
#include "Engine/ECS/Components.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

namespace MyEngine
{
    void GravitySystem::Init()
    {
    }

    void GravitySystem::Start(Scene* pScene)
    {
    }

    void GravitySystem::Update(Scene* pScene, float deltaTime)
    {
        StateComponent* pState = CoreLocator::GetState();
        if (pState->currState == eStates::SIMULATION_STOPPED)
        {
            return;
        }

        // Update velocity and position
        for (Entity entityId : SceneView<MovementComponent, GravityComponent>(*pScene))
        {
            MovementComponent* pMovement = pScene->Get<MovementComponent>(entityId);
            GravityComponent* pGravity = pScene->Get<GravityComponent>(entityId);

            pMovement->velocity = pMovement->velocity + (pGravity->acceleration * deltaTime);
        }
    }

    void GravitySystem::Render(Scene* pScene)
    {
    }

    void GravitySystem::End(Scene* pScene)
    {
    }

    void GravitySystem::Shutdown()
    {
    }
}
