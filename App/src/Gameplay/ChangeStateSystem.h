#pragma once

#include "Engine/ECS/System/iSystem.h"

#include "Engine/Events/InputEvent.h"

namespace MyEngine
{
	// When key "SPACE" is pressed changes simulation state
	class ChangeStateSystem : public iSystem
	{
	public:
		ChangeStateSystem() = default;
		virtual ~ChangeStateSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

		static void InputTriggered(const KeyboardEvent& event);
	};
}
