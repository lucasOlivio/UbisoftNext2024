#pragma once

#include "Engine/Core/iSystem.h"

#include "Engine/ECS/Components.h"

#include "Engine/Events/CollisionEvent.h"

namespace MyEngine
{
	// Handles the creation of all zombies and blood spawn on death
	class ZombieSpawnSystem : public iSystem
	{
	public:
		ZombieSpawnSystem() = default;
		virtual ~ZombieSpawnSystem() { };

		virtual std::string SystemName() { return "ZombieSpawnSystem"; };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

		void OnCollision(const CollisionEnterEvent& event);
	};
}
