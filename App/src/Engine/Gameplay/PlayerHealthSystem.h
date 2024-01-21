#pragma once

#include "Engine/Core/iSystem.h"

#include "Engine/ECS/Components.h"

#include "Engine/Events/CollisionEvent.h"

namespace MyEngine
{
	// Manage player health on collisions and trigger game state to gameover on health 0
	class PlayerHealthSystem : public iSystem
	{
	public:
		PlayerHealthSystem() = default;
		virtual ~PlayerHealthSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

		static void OnCollision(const CollisionEnterEvent& event);
	};
}
