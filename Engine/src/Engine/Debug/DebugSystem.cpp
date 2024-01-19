#include "pch.h"

#include "DebugSystem.h"
#include "Engine/ECS/SingletonComponents/DebugLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"
#include "Engine/Graphics/VAO/VAOManagerLocator.h"

namespace MyEngine
{
    void DebugSystem::Init()
    {
        ConfigPathComponent* pConfigPath = CoreLocator::GetConfigPath();
        iVAOManager* pVAOManager = VAOManagerLocator::Get();

        DebugSquareComponent* pSquare = DebugLocator::GetSquare();
        DebugSphereComponent* pSphere = DebugLocator::GetSphere();

        pSquare->pMesh = pVAOManager->LoadModelIntoVAO(pConfigPath->pathDebugSquare, true);
        pSphere->pMesh = pVAOManager->LoadModelIntoVAO(pConfigPath->pathDebugSphere, true);
    }

    void DebugSystem::Start(Scene* pScene)
    {
    }

    void DebugSystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void DebugSystem::Render(Scene* pScene)
    {
    }

    void DebugSystem::End(Scene* pScene)
    {
    }

    void DebugSystem::Shutdown()
    {
    }
}
