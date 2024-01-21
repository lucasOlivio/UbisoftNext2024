#pragma once

#include "Engine/Core/iSystem.h"

#include "Engine/ECS/Components.h"

#include "Engine/Events/GameStateEvent.h"

namespace MyEngine
{
	// Adds and removes other systems based on game state
	class CoreSystem : public iSystem
	{
	public:
		CoreSystem() = default;
		virtual ~CoreSystem() { };

		virtual std::string SystemName() { return "CoreSystem"; };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

		static void OnStart(const GameStartedEvent& event);

		static void OnRunning(const GameRunningEvent& event);

		static void OnLevelUp(const GameLevelUpEvent& event);

		static void OnGameOver(const GameOverEvent& event);
	};
}
