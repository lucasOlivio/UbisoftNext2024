#pragma once

#include "Engine/Gameplay/GameplayProperties.h"

#include "Engine/Core/iSystem.h"

namespace MyEngine
{
	// Triggers state changes events when state component changes
	class StateSystem : public iSystem
	{
	public:
		StateSystem() = default;
		virtual ~StateSystem() { };

		virtual std::string SystemName() { return "StateSystem"; };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

	private:
		static void m_TriggerStateChange(Scene* pScene, const eGameStates& newState);
	};
}
