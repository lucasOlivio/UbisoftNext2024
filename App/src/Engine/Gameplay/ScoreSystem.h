#pragma once

#include "Engine/Core/iSystem.h"

#include "Engine/ECS/Components.h"

#include "Engine/Events/CollisionEvent.h"

namespace MyEngine
{
	// Awards the player for every zombie killed or item picked
	class ScoreSystem : public iSystem
	{
	public:
		ScoreSystem() = default;
		virtual ~ScoreSystem() { };

		virtual std::string SystemName() { return "ScoreSystem"; };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

		static void OnCollision(const CollisionEnterEvent& event);
	};
}
