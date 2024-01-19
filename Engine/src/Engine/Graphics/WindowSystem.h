#pragma once

#include "Engine/ECS/System/iSystem.h"

namespace MyEngine
{
	class WindowSystem : public iSystem
	{
	public:
		WindowSystem() = default;
		virtual ~WindowSystem() { };

		virtual void Init();

		// Initializes whole glfw and GLAD, this system should be the first in the list
		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
