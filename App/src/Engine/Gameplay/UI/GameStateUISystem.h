#pragma once

#include "Engine/Core/iSystem.h"

namespace MyEngine
{
	// Render UI state changes to keep player informed
	class GameStateUISystem : public iSystem
	{
	public:
		GameStateUISystem() = default;
		virtual ~GameStateUISystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
