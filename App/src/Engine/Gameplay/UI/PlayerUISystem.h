#pragma once

#include "Engine/Core/iSystem.h"

#include "Engine/ECS/Components.h"

namespace MyEngine
{
	// Render player stats
	class PlayerUISystem : public iSystem
	{
	public:
		PlayerUISystem() = default;
		virtual ~PlayerUISystem() { };

		virtual std::string SystemName() { return "PlayerUISystem"; };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
