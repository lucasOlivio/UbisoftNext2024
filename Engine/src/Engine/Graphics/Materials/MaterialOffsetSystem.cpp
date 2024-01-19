#include "pch.h"

#include "MaterialOffsetSystem.h"
#include "Engine/ECS/Scene/SceneView.hpp"
#include "Engine/ECS/Components.h"

namespace MyEngine
{
	void MaterialOffsetSystem::Init()
	{
	}

	void MaterialOffsetSystem::Start(Scene* pScene)
	{
	}

	void MaterialOffsetSystem::Update(Scene* pScene, float deltaTime)
	{
		// Increase offset for all materials
		for (Entity entityId : SceneView<MaterialComponent>(*pScene))
		{
			MaterialComponent* pMaterial = pScene->Get<MaterialComponent>(entityId);

			pMaterial->currOffset += pMaterial->offsetMove * deltaTime;

			float resetValue = 1.0;
			if (pMaterial->useCubeTexture)
			{
				resetValue = 2.0;
			}
			// Clamp offset between 0 and 1
			if (pMaterial->currOffset.x > 1)
			{
				pMaterial->currOffset.x = 0;
			}
			if (pMaterial->currOffset.y > 1)
			{
				pMaterial->currOffset.y = 0;
			}
		}
	}

	void MaterialOffsetSystem::Render(Scene* pScene)
	{
	}

	void MaterialOffsetSystem::End(Scene* pScene)
	{
	}

	void MaterialOffsetSystem::Shutdown()
	{
	}
}