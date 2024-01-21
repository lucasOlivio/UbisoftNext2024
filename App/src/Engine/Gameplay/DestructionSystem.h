#pragma once

#include "Engine/Core/iSystem.h"

#include "Engine/ECS/Components.h"

#include "Engine/Events/CollisionEvent.h"

namespace MyEngine
{
	// Handles destruction of all objects that collide or bullets that get out of window
	class DestructionSystem : public iSystem
	{
	public:
		DestructionSystem() = default;
		virtual ~DestructionSystem() { };

		virtual std::string SystemName() { return "DestructionSystem"; };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

		static void OnCollision(const CollisionEnterEvent& event);
	};
}
