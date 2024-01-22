#pragma once

#include "Engine/Core/iSystem.h"

#include "Engine/ECS/Components.h"

#include "Engine/Events/CollisionEvent.h"

namespace MyEngine
{
	// Handles items interactions with player
	class ItemSystem : public iSystem
	{
	public:
		ItemSystem() = default;
		virtual ~ItemSystem() { };

		virtual std::string SystemName() { return "ItemSystem"; };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

		static void OnCollision(const CollisionEnterEvent& event);
	};
}
