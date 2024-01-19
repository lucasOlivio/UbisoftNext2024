#pragma once

#include "Engine/ECS/System/iSystem.h"
#include "Engine/Events/CollisionEvent.h"

namespace MyEngine
{
	// Draw collisions on collision event notification
	class DrawCollisionSystem : public iSystem
	{
	public:
		DrawCollisionSystem() = default;
		virtual ~DrawCollisionSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
