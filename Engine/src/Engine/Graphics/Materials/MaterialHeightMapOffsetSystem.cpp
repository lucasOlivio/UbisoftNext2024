#include "pch.h"

#include "MaterialHeightMapOffsetSystem.h"
#include "Engine/ECS/Scene/SceneView.hpp"
#include "Engine/ECS/Components.h"

namespace MyEngine
{
	void MaterialHeightMapOffsetSystem::Start(Scene* pScene)
	{
	}

	void MaterialHeightMapOffsetSystem::Update(Scene* pScene, float deltaTime)
	{
		// Increase offset for all materials
		for (Entity entityId : SceneView<MaterialComponent>(*pScene))
		{
			MaterialComponent* pMaterial = pScene->Get<MaterialComponent>(entityId);

			if (pMaterial->offsetHeightMap == glm::vec3(0))
			{
				return;
			}

			pMaterial->currOffsetHeightMap += pMaterial->offsetHeightMap * deltaTime;

			// Clamp offset between 0 and 1
			if (pMaterial->currOffsetHeightMap.x > 1)
			{
				pMaterial->currOffsetHeightMap.x = 0;
			}
			if (pMaterial->currOffsetHeightMap.y > 1)
			{
				pMaterial->currOffsetHeightMap.y = 0;
			}
		}
	}

	void MaterialHeightMapOffsetSystem::Render(Scene* pScene)
	{
	}

	void MaterialHeightMapOffsetSystem::End(Scene* pScene)
	{
	}
}
