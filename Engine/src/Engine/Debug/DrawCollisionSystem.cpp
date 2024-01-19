#include "pch.h"

#include "DrawCollisionSystem.h"

#include "Engine/ECS/SingletonComponents/DebugLocator.h"
#include "Engine/ECS/SingletonComponents/PhysicsLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Utils/GraphicsUtils.h"

namespace MyEngine
{
	void DrawCollisionSystem::Init()
	{
	}

	void DrawCollisionSystem::Start(Scene* pScene)
	{
	}

	void DrawCollisionSystem::Update(Scene* pScene, float deltaTime)
	{
	}

	void DrawCollisionSystem::Render(Scene* pScene)
	{
		FrameCounterComponent* pFrames = CoreLocator::GetFrameCounter();
		FrameCollisionComponent* pFrameColl = PhysicsLocator::GetFrameCollision();
		DebugSphereComponent* pSphere = DebugLocator::GetSphere();
		sMesh* pMesh = pSphere->pMesh;

		int currFrame = pFrames->frameCount % FRAME_RATE;
		const std::vector<sCollisionData>& currFrameColls = pFrameColl->collisions[currFrame];
		// Draw a wireframe blue sphere at the contact points
		for (const sCollisionData& coll : currFrameColls)
		{
			glm::mat4 matTransf = glm::mat4(1.0f);
			TransformUtils::GetTransform(coll.contactPoint, 1.0f, matTransf);

			GraphicsUtils::DrawDebugModel(matTransf,
										  pMesh->VAO_ID,
										  pMesh->numberOfIndices,
										  BLUE);
		}
	}

	void DrawCollisionSystem::End(Scene* pScene)
	{
	}

	void DrawCollisionSystem::Shutdown()
	{
	}
}
