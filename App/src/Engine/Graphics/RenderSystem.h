#pragma once

#include "Engine/Core/iSystem.h"
#include "Engine/ECS/Components.h"

namespace MyEngine
{
	// Takes care of managing the sprites and rendering them
	class RenderSystem : public iSystem
	{
	public:
		RenderSystem() = default;
		virtual ~RenderSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

	private:
		// Creates the animations and frames for the sprite based on the cols and rows given
		void m_CreateAnimation(SpriteComponent* pSprite);

		// Set transform values to sprite object
		void m_UpdateSprite(SpriteComponent* pSprite, TransformComponent* pTransform);
	};
}
