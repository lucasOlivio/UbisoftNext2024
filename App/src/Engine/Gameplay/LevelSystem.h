#pragma once

#include "Engine/Core/iSystem.h"

#include "Engine/Events/GameStateEvent.h"

namespace MyEngine
{
	// Handles how the levels will run and start
	class LevelSystem : public iSystem
	{
	public:
		LevelSystem() = default;
		virtual ~LevelSystem() { };

		virtual std::string SystemName() { return "LevelSystem"; };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

		static void OnLevelUp(const GameLevelUpEvent& event);

		static void OnGameOver(const GameOverEvent& event);
	};
}
