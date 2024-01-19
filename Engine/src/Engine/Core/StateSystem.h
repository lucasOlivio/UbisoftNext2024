#pragma once

#include "Engine/Core/StateProperties.h"

#include "Engine/ECS/System/iSystem.h"

namespace MyEngine
{
	// Triggers state changes events when state component changes
	class StateSystem : public iSystem
	{
	public:
		StateSystem() = default;
		virtual ~StateSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

	private:
		static void m_TriggerStateChange(const eStates& newState);
	};
}
