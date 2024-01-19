#pragma once

#include "Engine/ECS/System/iSystem.h"

#include "Engine/Events/InputEvent.h"

namespace MyEngine
{
	// When key "ENTER" is pressed alternate between scene 1 and 2
	class ChangeSceneSystem : public iSystem
	{
	public:
		ChangeSceneSystem() = default;
		virtual ~ChangeSceneSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

		static void InputTriggered(const KeyboardEvent& event);
	};
}
