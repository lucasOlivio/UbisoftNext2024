#pragma once

#include "Engine/ECS/Components.h"
#include "Engine/ECS/Scene.h"

namespace MyEngine
{
	class GraphicsUtils
	{
	public:
		static void UpdateAnimation(SpriteComponent* pSprite, TransformComponent* pTransform, const float& deltaTime);

		// Creates the animations and frames for the sprite based on the cols and rows given
		static void CreateAnimation(SpriteComponent* pSprite);

		// Creates sprite using API and updates, setting up everything needed for the sprite
		static void SetupSprite(SpriteComponent* pSprite, TransformComponent* pTransform);

		static void DrawSprite(SpriteComponent* pSprite);

		static void DrawRectangle(const Vec2& min, const Vec2& max, const float color[3]);

		// Print out a horizontal bar with label
		static void PrintBarWidget(const std::string& label, const int& size, 
								   const float& x, const float& y, const float color[3]);
	};
}
