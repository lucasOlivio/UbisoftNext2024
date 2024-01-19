#include "pch.h"

#include "DrawGridSystem.h"
#include "Engine/ECS/SingletonComponents/PhysicsLocator.h"
#include "Engine/ECS/SingletonComponents/DebugLocator.h"
#include "Engine/Utils/TransformUtils.h"
#include "Engine/Utils/GraphicsUtils.h"

namespace MyEngine
{
	void DrawGridSystem::Init()
	{
		// Just a check if the debug square mesh loaded
		DebugSquareComponent* pSquare = DebugLocator::GetSquare();

		sMesh* pMesh = pSquare->pMesh;
		if (!pMesh)
		{
			LOG_WARNING("Debug Square not loaded!");
			return;
		}
	}

	void DrawGridSystem::Start(Scene* pScene)
	{
	}

	void DrawGridSystem::Update(Scene* pScene, float deltaTime)
	{
	}

	void DrawGridSystem::Render(Scene* pScene)
	{
		GridBroadphaseComponent* pGrid = PhysicsLocator::GetGridBroadphase();
		DebugSquareComponent* pSquare = DebugLocator::GetSquare();

		sMesh* pMesh = pSquare->pMesh;

		if (!pMesh)
		{
			return;
		}

		// Draw a red wireframe square for every AABB in the grid
		for (std::pair<uint, GridAABB*> pairAABB : pGrid->mapAABBs)
		{
			GridAABB* pAABB = pairAABB.second;

			glm::mat4 matTransf = glm::mat4(1.0f);
			TransformUtils::GetTransform(pAABB->minXYZ, pGrid->lengthPerBox.x, matTransf);

			GraphicsUtils::DrawDebugModel(matTransf,
										  pMesh->VAO_ID,
										  pMesh->numberOfIndices,
										  RED);
		}
	}

	void DrawGridSystem::End(Scene* pScene)
	{
	}

	void DrawGridSystem::Shutdown()
	{
	}
}
