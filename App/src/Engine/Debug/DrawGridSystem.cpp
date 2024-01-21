#include "stdafx.h"

#include "DrawGridSystem.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/Components.h"
#include "Engine/ECS/SingletonComponents/PhysicsLocator.h"

#include "Engine/Utils/GraphicsUtils.h"

namespace MyEngine
{
    void DrawGridSystem::Init()
    {
    }

    void DrawGridSystem::Start(Scene* pScene)
    {
    }

    void DrawGridSystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void DrawGridSystem::Render(Scene* pScene)
    {
        GridBroadphaseComponent* pGridComp = PhysicsLocator::GetGridBroadphase();
        for (std::pair< uint, GridAABB*> pairGrid : pGridComp->mapAABBs)
        {
            GridAABB* pGrid = pairGrid.second;
            GraphicsUtils::DrawRectangle(pGrid->minXY, pGrid->maxXY, RED);
        }
    }

    void DrawGridSystem::End(Scene* pScene)
    {
    }

    void DrawGridSystem::Shutdown()
    {
    }
}
