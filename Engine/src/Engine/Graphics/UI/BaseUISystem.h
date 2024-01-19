#pragma once

#include "Engine/ECS/System/iSystem.h"

namespace MyEngine
{
	// Manages imgui initialization and shutdown
	class BaseUISystem : public iSystem
	{
	public:
		BaseUISystem() = default;
		virtual ~BaseUISystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
