#pragma once

#include "Engine/Core/iSystem.h"

#include "Engine/ECS/Components.h"

namespace MyEngine
{
	// Behavior of the zombies (they basically just follow the player)
	class ZombieBrainSystem : public iSystem
	{
	public:
		ZombieBrainSystem() = default;
		virtual ~ZombieBrainSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
