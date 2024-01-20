#pragma once

#include "Engine/ECS/Components.h"
#include "Engine/ECS/Scene.h"

namespace MyEngine
{
	class GraphicsUtils
	{
	public:
		static void UpdateAnimation(SpriteComponent* pSprite, TransformComponent* pTransform, float deltaTime);

		// Creates the animations and frames for the sprite based on the cols and rows given
		static void CreateAnimation(SpriteComponent* pSprite);

		static void SetupSprite(SpriteComponent* pSprite, TransformComponent* pTransform);
	};
}
